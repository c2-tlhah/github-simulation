#pragma once
#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;
struct SIGNIN {
    string username;
    string password;
};

struct Node {
    SIGNIN signin;
    Node* next;

    Node() {
        next = nullptr;
    }
};

class User {
    Node** usertable_;
    int capacity;

public:
    User();
    ~User();
    int hashfunc(int& id);
    int HashFunc(const string& name);
    void userRegister(const string& uname, const string& password);
    bool Login(const string& uname, const string& password);
    void viewProfile(const string& username);
    void delayProgram(int time);
};
