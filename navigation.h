#ifndef NAVIGATIONSYSTEM_H
#define NAVIGATIONSYSTEM_H

#include <string>

using namespace std;

// Abstract Navigation System
class NavigationSystem {

protected:
    string source;
    string destination;

public:

    NavigationSystem(string src = "", string dest = "");

    virtual void calculateRoute() = 0;

    virtual ~NavigationSystem() {}

    void setRoute(string src, string dest);
};

#endif
