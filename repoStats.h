#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "connections_node.h"
using namespace std;

class repoStats {
private:
    connections_node* head;

    connections_node* findOrCreateVertex(const string& name);
public:
    repoStats();
    ~repoStats();
    void follow(const string& follower, const string& following);
    void unfollow(const string& follower, const string& following);
    void displayFollowers(const string& user);
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
};
