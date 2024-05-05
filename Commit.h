#pragma once
#ifndef COMMIT_H
#define COMMIT_H

#include <string>
#include <ctime>
using namespace std;
struct Commit {
    string id;
    string message;
    time_t timestamp;
    Commit* next;

    Commit(string id, string message, time_t timestamp);
};

#endif // COMMIT_H
#pragma once
