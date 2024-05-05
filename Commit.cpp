#include "Commit.h"
using namespace std;
Commit::Commit(string id, string message, time_t timestamp)
    : id(id), message(message), timestamp(timestamp), next(nullptr) {}
