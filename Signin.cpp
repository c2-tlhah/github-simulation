#include "Signin.h"
#include "Graph.h" // Assuming Graph class is defined in Graph.h

using namespace std;

User::User() {
    capacity = 1001;
    usertable_ = new Node * [capacity];
    for (int i = 0; i < capacity; ++i) {
        usertable_[i] = nullptr;
    }
}

User::~User() {
    for (int i = 0; i < capacity; ++i) {
        Node* current = usertable_[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] usertable_;
}

int User::hashfunc(int& id) {
    return id % capacity;
}

int User::HashFunc(const string& name) {
    return name.length() % capacity;
}

void User::userRegister(const string& uname, const string& password) {
    ofstream fout;
    fout.open("UserINFO.csv", ios::app); // Change to CSV file
    if (!fout.is_open()) {
        cout << "File is not opened" << endl;
        return;
    }
    fout << uname << "," << password << endl; // Store as CSV format
    fout.close();
}

bool User::Login(const string& uname, const string& password) {
    ifstream fin;
    fin.open("UserINFO.csv"); // Change to CSV file
    if (!fin.is_open()) {
        cout << "File is not found" << endl;
        return false;
    }
    string line;
    while (getline(fin, line)) {
        stringstream ss(line);
        string name, pass;
        getline(ss, name, ',');
        getline(ss, pass, ',');
        if (name == uname && pass == password) {
            fin.close();
            return true;
        }
    }
    fin.close();
    return false;
}

void User::viewProfile(const string& username) {
    ifstream file("repo.csv");
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file repo.csv" << endl;
        return;
    }

    string line;
    int totalRepositories = 0;
    while (getline(file, line)) {
        stringstream ss(line);
        string owner, name, isPrivate;
        getline(ss, owner, ',');
        getline(ss, name, ',');
        getline(ss, isPrivate, ',');
        if (owner == username) {
            totalRepositories++;
        }
    }
    file.close();
    Graph network;
    network.loadFromFile("social_network.csv");
    cout << "Profile of user: " << username << endl;
    cout << "Total number of repositories: " << totalRepositories << endl;

    network.displayFollowers(username);
}

void User::delayProgram(int time) {
    using namespace this_thread; // sleep_for, sleep_until
    using namespace chrono; // nanoseconds, system_clock, seconds

    sleep_for(nanoseconds(0));
    sleep_until(system_clock::now() + seconds(time));
}
