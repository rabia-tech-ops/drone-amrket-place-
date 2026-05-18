#include "FleetManager.h"
#include "SurveillanceDrone.h"
#include "DeliveryDrone.h"
#include "ConsoleUI.h"

#include <iostream>
#include <iomanip>

using namespace std;

// ==========================================
// Constructor
// ==========================================

FleetManager::FleetManager() {

    totalDrones = 0;
    isVIP       = false;

    for (int i = 0; i < 100; i++) {
        droneReviews[i]   = "No review yet.";
        droneInsurance[i] = "Not insured";
    }

    loadSampleDrones();
}

// ==========================================
// Destructor
// ==========================================

FleetManager::~FleetManager() {

    for (int i = 0; i < totalDrones; i++) {
        delete drones[i];
    }
}

// ==========================================
// Load Sample Drones  (7 drones : 3 Rented)
// ==========================================

void FleetManager::loadSampleDrones() {

    drones[totalDrones++] =
        new SurveillanceDrone("D101", "SkyCam Pro",  "Wedding",      6,  80,  220000, "4K HD");

    drones[totalDrones++] =
        new DeliveryDrone    ("D102", "MediFly X",   "Emergency",    8,  120, 450000, 5.0);

    drones[totalDrones++] =
        new SurveillanceDrone("D103", "Hawk Eye",    "Surveillance", 10, 100, 390000, "8K");

    drones[totalDrones++] =
        new DeliveryDrone    ("D104", "FoodExpress", "Delivery",     5,  90,  250000, 3.0);

    drones[totalDrones++] =
        new DeliveryDrone    ("D105", "AgroFly Pro", "Farming",      7,  70,  310000, 8.0);

    drones[totalDrones++] =
        new SurveillanceDrone("D106", "NightWatch",  "Surveillance", 9,  95,  370000, "4K");

    drones[totalDrones++] =
        new DeliveryDrone    ("D107", "SwiftCarry",  "Delivery",     6,  85,  275000, 4.5);

    // Three pre-rented drones
    drones[2]->setStatus("Rented");
    drones[5]->setStatus("Rented");
    drones[6]->setStatus("Rented");

    // Sample reviews
    droneReviews[0] = "Stunning 4K footage at our wedding!";
    droneReviews[1] = "Arrived in minutes, very reliable.";
    droneReviews[2] = "Crystal-clear 8K surveillance feed.";
    droneReviews[3] = "Delivered meals hot and on time.";
    droneReviews[4] = "Handled heavy crop loads with ease.";
    droneReviews[5] = "Excellent night vision, highly trusted.";
    droneReviews[6] = "Fast and sturdy for daily deliveries.";

    // Sample insurance (duration in years)
    droneInsurance[0] = "2 Years  (Jun 2025 - Jun 2027)";
    droneInsurance[1] = "1 Year   (Jan 2025 - Jan 2026)";
    droneInsurance[2] = "2 Years  (Mar 2025 - Mar 2027)";
    droneInsurance[3] = "Not insured";
    droneInsurance[4] = "3 Years  (Sep 2025 - Sep 2028)";
    droneInsurance[5] = "1 Year   (Apr 2025 - Apr 2026)";
    droneInsurance[6] = "Not insured";
}

// ==========================================
// Internal Helper : LIVE DRONE MARKETPLACE table
// ==========================================

void FleetManager::drawTable() {

    cout << CYAN << BOLD;
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                          LIVE DRONE MARKETPLACE                                  ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════════╣\n";

    // Header
    cout << "║ "
         << left
         << setw(5)  << "ID"
         << " │ " << setw(13) << "NAME"
         << " │ " << setw(12) << "PURPOSE"
         << " │ " << setw(4)  << "BAT"
         << " │ " << setw(9)  << "SPEED"
         << " │ " << setw(11) << "PRICE"
         << " │ " << setw(9)  << "STATUS"
         << " ║\n";

    cout << "╠══════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << RESET;

    // Rows
    for (int i = 0; i < totalDrones; i++) {

        Drone*  d      = drones[i];
        string  status = d->getStatus();
        string  bat    = to_string(d->getBattery()) + "h";
        string  speed  = to_string(d->getSpeed())   + " KM/H";
        string  price  = "Rs." + to_string((int)d->getPrice());

        if      (status == "Rented")  cout << RED;
        else if (status == "Sold")    cout << YELLOW;
        else                          cout << GREEN;

        cout << "║ "
             << left
             << setw(5)  << d->getId()
             << " │ " << setw(13) << d->getName()
             << " │ " << setw(12) << d->getPurpose()
             << " │ " << setw(4)  << bat
             << " │ " << setw(9)  << speed
             << " │ " << setw(11) << price
             << " │ " << setw(9)  << status
             << " ║\n";

        cout << RESET;
    }

    cout << CYAN;
    cout << "╚══════════════════════════════════════════════════════════════════════════════════╝\n";
    cout << RESET;
}

// ==========================================
// Option 1 : showTable
// Directly shows the marketplace table —
// NO sub-menu, just the table.
// ==========================================

void FleetManager::showTable() {

    drawTable();
}

// ==========================================
// Option 2 : Buy Drone
// Table → Enter ID → show price →
// payment choice → success message
// ==========================================

void FleetManager::buyDroneMenu() {

    // Show full table first
    drawTable();

    // Enter drone ID
    string id;
  
    cout << "\nEnter Drone ID to Buy : ";
    cin  >> id;

    Drone* d = findById(id);

    if (d == NULL) {
        cout << RED << "\n[ERROR] Drone ID not found!\n" << RESET;
        return;
    }

    if (d->getStatus() == "Rented") {
        cout << RED << "\n[ERROR] This drone is currently Rented. Cannot purchase.\n" << RESET;
        return;
    }

    if (d->getStatus() == "Sold") {
        cout << RED << "\n[ERROR] This drone is already Sold!\n" << RESET;
        return;
    }

    // Calculate total (VIP gets 15% off)
    double total = d->getPrice();
    if (isVIP) total = total * 0.85;

    // Order summary box
    cout << YELLOW << BOLD;
    cout << "\n╔══════════════════════════════════════════╗\n";
    cout << "║             ORDER SUMMARY                ║\n";
    cout << "╠══════════════════════════════════════════╣\n";
    cout << "║  Drone   : " << left << setw(30) << d->getName()    << "║\n";
    cout << "║  Purpose : " << left << setw(30) << d->getPurpose() << "║\n";
    cout << "║  Battery : " << left << setw(30) << (to_string(d->getBattery()) + "h") << "║\n";
    cout << "║  Speed   : " << left << setw(30) << (to_string(d->getSpeed()) + " KM/H") << "║\n";

    if (isVIP) {
        cout << "║  Price   : Rs." << left << setw(27) << (int)d->getPrice() << "║\n";
        cout << "║  VIP 15% : -Rs." << left << setw(26) << (int)(d->getPrice() * 0.15) << "║\n";
        cout << "║  TOTAL   : Rs." << left << setw(27) << (int)total << "║\n";
    } else {
        cout << "║  TOTAL   : Rs." << left << setw(27) << (int)total << "║\n";
    }

    cout << "╚══════════════════════════════════════════╝\n";
    cout << RESET;

    // Payment method
    cout << CYAN << BOLD;
    cout << "\n╔══════════════════════════════════════════╗\n";
    cout << "║          SELECT PAYMENT METHOD           ║\n";
    cout << "╠══════════════════════════════════════════╣\n";
    cout << "║   1. Cash on Delivery                    ║\n";
    cout << "║   2. PayPal                              ║\n";
    cout << "║   3. Card                                ║\n";
    cout << "╚══════════════════════════════════════════╝\n";
    cout << RESET;

    cout << "\nEnter Payment Choice : ";
    int pay;
    cin  >> pay;

    string payMethod;

    if      (pay == 1) payMethod = "Cash on Delivery";
    else if (pay == 2) payMethod = "PayPal";
    else if (pay == 3) payMethod = "Card";
    else {
        cout << RED << "\n[ERROR] Invalid payment choice!\n" << RESET;
        return;
    }

    // Mark drone as Sold
    d->setStatus("Sold");

    // Success message
    cout << GREEN << BOLD;
    cout << "\n╔══════════════════════════════════════════╗\n";
    cout << "║        ORDER PLACED SUCCESSFULLY!        ║\n";
    cout << "╠══════════════════════════════════════════╣\n";
    cout << "║  Drone   : " << left << setw(30) << d->getName()  << "║\n";
    cout << "║  Payment : " << left << setw(30) << payMethod      << "║\n";
    cout << "║  Amount  : Rs." << left << setw(27) << (int)total  << "║\n";
    cout << "║  Status  : Sold                          ║\n";
    cout << "║                                          ║\n";
    cout << "║   Thank you for your purchase!           ║\n";
    cout << "╚══════════════════════════════════════════╝\n";
    cout << RESET;
}

// ==========================================
// Option 3 : Rent Drone
// Table → Enter ID → enter days →
// show rental price → payment → success
// ==========================================

void FleetManager::rentDroneMenu() {

    // Show full marketplace table first
    drawTable();

    // Enter drone ID
    string id;
    cout << "\nEnter Drone ID to Rent : ";
    cin  >> id;

    Drone* d = findById(id);

    if (d == NULL) {
        cout << RED << "\n[ERROR] Drone ID not found!\n" << RESET;
        return;
    }

    if (d->getStatus() == "Rented") {
        cout << RED << "\n[ERROR] This drone is already Rented!\n" << RESET;
        return;
    }

    if (d->getStatus() == "Sold") {
        cout << RED << "\n[ERROR] This drone is Sold, not available for rent.\n" << RESET;
        return;
    }

    // Enter rental days
    int days;
    cout << "Enter Number of Rental Days : ";
    cin  >> days;

    if (days <= 0) {
        cout << RED << "\n[ERROR] Invalid number of days!\n" << RESET;
        return;
    }

    // Daily rate = 1% of price
    double dailyRate = d->getPrice() * 0.01;
    double total     = dailyRate * days;
    if (isVIP) total = total * 0.85;

    // Rental summary box
    cout << YELLOW << BOLD;
    cout << "\n╔══════════════════════════════════════════╗\n";
    cout << "║            RENTAL SUMMARY                ║\n";
    cout << "╠══════════════════════════════════════════╣\n";
    cout << "║  Drone      : " << left << setw(27) << d->getName()                       << "║\n";
    cout << "║  Purpose    : " << left << setw(27) << d->getPurpose()                    << "║\n";
    cout << "║  Battery    : " << left << setw(27) << (to_string(d->getBattery()) + "h") << "║\n";
    cout << "║  Speed      : " << left << setw(27) << (to_string(d->getSpeed()) + " KM/H") << "║\n";
    cout << "║  Daily Rate : Rs." << left << setw(24) << (int)dailyRate                  << "║\n";
    cout << "║  Days       : " << left << setw(27) << days                               << "║\n";

    if (isVIP) {
        cout << "║  VIP 15%   : -Rs." << left << setw(24) << (int)(dailyRate * days * 0.15) << "║\n";
    }

    cout << "║  TOTAL      : Rs." << left << setw(24) << (int)total << "║\n";
    cout << "╚══════════════════════════════════════════╝\n";
    cout << RESET;

    // Payment method
    cout << CYAN << BOLD;
    cout << "\n╔══════════════════════════════════════════╗\n";
    cout << "║          SELECT PAYMENT METHOD           ║\n";
    cout << "╠══════════════════════════════════════════╣\n";
    cout << "║   1. Cash on Delivery                    ║\n";
    cout << "║   2. PayPal                              ║\n";
    cout << "║   3. Card                                ║\n";
    cout << "╚══════════════════════════════════════════╝\n";
    cout << RESET;

    cout << "\nEnter Payment Choice : ";
    int pay;
    cin  >> pay;

    string payMethod;

    if      (pay == 1) payMethod = "Cash on Delivery";
    else if (pay == 2) payMethod = "PayPal";
    else if (pay == 3) payMethod = "Card";
    else {
        cout << RED << "\n[ERROR] Invalid payment choice!\n" << RESET;
        return;
    }

    // Mark drone as Rented
    d->setStatus("Rented");

    // Success message
    cout << GREEN << BOLD;
    cout << "\n╔══════════════════════════════════════════╗\n";
    cout << "║         RENTAL CONFIRMED!                ║\n";
    cout << "╠══════════════════════════════════════════╣\n";
    cout << "║  Drone   : " << left << setw(30) << d->getName()  << "║\n";
    cout << "║  Days    : " << left << setw(30) << days           << "║\n";
    cout << "║  Payment : " << left << setw(30) << payMethod      << "║\n";
    cout << "║  Amount  : Rs." << left << setw(27) << (int)total  << "║\n";
    cout << "║  Status  : Rented                        ║\n";
    cout << "║                                          ║\n";
    cout << "║   Enjoy your rental!                     ║\n";
    cout << "╚══════════════════════════════════════════╝\n";
    cout << RESET;
}

// ==========================================
// Option 4 : Recommend Drone by Purpose
// Customer enters purpose → show best drone
// with reason (battery + speed/range)
// ==========================================

void FleetManager::recommendByPurpose() {

    string purpose;
    cout << "\nEnter Purpose (Wedding / Delivery / Farming / Emergency / Surveillance) : ";
    cin  >> purpose;

    // Find best available drone: highest battery among matches
    Drone* best = NULL;

    for (int i = 0; i < totalDrones; i++) {

        if (drones[i]->getPurpose() == purpose &&
            drones[i]->getStatus()  == "Available") {

            if (best == NULL || drones[i]->getBattery() > best->getBattery()) {
                best = drones[i];
            }
        }
    }

    cout << MAGENTA << BOLD;
    cout << "\n╔══════════════════════════════════════════════════╗\n";
    cout << "║           BEST DRONE RECOMMENDATION             ║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    cout << RESET;

    if (best == NULL) {

        cout << RED;
        cout << "║   No available drone found for : "
             << left << setw(16) << purpose << "║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";
        cout << RESET;
        return;
    }

    // Estimated range = speed * battery (km)
    int range = best->getSpeed() * best->getBattery();

    cout << MAGENTA;
    cout << "║   Drone   : " << left << setw(37) << best->getName()    << "║\n";
    cout << "║   Purpose : " << left << setw(37) << best->getPurpose() << "║\n";
    cout << "║   Price   : Rs." << left << setw(34) << (int)best->getPrice() << "║\n";
    cout << "║   Status  : " << left << setw(37) << best->getStatus()  << "║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    cout << "║   WHY THIS DRONE?                                ║\n";
    cout << "╠══════════════════════════════════════════════════╣\n";
    cout << "║   Battery : " << left << setw(37)
         << (to_string(best->getBattery()) + "h (longest flight time)")       << "║\n";
    cout << "║   Speed   : " << left << setw(37)
         << (to_string(best->getSpeed()) + " KM/H (top speed)")               << "║\n";
    cout << "║   Range   : " << left << setw(37)
         << (to_string(range) + " KM (estimated max range)")                  << "║\n";
    cout << "╚══════════════════════════════════════════════════╝\n";
    cout << RESET;
}

// ==========================================
// Option 7 : Reviews
// Shows LIVE DRONE MARKETPLACE table
// then shows each drone with its review
// Customer can add a review at the end
// ==========================================

void FleetManager::showReviews() {

    // Full marketplace table
    drawTable();

    // Reviews section
    cout << MAGENTA << BOLD;
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                          LIVE DRONE MARKETPLACE                                  ║\n";
    cout << "║                               DRONE REVIEWS                                      ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════════╣\n";

    cout << "║ "
         << left
         << setw(5)  << "ID"
         << " │ " << setw(13) << "NAME"
         << " │ " << setw(56) << "REVIEW"
         << " ║\n";

    cout << "╠══════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << RESET;

    for (int i = 0; i < totalDrones; i++) {

        cout << MAGENTA;
        cout << "║ "
             << left
             << setw(5)  << drones[i]->getId()
             << " │ " << setw(13) << drones[i]->getName()
             << " │ " << setw(56) << droneReviews[i]
             << " ║\n";
        cout << RESET;
    }

    cout << MAGENTA;
    cout << "╚══════════════════════════════════════════════════════════════════════════════════╝\n";
    cout << RESET;

    // Option to add a review
    cout << "\nWould you like to add a review? (Y/N) : ";
    char opt;
    cin  >> opt;

    if (opt == 'Y' || opt == 'y') {

        string id;
        cout << "Enter Drone ID : ";
        cin  >> id;

        for (int i = 0; i < totalDrones; i++) {

            if (drones[i]->getId() == id) {

                cout << "Enter Review   : ";
                cin.ignore();
                getline(cin, droneReviews[i]);

                cout << GREEN << "\n[SUCCESS] Review Added Successfully!\n" << RESET;
                return;
            }
        }

        cout << RED << "[ERROR] Drone Not Found!\n" << RESET;
    }
}

// ==========================================
// Option 8 : VIP Status
// Shows current status + benefits
// Option to upgrade (Rs.5000) or downgrade
// ==========================================

void FleetManager::showVIPMenu() {

    cout << YELLOW << BOLD;
    cout << "\n╔══════════════════════════════════════════╗\n";
    cout << "║              VIP STATUS                  ║\n";
    cout << "╠══════════════════════════════════════════╣\n";

    if (isVIP) {
        cout << "║   Current Status : ★  VIP MEMBER         ║\n";
        cout << "╠══════════════════════════════════════════╣\n";
        cout << "║   YOUR VIP BENEFITS :                    ║\n";
        cout << "║    • 15% discount on all purchases       ║\n";
        cout << "║    • 15% discount on all rentals         ║\n";
        cout << "║    • Priority customer support           ║\n";
        cout << "║    • Early access to new drones          ║\n";
        cout << "║    • Exclusive VIP drone listings        ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        cout << RESET;

        cout << "\nDowngrade to Standard? (Y/N) : ";
        char opt;
        cin  >> opt;

        if (opt == 'Y' || opt == 'y') {
            isVIP = false;
            cout << YELLOW << "\n[INFO] You have been downgraded to Standard.\n" << RESET;
        } else {
            cout << GREEN << "\nStaying VIP! Enjoy your exclusive perks.\n" << RESET;
        }

    } else {
        cout << "║   Current Status : Standard User         ║\n";
        cout << "╠══════════════════════════════════════════╣\n";
        cout << "║   UPGRADE TO VIP — Rs.5000/month         ║\n";
        cout << "╠══════════════════════════════════════════╣\n";
        cout << "║   VIP BENEFITS :                         ║\n";
        cout << "║    • 15% discount on all purchases       ║\n";
        cout << "║    • 15% discount on all rentals         ║\n";
        cout << "║    • Priority customer support           ║\n";
        cout << "║    • Early access to new drones          ║\n";
        cout << "║    • Exclusive VIP drone listings        ║\n";
        cout << "╚══════════════════════════════════════════╝\n";
        cout << RESET;

        cout << "\nUpgrade to VIP for Rs.5000/month? (Y/N) : ";
        char opt;
        cin  >> opt;

        if (opt == 'Y' || opt == 'y') {
            isVIP = true;
            cout << GREEN << BOLD;
            cout << "\n╔══════════════════════════════════════════╗\n";
            cout << "║   Welcome to VIP! You now enjoy 15% off  ║\n";
            cout << "║   on all purchases and rentals.           ║\n";
            cout << "╚══════════════════════════════════════════╝\n";
            cout << RESET;
        } else {
            cout << YELLOW << "\nStaying Standard. You can upgrade anytime!\n" << RESET;
        }
    }
}

// ==========================================
// Option 9 : Insurance
// Shows LIVE DRONE MARKETPLACE table
// then shows each drone + insurance info
// ==========================================

void FleetManager::showInsurance() {

    // Full marketplace table first
    drawTable();

    // Insurance table
    cout << CYAN << BOLD;
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                          LIVE DRONE MARKETPLACE                                  ║\n";
    cout << "║                           DRONE INSURANCE INFO                                   ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════════╣\n";

    cout << "║ "
         << left
         << setw(5)  << "ID"
         << " │ " << setw(13) << "NAME"
         << " │ " << setw(10) << "DURATION"
         << " │ " << setw(38) << "PERIOD"
         << " ║\n";

    cout << "╠══════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << RESET;

    for (int i = 0; i < totalDrones; i++) {

        bool insured = (droneInsurance[i] != "Not insured");

        if (insured) cout << GREEN;
        else         cout << RED;

        // Duration label extracted from stored string e.g. "2 Years  (Jun 2025 - Jun 2027)"
        // We store the full string in droneInsurance — display it as the period column
        string duration = "N/A";
        string period   = droneInsurance[i];

        // If insured, parse first word pair as duration
        if (insured) {
            // e.g. "2 Years  (Jun 2025 - Jun 2027)"
            // duration = first token before '('
            size_t paren = droneInsurance[i].find('(');
            if (paren != string::npos) {
                duration = droneInsurance[i].substr(0, paren - 2);   // "2 Years"
                period   = droneInsurance[i].substr(paren);          // "(Jun 2025 - Jun 2027)"
            }
        } else {
            duration = "None";
            period   = "Not insured";
        }

        cout << "║ "
             << left
             << setw(5)  << drones[i]->getId()
             << " │ " << setw(13) << drones[i]->getName()
             << " │ " << setw(10) << duration
             << " │ " << setw(38) << period
             << " ║\n";

        cout << RESET;
    }

    cout << CYAN;
    cout << "╚══════════════════════════════════════════════════════════════════════════════════╝\n";
    cout << RESET;
}

// ==========================================
// Add Drone  (admin use)
// ==========================================

void FleetManager::addDroneMenu() {

    string id, name, purpose, type;
    int    battery, speed;
    double price;

    cout << "\nEnter ID      : "; cin >> id;
    cout << "Enter Name    : "; cin >> name;
    cout << "Enter Purpose : "; cin >> purpose;
    cout << "Enter Battery : "; cin >> battery;
    cout << "Enter Speed   : "; cin >> speed;
    cout << "Enter Price   : "; cin >> price;
    cout << "Type (S/D)    : "; cin >> type;

    if (type == "S" || type == "s") {
        drones[totalDrones] = new SurveillanceDrone(id, name, purpose, battery, speed, price, "HD");
    } else {
        drones[totalDrones] = new DeliveryDrone(id, name, purpose, battery, speed, price, 2.0);
    }

    droneReviews[totalDrones]   = "No review yet.";
    droneInsurance[totalDrones] = "Not insured";

    totalDrones++;

    cout << GREEN << "\n[SUCCESS] Drone Added Successfully!\n" << RESET;
}

// ==========================================
// Remove Drone  (admin use)
// ==========================================

void FleetManager::removeDroneMenu() {

    string id;

    cout << "\nEnter Drone ID to Remove : ";
    cin  >> id;

    for (int i = 0; i < totalDrones; i++) {

        if (drones[i]->getId() == id) {

            delete drones[i];

            for (int j = i; j < totalDrones - 1; j++) {
                drones[j]         = drones[j + 1];
                droneReviews[j]   = droneReviews[j + 1];
                droneInsurance[j] = droneInsurance[j + 1];
            }

            totalDrones--;

            cout << GREEN << "\nDrone Removed Successfully!\n" << RESET;
            return;
        }
    }

    cout << RED << "\nDrone Not Found!\n" << RESET;
}

// ==========================================
// Monitor All Drones
// ==========================================

void FleetManager::monitorAll() {

    cout << YELLOW;
    cout << "\n========== DRONE STATUS ==========\n";
    cout << RESET;

    for (int i = 0; i < totalDrones; i++) {
        drones[i]->display();
    }
}

// ==========================================
// Recommendation System  (original)
// ==========================================

void FleetManager::recommend(string purpose, double budget) {

    Drone* best = NULL;

    for (int i = 0; i < totalDrones; i++) {

        if (drones[i]->getPurpose() == purpose &&
            drones[i]->getPrice()   <= budget) {

            best = drones[i];
        }
    }

    cout << MAGENTA << BOLD;
    cout << "\n========== BEST DRONE ==========\n";
    cout << RESET;

    if (best == NULL) {
        cout << RED << "No Drone Found In Budget.\n" << RESET;
        return;
    }

    cout << "Drone   : " << best->getName()    << "\n";
    cout << "Purpose : " << best->getPurpose() << "\n";
    cout << "Price   : Rs." << best->getPrice() << "\n";

    cout << GREEN << "Recommended Successfully!\n" << RESET;
}

// ==========================================
// Option 10 : Search By Budget
// ==========================================

void FleetManager::searchByBudget(double maxPrice) {

    cout << GREEN << BOLD;
    cout << "\n╔══════════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                       DRONES WITHIN YOUR BUDGET                                  ║\n";
    cout << "╠══════════════════════════════════════════════════════════════════════════════════╣\n";

    cout << "║ "
         << left
         << setw(5)  << "ID"
         << " │ " << setw(13) << "NAME"
         << " │ " << setw(12) << "PURPOSE"
         << " │ " << setw(4)  << "BAT"
         << " │ " << setw(9)  << "SPEED"
         << " │ " << setw(11) << "PRICE"
         << " │ " << setw(9)  << "STATUS"
         << " ║\n";

    cout << "╠══════════════════════════════════════════════════════════════════════════════════╣\n";
    cout << RESET;

    bool found = false;

    for (int i = 0; i < totalDrones; i++) {

        if (drones[i]->getPrice() <= maxPrice) {

            found = true;

            Drone*  d      = drones[i];
            string  status = d->getStatus();
            string  bat    = to_string(d->getBattery()) + "h";
            string  speed  = to_string(d->getSpeed())   + " KM/H";
            string  price  = "Rs." + to_string((int)d->getPrice());

            if      (status == "Rented")  cout << RED;
            else if (status == "Sold")    cout << YELLOW;
            else                          cout << GREEN;

            cout << "║ "
                 << left
                 << setw(5)  << d->getId()
                 << " │ " << setw(13) << d->getName()
                 << " │ " << setw(12) << d->getPurpose()
                 << " │ " << setw(4)  << bat
                 << " │ " << setw(9)  << speed
                 << " │ " << setw(11) << price
                 << " │ " << setw(9)  << status
                 << " ║\n";

            cout << RESET;
        }
    }

    if (!found) {
        cout << RED;
        cout << "║   No drones found within this budget.                                             ║\n";
        cout << RESET;
    }

    cout << GREEN;
    cout << "╚══════════════════════════════════════════════════════════════════════════════════╝\n";
    cout << RESET;
}

// ==========================================
// Find Drone By ID
// ==========================================

Drone* FleetManager::findById(string id) {

    for (int i = 0; i < totalDrones; i++) {

        if (drones[i]->getId() == id) {
            return drones[i];
        }
    }

    return NULL;
}

// ==========================================
// Return Drone Array
// ==========================================

Drone** FleetManager::getDrones() {
    return drones;
}

// ==========================================
// Drone Count
// ==========================================

int FleetManager::getDroneCount() {
    return totalDrones;
}
