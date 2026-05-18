#include "AINavigation.h"
#include "ConsoleUI.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

AINavigation::AINavigation(string src, string dest)
    : NavigationSystem(src, dest)
{
}

// ==========================================
// AI Route Calculation
// ==========================================

void AINavigation::calculateRoute() {

    cout << MAGENTA << BOLD;

    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║        AI NAVIGATION CENTER        ║\n";
    cout << "╚════════════════════════════════════╝\n";

    cout << RESET;

    cout << "Source      : " << source << endl;
    cout << "Destination : " << destination << endl;

    loadingBar("AI scanning air routes...");

    cout << GREEN;
    cout << "\nOptimal Route : Sector A-12\n";
    cout << "Estimated Time: 22 Minutes\n";
    cout << "Route Status  : Safe & Clear\n";
    cout << RESET;
}
