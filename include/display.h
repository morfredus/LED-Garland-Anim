/**
 * @file display.h
 * @brief Module de gestion de l'écran ST7789 (ESP32 IdeaSpark 1.14" LCD)
 * @version 1.1.0
 * @date 2025-12-30
 *
 * Ce module fournit une interface pour gérer l'affichage sur l'écran
 * ST7789 intégré à l'ESP32 IdeaSpark.
 * Il gère l'initialisation, le boot screen, et l'affichage de l'état.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.h"
#include "board_config.h"

#ifdef HAS_ST7789
    #include <Adafruit_GFX.h>
    #include <Adafruit_ST7789.h>
    #include <SPI.h>
#endif

// --- OBJET GLOBAL ---
#ifdef HAS_ST7789
    extern Adafruit_ST7789 display;
#endif

// --- PROTOTYPES DE FONCTIONS ---

/**
 * @brief Initialise l'écran ST7789
 *
 * Configure les pins SPI, initialise l'écran et active le rétroéclairage.
 *
 * @note Appeler cette fonction une seule fois dans setup()
 */
void setupDisplay();

/**
 * @brief Affiche l'écran de démarrage avec progression WiFi
 *
 * Affiche :
 * - Nom du projet (PROJECT_NAME)
 * - Version du projet (PROJECT_VERSION)
 * - Barre de progression WiFi (0-100%)
 *
 * @param projectName Nom du projet à afficher
 * @param projectVersion Version du projet à afficher
 * @param wifiProgress Progression WiFi (0-100), -1 pour ne pas afficher
 */
void displayBootScreen(const char* projectName, const char* projectVersion, int wifiProgress = -1);

/**
 * @brief Affiche l'écran principal avec les informations système
 *
 * Affiche :
 * - En-tête (Nom + Version)
 * - SSID + IP
 * - Mode (Manuel / Auto / Permanent)
 * - Animation en cours
 * - Zone graphique représentant l'animation active
 *
 * @param ssid Nom du réseau WiFi connecté
 * @param ip Adresse IP locale
 * @param modeName Nom du mode actuel
 * @param animationName Nom de l'animation active
 */
void displayMainScreen(const char* ssid, IPAddress ip, const char* modeName, const char* animationName);

/**
 * @brief Met à jour uniquement la zone d'animation sans redessiner tout l'écran
 *
 * @param animationName Nom de l'animation active
 */
void updateAnimationVisual(const char* animationName);

#endif // DISPLAY_H
