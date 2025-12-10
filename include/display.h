/**
 * @file display.h
 * @brief Module de gestion centralisée des écrans (OLED et ST7789)
 * @version 0.7.0
 * @date 2025-12-06
 * 
 * Ce module fournit une interface unifiée pour gérer l'affichage
 * sur les écrans OLED (SSD1306) et TFT couleur (ST7789).
 * Il gère automatiquement l'initialisation et l'affichage des informations
 * de démarrage, progression WiFi et état de connexion.
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include <Wire.h>
#include "config.h"
#include "board_config.h"

// Includes conditionnels selon les écrans activés
#ifdef HAS_OLED
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h>
#endif

#ifdef HAS_ST7789
    #include <Adafruit_GFX.h>
    #include <Adafruit_ST7789.h>
#endif

// --- OBJETS GLOBAUX ---
#ifdef HAS_OLED
    extern Adafruit_SSD1306 display_oled;
#endif

#ifdef HAS_ST7789
    extern Adafruit_ST7789 display_tft;
#endif

// --- PROTOTYPES DE FONCTIONS ---

/**
 * @brief Initialise tous les écrans activés (OLED et/ou ST7789)
 * 
 * Cette fonction détecte automatiquement les écrans définis dans config.h
 * et les initialise avec les paramètres appropriés.
 * 
 * @note Appeler cette fonction une seule fois dans setup()
 */
void setupDisplays();

/**
 * @brief Affiche l'écran de démarrage avec nom du projet et version
 * 
 * Affiche sur tous les écrans disponibles :
 * - Nom du projet (PROJECT_NAME)
 * - Version du projet (PROJECT_VERSION)
 * 
 * @param projectName Nom du projet à afficher
 * @param projectVersion Version du projet à afficher
 */
void displayStartup(const char* projectName, const char* projectVersion);

/**
 * @brief Affiche la progression de la connexion WiFi
 * 
 * Affiche une barre de progression et le pourcentage sur tous les écrans.
 * Utilisé pendant la tentative de connexion au réseau WiFi.
 * 
 * @param progress Progression en pourcentage (0-100)
 */
void displayWifiProgress(int progress);

/**
 * @brief Affiche les informations de connexion WiFi réussie
 * 
 * Affiche sur tous les écrans :
 * - Nom du projet et version
 * - SSID du réseau connecté
 * - Adresse IP locale
 * 
 * @param ssid Nom du réseau WiFi connecté
 * @param ip Adresse IP locale attribuée
 */
void displayWifiConnected(const char* ssid, IPAddress ip);

/**
 * @brief Affiche un message d'erreur de connexion WiFi
 * 
 * Affiche sur tous les écrans un message d'échec de connexion.
 */
void displayWifiFailed();

/**
 * @brief Affiche l'animation et le mode actifs sur l'OLED après connexion WiFi
 * 
 * Appelée après la connexion WiFi pour afficher les infos d'animation et mode.
 * S'adapte à la hauteur de l'écran (32 ou 64 pixels).
 * 
 * @param ip Adresse IP locale (optionnel)
 */
void displayAnimationMode(IPAddress ip = IPAddress(0, 0, 0, 0));

/**
 * @brief Met à jour l'affichage OLED avec les infos d'animation et de mode
 * 
 * Cette fonction est disponible même si HAS_OLED n'est pas défini (ne fait rien dans ce cas).
 * Utile pour être appelée depuis d'autres modules sans vérifier HAS_OLED.
 * 
 * @param animationName Nom de l'animation actuelle
 * @param modeName Nom du mode actuel
 * @param ip Adresse IP locale (optionnel)
 */
void updateOledAnimationStatus(const char* animationName, const char* modeName, IPAddress ip = IPAddress(0, 0, 0, 0));

/**
 * @brief Affiche l'écran de veille (mode nuit) avec points fixes
 */
void displayOledSleepMode();

// --- FONCTIONS INTERNES (pour OLED) ---
#ifdef HAS_OLED
/**
 * @brief Initialise l'écran OLED SSD1306
 * @return true si l'initialisation réussit, false sinon
 */
bool setupOled();

/**
 * @brief Met à jour l'affichage OLED avec un statut et une progression
 * @param status Texte du statut à afficher
 * @param progress Progression (0-100), ou -1 pour ne pas afficher de barre
 */
void updateOledStatus(const char* status, int progress = -1);

/**
 * @brief Affiche les informations de connexion WiFi sur l'OLED
 * @param ssid SSID du réseau WiFi
 * @param ip Adresse IP locale
 */
void updateOledConnected(const char* ssid, IPAddress ip);

/**
 * @brief Dessine une barre d'animation visuelle selon l'animation en cours
 * @param animationName Nom de l'animation
 */
void drawAnimationBar(const char* animationName);
#endif

// --- FONCTIONS INTERNES (pour ST7789) ---
#ifdef HAS_ST7789
/**
 * @brief Initialise l'écran TFT ST7789
 * @return true si l'initialisation réussit, false sinon
 */
bool setupST7789();

/**
 * @brief Affiche l'écran de démarrage sur le ST7789
 * @param projectName Nom du projet
 * @param projectVersion Version du projet
 */
void displayST7789Startup(const char* projectName, const char* projectVersion);

/**
 * @brief Affiche la progression WiFi sur le ST7789
 * @param progress Progression en pourcentage (0-100)
 */
void displayST7789Progress(int progress);

/**
 * @brief Affiche les informations de connexion WiFi sur le ST7789
 * @param ssid SSID du réseau WiFi
 * @param ip Adresse IP locale
 */
void displayST7789Connected(const char* ssid, IPAddress ip);

/**
 * @brief Affiche un message d'erreur sur le ST7789
 */
void displayST7789Failed();
#endif

#endif // DISPLAY_H
