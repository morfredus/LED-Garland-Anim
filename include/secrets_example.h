#include <cstddef>
#ifndef SECRETS_H
#define SECRETS_H

// Liste des réseaux connus (SSID, Mot de passe)
// Inline pour éviter les définitions multiples
inline const char* WIFI_NETWORKS[][2] = {
	{"YourSSID_1", "YourSSID_Password_1"},
	{"YourSSID_2", "YourSSID_Password_2"}
};

inline constexpr size_t WIFI_NETWORKS_COUNT = sizeof(WIFI_NETWORKS) / sizeof(WIFI_NETWORKS[0]);

#endif // SECRETS_H