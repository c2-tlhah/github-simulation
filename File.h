#pragma once
#pragma once
#ifndef FILE_H
#define FILE_H

#include <string>
using namespace std;
struct File {
    string name;
    File* next;

    File(string name);
};

#endif // FILE_H
