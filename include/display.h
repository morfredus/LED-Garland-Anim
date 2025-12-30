// ---
// Changelog :
// #3 (2025-12-30) : Suppression du support TFT/ILI9341, LCD ST7789 unique, OLED secours, harmonisation des fonctions
// ---
/**
 * @file display.h
 * @brief Module de gestion centralisée des écrans (OLED et ST7789)
 * @version 0.7.0
 * @date 2025-12-06
 * 
 * Ce module fournit une interface unifiée pour gérer l'affichage
 * sur les écrans OLED (SSD1306) et LCD couleur (ST7789).
 * Il gère automatiquement l'initialisation et l'affichage des informations
 * de démarrage, progression WiFi et état de connexion.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "board_config.h"


// LCD couleur ST7789 (remplace le support TFT)
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// --- OBJET GLOBAL LCD ---
extern Adafruit_ST7789 display_lcd;


// --- PROTOTYPES DE FONCTIONS ---


void setupDisplays();
void drawAnimationGraph(int x, int y, int w, int h);
void displayLCDStartup(const char* projectName, const char* projectVersion);
void displayLCDProgress(int progress);
void displayLCDConnected(const char* ssid, IPAddress ip);
void displayLCDFailed();

// --- FONCTIONS INTERNES (pour LCD ST7789) ---
#ifdef HAS_LCD
/**
 * @brief Initialise l'écran LCD ST7789
 * @return true si l'initialisation réussit, false sinon
 *
 * Changement #3 (2025-12-30) : Suppression du support TFT, LCD ST7789 unique
 */
bool setupLCD();

/**
 * @brief Affiche l'écran de démarrage sur le LCD ST7789
 * @param projectName Nom du projet
 * @param projectVersion Version du projet
 */
void displayLCDStartup(const char* projectName, const char* projectVersion);

/**
 * @brief Affiche la progression WiFi sur le LCD ST7789
 * @param progress Progression en pourcentage (0-100)
 */
void displayLCDProgress(int progress);

/**
 * @brief Affiche les informations de connexion WiFi sur le LCD ST7789
 * @param ssid SSID du réseau WiFi
 * @param ip Adresse IP locale
 */
void displayLCDConnected(const char* ssid, IPAddress ip);

/**
 * @brief Affiche un message d'erreur sur le LCD ST7789
 */
void displayLCDFailed();
#endif

#endif // DISPLAY_H
