#include "connections_node.h"

#include <string>
using namespace std;

FollowerNode::FollowerNode(const string& name) : name(name), next(nullptr) {}

connections_node::connections_node(const string& name) : name(name), followersHead(nullptr), next(nullptr) {}

connections_node::~connections_node() {
    FollowerNode* current = followersHead;
    while (current != nullptr) {
        FollowerNode* next = current->next;
        delete current;
        current = next;
    }
}

void connections_node::addFollower(const string& followerName) {
    if (followersHead == nullptr) {
        followersHead = new FollowerNode(followerName);
    }
    else {
        FollowerNode* newNode = new FollowerNode(followerName);
        newNode->next = followersHead;
        followersHead = newNode;
    }
}

void connections_node::removeFollower(const string& followerName) {
    FollowerNode* current = followersHead;
    FollowerNode* prev = nullptr;
    while (current != nullptr) {
        if (current->name == followerName) {
            if (prev == nullptr) {
                followersHead = current->next;
            }
            else {
                prev->next = current->next;
            }
            delete current;
            break;
        }
        prev = current;
        current = current->next;
    }
}
