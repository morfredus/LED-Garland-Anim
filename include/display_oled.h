extern void displayMainScreen(const char* projectName, const char* projectVersion, const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName, const char* mDnsName);
#ifndef DISPLAY_OLED_H
#define DISPLAY_OLED_H

#include <Arduino.h>
#include <IPAddress.h>


#ifdef __cplusplus
extern "C" {
#endif

extern void setupDisplay();
extern void displayBootScreen(const char* projectName, const char* projectVersion, int wifiProgress);
extern void displayScreenByMode(const char* ssid, IPAddress ip, const char* modeName, const char* animationName, const char* matrixAnimationName, const char* mDnsName);
extern void updateAnimationVisual(const char* animationName, bool hasMatrix);

#ifdef __cplusplus
}
#endif

#endif // DISPLAY_OLED_H
