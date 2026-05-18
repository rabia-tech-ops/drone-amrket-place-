#include "ConsoleUI.h"        // Contains console colors and UI helper functions
#include "Admin.h"            // Contains Admin class
#include "Operator.h"         // Contains Operator class
#include "FleetManager.h"     // Contains FleetManager class
#include "AuthManager.h"      // Handles login and registration system
#include "DataManager.h"      // Handles reports and customer data
#include "MissionPlanner.h"   // Handles mission assignment and tracking
#include "Payment.h"          // Handles wallet and payments
#include "Rental.h"           // Handles drone rental system
#include "GPSNavigation.h"    // Contains GPS navigation system
#include "AINavigation.h"     // Contains AI navigation system
#include <conio.h>            // Used for keyboard input functions
#include <iostream>           // Used for input and output
#include <windows.h>          // Used for Sleep and Windows console functions
#include <fstream>

using namespace std;

// ==========================================
// Global Managers
// ==========================================

FleetManager fleet;
AuthManager auth;
DataManager dataManager(&auth, &fleet);

MissionPlanner planner;
Rental rental;
Payment pay(0);
// ================= FILE HANDLING =================

void saveCustomers(AuthManager& auth) {

    ofstream file("customers.txt");

    CustomerAccount* users = auth.getAllCustomers();
    int total = auth.getTotalCustomers();

    for (int i = 0; i < total; i++) {

        file << users[i].name << ","
            << users[i].password << ","
            << users[i].wallet << ","
            << users[i].vip << "\n";
    }


    file.close();
}

void loadCustomers(AuthManager& auth) {

    ifstream file("customers.txt");

    string name, pass, vip;
    double wallet;

    while (getline(file, name, ',')) {

        getline(file, pass, ',');
        file >> wallet;
        file.ignore(1, ',');
        getline(file, vip);

        auth.registerCustomer(name, pass);

        CustomerAccount* users = auth.getAllCustomers();
        int idx = auth.getTotalCustomers() - 1;

        users[idx].wallet = wallet;
        users[idx].vip = vip;
    }

    file.close();
}
// ==========================================
// Welcome Screen
// ==========================================

void welcomeScreen() {

    system("cls");

    enableColors();

    cout << CYAN << BOLD;

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════════════════════════════╗\n";
    cout << "║                                                                              ║\n";
    cout << "║               ██████╗ ██████╗  ██████╗ ███╗   ██╗███████╗                    ║\n";
    cout << "║               ██╔══██╗██╔══██╗██╔═══██╗████╗  ██║██╔════╝                    ║\n";
    cout << "║               ██║  ██║██████╔╝██║   ██║██╔██╗ ██║█████╗                      ║\n";
    cout << "║               ██║  ██║██╔══██╗██║   ██║██║╚██╗██║██╔══╝                      ║\n";
    cout << "║               ██████╔╝██║  ██║╚██████╔╝██║ ╚████║███████╗                    ║\n";
    cout << "║               ╚═════╝ ╚═╝  ╚═╝ ╚═════╝ ╚═╝  ╚═══╝╚══════╝                    ║\n";
    cout << "║                                                                              ║\n";
    cout << "║                 DRONE MARKETPLACE MANAGEMENT SYSTEM                          ║\n";
    cout << "║                                                                              ║\n";
    cout << "║              Smart Delivery • AI Routing • Security                          ║\n";
    cout << "║                                                                              ║\n";
    cout << "║                    Powered By Rabia Tech Team                                ║\n";
    cout << "║                                                                              ║\n";
    cout << "╚══════════════════════════════════════════════════════════════════════════════╝\n";

    cout << RESET;

    loadingBar("Initializing Smart Marketplace...");

    cout << GREEN;
    cout << "Connecting To Global Drone Network...\n";
    cout << "Checking Live GPS Services...\n";
    cout << "Activating AI Navigation Engine...\n";
    cout << "Loading Customer Dashboard...\n";
    cout << "Loading Admin Services...\n";
    cout << "SYSTEM READY SUCCESSFULLY!\n";
    cout << RESET;

    cout << YELLOW;
    cout << "\nPress any key to continue...";
    cout << RESET;

    // Wait max 5 seconds OR any key press
    for (int i = 0; i < 50; i++) {

        if (_kbhit()) {
            _getch();
            break;
        }

        Sleep(100);
    };
}

// ==========================================
// Exit Screen
// ==========================================

void exitScreen() {

    system("cls");

    cout << MAGENTA << BOLD;

    cout << "\n";
    cout << "╔════════════════════════════════════════════════╗\n";
    cout << "║             THANK YOU FOR USING               ║\n";
    cout << "║        DRONE MARKETPLACE MANAGEMENT           ║\n";
    cout << "║          Powered By Rabia Tech Team           ║\n";
    cout << "╚════════════════════════════════════════════════╝\n";

    cout << RESET;

    loadingBar("Closing system...");

    cout << GREEN;
    cout << "SYSTEM EXIT SUCCESSFUL\n";
    cout << RESET;
}

// ==========================================
// Admin Menu
// ==========================================

void adminMenu(Admin& admin) {

    int ch;

    do {

        system("cls");

        admin.showPanel();

        cout << "\n1. Add Drone\n";
        cout << "2. Remove Drone\n";
        cout << "3. Show Marketplace\n";
        cout << "4. View Users\n";
        cout << "5. View Reports\n";
        cout << "6. Weather Check\n";
        cout << "7. Logout\n";

        cout << "\nChoice: ";
        cin >> ch;

        switch (ch) {

        case 1:
            admin.addDrone();
            break;

        case 2:
            admin.removeDrone();
            break;

        case 3:
            admin.manageMarketplace();
            break;

        case 4:
            admin.viewUsers();
            break;

        case 5:
            admin.viewReports();
            break;

        case 6:
            planner.checkWeather();
            break;

        case 7:
            return;

        default:
            cout << RED;
            cout << "Invalid Choice!\n";
            cout << RESET;
        }

        pauseScreen();

    } while (ch != 7);
}

// ==========================================
// Operator Menu
// ==========================================

void operatorMenu(Operator& op) {

    int ch;

    string src;
    string dest;

    do {

        system("cls");

        op.showPanel();

        cout << "\n1. Assign Mission\n";
        cout << "2. Monitor Drones\n";
        cout << "3. Track Delivery\n";
        cout << "4. Battery Monitor\n";
        cout << "5. GPS Navigation\n";
        cout << "6. AI Navigation\n";
        cout << "7. Emergency Rescue\n";
        cout << "8. Logout\n";

        cout << "\nChoice: ";
        cin >> ch;

        switch (ch) {

        case 1:
            op.assignMission();
            break;

        case 2:
            op.monitorStatus();
            break;

        case 3:
            op.viewDelivery();
            break;

        case 4:
            planner.checkBattery(&fleet);
            break;

        case 5: {

            cout << "Enter Source: ";
            cin >> src;

            cout << "Enter Destination: ";
            cin >> dest;

            GPSNavigation gps(src, dest);
            gps.calculateRoute();

            break;
        }

        case 6: {

            cout << "Enter Source: ";
            cin >> src;

            cout << "Enter Destination: ";
            cin >> dest;

            AINavigation ai(src, dest);
            ai.calculateRoute();

            break;
        }

        case 7:
            planner.emergencyRescue();
            break;

        case 8:
            return;

        default:
            cout << RED;
            cout << "Invalid Choice!\n";
            cout << RESET;
        }

        pauseScreen();

    } while (ch != 8);
}

// ==========================================
// Customer Menu
// ==========================================

void customerMenu() {

    CustomerAccount* c = auth.getCurrentCustomer();

    if (c == NULL)
        return;

    pay = Payment(c->wallet);

    int ch;

    string id;
    string purpose;

    double budget;

    do {

        system("cls");

        cout << GREEN << BOLD;

        cout << "\n";
        cout << "╔══════════════════════════════════════╗\n";
        cout << "║          CUSTOMER DASHBOARD          ║\n";
        cout << "╚══════════════════════════════════════╝\n";

        cout << RESET;

        cout << "Customer : " << c->name << endl;
        cout << "Wallet   : Rs." << pay.getWallet() << endl;
        cout << "VIP      : " << c->vip << endl;

        cout << "\n1. View Drones\n";
        cout << "2. Buy Drone\n";
        cout << "3. Rent Drone\n";
        cout << "4. Recommend Drone\n";
        cout << "5. Track Delivery\n";
        cout << "6. Wallet\n";
        cout << "7. Reviews\n";
        cout << "8. VIP Status\n";
        cout << "9. Insurance\n";
        cout << "10. Search By Budget\n";
        cout << "11. Logout\n";

        cout << "\nChoice: ";
        cin >> ch;

        switch (ch) {

        case 1:

            fleet.showTable();
            break;

        case 2: {

            cout << "Enter Drone ID: ";
            cin >> id;

            Drone* d = fleet.findById(id);

            if (d != NULL) {

                pay.buyDrone(d->getPrice());
            }
            else {

                cout << RED;
                cout << "Drone Not Found!\n";
                cout << RESET;
            }

            break;
        }

        case 3: {

            int days;

            cout << "Enter Drone ID: ";
            cin >> id;

            cout << "Enter Days: ";
            cin >> days;

            rental.rentDrone(&fleet, id, days, &pay);

            rental.showRentals();

            break;
        }

        case 4:

            cout << "Enter Purpose: ";
            cin >> purpose;

            cout << "Enter Budget: ";
            cin >> budget;

            fleet.recommend(purpose, budget);

            break;

        case 5:

            planner.trackDelivery();
            break;

        case 6:

            pay.showWallet();
            break;

        case 7:

            cout << "★★★★★ Excellent Service!\n";
            break;

        case 8:

            cout << "VIP Status: " << c->vip << endl;
            break;

        case 9:

            cout << "Insurance Status: ACTIVE\n";
            break;

        case 10:

            cout << "Enter Budget: ";
            cin >> budget;

            fleet.searchByBudget(budget);

            break;

        case 11:

            c->wallet = pay.getWallet();

            auth.logoutCustomer();

            return;

        default:

            cout << RED;
            cout << "Invalid Choice!\n";
            cout << RESET;
        }

        c->wallet = pay.getWallet();

        pauseScreen();

    } while (true);
}

// ==========================================
// MAIN FUNCTION
// ==========================================

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    welcomeScreen();

    int choice;

    string user;
    string pass;

    do {

        system("cls");

        cout << CYAN << BOLD;

        cout << "\n";
        cout << "              ____               " << endl;

        cout << GRAY << "         ____/____\\____         " << endl;

        cout << WHITE << "        /      " << YELLOW << "DRONE" << WHITE << "    \\       " << endl;

        cout << CYAN << "   O---|" << WHITE << "                 " << CYAN << "|---O  " << endl;

        cout << WHITE << "        \\_________________/     " << endl;

        cout << GRAY << "           / /       \\ \\       " << endl;

        cout << WHITE << "          O O         O O       " << endl;

        cout << RESET << "\n";

        cout << DARKCYAN;

        cout << "╔══════════════════════════════════════════════╗\n";

        cout << "║        🛸 " << BWHITE << "DRONE MANAGEMENT SYSTEM" << DARKCYAN << "            ║\n";

        cout << "║              " << AMBER << "SECURE ACCESS" << DARKCYAN << "                   ║\n";

        cout << "╚══════════════════════════════════════════════╝\n";

        cout << RESET;

        cout << RESET;

        cout << "STATUS: ONLINE ●\n";
        cout << "──────────────────────────────────────────────\n";

        // ==========================================
        // FIX: Menu now correctly shows 4 options
        // 1=Login  2=Register  3=Exit
        // ==========================================
        cout << "1. LOGIN\n";
        cout << "2. REGISTER (New Customer)\n";
        cout << "3. EXIT\n";

        cout << "──────────────────────────────────────────────\n";

        cout << "\nEnter Choice: ";

        cin >> choice;

        switch (choice) {

            // ==========================================
            // CASE 1: LOGIN
            // ==========================================
        case 1: {

            cout << "\nUsername: ";
            cin >> user;

            cout << "Password: ";
            cin >> pass;

            cout << "\nVERIFYING CREDENTIALS...\n";

            const char* stages[] = {
                "\r█▒▒▒▒▒▒▒▒▒▒▒▒  25%  ",
                "\r█████▒▒▒▒▒▒▒▒  50%  ",
                "\r█████████▒▒▒▒  75%  ",
                "\r█████████████ 100%  "
            };

            for (int i = 0; i < 4; i++) {
                cout << stages[i] << flush;
                Sleep(700);
            }

            cout << "\n\n";

            bool success = false;

            // --- Try Admin login ---
            if (auth.loginAdmin(user, pass)) {

                cout << GREEN << "✔ ACCESS GRANTED\n" << RESET;

                Admin admin("RabiaAdmin", "A01", &fleet, &dataManager);

                adminMenu(admin);

                success = true;
            }
            // --- Try Operator login ---
            else if (auth.loginOperator(user, pass)) {

                cout << GREEN << "✔ ACCESS GRANTED\n" << RESET;

                Operator op("RabiaOperator", "O01", &fleet, &planner);

                operatorMenu(op);

                success = true;
            }
            // --- Try Customer login ---
            else if (auth.loginCustomer(user, pass)) {

                cout << GREEN << "✔ ACCESS GRANTED\n" << RESET;

                customerMenu();

                success = true;
            }

            // --- LOGIN FAILED ---
            if (!success) {

                cout << RED << "❌ Incorrect username or password!\n" << RESET;
                cout << RED << "❌ LOGIN FAILED!\n" << RESET;

                cout << CYAN;
                cout << endl;
                cout << "──────────────────────────────────────────────\n";
                cout << "             FORGOT PASSWORD                  \n";
                cout << "──────────────────────────────────────────────\n";

                cout << YELLOW << "\n1. YES\n";
                cout << "2. NO\n";
                cout << "3. EXIT\n";
                cout << "Enter Choice: ";

                int fpChoice;
                cin >> fpChoice;

                if (fpChoice == 1) {

                    string uname, newPass;

                    cout << "\nEnter Username: ";
                    cin >> uname;

                    cout << "Enter New Password: ";
                    cin >> newPass;

                    bool found = false;

                    // Admin check
                    if (uname == auth.adminUser) {

                        auth.adminPass = newPass;
                        found = true;

                        cout << GREEN << "\n✔ ADMIN PASSWORD UPDATED!\n" << RESET;
                    }
                    // Operator check
                    else if (uname == auth.opUser) {

                        auth.opPass = newPass;
                        found = true;

                        cout << GREEN << "\n✔ OPERATOR PASSWORD UPDATED!\n" << RESET;
                    }
                    // Customer check
                    else {

                        CustomerAccount* users = auth.getAllCustomers();
                        int total = auth.getTotalCustomers();

                        for (int i = 0; i < total; i++) {

                            if (users[i].name == uname) {

                                users[i].password = newPass;
                                found = true;

                                cout << GREEN << "\n✔ CUSTOMER PASSWORD UPDATED!\n" << RESET;

                                auth.saveCustomersToFile();
                                break;
                            }
                        }
                    }

                    if (!found) {
                        cout << RED << "❌ USER NOT FOUND\n" << RESET;
                    }
                }
                else if (fpChoice == 2) {
                    cout << "\nReturning to menu...\n";
                }
                else if (fpChoice == 3) {
                    exit(0);
                }
            }

            pauseScreen();
            break;
        }

              // ==========================================
              // CASE 2: REGISTER (New Customer)
              // ==========================================
        case 2: {

            cout << "\nEnter New Username: ";
            cin >> user;

            cout << "Enter Password: ";
            cin >> pass;

            if (auth.registerCustomer(user, pass)) {

                cout << GREEN;
                cout << "\nCreating account";

                for (int i = 0; i < 3; i++) {
                    cout << ".";
                    Sleep(500);
                }

                cout << "\n\n🎉 CONGRATULATIONS!\n";
                cout << "✔ ACCOUNT CREATED SUCCESSFULLY\n";
                cout << "You can now LOGIN with your username and password.\n";
                cout << RESET;

                // Save immediately so account persists
                auth.saveCustomersToFile();
            }
            else {
                cout << RED << "\nRegistration Failed! Username may already exist.\n" << RESET;
            }

            Sleep(1200);
            pauseScreen();
            break;
        }

              // ==========================================
              // CASE 3: EXIT
              // ==========================================
        case 3: {

            exitScreen();
            return 0;
        }

        default:

            cout << RED;
            cout << "Invalid Choice!\n";
            cout << RESET;

            pauseScreen();
        }

    } while (choice != 3);

    return 0;
}
