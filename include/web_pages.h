#ifndef WEB_PAGES_H
#define WEB_PAGES_H

/**
 * @file web_pages.h
 * @brief Génération des pages HTML pour l'interface web
 * @version 1.12.0
 *
 * Module dédié à la génération du contenu HTML de l'interface web.
 * Contient les fonctions pour construire les différentes cartes et sections.
 */

#include "web_styles.h"
#include "garland_control.h"
#include "matrix8x8_control.h"

/**
 * @brief Génère la page HTML complète du tableau de bord
 * @param chipId Identifiant unique du chip ESP32

 * @param flashSize Taille de la mémoire flash en bytes
 * @param flashSpeed Vitesse de la flash en MHz
 * @param heapSize Taille du heap total en bytes
 * @param freeHeap Heap libre en bytes
 */
String generateDashboardPage(uint32_t chipId, uint32_t flashSize, uint32_t flashSpeed, uint32_t heapSize, uint32_t freeHeap, uint32_t psramSize, uint32_t freePsram, uint32_t cpuFreq);

/**
 * @brief Génère la page HTML pour la mise à jour OTA du firmware
 * @return String contenant le HTML complet de la page OTA
 */
String generateOTAPage();

#endif // WEB_PAGES_H
