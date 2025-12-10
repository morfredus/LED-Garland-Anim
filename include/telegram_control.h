#ifndef TELEGRAM_CONTROL_H
#define TELEGRAM_CONTROL_H

#include <Arduino.h>
#include <WiFi.h>

/**
 * @brief Initialise le client Telegram (TLS)
 */
void setupTelegramBot();

/**
 * @brief Vérifie périodiquement les commandes Telegram et les applique
 *
 * À appeler dans loop(). La fonction est non bloquante et retourne vite
 * si l'intervalle de polling n'est pas atteint ou si le WiFi est coupé.
 */
void handleTelegramBot();

/**
 * @brief Envoie une notification de statut (SSID, IP, anim/mode)
 */
void sendTelegramStatus(const char* ssid, IPAddress ip);

#endif // TELEGRAM_CONTROL_H
