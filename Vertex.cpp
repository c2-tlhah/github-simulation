#include "Vertex.h"

Vertex::Vertex(const string& name) : name(name), followersHead(nullptr), next(nullptr) {}

Vertex::~Vertex() {
    FollowerNode* current = followersHead;
    while (current != nullptr) {
        FollowerNode* next = current->next;
        delete current;
        current = next;
    }
}

void Vertex::addFollower(const string& followerName) {
    if (followersHead == nullptr) {
        followersHead = new FollowerNode(followerName);
    }
    else {
        FollowerNode* newNode = new FollowerNode(followerName);
        newNode->next = followersHead;
        followersHead = newNode;
    }
}

void Vertex::removeFollower(const string& followerName) {
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
