/**
 * @file matrix8x8_control.cpp
 * @brief Implementation of 8x8 NeoPixel matrix control with festive animations
 * @version 1.6.0
 * @date 2026-01-01
 */

#include "matrix8x8_control.h"

// =============================================================================
// GLOBAL VARIABLES
// =============================================================================

static Adafruit_NeoPixel matrix = Adafruit_NeoPixel(MATRIX8X8_NUMPIXELS, MATRIX8X8_PIN, NEO_GRB + NEO_KHZ800);

static Matrix8x8Animation currentAnimation = MATRIX_ANIM_STAR;  // Start with star animation
static unsigned long animationStartTime = 0;
static uint8_t matrixBrightness = 128;  // Default brightness (50%)
static bool matrixEnabled = true;

// Animation state variables
static uint8_t animationPhase = 0;
static int8_t animationPosition = 0;
static uint8_t animationCounter = 0;

// =============================================================================
// ANIMATION NAMES
// =============================================================================

static const char* animationNames[] = {
    "Off",
    "Star",
    "Meteor",
    "Shooting Star",
    "Santa",
    "Tree",
    "Bell",
    "Snow",
    "Gift",
    "Candle",
    "Snowflake"
};

// =============================================================================
// UTILITY FUNCTIONS
// =============================================================================

/**
 * @brief Convert X,Y coordinates to pixel index
 * @param x X coordinate (0-7)
 * @param y Y coordinate (0-7)
 * @return Pixel index for NeoPixel array
 *
 * Assumes zigzag wiring pattern:
 * Row 0: 0->7 (left to right)
 * Row 1: 15->8 (right to left)
 * Row 2: 16->23 (left to right)
 * etc.
 */
static uint16_t xy(uint8_t x, uint8_t y) {
    if (x >= 8 || y >= 8) return 0;

    uint16_t index;
    if (y % 2 == 0) {
        // Even rows: left to right
        index = y * 8 + x;
    } else {
        // Odd rows: right to left
        index = y * 8 + (7 - x);
    }
    return index;
}

/**
 * @brief Set a pixel at X,Y coordinates
 */
static void setPixel(uint8_t x, uint8_t y, uint32_t color) {
    if (x < 8 && y < 8) {
        matrix.setPixelColor(xy(x, y), color);
    }
}

/**
 * @brief Get a pixel color at X,Y coordinates
 */
static uint32_t getPixel(uint8_t x, uint8_t y) {
    if (x < 8 && y < 8) {
        return matrix.getPixelColor(xy(x, y));
    }
    return 0;
}

/**
 * @brief Clear all pixels
 */
static void clearMatrix() {
    matrix.clear();
}

/**
 * @brief Dim a color by a factor
 */
static uint32_t dimColor(uint32_t color, uint8_t factor) {
    uint8_t r = (color >> 16) & 0xFF;
    uint8_t g = (color >> 8) & 0xFF;
    uint8_t b = color & 0xFF;

    r = (r * factor) / 255;
    g = (g * factor) / 255;
    b = (b * factor) / 255;

    return matrix.Color(r, g, b);
}

// =============================================================================
// ANIMATION PATTERNS (8x8 bitmaps)
// =============================================================================

// Star pattern (8x8)
static const uint8_t STAR_PATTERN[] = {
    0b00011000,
    0b00011000,
    0b11111111,
    0b01111110,
    0b00111100,
    0b01011010,
    0b10000001,
    0b00000000
};

// Christmas tree pattern
static const uint8_t TREE_PATTERN[] = {
    0b00011000,
    0b00111100,
    0b01111110,
    0b00111100,
    0b01111110,
    0b11111111,
    0b00011000,
    0b00111100
};

// Santa face pattern
static const uint8_t SANTA_PATTERN[] = {
    0b11111111,
    0b01111110,
    0b01011010,
    0b01111110,
    0b00111100,
    0b00111100,
    0b01111110,
    0b11111111
};

// Bell pattern
static const uint8_t BELL_PATTERN[] = {
    0b00011000,
    0b00111100,
    0b01111110,
    0b01111110,
    0b01111110,
    0b11111111,
    0b00011000,
    0b00000000
};

// Gift box pattern
static const uint8_t GIFT_PATTERN[] = {
    0b00111100,
    0b00111100,
    0b11111111,
    0b11111111,
    0b11010111,
    0b11010111,
    0b11111111,
    0b11111111
};

// Snowflake pattern
static const uint8_t SNOWFLAKE_PATTERN[] = {
    0b10011001,
    0b01011010,
    0b00111100,
    0b11111111,
    0b11111111,
    0b00111100,
    0b01011010,
    0b10011001
};

/**
 * @brief Draw a pattern from PROGMEM
 */
static void drawPattern(const uint8_t* pattern, uint32_t color) {
    for (uint8_t y = 0; y < 8; y++) {
        uint8_t row = pattern[y];
        for (uint8_t x = 0; x < 8; x++) {
            if (row & (1 << (7 - x))) {
                setPixel(x, y, color);
            }
        }
    }
}

// =============================================================================
// ANIMATIONS
// =============================================================================

/**
 * @brief Animation: Twinkling Star (startup animation)
 */
static void animateStar() {
    unsigned long elapsed = millis() - animationStartTime;
    float phase = (elapsed % 2000) / 2000.0;

    // Pulsating brightness
    uint8_t brightness = (uint8_t)((sin(phase * 2.0 * PI) + 1.0) * 127.5);

    clearMatrix();

    // Draw star with pulsating yellow color
    uint32_t color = matrix.Color(brightness, brightness, brightness / 4);
    drawPattern(STAR_PATTERN, color);

    // Add random twinkles
    if (random(0, 10) > 7) {
        uint8_t x = random(0, 8);
        uint8_t y = random(0, 8);
        setPixel(x, y, matrix.Color(255, 255, 200));
    }

    matrix.show();
}

/**
 * @brief Animation: Meteor shower
 */
static void animateMeteor() {
    unsigned long elapsed = millis() - animationStartTime;

    // Move every 100ms
    if (elapsed % 100 == 0) {
        // Fade all pixels
        for (uint8_t i = 0; i < 64; i++) {
            uint32_t color = matrix.getPixelColor(i);
            matrix.setPixelColor(i, dimColor(color, 180));
        }

        // Add new meteor at random position
        if (random(0, 100) > 70) {
            uint8_t x = random(0, 8);
            setPixel(x, 0, matrix.Color(255, 255, 200));
        }

        // Move meteors down
        for (int8_t y = 7; y > 0; y--) {
            for (uint8_t x = 0; x < 8; x++) {
                uint32_t color = getPixel(x, y - 1);
                setPixel(x, y, color);
            }
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Shooting star
 */
static void animateShootingStar() {
    unsigned long elapsed = millis() - animationStartTime;

    if (elapsed % 50 == 0) {
        clearMatrix();

        // Calculate diagonal position
        int8_t pos = (elapsed / 50) % 16;

        // Draw shooting star trail
        for (int8_t i = 0; i < 4; i++) {
            int8_t x = pos - i;
            int8_t y = pos - i;
            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                uint8_t brightness = 255 - (i * 60);
                setPixel(x, y, matrix.Color(brightness, brightness, brightness));
            }
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Santa face
 */
static void animateSanta() {
    unsigned long elapsed = millis() - animationStartTime;
    float phase = (elapsed % 2000) / 2000.0;

    clearMatrix();

    // Pulsating red color for Santa
    uint8_t brightness = (uint8_t)((sin(phase * 2.0 * PI) + 1.0) * 100 + 55);
    uint32_t color = matrix.Color(brightness, 0, 0);

    drawPattern(SANTA_PATTERN, color);

    // White beard area (bottom part)
    for (uint8_t x = 0; x < 8; x++) {
        setPixel(x, 7, matrix.Color(255, 255, 255));
        setPixel(x, 0, matrix.Color(255, 255, 255));
    }

    matrix.show();
}

/**
 * @brief Animation: Christmas tree with lights
 */
static void animateTree() {
    unsigned long elapsed = millis() - animationStartTime;

    clearMatrix();

    // Draw green tree
    drawPattern(TREE_PATTERN, matrix.Color(0, 100, 0));

    // Add blinking lights
    uint8_t phase = (elapsed / 300) % 4;
    uint32_t lightColor = (phase % 2 == 0) ? matrix.Color(255, 0, 0) : matrix.Color(0, 0, 255);

    // Add some lights
    if (phase < 2) {
        setPixel(2, 2, lightColor);
        setPixel(5, 2, lightColor);
        setPixel(3, 4, lightColor);
        setPixel(4, 4, lightColor);
    }

    // Star on top
    setPixel(3, 0, matrix.Color(255, 255, 0));
    setPixel(4, 0, matrix.Color(255, 255, 0));

    matrix.show();
}

/**
 * @brief Animation: Ringing bell
 */
static void animateBell() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t phase = (elapsed / 200) % 4;

    clearMatrix();

    // Draw bell with swing effect (slight offset)
    int8_t offset = 0;
    if (phase == 1) offset = -1;
    else if (phase == 3) offset = 1;

    uint32_t goldColor = matrix.Color(255, 200, 0);

    for (uint8_t y = 0; y < 8; y++) {
        uint8_t row = BELL_PATTERN[y];
        for (uint8_t x = 0; x < 8; x++) {
            if (row & (1 << (7 - x))) {
                int8_t newX = x + offset;
                if (newX >= 0 && newX < 8) {
                    setPixel(newX, y, goldColor);
                }
            }
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Falling snow
 */
static void animateSnow() {
    unsigned long elapsed = millis() - animationStartTime;

    if (elapsed % 200 == 0) {
        // Move everything down
        for (int8_t y = 7; y > 0; y--) {
            for (uint8_t x = 0; x < 8; x++) {
                setPixel(x, y, getPixel(x, y - 1));
            }
        }

        // Clear top row
        for (uint8_t x = 0; x < 8; x++) {
            setPixel(x, 0, 0);
        }

        // Add new snowflakes randomly
        if (random(0, 100) > 60) {
            uint8_t x = random(0, 8);
            setPixel(x, 0, matrix.Color(255, 255, 255));
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Gift box
 */
static void animateGift() {
    unsigned long elapsed = millis() - animationStartTime;
    float phase = (elapsed % 2000) / 2000.0;

    clearMatrix();

    // Alternating colors for gift wrap
    uint32_t color1 = matrix.Color(255, 0, 0);  // Red
    uint32_t color2 = matrix.Color(0, 255, 0);  // Green

    uint32_t currentColor = (phase < 0.5) ? color1 : color2;

    drawPattern(GIFT_PATTERN, currentColor);

    // Yellow ribbon (center lines)
    for (uint8_t y = 0; y < 8; y++) {
        setPixel(3, y, matrix.Color(255, 200, 0));
        setPixel(4, y, matrix.Color(255, 200, 0));
    }
    for (uint8_t x = 0; x < 8; x++) {
        setPixel(x, 0, matrix.Color(255, 200, 0));
        setPixel(x, 1, matrix.Color(255, 200, 0));
    }

    matrix.show();
}

/**
 * @brief Animation: Flickering candle
 */
static void animateCandle() {
    unsigned long elapsed = millis() - animationStartTime;

    clearMatrix();

    // Candle body (white)
    for (uint8_t y = 3; y < 8; y++) {
        for (uint8_t x = 3; x < 5; x++) {
            setPixel(x, y, matrix.Color(200, 200, 150));
        }
    }

    // Flickering flame
    uint8_t flicker = random(180, 255);
    uint8_t flameHeight = random(2, 4);

    for (uint8_t y = 0; y < flameHeight; y++) {
        for (uint8_t x = 2; x < 6; x++) {
            uint8_t brightness = flicker - (y * 50);
            if (y == 0 && (x == 2 || x == 5)) continue;  // Flame shape
            setPixel(x, 2 - y, matrix.Color(brightness, brightness / 2, 0));
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Rotating snowflake
 */
static void animateSnowflake() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t rotation = (elapsed / 300) % 4;

    clearMatrix();

    uint32_t cyanColor = matrix.Color(0, 200, 255);

    if (rotation == 0) {
        drawPattern(SNOWFLAKE_PATTERN, cyanColor);
    } else {
        // Rotate the pattern
        for (uint8_t y = 0; y < 8; y++) {
            uint8_t row = SNOWFLAKE_PATTERN[y];
            for (uint8_t x = 0; x < 8; x++) {
                if (row & (1 << (7 - x))) {
                    uint8_t newX = x, newY = y;

                    // Simple rotation (90, 180, 270 degrees)
                    switch (rotation) {
                        case 1: newX = 7 - y; newY = x; break;      // 90°
                        case 2: newX = 7 - x; newY = 7 - y; break;  // 180°
                        case 3: newX = y; newY = 7 - x; break;      // 270°
                    }

                    setPixel(newX, newY, cyanColor);
                }
            }
        }
    }

    matrix.show();
}

// =============================================================================
// NVS PERSISTENCE
// =============================================================================

void loadMatrix8x8Settings() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE_MATRIX, NVS_READONLY, &handle);

    if (err != ESP_OK) {
        LOG_PRINTLN("⚠ NVS (matrix) not initialized or empty");
        return;
    }

    // Load animation
    uint8_t anim = (uint8_t)MATRIX_ANIM_STAR;
    if (nvs_get_u8(handle, "animation", &anim) == ESP_OK) {
        currentAnimation = (Matrix8x8Animation)anim;
        LOG_PRINTF("Matrix animation restored: %s\n", animationNames[currentAnimation]);
    }

    // Load brightness
    uint8_t brightness = 128;
    if (nvs_get_u8(handle, "brightness", &brightness) == ESP_OK) {
        matrixBrightness = brightness;
        LOG_PRINTF("Matrix brightness restored: %d\n", matrixBrightness);
    }

    nvs_close(handle);
}

void saveMatrix8x8Settings() {
    nvs_handle_t handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE_MATRIX, NVS_READWRITE, &handle);

    if (err != ESP_OK) {
        LOG_PRINTLN("✗ Error: cannot open NVS (matrix)");
        return;
    }

    nvs_set_u8(handle, "animation", (uint8_t)currentAnimation);
    nvs_set_u8(handle, "brightness", matrixBrightness);

    err = nvs_commit(handle);
    nvs_close(handle);

    if (err == ESP_OK) {
        LOG_PRINTLN("✓ Matrix settings saved to NVS");
    } else {
        LOG_PRINTLN("✗ Error saving matrix settings");
    }
}

// =============================================================================
// PUBLIC FUNCTIONS
// =============================================================================

void setupMatrix8x8() {
    LOG_PRINTLN("--- Initializing 8x8 NeoPixel matrix ---");

    // Initialize NeoPixel
    matrix.begin();
    matrix.setBrightness(matrixBrightness);
    matrix.show();  // Clear all pixels

    // Load saved settings
    loadMatrix8x8Settings();

    // Start with star animation
    animationStartTime = millis();
    matrixEnabled = true;

    LOG_PRINTF("✓ 8x8 Matrix initialized - Starting with: %s (brightness: %d)\n",
               animationNames[currentAnimation], matrixBrightness);
}

void updateMatrix8x8() {
    if (!matrixEnabled || currentAnimation == MATRIX_ANIM_OFF) {
        matrix8x8Off();
        return;
    }

    // Execute current animation
    switch (currentAnimation) {
        case MATRIX_ANIM_STAR:
            animateStar();
            break;
        case MATRIX_ANIM_METEOR:
            animateMeteor();
            break;
        case MATRIX_ANIM_SHOOTING_STAR:
            animateShootingStar();
            break;
        case MATRIX_ANIM_SANTA:
            animateSanta();
            break;
        case MATRIX_ANIM_TREE:
            animateTree();
            break;
        case MATRIX_ANIM_BELL:
            animateBell();
            break;
        case MATRIX_ANIM_SNOW:
            animateSnow();
            break;
        case MATRIX_ANIM_GIFT:
            animateGift();
            break;
        case MATRIX_ANIM_CANDLE:
            animateCandle();
            break;
        case MATRIX_ANIM_SNOWFLAKE:
            animateSnowflake();
            break;
        default:
            break;
    }

    yield();  // Allow other tasks to run
}

void setMatrix8x8Animation(Matrix8x8Animation animation) {
    currentAnimation = animation;
    animationStartTime = millis();

    if (animation == MATRIX_ANIM_OFF) {
        matrixEnabled = false;
        matrix8x8Off();
    } else {
        matrixEnabled = true;
    }

    LOG_PRINTF("Matrix animation changed: %s\n", animationNames[animation]);
    saveMatrix8x8Settings();
}

Matrix8x8Animation getMatrix8x8Animation() {
    return currentAnimation;
}

const char* getMatrix8x8AnimationName() {
    return animationNames[currentAnimation];
}

const char* getMatrix8x8AnimationNameById(int id) {
    if (id >= 0 && id < MATRIX_ANIM_COUNT) {
        return animationNames[id];
    }
    return "?";
}

void nextMatrix8x8Animation() {
    uint8_t next = (uint8_t)currentAnimation + 1;
    if (next >= MATRIX_ANIM_COUNT) {
        next = 0;
    }
    setMatrix8x8Animation((Matrix8x8Animation)next);
}

void matrix8x8Off() {
    clearMatrix();
    matrix.show();
    matrixEnabled = false;
}

void setMatrix8x8Brightness(uint8_t brightness) {
    matrixBrightness = constrain(brightness, 0, 255);
    matrix.setBrightness(matrixBrightness);
    matrix.show();
    LOG_PRINTF("Matrix brightness set to: %d\n", matrixBrightness);
    saveMatrix8x8Settings();
}

uint8_t getMatrix8x8Brightness() {
    return matrixBrightness;
}

bool isMatrix8x8Active() {
    return (currentAnimation != MATRIX_ANIM_OFF) && matrixEnabled;
}
