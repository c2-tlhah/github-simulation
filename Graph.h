#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Vertex.h"
using namespace std;

class Graph {
private:
    Vertex* head;

    Vertex* findOrCreateVertex(const string& name);
public:
    Graph();
    ~Graph();
    void follow(const string& follower, const string& following);
    void unfollow(const string& follower, const string& following);
    void displayFollowers(const string& user);
    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
};
