#include "AuthManager.h"
#include <iostream>
#include <fstream>   // ✅ ADDED

using namespace std;

// ==========================================
// Constructor
// ==========================================

AuthManager::AuthManager() {

    adminUser = "admin";
    adminPass = "admin123";

    opUser = "operator";
    opPass = "op123";

    loggedInIndex = -1;
    totalCustomers = 0;

    // ======================================
    // 🔥 LOAD DATA FROM FILE (ADDED)
    // ======================================
    loadCustomersFromFile();

    // If file is empty, add default user
    if (totalCustomers == 0) {

        customers[0].name = "Rabia";
        customers[0].password = "1234";
        customers[0].wallet = 500000;
        customers[0].vip = "Gold Member";

        totalCustomers = 1;   // ✅ FIXED (better than ++)
    }
}

// ==========================================
// Admin Login
// ==========================================

bool AuthManager::loginAdmin(string u, string p) {
    return (u == adminUser && p == adminPass);
}

// ==========================================
// Operator Login
// ==========================================

bool AuthManager::loginOperator(string u, string p) {
    return (u == opUser && p == opPass);
}

// ==========================================
// Customer Login
// ==========================================

bool AuthManager::loginCustomer(string u, string p) {

    for (int i = 0; i < totalCustomers; i++) {

        if (customers[i].name == u &&
            customers[i].password == p) {

            loggedInIndex = i;
            return true;
        }
    }

    return false;
}

// ==========================================
// Register Customer
// ==========================================

bool AuthManager::registerCustomer(string u, string p) {

    // ======================================
    // 🔥 FIX: PREVENT ARRAY OVERFLOW
    // ======================================
    if (totalCustomers >= 100) {
        cout << "Customer limit reached!\n";
        return false;
    }

    customers[totalCustomers].name = u;
    customers[totalCustomers].password = p;
    customers[totalCustomers].wallet = 100000;
    customers[totalCustomers].vip = "Standard";

    loggedInIndex = totalCustomers;

    totalCustomers++;

    // ======================================
    // 🔥 SAVE AFTER REGISTER (ADDED)
    // ======================================
    saveCustomersToFile();

    return true;
}

// ==========================================
// Forgot Password
// ==========================================

bool AuthManager::forgotPassword(string username) {

    for (int i = 0; i < totalCustomers; i++) {

        if (customers[i].name == username) {

            cout << "Your password is: "
                << customers[i].password << endl;

            return true;
        }
    }

    return false;
}

// ==========================================
// Get Current Customer
// ==========================================

CustomerAccount* AuthManager::getCurrentCustomer() {

    if (loggedInIndex < 0) {
        return NULL;
    }

    return &customers[loggedInIndex];
}

// ==========================================
// Logout Customer
// ==========================================

void AuthManager::logoutCustomer() {
    loggedInIndex = -1;
}

// ==========================================
// Return Customer Array
// ==========================================

CustomerAccount* AuthManager::getAllCustomers() {
    return customers;
}

// ==========================================
// Total Customers
// ==========================================

int AuthManager::getTotalCustomers() {
    return totalCustomers;
}

// ==========================================
// 🔥 SAVE TO FILE (ADDED)
// ==========================================

void AuthManager::saveCustomersToFile() {

    ofstream file("customers.txt");

    for (int i = 0; i < totalCustomers; i++) {

        file << customers[i].name << " "
            << customers[i].password << " "
            << customers[i].wallet << " "
            << customers[i].vip << endl;
    }

    file.close();
}

// ==========================================
// 🔥 LOAD FROM FILE (ADDED)
// ==========================================

void AuthManager::loadCustomersFromFile() {

    ifstream file("customers.txt");

    if (!file.is_open()) return;

    totalCustomers = 0;

    while (file >> customers[totalCustomers].name
        >> customers[totalCustomers].password
        >> customers[totalCustomers].wallet
        >> customers[totalCustomers].vip) {

        totalCustomers++;
    }

    file.close();
}
