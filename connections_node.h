#pragma once
#include <string>
#include "FollowerNode.h"
using namespace std;


class FollowerNode {
public:
    string name;
    FollowerNode* next;
    FollowerNode(const string& name);
};

class connections_node {
public:
    string name;
    FollowerNode* followersHead;
    connections_node* next;

    connections_node(const string& name);
    ~connections_node();
    void addFollower(const string& followerName);
    void removeFollower(const string& followerName);
};
