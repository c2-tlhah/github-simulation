#pragma once
#pragma once
#pragma once
#include <string>
#include "FollowerNode.h"
using namespace std;

class Vertex {
public:
    string name;
    FollowerNode* followersHead;
    Vertex* next;

    Vertex(const string& name);
    ~Vertex();
    void addFollower(const string& followerName);
    void removeFollower(const string& followerName);
};
