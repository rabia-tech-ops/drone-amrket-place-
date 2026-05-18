#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

#include <string>
#include <fstream>   // ✅ ADDED for file handling

using namespace std;

// ==========================================
// Customer Structure
// ==========================================

struct CustomerAccount {
    string name;
    string password;
    double wallet = 0;
    string vip;
};

// ==========================================
// AuthManager Class
// Handles Login & Registration
// ==========================================

class AuthManager {

private:

    

    // Customer Array
    CustomerAccount customers[100];

    // Total Customers
    int totalCustomers;

    // Logged in customer index
    int loggedInIndex;

    // ======================================
    // 🔥 FILE HANDLING (ADDED ONLY)
    // ======================================
    string customerFile = "customers.txt";

public:
    // Admin Login
    string adminUser;
    string adminPass;

    // Operator Login
    string opUser;
    string opPass;

    // Constructor
    AuthManager();

    // Login Functions
    bool loginAdmin(string u, string p);
    bool loginOperator(string u, string p);
    bool loginCustomer(string u, string p);

    // Register New Customer
    bool registerCustomer(string u, string p);

    // Forgot Password
    bool forgotPassword(string username);

    // Get Current Customer
    CustomerAccount* getCurrentCustomer();

    // Logout
    void logoutCustomer();

    // Get Customer List
    CustomerAccount* getAllCustomers();

    // Get Total Customers
    int getTotalCustomers();

    // ======================================
    // 🔥 FILE FUNCTIONS (ADDED ONLY)
    // ======================================

    void saveCustomersToFile();
    void loadCustomersFromFile();
};

#endif
