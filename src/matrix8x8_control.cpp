/**
 * @file matrix8x8_control.cpp
 * @brief Implementation of 8x8 NeoPixel matrix control with festive animations
 * @version 1.12.0
 * @date 2026-01-06
 */

#include "matrix8x8_control.h"
#include "garland_control.h"

// =============================================================================
// GLOBAL VARIABLES
// =============================================================================

static Adafruit_NeoPixel matrix = Adafruit_NeoPixel(MATRIX8X8_NUMPIXELS, MATRIX8X8_PIN, NEO_GRB + NEO_KHZ800);

static Matrix8x8Animation currentAnimation = MATRIX_ANIM_STAR;  // Selected animation (for display/save)
static Matrix8x8Animation activeAnimation = MATRIX_ANIM_STAR;   // Currently executing animation
static unsigned long animationStartTime = 0;
static unsigned long autoModeChangeTime = 0;  // Track last auto mode change
// NOTE: Auto mode interval is shared with garland - uses getAutoAnimationIntervalMs()
static uint8_t matrixBrightness = 128;  // Default brightness (50%)
static bool matrixEnabled = true;
static bool autoModeActive = false;  // Flag to track if auto mode is active

// Animation state variables
static uint8_t animationPhase = 0;
static int8_t animationPosition = 0;
static uint8_t animationCounter = 0;

// =============================================================================
// ANIMATION NAMES
// =============================================================================

static const char* animationNames[] = {
    "Off",
    // Original animations
    "Star",
    "Meteor",
    "Shooting Star",
    "Santa",
    "Tree",
    "Bell",
    "Snow",
    "Gift",
    "Candle",
    "Snowflake",
    // Christmas animations
    "Candy Cane",
    "Wreath",
    "Stocking",
    "Reindeer",
    "Gingerbread",
    "Hot Cocoa",
    "Fireplace",
    "Northern Lights",
    "Presents",
    // New Year animations
    "Fireworks",
    "Champagne",
    "Countdown",
    "Confetti",
    "Clock",
    "Party Popper",
    "Disco Ball",
    // Easter animations
    "Easter Egg",
    "Bunny",
    "Chick",
    "Flowers",
    // Abstract/Modern animations
    "Rainbow Wave",
    "Sparkle Rain",
    "Plasma",
    "Matrix Rain",
    "Spiral",
    "Heart",
    "Stars Field",
    "Campfire",
    "Radar",
    "Auto"
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
 * Uses linear wiring pattern:
 * All rows: 0->7 (left to right)
 * Row 0: 0-7
 * Row 1: 8-15
 * Row 2: 16-23
 * Row 3: 24-31
 * Row 4: 32-39
 * Row 5: 40-47
 * Row 6: 48-55
 * Row 7: 56-63
 */
static uint16_t xy(uint8_t x, uint8_t y) {
    if (x >= 8 || y >= 8) return 0;
    return y * 8 + x;  // Linear: all rows left to right
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

// Wreath pattern
static const uint8_t WREATH_PATTERN[] = {
    0b00111100,
    0b01000010,
    0b10000001,
    0b10000001,
    0b10000001,
    0b10000001,
    0b01000010,
    0b00111100
};

// Stocking pattern - redesigned for better recognition
// Represents a Christmas stocking hanging with cuff, leg, and foot
static const uint8_t STOCKING_PATTERN[] = {
    0b00111100,  // Row 0: White cuff top
    0b00111100,  // Row 1: White cuff
    0b00111100,  // Row 2: Red leg start
    0b00111100,  // Row 3: Red leg
    0b00111100,  // Row 4: Red leg
    0b01111110,  // Row 5: Red foot starts (wider)
    0b11111110,  // Row 6: Red foot
    0b01111100   // Row 7: Red toe (rounded)
};

// Reindeer pattern
static const uint8_t REINDEER_PATTERN[] = {
    0b10100101,
    0b10100101,
    0b01011010,
    0b00111100,
    0b00111100,
    0b01111110,
    0b00111100,
    0b01100110
};

// Gingerbread man pattern
static const uint8_t GINGERBREAD_PATTERN[] = {
    0b00111100,
    0b01111110,
    0b00111100,
    0b11111111,
    0b00111100,
    0b00111100,
    0b01100110,
    0b11000011
};

// Heart pattern
static const uint8_t HEART_PATTERN[] = {
    0b00000000,
    0b01100110,
    0b11111111,
    0b11111111,
    0b01111110,
    0b00111100,
    0b00011000,
    0b00000000
};

// Easter egg pattern
static const uint8_t EASTER_EGG_PATTERN[] = {
    0b00111100,
    0b01111110,
    0b11011011,
    0b11111111,
    0b11011011,
    0b11111111,
    0b01111110,
    0b00111100
};

// Bunny pattern
static const uint8_t BUNNY_PATTERN[] = {
    0b01000010,
    0b01000010,
    0b01111110,
    0b01111110,
    0b00111100,
    0b00111100,
    0b01100110,
    0b11000011
};

// Chick pattern
static const uint8_t CHICK_PATTERN[] = {
    0b00000000,
    0b00011000,
    0b00111100,
    0b01111110,
    0b01111110,
    0b00111100,
    0b00100100,
    0b00100100
};

// Flower pattern
static const uint8_t FLOWER_PATTERN[] = {
    0b00000000,
    0b00100100,
    0b01011010,
    0b00111100,
    0b00111100,
    0b01011010,
    0b00100100,
    0b00000000
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
 * @brief Animation: Meteor shower - Diagonal meteors across full matrix
 */
static void animateMeteor() {
    static unsigned long lastUpdate = 0;
    static uint8_t meteorPos = 0;
    unsigned long currentMillis = millis();

    // Move every 120ms
    if (currentMillis - lastUpdate >= 120) {
        lastUpdate = currentMillis;

        // Fade all pixels (trail effect)
        for (uint8_t i = 0; i < 64; i++) {
            matrix.setPixelColor(i, dimColor(matrix.getPixelColor(i), 170));
        }

        // Draw meteor diagonally across full matrix
        // Multiple meteors at different stages
        for (uint8_t m = 0; m < 3; m++) {
            int8_t pos = (meteorPos + m * 5) % 16;  // 16 diagonal positions across matrix

            // Draw meteor with trail (4 pixels long)
            for (int8_t trail = 0; trail < 4; trail++) {
                int8_t x = pos - trail;
                int8_t y = pos - trail;

                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    uint8_t brightness = 255 - (trail * 60);  // Dimmer trail
                    uint32_t color = matrix.Color(brightness, brightness, brightness * 0.8);
                    setPixel(x, y, color);
                }
            }
        }

        meteorPos++;
        if (meteorPos >= 16) meteorPos = 0;

        matrix.show();
    }
}

/**
 * @brief Animation: Shooting star
 * @note FIX #2: Changed from modulo timing to threshold-based timing
 */
static void animateShootingStar() {
    static unsigned long lastUpdate = 0;
    static uint8_t frameCount = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= 50) {
        lastUpdate = currentMillis;
        frameCount++;

        clearMatrix();

        // Calculate diagonal position
        int8_t pos = frameCount % 16;

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
 * @brief Animation: Santa face - Improved with hat, eyes, and beard
 */
static void animateSanta() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t blinkPhase = (elapsed / 2500) % 10;

    clearMatrix();

    // Red hat (rows 0-2)
    for (uint8_t y = 0; y < 3; y++) {
        for (uint8_t x = 1; x < 7; x++) {
            setPixel(x, y, matrix.Color(220, 0, 0));
        }
    }

    // White hat trim (row 2)
    for (uint8_t x = 1; x < 7; x++) {
        setPixel(x, 2, matrix.Color(255, 255, 255));
    }

    // White pom-pom on hat
    setPixel(7, 0, matrix.Color(255, 255, 255));

    // Skin tone face (rows 3-5)
    for (uint8_t y = 3; y < 6; y++) {
        for (uint8_t x = 1; x < 7; x++) {
            setPixel(x, y, matrix.Color(255, 220, 180));
        }
    }

    // Eyes (black, blink occasionally)
    if (blinkPhase != 0) {
        setPixel(2, 4, matrix.Color(0, 0, 0));  // Left eye
        setPixel(5, 4, matrix.Color(0, 0, 0));  // Right eye
    }

    // Red nose (Rudolph!)
    setPixel(3, 5, matrix.Color(255, 0, 0));
    setPixel(4, 5, matrix.Color(255, 0, 0));

    // White beard (rows 6-7)
    for (uint8_t y = 6; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            setPixel(x, y, matrix.Color(255, 255, 255));
        }
    }

    // Beard detail (mustache gap)
    setPixel(3, 6, matrix.Color(255, 220, 180));
    setPixel(4, 6, matrix.Color(255, 220, 180));

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
 * @note BUGFIX #6 (v1.8.1): Bell stays fixed, only clapper moves
 */
static void animateBell() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t phase = (elapsed / 200) % 4;

    clearMatrix();

    // Draw bell (fixed, no offset)
    uint32_t goldColor = matrix.Color(255, 200, 0);

    for (uint8_t y = 0; y < 8; y++) {
        uint8_t row = BELL_PATTERN[y];
        for (uint8_t x = 0; x < 8; x++) {
            if (row & (1 << (7 - x))) {
                setPixel(x, y, goldColor);
            }
        }
    }

    // Draw moving clapper (pendulum) inside bell
    int8_t clapperX = 4;  // Center x position
    if (phase == 1) clapperX = 3;  // Swing left
    else if (phase == 3) clapperX = 5;  // Swing right

    // Clapper at bottom of bell (y=6)
    if (clapperX >= 0 && clapperX < 8) {
        setPixel(clapperX, 6, matrix.Color(150, 150, 150));  // Gray clapper
    }

    matrix.show();
}

/**
 * @brief Animation: Falling snow
 * @note FIX #3: Changed from modulo timing to threshold-based timing
 */
static void animateSnow() {
    static unsigned long lastUpdate = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= 200) {
        lastUpdate = currentMillis;

        // Move everything down
        for (int8_t y = 7; y >= 1; y--) {
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
 * @brief Animation: Gift box - Clear box with ribbon and animated bow
 */
static void animateGift() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t colorPhase = (elapsed / 1000) % 3;
    uint8_t sparklePhase = (elapsed / 300) % 4;

    clearMatrix();

    // Gift box colors (cycle: red, green, blue)
    uint32_t boxColor;
    if (colorPhase == 0) boxColor = matrix.Color(200, 0, 0);      // Red
    else if (colorPhase == 1) boxColor = matrix.Color(0, 180, 0); // Green
    else boxColor = matrix.Color(0, 0, 200);                      // Blue

    // Draw gift box (rows 2-7, cols 1-6)
    for (uint8_t y = 2; y < 8; y++) {
        for (uint8_t x = 1; x < 7; x++) {
            setPixel(x, y, boxColor);
        }
    }

    // Gold ribbon (vertical down center)
    for (uint8_t y = 2; y < 8; y++) {
        setPixel(3, y, matrix.Color(255, 215, 0));
        setPixel(4, y, matrix.Color(255, 215, 0));
    }

    // Gold ribbon (horizontal across top of box)
    for (uint8_t x = 1; x < 7; x++) {
        setPixel(x, 2, matrix.Color(255, 215, 0));
        setPixel(x, 3, matrix.Color(255, 215, 0));
    }

    // Bow on top (rows 0-1) - sparkles
    uint8_t bowBrightness = (sparklePhase == 0) ? 255 : 200;
    setPixel(2, 0, matrix.Color(bowBrightness, 180, 0));  // Left bow
    setPixel(2, 1, matrix.Color(bowBrightness, 180, 0));
    setPixel(3, 0, matrix.Color(255, 215, 0));  // Center knot
    setPixel(4, 0, matrix.Color(255, 215, 0));
    setPixel(3, 1, matrix.Color(255, 215, 0));
    setPixel(4, 1, matrix.Color(255, 215, 0));
    setPixel(5, 0, matrix.Color(bowBrightness, 180, 0));  // Right bow
    setPixel(5, 1, matrix.Color(bowBrightness, 180, 0));

    matrix.show();
}

/**
 * @brief Animation: Flickering candle
 * @note BUGFIX #5 (v1.8.1): Wider base (4px), narrower flickering flame (2px)
 */
static void animateCandle() {
    unsigned long elapsed = millis() - animationStartTime;

    clearMatrix();

    // Candle body (white) - 4 pixels wide (x=2 to x=5)
    for (uint8_t y = 3; y < 8; y++) {
        for (uint8_t x = 2; x < 6; x++) {
            setPixel(x, y, matrix.Color(200, 200, 150));
        }
    }

    // Flickering flame - 2 pixels wide (x=3 to x=4)
    uint8_t flicker = random(180, 255);
    uint8_t flameHeight = random(2, 4);

    for (uint8_t y = 0; y < flameHeight; y++) {
        for (uint8_t x = 3; x < 5; x++) {  // 2 pixels wide
            uint8_t brightness = flicker - (y * 50);
            setPixel(x, 2 - y, matrix.Color(brightness, brightness / 2, 0));
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Snowflake - Rotating with heartbeat pulse effect
 */
static void animateSnowflake() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t rotation = (elapsed / 300) % 4;

    // Heartbeat pulse effect (same color, varying brightness)
    float pulsePhase = (elapsed % 1500) / 1500.0;  // 1.5 second cycle
    // Create heartbeat pattern: two quick pulses, then pause
    float pulse;
    if (pulsePhase < 0.15) {
        // First pulse (0-0.15)
        pulse = sin(pulsePhase / 0.15 * PI);
    } else if (pulsePhase > 0.25 && pulsePhase < 0.4) {
        // Second pulse (0.25-0.4)
        pulse = sin((pulsePhase - 0.25) / 0.15 * PI);
    } else {
        // Rest period
        pulse = 0;
    }

    // Brightness varies from 100 to 255
    uint8_t brightness = 100 + (uint8_t)(pulse * 155);
    uint32_t cyanColor = matrix.Color(0, brightness * 0.78, brightness);

    clearMatrix();

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

/**
 * @brief Animation: Candy Cane - Realistic candy cane with hook and rotating diagonal stripes
 */
static void animateCandyCane() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t offset = (elapsed / 200) % 8;  // Rotate stripes

    clearMatrix();

    // Candy cane shape: hook at top (rows 0-2), straight stick (rows 3-7)
    // The hook curves from left to right at the top

    // Define the candy cane pixels (1 = part of cane, 0 = background)
    const uint8_t CANE_SHAPE[] = {
        0b00111110,  // Row 0: Hook top (curved)
        0b01000001,  // Row 1: Hook sides
        0b00000011,  // Row 2: Hook bends down right
        0b00001100,  // Row 3: Stick starts
        0b00001100,  // Row 4: Straight stick
        0b00001100,  // Row 5: Straight stick
        0b00001100,  // Row 6: Straight stick
        0b00001100   // Row 7: Stick bottom
    };

    // Draw candy cane with rotating diagonal stripes
    for (uint8_t y = 0; y < 8; y++) {
        uint8_t row = CANE_SHAPE[y];
        for (uint8_t x = 0; x < 8; x++) {
            if (row & (1 << (7 - x))) {
                // This pixel is part of the candy cane
                // Diagonal stripe pattern that rotates
                if ((x + y + offset) % 4 < 2) {
                    setPixel(x, y, matrix.Color(255, 0, 0));  // Red stripe
                } else {
                    setPixel(x, y, matrix.Color(255, 255, 255));  // White stripe
                }
            }
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Christmas Wreath with bow
 */
static void animateWreath() {
    unsigned long elapsed = millis() - animationStartTime;
    float phase = (elapsed % 2000) / 2000.0;

    clearMatrix();

    // Pulsating green wreath
    uint8_t brightness = (uint8_t)((sin(phase * 2.0 * PI) + 1.0) * 50 + 100);
    uint32_t greenColor = matrix.Color(0, brightness, 0);

    drawPattern(WREATH_PATTERN, greenColor);

    // Red bow at top
    setPixel(3, 0, matrix.Color(255, 0, 0));
    setPixel(4, 0, matrix.Color(255, 0, 0));

    // Add some berries
    if ((elapsed / 500) % 2 == 0) {
        setPixel(2, 2, matrix.Color(255, 0, 0));
        setPixel(5, 2, matrix.Color(255, 0, 0));
        setPixel(2, 5, matrix.Color(255, 0, 0));
        setPixel(5, 5, matrix.Color(255, 0, 0));
    }

    matrix.show();
}

/**
 * @brief Animation: Hanging Stocking
 */
/**
 * @brief Animation: Stocking - Completely redesigned Christmas stocking
 * Displays a red stocking with white cuff and decorative elements
 */
static void animateStocking() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t phase = (elapsed / 300) % 8;  // Slower swing

    clearMatrix();

    // Realistic swing effect (pendulum motion)
    int8_t offset = 0;
    if (phase == 1) offset = -1;
    else if (phase == 2) offset = -1;
    else if (phase == 6) offset = 1;
    else if (phase == 7) offset = 1;

    // Draw red stocking body
    for (uint8_t y = 2; y < 8; y++) {  // Start from row 2 (after cuff)
        uint8_t row = STOCKING_PATTERN[y];
        for (uint8_t x = 0; x < 8; x++) {
            if (row & (1 << (7 - x))) {
                int8_t newX = x + offset;
                if (newX >= 0 && newX < 8) {
                    setPixel(newX, y, matrix.Color(220, 0, 0));  // Red
                }
            }
        }
    }

    // White cuff at top (rows 0-1)
    for (uint8_t y = 0; y < 2; y++) {
        uint8_t row = STOCKING_PATTERN[y];
        for (uint8_t x = 0; x < 8; x++) {
            if (row & (1 << (7 - x))) {
                int8_t newX = x + offset;
                if (newX >= 0 && newX < 8) {
                    setPixel(newX, y, matrix.Color(255, 255, 255));  // White cuff
                }
            }
        }
    }

    // Add decorative green stripe on leg
    for (int8_t x = 2 + offset; x < 6 + offset; x++) {
        if (x >= 0 && x < 8) {
            setPixel(x, 3, matrix.Color(0, 180, 0));  // Green stripe
        }
    }

    // Add twinkling star/sparkle on stocking (for interest)
    if (phase % 4 < 2) {
        int8_t starX = 3 + offset;
        if (starX >= 0 && starX < 8) {
            setPixel(starX, 5, matrix.Color(255, 215, 0));  // Gold sparkle
        }
    }

    // Optional: Hanging loop/hook at top
    int8_t hookX = 3 + offset;
    if (hookX >= 0 && hookX < 8) {
        setPixel(hookX, 0, matrix.Color(150, 150, 150));  // Gray hook
    }

    matrix.show();
}

/**
 * @brief Animation: Reindeer
 */
static void animateReindeer() {
    unsigned long elapsed = millis() - animationStartTime;
    float phase = (elapsed % 1500) / 1500.0;

    clearMatrix();

    // Brown reindeer
    drawPattern(REINDEER_PATTERN, matrix.Color(139, 69, 19));

    // Blinking red nose
    if (phase < 0.5) {
        setPixel(3, 3, matrix.Color(255, 0, 0));
        setPixel(4, 3, matrix.Color(255, 0, 0));
    }

    matrix.show();
}

/**
 * @brief Animation: Gingerbread Man
 */
static void animateGingerbread() {
    unsigned long elapsed = millis() - animationStartTime;

    clearMatrix();

    // Brown gingerbread
    drawPattern(GINGERBREAD_PATTERN, matrix.Color(180, 100, 50));

    // White icing details (blinking)
    if ((elapsed / 500) % 2 == 0) {
        setPixel(2, 1, matrix.Color(255, 255, 255));
        setPixel(5, 1, matrix.Color(255, 255, 255));
        setPixel(3, 3, matrix.Color(255, 255, 255));
        setPixel(4, 3, matrix.Color(255, 255, 255));
    }

    matrix.show();
}

/**
 * @brief Animation: Hot Cocoa with steam
 */
static void animateHotCocoa() {
    unsigned long elapsed = millis() - animationStartTime;

    clearMatrix();

    // Mug (white)
    for (uint8_t y = 2; y < 8; y++) {
        for (uint8_t x = 1; x < 6; x++) {
            setPixel(x, y, matrix.Color(200, 200, 200));
        }
    }

    // Hot cocoa (brown)
    for (uint8_t y = 3; y < 7; y++) {
        for (uint8_t x = 2; x < 5; x++) {
            setPixel(x, y, matrix.Color(101, 67, 33));
        }
    }

    // Rising steam
    uint8_t steamY = (elapsed / 200) % 3;
    setPixel(2, steamY, matrix.Color(200, 200, 200));
    setPixel(4, 1 - steamY % 2, matrix.Color(150, 150, 150));

    matrix.show();
}

/**
 * @brief Animation: Fireplace
 */
static void animateFireplace() {
    clearMatrix();

    // Fireplace structure (brown/gray)
    for (uint8_t y = 5; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            setPixel(x, y, matrix.Color(80, 40, 20));
        }
    }

    // Flickering flames
    for (uint8_t x = 1; x < 7; x++) {
        uint8_t flameHeight = random(2, 5);
        for (uint8_t y = 0; y < flameHeight; y++) {
            uint8_t r = 255 - y * 40;
            uint8_t g = random(50, 150) - y * 20;
            setPixel(x, 4 - y, matrix.Color(r, g, 0));
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Northern Lights (Aurora)
 */
static void animateNorthernLights() {
    unsigned long elapsed = millis() - animationStartTime;
    float phase = (elapsed % 3000) / 3000.0;

    clearMatrix();

    // Animated aurora waves
    for (uint8_t x = 0; x < 8; x++) {
        float wave1 = sin((x + phase * 8) * 0.5) * 3 + 4;
        float wave2 = sin((x + phase * 10) * 0.7) * 2 + 3;

        for (uint8_t y = 0; y < 8; y++) {
            if (abs(y - wave1) < 1.5) {
                setPixel(x, y, matrix.Color(0, 255, 100));
            }
            if (abs(y - wave2) < 1.0) {
                setPixel(x, y, matrix.Color(100, 0, 255));
            }
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Stack of Presents
 */
static void animatePresents() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t colorCycle = (elapsed / 800) % 3;

    clearMatrix();

    // Bottom present (large)
    uint32_t color1 = (colorCycle == 0) ? matrix.Color(255, 0, 0) :
                      (colorCycle == 1) ? matrix.Color(0, 255, 0) : matrix.Color(0, 0, 255);
    for (uint8_t y = 5; y < 8; y++) {
        for (uint8_t x = 1; x < 7; x++) {
            setPixel(x, y, color1);
        }
    }

    // Top present (smaller)
    uint32_t color2 = (colorCycle == 1) ? matrix.Color(255, 0, 0) :
                      (colorCycle == 2) ? matrix.Color(0, 255, 0) : matrix.Color(0, 0, 255);
    for (uint8_t y = 2; y < 5; y++) {
        for (uint8_t x = 2; x < 6; x++) {
            setPixel(x, y, color2);
        }
    }

    // Ribbons (gold)
    for (uint8_t y = 0; y < 8; y++) {
        setPixel(3, y, matrix.Color(255, 215, 0));
        setPixel(4, y, matrix.Color(255, 215, 0));
    }

    matrix.show();
}

/**
 * @brief Animation: Fireworks bursts
 */
static void animateFireworks() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t phase = (elapsed / 300) % 8;

    clearMatrix();

    // Burst animation from center
    uint8_t cx = 4, cy = 4;
    for (int8_t dx = -phase; dx <= phase; dx++) {
        for (int8_t dy = -phase; dy <= phase; dy++) {
            if (abs(dx) + abs(dy) == phase) {
                int8_t x = cx + dx;
                int8_t y = cy + dy;
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    uint8_t hue = (phase * 32 + dx * 10 + dy * 10) % 256;
                    uint32_t color = (phase % 3 == 0) ? matrix.Color(255, 0, 0) :
                                     (phase % 3 == 1) ? matrix.Color(0, 255, 0) :
                                                        matrix.Color(0, 0, 255);
                    setPixel(x, y, color);
                }
            }
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Champagne bubbles
 * @note FIX #4: Changed from modulo timing to threshold-based timing
 */
static void animateChampagne() {
    static unsigned long lastUpdate = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= 150) {
        lastUpdate = currentMillis;

        // Move bubbles up
        for (int8_t y = 0; y <= 6; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                setPixel(x, y, getPixel(x, y + 1));
            }
        }

        // Clear bottom row
        for (uint8_t x = 0; x < 8; x++) {
            setPixel(x, 7, 0);
        }

        // Add new bubbles at bottom
        if (random(0, 100) > 50) {
            uint8_t x = random(0, 8);
            setPixel(x, 7, matrix.Color(255, 255, 100));
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Countdown 3-2-1
 * @note BUGFIX #3 (v1.8.1): Redrawn readable digits for 8x8 matrix
 */
static void animateCountdown() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t number = 3 - ((elapsed / 1000) % 4);

    clearMatrix();
    uint32_t color = matrix.Color(255, 255, 0);

    if (number == 3) {
        // ----- "3" bien centré, style 5x7 -----
        // Top horizontal
        setPixel(2, 1, color); setPixel(3, 1, color); setPixel(4, 1, color); setPixel(5, 1, color);
        // Upper right vertical
        setPixel(5, 2, color); setPixel(5, 3, color);
        // Middle horizontal
        setPixel(3, 3, color); setPixel(4, 3, color); setPixel(5, 3, color);
        // Lower right vertical
        setPixel(5, 4, color); setPixel(5, 5, color);
        // Bottom horizontal
        setPixel(2, 6, color); setPixel(3, 6, color); setPixel(4, 6, color); setPixel(5, 6, color);

    } else if (number == 2) {
        // ----- "2" lisible et symétrique -----
        // Top horizontal
        setPixel(2, 1, color); setPixel(3, 1, color); setPixel(4, 1, color); setPixel(5, 1, color);
        // Upper right
        setPixel(5, 2, color);
        // Middle horizontal
        setPixel(2, 3, color); setPixel(3, 3, color); setPixel(4, 3, color); setPixel(5, 3, color);
        // Lower left
        setPixel(2, 4, color); setPixel(2, 5, color);
        // Bottom horizontal
        setPixel(2, 6, color); setPixel(3, 6, color); setPixel(4, 6, color); setPixel(5, 6, color);

    } else if (number == 1) {
        // ----- "1" simple, bien centré -----
        // Small base (pied)
        setPixel(3, 6, color); setPixel(4, 6, color); setPixel(5, 6, color);
        // Vertical line
        setPixel(4, 1, color); setPixel(4, 2, color); setPixel(4, 3, color);
        setPixel(4, 4, color); setPixel(4, 5, color);
        // Slight top tick (optionnel mais lisible)
        setPixel(3, 2, color);

    } else {
        // Explosion!
        for (uint8_t x = 0; x < 8; x++) {
            for (uint8_t y = 0; y < 8; y++) {
                if (random(0, 100) > 60) {
                    setPixel(x, y, matrix.Color(255, random(0, 255), 0));
                }
            }
        }
    }

    matrix.show();
}


/**
 * @brief Animation: Falling Confetti
 * @note FIX #5: Changed from modulo timing to threshold-based timing
 */
static void animateConfetti() {
    static unsigned long lastUpdate = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= 200) {
        lastUpdate = currentMillis;

        // Move everything down
        for (int8_t y = 7; y >= 1; y--) {
            for (uint8_t x = 0; x < 8; x++) {
                setPixel(x, y, getPixel(x, y - 1));
            }
        }

        // Clear top row
        for (uint8_t x = 0; x < 8; x++) {
            setPixel(x, 0, 0);
        }

        // Add new confetti
        if (random(0, 100) > 40) {
            uint8_t x = random(0, 8);
            uint32_t colors[] = {
                matrix.Color(255, 0, 0),
                matrix.Color(0, 255, 0),
                matrix.Color(0, 0, 255),
                matrix.Color(255, 255, 0),
                matrix.Color(255, 0, 255),
                matrix.Color(0, 255, 255)
            };
            setPixel(x, 0, colors[random(0, 6)]);
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Clock - Clean analog clock with smooth second hand
 * Redesigned: Simpler, cleaner, more readable
 */
static void animateClock() {
    unsigned long elapsed = millis() - animationStartTime;
    // One full rotation every 60 seconds
    float angle = (elapsed % 60000) / 60000.0 * TWO_PI - PI/2;  // Start at 12 o'clock

    clearMatrix();

    // Draw clock face outline (circle)
    // Top row
    setPixel(2, 0, matrix.Color(80, 80, 120));
    setPixel(3, 0, matrix.Color(100, 100, 150));
    setPixel(4, 0, matrix.Color(100, 100, 150));
    setPixel(5, 0, matrix.Color(80, 80, 120));

    // Second row
    setPixel(1, 1, matrix.Color(80, 80, 120));
    setPixel(6, 1, matrix.Color(80, 80, 120));

    // Middle rows
    setPixel(0, 2, matrix.Color(80, 80, 120));
    setPixel(7, 2, matrix.Color(80, 80, 120));
    setPixel(0, 3, matrix.Color(100, 100, 150));
    setPixel(7, 3, matrix.Color(100, 100, 150));
    setPixel(0, 4, matrix.Color(100, 100, 150));
    setPixel(7, 4, matrix.Color(100, 100, 150));
    setPixel(0, 5, matrix.Color(80, 80, 120));
    setPixel(7, 5, matrix.Color(80, 80, 120));

    // Bottom rows
    setPixel(1, 6, matrix.Color(80, 80, 120));
    setPixel(6, 6, matrix.Color(80, 80, 120));

    setPixel(2, 7, matrix.Color(80, 80, 120));
    setPixel(3, 7, matrix.Color(100, 100, 150));
    setPixel(4, 7, matrix.Color(100, 100, 150));
    setPixel(5, 7, matrix.Color(80, 80, 120));

    // Draw 4 main hour markers (12, 3, 6, 9) in gold
    setPixel(3, 1, matrix.Color(255, 200, 0));  // 12 o'clock (top)
    setPixel(4, 1, matrix.Color(255, 200, 0));
    setPixel(6, 3, matrix.Color(255, 200, 0));  // 3 o'clock (right)
    setPixel(6, 4, matrix.Color(255, 200, 0));
    setPixel(3, 6, matrix.Color(255, 200, 0));  // 6 o'clock (bottom)
    setPixel(4, 6, matrix.Color(255, 200, 0));
    setPixel(1, 3, matrix.Color(255, 200, 0));  // 9 o'clock (left)
    setPixel(1, 4, matrix.Color(255, 200, 0));

    // Center point (small, elegant)
    setPixel(3, 3, matrix.Color(150, 150, 200));
    setPixel(4, 3, matrix.Color(150, 150, 200));
    setPixel(3, 4, matrix.Color(150, 150, 200));
    setPixel(4, 4, matrix.Color(150, 150, 200));

    // Draw second hand (red, smooth)
    for (float r = 0.8; r <= 2.5; r += 0.5) {
        int8_t hx = 3.5 + cos(angle) * r;
        int8_t hy = 3.5 + sin(angle) * r;

        if (hx >= 0 && hx < 8 && hy >= 0 && hy < 8) {
            setPixel(hx, hy, matrix.Color(255, 50, 50));  // Bright red hand
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Party Popper explosion
 */
static void animatePartyPopper() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t phase = (elapsed / 200) % 10;

    clearMatrix();

    if (phase < 3) {
        // Popper at bottom
        for (uint8_t y = 5; y < 8; y++) {
            setPixel(3, y, matrix.Color(200, 150, 0));
            setPixel(4, y, matrix.Color(200, 150, 0));
        }
    } else {
        // Explosion
        for (uint8_t i = 0; i < phase - 2; i++) {
            int8_t x = 4 + random(-i, i+1);
            int8_t y = 4 - i + random(-1, 2);
            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                uint32_t colors[] = {
                    matrix.Color(255, 0, 0),
                    matrix.Color(0, 255, 0),
                    matrix.Color(0, 0, 255),
                    matrix.Color(255, 255, 0)
                };
                setPixel(x, y, colors[random(0, 4)]);
            }
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Disco Ball
 */
static void animateDiscoBall() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t rotation = (elapsed / 150) % 16;

    clearMatrix();

    // Central ball
    for (int8_t y = 2; y < 6; y++) {
        for (int8_t x = 2; x < 6; x++) {
            setPixel(x, y, matrix.Color(200, 200, 200));
        }
    }

    // Rotating light rays
    for (uint8_t i = 0; i < 4; i++) {
        float angle = (rotation + i * 4) * PI / 8.0;
        for (uint8_t r = 3; r < 6; r++) {
            int8_t x = 4 + cos(angle) * r;
            int8_t y = 4 + sin(angle) * r;
            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                uint32_t color = (i % 2 == 0) ? matrix.Color(255, 0, 255) : matrix.Color(0, 255, 255);
                setPixel(x, y, color);
            }
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Easter Egg
 */
static void animateEasterEgg() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t colorPhase = (elapsed / 500) % 4;

    clearMatrix();

    uint32_t eggColors[] = {
        matrix.Color(255, 0, 0),
        matrix.Color(0, 255, 0),
        matrix.Color(0, 0, 255),
        matrix.Color(255, 255, 0)
    };

    drawPattern(EASTER_EGG_PATTERN, eggColors[colorPhase]);

    matrix.show();
}

/**
 * @brief Animation: Hopping Bunny - With animated eyes
 */
static void animateBunny() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t hopPhase = (elapsed / 300) % 4;
    uint8_t blinkPhase = (elapsed / 2000) % 10;  // Blink cycle

    clearMatrix();

    int8_t yOffset = (hopPhase == 1) ? -1 : 0;  // Hop up on phase 1

    // Draw bunny body (white)
    for (uint8_t y = 0; y < 8; y++) {
        uint8_t row = BUNNY_PATTERN[y];
        for (uint8_t x = 0; x < 8; x++) {
            if (row & (1 << (7 - x))) {
                int8_t newY = y + yOffset;
                if (newY >= 0 && newY < 8) {
                    setPixel(x, newY, matrix.Color(255, 255, 255));
                }
            }
        }
    }

    // Eyes (move with bunny, blink occasionally)
    int8_t eyeY = 2 + yOffset;  // Eyes at row 2
    if (eyeY >= 0 && eyeY < 8 && blinkPhase != 0) {  // Blink when phase == 0
        setPixel(2, eyeY, matrix.Color(0, 0, 0));  // Left eye (black)
        setPixel(5, eyeY, matrix.Color(0, 0, 0));  // Right eye (black)
    }

    // Pink nose (moves with bunny)
    int8_t noseY = 3 + yOffset;
    if (noseY >= 0 && noseY < 8) {
        setPixel(3, noseY, matrix.Color(255, 100, 150));
        setPixel(4, noseY, matrix.Color(255, 100, 150));
    }

    matrix.show();
}

/**
 * @brief Animation: Hatching Chick
 */
static void animateChick() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t phase = (elapsed / 500) % 6;

    clearMatrix();

    if (phase < 3) {
        // Egg
        drawPattern(EASTER_EGG_PATTERN, matrix.Color(255, 255, 200));
    } else {
        // Chick hatching
        drawPattern(CHICK_PATTERN, matrix.Color(255, 255, 0));
        // Eyes
        setPixel(2, 1, matrix.Color(0, 0, 0));
        setPixel(5, 1, matrix.Color(0, 0, 0));
        // Beak
        setPixel(3, 2, matrix.Color(255, 150, 0));
    }

    matrix.show();
}

/**
 * @brief Animation: Spring Flowers - Blooming flowers with petals opening/closing
 */
static void animateFlowers() {
    unsigned long elapsed = millis() - animationStartTime;
    float bloomPhase = (elapsed % 3000) / 3000.0;  // 0 to 1 bloom cycle

    clearMatrix();

    // Two flowers side by side
    for (uint8_t flowerNum = 0; flowerNum < 2; flowerNum++) {
        uint8_t cx = 2 + flowerNum * 4;  // Centers at x=2 and x=6
        uint8_t cy = 3;  // Center y

        // Blooming effect: 0=closed, 1=fully open
        float bloom = (sin(bloomPhase * TWO_PI + flowerNum * PI) + 1.0) / 2.0;

        // Yellow center (always visible)
        setPixel(cx, cy, matrix.Color(255, 255, 0));

        // 8 petals around center (open/close based on bloom phase)
        if (bloom > 0.3) {
            // 4 cardinal petals (pink/magenta)
            setPixel(cx - 1, cy, matrix.Color(255, 0, 255));  // Left
            setPixel(cx + 1, cy, matrix.Color(255, 0, 255));  // Right
            setPixel(cx, cy - 1, matrix.Color(255, 100, 200));  // Top
            setPixel(cx, cy + 1, matrix.Color(255, 100, 200));  // Bottom
        }

        if (bloom > 0.6) {
            // 4 diagonal petals (lighter pink) - only when fully blooming
            setPixel(cx - 1, cy - 1, matrix.Color(255, 150, 200));  // Top-left
            setPixel(cx + 1, cy - 1, matrix.Color(255, 150, 200));  // Top-right
            setPixel(cx - 1, cy + 1, matrix.Color(255, 150, 200));  // Bottom-left
            setPixel(cx + 1, cy + 1, matrix.Color(255, 150, 200));  // Bottom-right
        }

        // Green stem from flower down to bottom
        for (uint8_t y = cy + 1; y < 8; y++) {
            setPixel(cx, y, matrix.Color(0, 180, 0));
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Rainbow Wave - True sine wave effect with rainbow colors
 */
static void animateRainbowWave() {
    unsigned long elapsed = millis() - animationStartTime;
    float timeOffset = elapsed / 500.0;  // Slower movement for smoother wave

    clearMatrix();

    for (uint8_t x = 0; x < 8; x++) {
        // Create sine wave pattern
        float wave = sin((x * 0.8) + timeOffset) * 3.5 + 3.5;  // Wave from 0 to 7
        int8_t waveY = (int8_t)wave;

        // Rainbow color based on x position + time
        uint8_t hue = ((x * 32) + (uint8_t)(elapsed / 50)) % 256;
        uint32_t color;

        if (hue < 43) color = matrix.Color(255, hue * 6, 0);
        else if (hue < 85) color = matrix.Color(255 - (hue - 43) * 6, 255, 0);
        else if (hue < 128) color = matrix.Color(0, 255, (hue - 85) * 6);
        else if (hue < 171) color = matrix.Color(0, 255 - (hue - 128) * 6, 255);
        else if (hue < 214) color = matrix.Color((hue - 171) * 6, 0, 255);
        else color = matrix.Color(255, 0, 255 - (hue - 214) * 6);

        // Draw wave with vertical gradient
        for (int8_t y = 0; y < 8; y++) {
            int8_t dist = abs(y - waveY);
            if (dist == 0) {
                setPixel(x, y, color);  // Brightest at wave peak
            } else if (dist == 1) {
                setPixel(x, y, dimColor(color, 180));  // Slightly dimmer nearby
            } else if (dist == 2) {
                setPixel(x, y, dimColor(color, 80));  // Very dim
            }
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Sparkling Rain
 */
/**
 * @note FIX #6: Changed from modulo timing to threshold-based timing
 */
static void animateSparkleRain() {
    static unsigned long lastUpdate = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= 100) {
        lastUpdate = currentMillis;

        // Fade all pixels
        for (uint8_t i = 0; i < 64; i++) {
            matrix.setPixelColor(i, dimColor(matrix.getPixelColor(i), 200));
        }

        // Add new sparkles
        for (uint8_t i = 0; i < 3; i++) {
            uint8_t x = random(0, 8);
            uint8_t y = random(0, 8);
            uint32_t colors[] = {
                matrix.Color(255, 255, 255),
                matrix.Color(255, 255, 100),
                matrix.Color(200, 200, 255),
                matrix.Color(255, 200, 255)
            };
            setPixel(x, y, colors[random(0, 4)]);
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Plasma Effect
 */
static void animatePlasma() {
    unsigned long elapsed = millis() - animationStartTime;
    float time = elapsed / 1000.0;

    clearMatrix();

    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            float v = sin(x * 0.5 + time);
            v += sin(y * 0.5 + time);
            v += sin((x + y) * 0.5 + time);
            v += sin(sqrt(x * x + y * y) * 0.5 + time);
            v = (v + 4.0) / 8.0;

            uint8_t r = (uint8_t)(sin(v * PI) * 255);
            uint8_t g = (uint8_t)(sin(v * PI + 2.0) * 255);
            uint8_t b = (uint8_t)(sin(v * PI + 4.0) * 255);

            setPixel(x, y, matrix.Color(r, g, b));
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Matrix Digital Rain
 * Redesigned: Full height usage with multiple independent falling streams
 */
static void animateMatrixRain() {
    static unsigned long lastUpdate = 0;
    static uint8_t streamPos[8] = {0, 2, 4, 6, 1, 3, 5, 7};  // Staggered start positions
    static uint8_t streamSpeed[8];  // Different speeds for each column
    static bool initialized = false;

    unsigned long currentMillis = millis();

    if (!initialized) {
        for (uint8_t i = 0; i < 8; i++) {
            streamSpeed[i] = random(1, 4);  // Random speed 1-3
        }
        initialized = true;
    }

    if (currentMillis - lastUpdate >= 100) {
        lastUpdate = currentMillis;

        clearMatrix();

        // Draw each column as an independent stream
        for (uint8_t x = 0; x < 8; x++) {
            // Move stream down
            streamPos[x] += streamSpeed[x];
            if (streamPos[x] >= 16) {  // Reset when off screen
                streamPos[x] = 0;
                streamSpeed[x] = random(1, 4);
            }

            // Draw trailing characters with fade
            for (uint8_t i = 0; i < 8; i++) {
                int16_t y = streamPos[x] - i;
                if (y >= 0 && y < 8) {
                    uint8_t brightness;
                    if (i == 0) {
                        brightness = 255;  // Bright head
                    } else if (i == 1) {
                        brightness = 200;
                    } else if (i == 2) {
                        brightness = 150;
                    } else if (i == 3) {
                        brightness = 100;
                    } else {
                        brightness = max(0, 80 - i * 15);  // Fading tail
                    }
                    setPixel(x, y, matrix.Color(0, brightness, 0));
                }
            }
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Rotating Spiral
 */
static void animateSpiral() {
    unsigned long elapsed = millis() - animationStartTime;
    float rotation = (elapsed / 100.0) * 0.1;

    clearMatrix();

    for (uint8_t i = 0; i < 16; i++) {
        float angle = i * PI / 8.0 + rotation;
        float radius = i * 0.3;

        int8_t x = 3.5 + cos(angle) * radius;
        int8_t y = 3.5 + sin(angle) * radius;

        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            uint8_t brightness = 255 - i * 15;
            setPixel(x, y, matrix.Color(brightness, 0, 255 - brightness));
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Pulsing Heart
 */
static void animateHeart() {
    unsigned long elapsed = millis() - animationStartTime;
    float phase = (elapsed % 1000) / 1000.0;

    clearMatrix();

    // Pulsating brightness
    uint8_t brightness = (uint8_t)((sin(phase * 2.0 * PI) + 1.0) * 100 + 55);
    uint32_t color = matrix.Color(brightness, 0, brightness / 4);

    drawPattern(HEART_PATTERN, color);

    matrix.show();
}

/**
 * @brief Animation: Twinkling Stars Field
 * @note FIX #8: Changed from modulo timing to threshold-based timing
 */
static void animateStarsField() {
    static unsigned long lastUpdate = 0;
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= 200) {
        lastUpdate = currentMillis;

        // Slowly fade all stars
        for (uint8_t i = 0; i < 64; i++) {
            matrix.setPixelColor(i, dimColor(matrix.getPixelColor(i), 240));
        }

        // Add new twinkling stars
        for (uint8_t i = 0; i < 2; i++) {
            uint8_t x = random(0, 8);
            uint8_t y = random(0, 8);
            uint8_t brightness = random(150, 255);
            setPixel(x, y, matrix.Color(brightness, brightness, brightness));
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Campfire - Realistic fire simulation with heat propagation
 */
static void animateCampfire() {
    static unsigned long lastUpdate = 0;
    static uint8_t heat[64];  // Heat map for each pixel
    unsigned long currentMillis = millis();

    if (currentMillis - lastUpdate >= 60) {
        lastUpdate = currentMillis;

        // Cool down every cell a little
        for (uint8_t i = 0; i < 64; i++) {
            uint8_t cooling = random(0, 20);
            if (heat[i] > cooling) {
                heat[i] -= cooling;
            } else {
                heat[i] = 0;
            }
        }

        // Heat from bottom (fire source at bottom rows)
        for (uint8_t x = 0; x < 8; x++) {
            // Bottom two rows are the fire source
            if (random(0, 100) < 70) {
                heat[56 + x] = random(200, 255);  // Row 7 (bottom)
            }
            if (random(0, 100) < 60) {
                heat[48 + x] = random(180, 240);  // Row 6
            }
        }

        // Propagate heat upward with diffusion
        for (int8_t y = 0; y < 6; y++) {  // Don't process bottom 2 rows
            for (uint8_t x = 0; x < 8; x++) {
                uint8_t idx = y * 8 + x;
                uint8_t below = (y + 1) * 8 + x;

                // Heat rises from pixel below
                heat[idx] = (heat[idx] + heat[below] * 2) / 3;

                // Diffuse left/right slightly
                if (x > 0) heat[idx] = (heat[idx] * 3 + heat[idx - 1]) / 4;
                if (x < 7) heat[idx] = (heat[idx] * 3 + heat[idx + 1]) / 4;
            }
        }

        // Convert heat to color (red->orange->yellow->white for hottest)
        for (uint8_t y = 0; y < 8; y++) {
            for (uint8_t x = 0; x < 8; x++) {
                uint8_t h = heat[y * 8 + x];
                uint32_t color;

                if (h < 85) {
                    // Dark red to red
                    color = matrix.Color(h * 3, 0, 0);
                } else if (h < 170) {
                    // Red to orange
                    uint8_t t = (h - 85) * 3;
                    color = matrix.Color(255, t / 2, 0);
                } else {
                    // Orange to yellow/white
                    uint8_t t = (h - 170) * 3;
                    color = matrix.Color(255, 200 + t / 4, t / 2);
                }

                setPixel(x, y, color);
            }
        }

        matrix.show();
    }
}

/**
 * @brief Animation: Radar - Military green radar sweep with blips
 */
static void animateRadar() {
    static unsigned long lastUpdate = 0;
    static float angle = 0;
    static uint8_t blips[8][2];  // Store blip positions [x, y]
    static uint8_t blipAge[8];   // Age of each blip
    static unsigned long lastBlipAdd = 0;
    unsigned long currentMillis = millis();

    // Update radar sweep
    if (currentMillis - lastUpdate >= 50) {
        lastUpdate = currentMillis;
        angle += 0.2;
        if (angle >= TWO_PI) angle = 0;

        clearMatrix();

        // Draw radar grid (faint green circles)
        for (uint8_t r = 1; r <= 3; r++) {
            for (float a = 0; a < TWO_PI; a += PI / 16) {
                int8_t x = 3.5 + cos(a) * r;
                int8_t y = 3.5 + sin(a) * r;
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    setPixel(x, y, matrix.Color(0, 20, 0));
                }
            }
        }

        // Draw center point
        setPixel(3, 3, matrix.Color(0, 100, 0));
        setPixel(4, 3, matrix.Color(0, 100, 0));
        setPixel(3, 4, matrix.Color(0, 100, 0));
        setPixel(4, 4, matrix.Color(0, 100, 0));

        // Draw radar sweep line (bright green)
        for (float r = 0; r < 4; r += 0.3) {
            int8_t x = 3.5 + cos(angle) * r;
            int8_t y = 3.5 + sin(angle) * r;
            if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                uint8_t brightness = 255 - (r * 40);
                setPixel(x, y, matrix.Color(0, brightness, 0));
            }
        }

        // Draw fading trail behind sweep
        for (float trailAngle = angle - 0.5; trailAngle > angle - PI; trailAngle -= 0.15) {
            float dist = angle - trailAngle;
            uint8_t brightness = 100 - (dist * 60);
            if (brightness > 100) brightness = 0;

            for (float r = 1; r < 4; r += 0.5) {
                int8_t x = 3.5 + cos(trailAngle) * r;
                int8_t y = 3.5 + sin(trailAngle) * r;
                if (x >= 0 && x < 8 && y >= 0 && y < 8) {
                    uint32_t existing = getPixel(x, y);
                    if ((existing & 0xFF00) >> 8 < brightness) {
                        setPixel(x, y, matrix.Color(0, brightness, 0));
                    }
                }
            }
        }

        // Add new blip occasionally
        if (currentMillis - lastBlipAdd > 2000 && random(0, 100) < 30) {
            for (uint8_t i = 0; i < 8; i++) {
                if (blipAge[i] == 0) {
                    blips[i][0] = random(0, 8);
                    blips[i][1] = random(0, 8);
                    blipAge[i] = 255;
                    lastBlipAdd = currentMillis;
                    break;
                }
            }
        }

        // Draw and age blips
        for (uint8_t i = 0; i < 8; i++) {
            if (blipAge[i] > 0) {
                // Draw blip as bright dot
                setPixel(blips[i][0], blips[i][1], matrix.Color(0, blipAge[i], 0));

                // Age the blip (fade out)
                if (blipAge[i] > 8) {
                    blipAge[i] -= 8;
                } else {
                    blipAge[i] = 0;
                }
            }
        }

        matrix.show();
    }
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
    matrix.show();  // Clear all pixels

    // Load saved settings from NVS
    loadMatrix8x8Settings();

    // Apply loaded brightness
    matrix.setBrightness(matrixBrightness);

    // Start with selected animation
    animationStartTime = millis();
    matrixEnabled = true;

    LOG_PRINTF("✓ 8x8 Matrix initialized - Starting with: %s (brightness: %d)\n",
               animationNames[currentAnimation], matrixBrightness);
}

void updateMatrix8x8() {
    // Get current garland mode to determine matrix behavior
    GarlandMode mode = getGarlandMode();

    // In MODE_MOTION_TRIGGER, matrix follows garland state
    // In MODE_MOTION_MATRIX_INDEPENDENT and MODE_PERMANENT, matrix is independent
    bool matrixShouldBeOn = (currentAnimation != MATRIX_ANIM_OFF) && (currentAnimation != MATRIX_ANIM_AUTO || autoModeActive);

    if (mode == MODE_MOTION_TRIGGER) {
        // Matrix follows garland state in this mode
        // IMPORTANT: Don't use matrixEnabled here - it should turn back on automatically
        matrixShouldBeOn = matrixShouldBeOn && isGarlandEnabled();
    } else {
        // In other modes, respect the matrixEnabled flag
        matrixShouldBeOn = matrixShouldBeOn && matrixEnabled;
    }

    if (!matrixShouldBeOn) {
        // Clear matrix but DON'T set matrixEnabled = false
        // This allows matrix to turn back on when motion is detected
        clearMatrix();
        matrix.show();
        return;
    }

    // Auto mode: cycle through animations (excluding OFF and AUTO)
    // Uses the same interval as garland auto mode (configurable via web UI)
    if (autoModeActive) {
        unsigned long elapsed = millis() - autoModeChangeTime;
        unsigned long interval = getAutoAnimationIntervalMs();  // Shared with garland
        if (elapsed > interval) {
            // Move to next animation
            uint8_t nextAnim = (uint8_t)activeAnimation + 1;
            // Skip OFF (0) and AUTO (last), cycle from STAR (1) to RADAR (last-1)
            if (nextAnim == MATRIX_ANIM_OFF || nextAnim >= MATRIX_ANIM_AUTO) {
                nextAnim = MATRIX_ANIM_STAR;  // Loop back to first real animation
            }
            activeAnimation = (Matrix8x8Animation)nextAnim;
            animationStartTime = millis();
            autoModeChangeTime = millis();
            LOG_PRINTF("Auto Mode: Switched to %s (interval: %lu ms)\n", animationNames[activeAnimation], interval);
        }
    }

    // Execute current animation (use activeAnimation in auto mode, currentAnimation otherwise)
    Matrix8x8Animation animToExecute = autoModeActive ? activeAnimation : currentAnimation;

    switch (animToExecute) {
        // Original animations
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
        // Christmas animations
        case MATRIX_ANIM_CANDY_CANE:
            animateCandyCane();
            break;
        case MATRIX_ANIM_WREATH:
            animateWreath();
            break;
        case MATRIX_ANIM_STOCKING:
            animateStocking();
            break;
        case MATRIX_ANIM_REINDEER:
            animateReindeer();
            break;
        case MATRIX_ANIM_GINGERBREAD:
            animateGingerbread();
            break;
        case MATRIX_ANIM_HOT_COCOA:
            animateHotCocoa();
            break;
        case MATRIX_ANIM_FIREPLACE:
            animateFireplace();
            break;
        case MATRIX_ANIM_NORTHERN_LIGHTS:
            animateNorthernLights();
            break;
        case MATRIX_ANIM_PRESENTS:
            animatePresents();
            break;
        // New Year animations
        case MATRIX_ANIM_FIREWORKS:
            animateFireworks();
            break;
        case MATRIX_ANIM_CHAMPAGNE:
            animateChampagne();
            break;
        case MATRIX_ANIM_COUNTDOWN:
            animateCountdown();
            break;
        case MATRIX_ANIM_CONFETTI:
            animateConfetti();
            break;
        case MATRIX_ANIM_CLOCK:
            animateClock();
            break;
        case MATRIX_ANIM_PARTY_POPPER:
            animatePartyPopper();
            break;
        case MATRIX_ANIM_DISCO_BALL:
            animateDiscoBall();
            break;
        // Easter animations
        case MATRIX_ANIM_EASTER_EGG:
            animateEasterEgg();
            break;
        case MATRIX_ANIM_BUNNY:
            animateBunny();
            break;
        case MATRIX_ANIM_CHICK:
            animateChick();
            break;
        case MATRIX_ANIM_FLOWERS:
            animateFlowers();
            break;
        // Abstract/Modern animations
        case MATRIX_ANIM_RAINBOW_WAVE:
            animateRainbowWave();
            break;
        case MATRIX_ANIM_SPARKLE_RAIN:
            animateSparkleRain();
            break;
        case MATRIX_ANIM_PLASMA:
            animatePlasma();
            break;
        case MATRIX_ANIM_MATRIX_RAIN:
            animateMatrixRain();
            break;
        case MATRIX_ANIM_SPIRAL:
            animateSpiral();
            break;
        case MATRIX_ANIM_HEART:
            animateHeart();
            break;
        case MATRIX_ANIM_STARS_FIELD:
            animateStarsField();
            break;
        case MATRIX_ANIM_CAMPFIRE:
            animateCampfire();
            break;
        case MATRIX_ANIM_RADAR:
            animateRadar();
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
        autoModeActive = false;
        matrix8x8Off();
    } else if (animation == MATRIX_ANIM_AUTO) {
        // Enable auto mode
        autoModeActive = true;
        activeAnimation = MATRIX_ANIM_STAR;  // Start with first real animation
        autoModeChangeTime = millis();
        matrixEnabled = true;
        LOG_PRINTF("Auto Mode activated: Starting with %s\n", animationNames[activeAnimation]);
    } else {
        // Specific animation selected
        autoModeActive = false;
        activeAnimation = animation;
        matrixEnabled = true;
        // Force immediate display of first frame
        clearMatrix();
        matrix.show();
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
