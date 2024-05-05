#include "Graph.h"

Graph::Graph() : head(nullptr) {}

Graph::~Graph() {
    Vertex* current = head;
    while (current != nullptr) {
        Vertex* next = current->next;
        delete current;
        current = next;
    }
}

Vertex* Graph::findOrCreateVertex(const string& name) {
    Vertex* current = head;
    while (current != nullptr) {
        if (current->name == name) {
            return current;
        }
        current = current->next;
    }
    Vertex* newVertex = new Vertex(name);
    newVertex->next = head;
    head = newVertex;
    return newVertex;
}

void Graph::follow(const string& follower, const string& following) {
    ifstream file("UserINFO.csv");
    bool userExists = false;
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string name, pass;
            getline(ss, name, ',');
            if (name == following) {
                userExists = true;
                break;
            }
        }
        file.close();
    }
    if (!userExists) {
        cout << "Error: The user '" << following << "' does not exist." << endl;
        return;
    }

    Vertex* followerVertex = findOrCreateVertex(follower);
    followerVertex->addFollower(following);
}

void Graph::unfollow(const string& follower, const string& following) {
    Vertex* followerVertex = findOrCreateVertex(follower);
    followerVertex->removeFollower(following);
}
void Graph::displayFollowers(const string& user) {
    cout << "Followers of " << user << " are:" << endl;
    Vertex* current = head;
    bool found = false;

    while (current != nullptr) {
        if (current->name == user) {
            found = true;
            FollowerNode* follower = current->followersHead;
            if (follower == nullptr) {
                cout << "No followers found." << endl;
            }
            else {
                while (follower != nullptr) {
                    cout << follower->name << endl;
                    follower = follower->next;
                }
            }
            break;
        }
        current = current->next;
    }

    if (!found) {
        cout << "There are 0 followers!" << endl;
    }
}


void Graph::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        Vertex* current = head;
        while (current != nullptr) {
            FollowerNode* follower = current->followersHead;
            while (follower != nullptr) {
                file << current->name << " " << follower->name << endl;
                follower = follower->next;
            }
            current = current->next;
        }
        file.close();
    }
}

void Graph::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string follower, following;
            ss >> follower >> following;
            follow(follower, following);
        }
        file.close();
    }
}
