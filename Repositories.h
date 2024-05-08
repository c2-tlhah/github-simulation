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

struct repoNode {
    string owner;
    string name;
    bool isprivate;
    int forkCount;
    file* filehead;
    commit* commithead;
    repoNode* left;
    repoNode* right;
    repoNode(string o, string n, bool p) : owner(o), name(n), isprivate(p), forkCount(0), filehead(nullptr), commithead(nullptr), left(nullptr), right(nullptr) {}
};

class repoManager {
private:
    repoNode* root;
    repoNode* insert(repoNode* node, string owner, string name, bool isprivate);
    repoNode* search(repoNode* node, string name);
    string generateCommitID();
    void copyFiles(repoNode* originalnode, repoNode* newnode);
    void copyCommits(repoNode* originalnode, repoNode* newnode);
    void save_csv(repoNode* node, ofstream& file);
public:
    repoManager();
    repoNode* createRepo(string owner, string name, bool isprivate);
    void forkRepo(string forkOwner, string originalName);
    void addCommit(repoNode* node, string commit_message);
    void saveCommits(string repo_name);
    void loadCommits(string repo_name);
    void addFile(repoNode* node, string filename);
    void deleteFile(repoNode* node, string filename);
    void displayRepoStats(repoNode* node);
    void displayRepoStats(string repoName);
    void load_csv(string filename);
    void save_csv(string filename);
    void deleteRepo(string name);
    void displayMenu();
    repoNode* deleteRepo(repoNode* node, string name);
    repoNode* minValueNode(repoNode* node);

    void runGithub();
};

#endif // REPOSITORYMANAGER_H

