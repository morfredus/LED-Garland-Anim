/**
 * @file matrix8x8_control.cpp
 * @brief Implementation of 8x8 NeoPixel matrix control with festive animations
 * @version 1.7.0
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
    "Icicles",
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
    "Stars Field"
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

// Stocking pattern
static const uint8_t STOCKING_PATTERN[] = {
    0b00011000,
    0b00111100,
    0b00011000,
    0b00011000,
    0b00011000,
    0b01111110,
    0b11111111,
    0b11111111
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

/**
 * @brief Animation: Candy Cane with rotating stripes
 */
static void animateCandyCane() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t offset = (elapsed / 150) % 8;

    clearMatrix();

    // Draw diagonal red and white stripes
    for (uint8_t y = 0; y < 8; y++) {
        for (uint8_t x = 0; x < 8; x++) {
            if ((x + y + offset) % 2 == 0) {
                setPixel(x, y, matrix.Color(255, 0, 0));  // Red
            } else {
                setPixel(x, y, matrix.Color(255, 255, 255));  // White
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
static void animateStocking() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t phase = (elapsed / 200) % 6;

    clearMatrix();

    // Slight swing effect
    int8_t offset = 0;
    if (phase == 1 || phase == 2) offset = -1;
    else if (phase == 4 || phase == 5) offset = 1;

    // Draw red stocking
    for (uint8_t y = 0; y < 8; y++) {
        uint8_t row = STOCKING_PATTERN[y];
        for (uint8_t x = 0; x < 8; x++) {
            if (row & (1 << (7 - x))) {
                int8_t newX = x + offset;
                if (newX >= 0 && newX < 8) {
                    setPixel(newX, y, matrix.Color(255, 0, 0));
                }
            }
        }
    }

    // White cuff
    for (int8_t x = 1 + offset; x < 6 + offset; x++) {
        if (x >= 0 && x < 8) {
            setPixel(x, 0, matrix.Color(255, 255, 255));
            setPixel(x, 1, matrix.Color(255, 255, 255));
        }
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
 * @brief Animation: Hanging Icicles
 */
static void animateIcicles() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t phase = (elapsed / 100) % 8;

    clearMatrix();

    // Draw icicles hanging from top
    for (uint8_t x = 0; x < 8; x += 2) {
        uint8_t length = 3 + (x % 3);
        for (uint8_t y = 0; y < length; y++) {
            uint8_t brightness = 200 - y * 30;
            setPixel(x, y, matrix.Color(brightness, brightness, 255));
        }
    }

    // Dripping effect
    if (phase < 6) {
        setPixel(phase, 5, matrix.Color(150, 150, 255));
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
 */
static void animateChampagne() {
    unsigned long elapsed = millis() - animationStartTime;

    if (elapsed % 150 == 0) {
        // Move bubbles up
        for (int8_t y = 0; y < 7; y++) {
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
 */
static void animateCountdown() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t number = 3 - ((elapsed / 1000) % 4);

    clearMatrix();

    if (number == 3) {
        // Draw "3"
        for (uint8_t y = 0; y < 7; y++) {
            setPixel(2, y, matrix.Color(255, 255, 0));
            setPixel(5, y, matrix.Color(255, 255, 0));
        }
        setPixel(3, 0, matrix.Color(255, 255, 0));
        setPixel(4, 0, matrix.Color(255, 255, 0));
        setPixel(3, 3, matrix.Color(255, 255, 0));
        setPixel(4, 3, matrix.Color(255, 255, 0));
        setPixel(3, 6, matrix.Color(255, 255, 0));
        setPixel(4, 6, matrix.Color(255, 255, 0));
    } else if (number == 2) {
        // Draw "2"
        for (uint8_t x = 2; x <= 5; x++) {
            setPixel(x, 0, matrix.Color(255, 255, 0));
            setPixel(x, 3, matrix.Color(255, 255, 0));
            setPixel(x, 6, matrix.Color(255, 255, 0));
        }
        setPixel(5, 1, matrix.Color(255, 255, 0));
        setPixel(5, 2, matrix.Color(255, 255, 0));
        setPixel(2, 4, matrix.Color(255, 255, 0));
        setPixel(2, 5, matrix.Color(255, 255, 0));
    } else if (number == 1) {
        // Draw "1"
        for (uint8_t y = 0; y < 7; y++) {
            setPixel(4, y, matrix.Color(255, 255, 0));
        }
        setPixel(3, 1, matrix.Color(255, 255, 0));
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
 */
static void animateConfetti() {
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
 * @brief Animation: Clock at midnight
 */
static void animateClock() {
    unsigned long elapsed = millis() - animationStartTime;
    float angle = (elapsed % 12000) / 12000.0 * 2.0 * PI;

    clearMatrix();

    // Clock circle
    for (uint8_t i = 0; i < 8; i++) {
        float a = i * PI / 4.0;
        int8_t x = 3.5 + cos(a) * 3;
        int8_t y = 3.5 + sin(a) * 3;
        if (x >= 0 && x < 8 && y >= 0 && y < 8) {
            setPixel(x, y, matrix.Color(255, 255, 255));
        }
    }

    // Clock hand
    int8_t hx = 3.5 + cos(angle - PI/2) * 2.5;
    int8_t hy = 3.5 + sin(angle - PI/2) * 2.5;
    setPixel(3, 3, matrix.Color(255, 0, 0));
    setPixel(4, 4, matrix.Color(255, 0, 0));
    if (hx >= 0 && hx < 8 && hy >= 0 && hy < 8) {
        setPixel(hx, hy, matrix.Color(255, 0, 0));
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
 * @brief Animation: Hopping Bunny
 */
static void animateBunny() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t hopPhase = (elapsed / 300) % 4;

    clearMatrix();

    int8_t yOffset = (hopPhase == 1) ? -1 : 0;

    // Draw bunny with hop effect
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

    // Pink nose
    setPixel(3, 3 + yOffset, matrix.Color(255, 100, 150));
    setPixel(4, 3 + yOffset, matrix.Color(255, 100, 150));

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
 * @brief Animation: Spring Flowers blooming
 */
static void animateFlowers() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t bloomPhase = (elapsed / 400) % 8;

    clearMatrix();

    // Multiple flowers at different bloom stages
    for (uint8_t i = 0; i < 3; i++) {
        uint8_t cx = 1 + i * 3;
        uint8_t cy = 4;
        uint8_t size = min(bloomPhase + i, 3);

        // Flower center
        setPixel(cx, cy, matrix.Color(255, 255, 0));

        // Petals
        if (size > 0) {
            setPixel(cx - 1, cy, matrix.Color(255, 0, 255));
            setPixel(cx + 1, cy, matrix.Color(255, 0, 255));
        }
        if (size > 1) {
            setPixel(cx, cy - 1, matrix.Color(255, 100, 200));
            setPixel(cx, cy + 1, matrix.Color(255, 100, 200));
        }

        // Stem
        for (uint8_t y = cy + 1; y < 8; y++) {
            setPixel(cx, y, matrix.Color(0, 150, 0));
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Rainbow Wave
 */
static void animateRainbowWave() {
    unsigned long elapsed = millis() - animationStartTime;
    uint8_t offset = (elapsed / 100) % 8;

    clearMatrix();

    for (uint8_t x = 0; x < 8; x++) {
        uint8_t hue = ((x + offset) * 32) % 256;
        uint32_t color;

        if (hue < 43) color = matrix.Color(255, hue * 6, 0);
        else if (hue < 85) color = matrix.Color(255 - (hue - 43) * 6, 255, 0);
        else if (hue < 128) color = matrix.Color(0, 255, (hue - 85) * 6);
        else if (hue < 171) color = matrix.Color(0, 255 - (hue - 128) * 6, 255);
        else if (hue < 214) color = matrix.Color((hue - 171) * 6, 0, 255);
        else color = matrix.Color(255, 0, 255 - (hue - 214) * 6);

        for (uint8_t y = 0; y < 8; y++) {
            setPixel(x, y, color);
        }
    }

    matrix.show();
}

/**
 * @brief Animation: Sparkling Rain
 */
static void animateSparkleRain() {
    unsigned long elapsed = millis() - animationStartTime;

    if (elapsed % 100 == 0) {
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
 */
static void animateMatrixRain() {
    unsigned long elapsed = millis() - animationStartTime;

    if (elapsed % 150 == 0) {
        // Move everything down
        for (int8_t y = 7; y > 0; y--) {
            for (uint8_t x = 0; x < 8; x++) {
                setPixel(x, y, getPixel(x, y - 1));
            }
        }

        // Add new characters at top
        for (uint8_t x = 0; x < 8; x++) {
            if (random(0, 100) > 70) {
                uint8_t brightness = random(100, 255);
                setPixel(x, 0, matrix.Color(0, brightness, 0));
            } else {
                setPixel(x, 0, 0);
            }
        }

        // Fade existing pixels
        for (uint8_t i = 0; i < 64; i++) {
            matrix.setPixelColor(i, dimColor(matrix.getPixelColor(i), 220));
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
 */
static void animateStarsField() {
    unsigned long elapsed = millis() - animationStartTime;

    if (elapsed % 200 == 0) {
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
    if (!matrixEnabled || currentAnimation == MATRIX_ANIM_OFF) {
        matrix8x8Off();
        return;
    }

    // Execute current animation
    switch (currentAnimation) {
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
        case MATRIX_ANIM_ICICLES:
            animateIcicles();
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
