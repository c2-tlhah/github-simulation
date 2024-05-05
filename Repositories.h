#pragma once
#ifndef REPOSITORIES_H
#define REPOSITORIES_H

#include <string>
#include <fstream>

using namespace std;

struct file {
    string name;
    file* next;
    file(string n) : name(n), next(nullptr) {}
};

struct commit {
    string id;
    string message;
    time_t timestamp;
    commit* next;
    commit(string i, string m, time_t t) : id(i), message(m), timestamp(t), next(nullptr) {}
};

struct repositoryNode {
    string owner;
    string name;
    bool isprivate;
    int forkCount;
    file* filehead;
    commit* commithead;
    repositoryNode* left;
    repositoryNode* right;
    repositoryNode(string o, string n, bool p) : owner(o), name(n), isprivate(p), forkCount(0), filehead(nullptr), commithead(nullptr), left(nullptr), right(nullptr) {}
};

class repositorymanager {
private:
    repositoryNode* root;
    repositoryNode* insert(repositoryNode* node, string owner, string name, bool isprivate);
    repositoryNode* search(repositoryNode* node, string name);
    string generateCommitID();
    void copyFiles(repositoryNode* originalnode, repositoryNode* newnode);
    void copyCommits(repositoryNode* originalnode, repositoryNode* newnode);
    void save_csv(repositoryNode* node, ofstream& file);
public:
    repositorymanager();
    repositoryNode* createRepository(string owner, string name, bool isprivate);
    void forkRepo(string forkOwner, string originalName);
    void addCommit(repositoryNode* node, string commit_message);
    void saveCommits(string repo_name);
    void loadCommits(string repo_name);
    void addFile(repositoryNode* node, string filename);
    void deleteFile(repositoryNode* node, string filename);
    void displayRepositoryStats(repositoryNode* node);
    void displayRepositoryStats(string repoName);
    void load_csv(string filename);
    void save_csv(string filename);
    void deleteRepository(string name);
    void displayMenu();
    repositoryNode* deleteRepository(repositoryNode* node, string name);
    repositoryNode* minValueNode(repositoryNode* node);

    void run();
};

#endif // REPOSITORYMANAGER_H

