#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "AuthManager.h"
#include "FleetManager.h"

// ==========================================
// DataManager Class
// Handles Reports & User Information
// ==========================================

class DataManager {

private:

    AuthManager* auth;
    FleetManager* fleet;

public:

    // Constructor
    DataManager(AuthManager* a, FleetManager* f);

    // Show marketplace reports
    void showReports();

    // Show registered users
    void showUsers();
};

#endif
