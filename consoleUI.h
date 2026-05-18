#ifndef CONSOLEUI_H
#define CONSOLEUI_H

// ==========================================
// Windows Console UI System
// Colors + Loading Bars + UI Helpers
// ==========================================

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <iostream>
#include <string>

using namespace std;

// ==========================================
// Console Colors
// ==========================================

enum ConsoleColor {

    COL_DEFAULT = 7,
    COL_RED = 12,
    COL_GREEN = 10,
    COL_YELLOW = 14,
    COL_CYAN = 11,
    COL_MAGENTA = 13,
    COL_BRIGHT = 15,

    // ======================================
    // BASIC EXTRA COLORS
    // ======================================

    COL_BLACK = 0,
    COL_BLUE = 9,
    COL_WHITE = 15,

    COL_DARK_RED = 4,
    COL_DARK_GREEN = 2,
    COL_DARK_BLUE = 1,
    COL_DARK_CYAN = 3,
    COL_DARK_YELLOW = 6,
    COL_GRAY = 8,

    // ======================================
    // NEW UI / MODERN COLORS (ADDED)
    // ======================================

    COL_NAVY = 1,
    COL_TEAL = 3,
    COL_OLIVE = 6,
    COL_SILVER = 7,
    COL_DARK_GRAY = 8,
    COL_SKY_BLUE = 9,
    COL_LIME = 10,
    COL_AQUA = 11,
    COL_CRIMSON = 12,
    COL_PINK = 13,
    COL_AMBER = 14,
    COL_BRIGHT_WHITE = 15
};

// ==========================================
// Set Console Color
// ==========================================

inline void setColor(int c) {

    SetConsoleTextAttribute(
        GetStdHandle(STD_OUTPUT_HANDLE),
        (WORD)c
    );
}

// ==========================================
// Enable Colors
// ==========================================

inline void enableColors() {
}

// ==========================================
// Color Structures
// ==========================================

struct ConColor {

    int code;

    ConColor(int c) {
        code = c;
    }
};

struct ConReset {
};

// ==========================================
// Operator Overloading
// ==========================================

inline ostream& operator<<(ostream& os, ConColor c) {

    setColor(c.code);
    return os;
}

inline ostream& operator<<(ostream& os, ConReset) {

    setColor(COL_DEFAULT);
    return os;
}

// ==========================================
// BASIC COLOR MACROS
// ==========================================

#define RED      ConColor(COL_RED)
#define GREEN    ConColor(COL_GREEN)
#define YELLOW   ConColor(COL_YELLOW)
#define CYAN     ConColor(COL_CYAN)
#define MAGENTA  ConColor(COL_MAGENTA)
#define BOLD     ConColor(COL_BRIGHT)
#define RESET    ConReset()

// ==========================================
// ADDED COLOR MACROS
// ==========================================

#define BLUE        ConColor(COL_BLUE)
#define WHITE       ConColor(COL_WHITE)
#define BLACK       ConColor(COL_BLACK)

#define DARKRED     ConColor(COL_DARK_RED)
#define DARKGREEN   ConColor(COL_DARK_GREEN)
#define DARKBLUE    ConColor(COL_DARK_BLUE)
#define DARKCYAN    ConColor(COL_DARK_CYAN)
#define DARKYELLOW  ConColor(COL_DARK_YELLOW)

#define GRAY        ConColor(COL_GRAY)

// ==========================================
// NEW UI STYLE MACROS (ADDED)
// ==========================================

#define NAVY        ConColor(COL_NAVY)
#define TEAL        ConColor(COL_TEAL)
#define OLIVE       ConColor(COL_OLIVE)
#define SILVER      ConColor(COL_SILVER)
#define DARKGRAY    ConColor(COL_DARK_GRAY)
#define SKYBLUE     ConColor(COL_SKY_BLUE)
#define LIME        ConColor(COL_LIME)
#define AQUA        ConColor(COL_AQUA)
#define CRIMSON     ConColor(COL_CRIMSON)
#define PINK        ConColor(COL_PINK)
#define AMBER       ConColor(COL_AMBER)
#define BWHITE      ConColor(COL_BRIGHT_WHITE)

// ==========================================
// Pause Screen
// ==========================================

inline void pauseScreen() {

    cout << YELLOW;
    cout << "\nPress Enter to continue...";
    cout << RESET;

    cin.clear();
    cin.ignore(10000, '\n');
    cin.get();
}

// ==========================================
// Loading Bar Animation
// ==========================================

inline void loadingBar(string msg) {

    cout << CYAN << msg << RESET << endl;

    cout << "[";

    for (int i = 0; i < 20; i++) {

        cout << "#";
        Sleep(80);
    }

    cout << "] 100%\n";

    cout << GREEN << "Done Successfully!\n" << RESET;
}

// ==========================================
// Simple Line Divider
// ==========================================

inline void line() {

    cout << "==================================================\n";
}

#endif
