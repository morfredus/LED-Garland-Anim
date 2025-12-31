/**
 * @file telegram_control.cpp
 * @brief Module de contrôle Telegram (fonctionnalité à venir)
 * @version 1.5.3
 * @date 2025-12-30
 */

#include "telegram_control.h"

#include <HTTPClient.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>
#include <cstdlib>

#include "config.h"
#include "secrets.h"
#include "garland_control.h"
#include "display.h"

static WiFiClientSecure telegramClient;
static String telegramBaseUrl = String("https://api.telegram.org/bot") + TELEGRAM_BOT_TOKEN;
static long lastUpdateId = 0;
static unsigned long lastPollMillis = 0;
static constexpr unsigned long TELEGRAM_POLL_INTERVAL_MS = 2000;
static constexpr size_t TELEGRAM_JSON_BUFFER = 4096;
static int64_t allowedChatId = 0;

struct AnimMapEntry {
    const char* key;
    GarlandAnimation value;
};

struct ModeMapEntry {
    const char* key;
    GarlandMode value;
};

static const AnimMapEntry ANIM_MAP[] = {
    {"off", ANIM_OFF},
    {"eteint", ANIM_OFF},
    {"fade", ANIM_FADE_ALTERNATE},
    {"blink", ANIM_BLINK_ALTERNATE},
    {"clignotement", ANIM_BLINK_ALTERNATE},
    {"pulse", ANIM_PULSE},
    {"pulsation", ANIM_PULSE},
    {"breath", ANIM_BREATHING},
    {"respiration", ANIM_BREATHING},
    {"auto", ANIM_AUTO}
};

static const ModeMapEntry MODE_MAP[] = {
    {"permanent", MODE_PERMANENT},
    {"auto", MODE_PERMANENT},
    {"detect", MODE_MOTION_TRIGGER},
    {"pir", MODE_MOTION_TRIGGER},
    {"motion", MODE_MOTION_TRIGGER}
};

static int64_t parseChatId(const char* chatIdStr) {
    return strtoll(chatIdStr, nullptr, 10);
}

static String toLowerTrim(const String& value) {
    String out = value;
    out.trim();
    out.toLowerCase();
    return out;
}

static bool tryParseAnimation(const String& token, GarlandAnimation& outAnim) {
    if (token.length() == 0) {
        return false;
    }

    bool isNumber = true;
    for (size_t i = 0; i < token.length(); i++) {
        if (!isDigit(token[i]) && !(i == 0 && (token[i] == '-' || token[i] == '+'))) {
            isNumber = false;
            break;
        }
    }

    if (isNumber) {
        int value = token.toInt();
        if (value >= 0 && value < ANIM_COUNT) {
            outAnim = static_cast<GarlandAnimation>(value);
            return true;
        }
    }

    String lower = toLowerTrim(token);
    for (const auto& entry : ANIM_MAP) {
        if (lower == entry.key) {
            outAnim = entry.value;
            return true;
        }
    }
    return false;
}

static bool tryParseMode(const String& token, GarlandMode& outMode) {
    if (token.length() == 0) {
        return false;
    }

    bool isNumber = true;
    for (size_t i = 0; i < token.length(); i++) {
        if (!isDigit(token[i]) && !(i == 0 && (token[i] == '-' || token[i] == '+'))) {
            isNumber = false;
            break;
        }
    }

    if (isNumber) {
        int value = token.toInt();
        if (value >= 0 && value < MODE_COUNT) {
            outMode = static_cast<GarlandMode>(value);
            return true;
        }
    }

    String lower = toLowerTrim(token);
    for (const auto& entry : MODE_MAP) {
        if (lower == entry.key) {
            outMode = entry.value;
            return true;
        }
    }
    return false;
}

static void sendTelegramMessage(const String& text) {
    if (WiFi.status() != WL_CONNECTED) {
        return;
    }

    HTTPClient https;
    String url = telegramBaseUrl + "/sendMessage";
    String sanitized = text;
    sanitized.replace("\\", "\\\\");
    sanitized.replace("\"", "\\\"");
    sanitized.replace("\n", "\\n");
    sanitized.replace("\r", "");
    String payload = String("{\"chat_id\":\"") + TELEGRAM_CHAT_ID + "\",\"text\":\"" + sanitized + "\"}";

    if (https.begin(telegramClient, url)) {
        https.addHeader("Content-Type", "application/json");
        int httpCode = https.POST(payload);
        if (httpCode != HTTP_CODE_OK) {
            LOG_PRINTF("Telegram sendMessage failed: %d\n", httpCode);
        }
        https.end();
    }
}

static void applyAnimationCommand(const String& arg) {
    GarlandAnimation anim;
    if (tryParseAnimation(arg, anim)) {
        setGarlandAnimation(anim);
        displayMainScreen(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName());
        sendTelegramMessage(String("Animation -> ") + getGarlandAnimationName());
    } else {
        sendTelegramMessage("Animation inconnue. Exemple: /anim 3 ou /anim auto");
    }
}

static void applyModeCommand(const String& arg) {
    GarlandMode mode;
    if (tryParseMode(arg, mode)) {
        setGarlandMode(mode);
        displayMainScreen(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName());
        sendTelegramMessage(String("Mode -> ") + getGarlandModeName());
    } else {
        sendTelegramMessage("Mode inconnu. Exemple: /mode 1 ou /mode detect");
    }
}

static void sendList() {
    String msg = "Modes:\n";
    for (int i = 0; i < MODE_COUNT; i++) {
        msg += String(i) + ": " + getGarlandModeNameById(i) + "\n";
    }

    msg += "\nAnimations:\n";
    for (int i = 0; i < ANIM_COUNT; i++) {
        msg += String(i) + ": " + getGarlandAnimationNameById(i) + "\n";
    }

    sendTelegramMessage(msg);
}

static void processCommand(const String& text) {
    String lower = toLowerTrim(text);

    if (lower.startsWith("/anim")) {
        int spaceIdx = text.indexOf(' ');
        String arg = (spaceIdx > 0) ? text.substring(spaceIdx + 1) : "";
        applyAnimationCommand(arg);
        return;
    }

    if (lower.startsWith("/mode")) {
        int spaceIdx = text.indexOf(' ');
        String arg = (spaceIdx > 0) ? text.substring(spaceIdx + 1) : "";
        applyModeCommand(arg);
        return;
    }

    if (lower.startsWith("/nextanim")) {
        nextGarlandAnimation();
        displayMainScreen(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName());
        sendTelegramMessage(String("Animation -> ") + getGarlandAnimationName());
        return;
    }

    if (lower.startsWith("/nextmode")) {
        nextGarlandMode();
        displayMainScreen(WiFi.SSID().c_str(), WiFi.localIP(), getGarlandModeName(), getGarlandAnimationName());
        sendTelegramMessage(String("Mode -> ") + getGarlandModeName());
        return;
    }

    if (lower.startsWith("/status")) {
        String status = String("Anim: ") + getGarlandAnimationName() + " (" + (int)getGarlandAnimation() + ")";
        status += "\nMode: " + String(getGarlandModeName()) + " (" + (int)getGarlandMode() + ")";
        status += String("\nWiFi: ") + (WiFi.isConnected() ? WiFi.localIP().toString() : "offline");
        sendTelegramMessage(status);
        return;
    }

    if (lower.startsWith("/liste")) {
        sendList();
        return;
    }

    sendTelegramMessage("Commandes: /anim <id|nom>, /nextanim, /mode <id|nom>, /nextmode, /status");
}

static void handleUpdates(JsonArray updates) {
    for (JsonObject update : updates) {
        long updateId = update["update_id"] | 0;
        if (updateId > lastUpdateId) {
            lastUpdateId = updateId;
        }

        JsonObject message = update["message"];
        if (message.isNull()) {
            continue;
        }

        int64_t chatId = message["chat"]["id"] | 0;
        String text = message["text"] | "";

        if (chatId != allowedChatId) {
            LOG_PRINTF("Telegram message ignoré (chat %lld)\n", static_cast<long long>(chatId));
            continue;
        }

        if (text.length() > 0) {
            processCommand(text);
        }
    }
}

void setupTelegramBot() {
    allowedChatId = parseChatId(TELEGRAM_CHAT_ID);
    telegramClient.setInsecure();
    LOG_PRINTLN("Telegram bot prêt (polling)");
}

void sendTelegramStatus(const char* ssid, IPAddress ip) {
    String status = String("WiFi: ") + ssid + "\nIP: " + ip.toString();
    status += "\nAnim: " + String(getGarlandAnimationName()) + " (" + (int)getGarlandAnimation() + ")";
    status += "\nMode: " + String(getGarlandModeName()) + " (" + (int)getGarlandMode() + ")";
    sendTelegramMessage(status);
}

void handleTelegramBot() {
    if (WiFi.status() != WL_CONNECTED) {
        return;
    }

    unsigned long now = millis();
    if (now - lastPollMillis < TELEGRAM_POLL_INTERVAL_MS) {
        return;
    }
    lastPollMillis = now;

    String url = telegramBaseUrl + "/getUpdates?offset=" + String(lastUpdateId + 1);

    HTTPClient https;
    if (!https.begin(telegramClient, url)) {
        return;
    }

    int httpCode = https.GET();
    if (httpCode != HTTP_CODE_OK) {
        LOG_PRINTF("Telegram getUpdates failed: %d\n", httpCode);
        https.end();
        return;
    }

    String payload = https.getString();
    https.end();

    JsonDocument doc;
    DeserializationError err = deserializeJson(doc, payload);
    if (err) {
        LOG_PRINTF("Telegram JSON parse error: %s\n", err.f_str());
        return;
    }

    if (!doc["ok"].as<bool>()) {
        LOG_PRINTLN("Telegram API returned not ok");
        return;
    }

    JsonArray result = doc["result"].as<JsonArray>();
    if (!result.isNull()) {
        handleUpdates(result);
    }
}
