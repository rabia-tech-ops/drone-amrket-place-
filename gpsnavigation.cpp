#include "GPSNavigation.h"
#include "ConsoleUI.h"

#include <iostream>

using namespace std;

// ==========================================
// Constructor
// ==========================================

GPSNavigation::GPSNavigation(
    string src,
    string dest
)
    : NavigationSystem(src, dest)
{
}

// ==========================================
// GPS Route Calculation
// ==========================================

void GPSNavigation::calculateRoute() {

    cout << CYAN << BOLD;

    cout << "\n╔════════════════════════════════════╗\n";
    cout << "║          GPS NAVIGATION           ║\n";
    cout << "╚════════════════════════════════════╝\n";

    cout << RESET;

    cout << "Source      : "
        << source << endl;

    cout << "Destination : "
        << destination << endl;

    loadingBar("Connecting to GPS satellites...");

    cout << GREEN;

    cout << "\nRoute          : Highway Route 7\n";
    cout << "Estimated Time : 25 Minutes\n";
    cout << "GPS Status     : Connected\n";

    cout << RESET;
}
