#ifndef WEB_INTERFACE_H
#define WEB_INTERFACE_H

/**
 * @file web_interface.h
 * @brief Gestion de l'interface web et des handlers du serveur
 * @version 1.12.1
 *
 * Module dédié à la gestion des routes HTTP et handlers du serveur web.
 * Contient les callbacks pour les différents endpoints de l'API web.
 */

#include <Update.h>
#include "web_pages.h"
#include "garland_control.h"
#include "matrix8x8_control.h"
#include "display.h"

// Déclaration du serveur web (défini dans main.cpp)
extern WebServer server;

// Déclaration du handler pour le mode d'affichage
void handleSetDisplayMode();

/**
 * @brief Handler pour la page d'accueil (GET /)
 * Génère et envoie le tableau de bord avec toutes les informations système
 */
void handleRoot();

/**
 * @brief Handler pour le redémarrage (GET /reboot)
 * Redémarre l'ESP32 après confirmation
 */
void handleReboot();

/**
 * @brief Handler pour changer l'animation (GET /animation?id=X)
 */
void handleSetAnimation();

/**
 * @brief Handler pour changer le mode (GET /mode?id=X)
 */
void handleSetMode();

/**
 * @brief Handler pour récupérer l'état de la guirlande (GET /status)
 */
void handleStatus();

/**
 * @brief Handler pour changer l'intervalle du mode AUTO (GET /auto_interval?ms=X)
 */
void handleSetAutoInterval();

/**
 * @brief Handler pour changer la durée de déclenchement mouvement (GET /motion_duration?ms=X)
 */
void handleSetMotionDuration();

/** Sauvegarde manuelle des paramètres en NVS */
void handleSaveSettings();

/** Recharge les paramètres depuis NVS */
void handleLoadSettings();

/** Efface l'espace NVS de l'application */
void handleEraseSettings();

/**
 * @brief Handler pour changer l'animation de la matrice 8x8 (GET /matrix_animation?id=X)
 */
/**
 * @note FIX #9: Added debug logging to trace API calls
 */
void handleSetMatrix8x8Animation();

/**
 * @brief Handler pour changer la luminosité de la matrice 8x8 (GET /matrix_brightness?value=X)
 * @note FIX #10: Added debug logging to trace API calls
 */
void handleSetMatrix8x8Brightness();

/**
 * @brief Handler pour la page de mise à jour OTA (GET /update)
 * Affiche la page d'upload du firmware
 */
void handleOTAPage();

/**
 * @brief Handler pour l'upload du firmware OTA (POST /update)
 * Gère le téléversement du fichier .bin et la mise à jour du firmware
 */
void handleOTAUpload();
void handleOTAUploadComplete();

/**
 * @brief Handler pour les pages non trouvées (404)
 */
void handleNotFound();

/**
 * @brief Handler pour récupérer le nom d'appareil (GET /device_name)
 */
void handleGetDeviceName();

/**
 * @brief Handler pour définir le nom d'appareil (POST /device_name?name=X)
 */
void handleSetDeviceName();

/**
 * @brief Initialise les routes du serveur web
 * À appeler dans setup() après la connexion WiFi
 */
void setupWebServer();

#endif // WEB_INTERFACE_H
