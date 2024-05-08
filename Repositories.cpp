#include"Repositories.h"
#include"repoStats.h"
#include"signIn.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include<vector>
#include <ctime>
#include <cstdlib>

using namespace std;

void repoManager::deleteRepo(string name) {
    root = deleteRepo(root, name);
}

repoNode* repoManager::deleteRepo(repoNode* node, string name) {
    if (node == nullptr) {
        return nullptr;
    }
    if (name < node->name) {
        node->left = deleteRepo(node->left, name);
    }
    else if (name > node->name) {
        node->right = deleteRepo(node->right, name);
    }
    else {
        if (node->left == nullptr) {
            repoNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) {
            repoNode* temp = node->left;
            delete node;
            return temp;
        }
        repoNode* temp = minValueNode(node->right);
        node->name = temp->name;
        node->right = deleteRepo(node->right, temp->name);
    }

    // Update the repo.csv file after deletion
    save_csv("repo.csv");

    return node;
}


repoNode* repoManager::minValueNode(repoNode* node) {
    repoNode* current = node;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

repoManager::repoManager() : root(nullptr) {}

repoNode* repoManager::createRepo(string owner, string name, bool isprivate) {
    root = insert(root, owner, name, isprivate);
    return root;
}

repoNode* repoManager::insert(repoNode* node, string owner, string name, bool isprivate) {
    if (node == nullptr) {
        return new repoNode(owner, name, isprivate);
    }
    else if (name.compare(node->name) < 0) {
        node->left = insert(node->left, owner, name, isprivate);
    }
    else {
        node->right = insert(node->right, owner, name, isprivate);
    }
    return node;
}

repoNode* repoManager::search(repoNode* node, string name) {
    if (node == nullptr || node->name == name) {
        return node;
    }
    if (name < node->name) {
        return search(node->left, name);
    }
    else {
        return search(node->right, name);
    }
}

void repoManager::forkRepo(string forkowner, string original_name) {
    repoNode* originalrepo = search(root, original_name);
    if (originalrepo != nullptr) {
        repoNode* forkedrepo = createRepo(forkowner, originalrepo->name + "_fork", originalrepo->isprivate);
        copyFiles(originalrepo, forkedrepo);
        copyCommits(originalrepo, forkedrepo);
        originalrepo->forkCount++;
        cout << "Repository forked successfully." << endl;
    }
    else {
        cout << "Original repository not found." << endl;
    }
}

void repoManager::copyFiles(repoNode* originalnode, repoNode* newnode) {
    if (originalnode == nullptr || newnode == nullptr) {
        return;
    }
    file* originalfileptr = originalnode->filehead;
    file* newfileptr = nullptr;
    while (originalfileptr != nullptr) {
        file* newfile = new file(originalfileptr->name);
        if (newnode->filehead == nullptr) {
            newnode->filehead = newfile;
            newfileptr = newfile;
        }
        else {
            newfileptr->next = newfile;
            newfileptr = newfileptr->next;
        }
        originalfileptr = originalfileptr->next;
    }
}

void repoManager::copyCommits(repoNode* originalnode, repoNode* newnode) {
    if (originalnode == nullptr || newnode == nullptr) {
        return;
    }
    commit* originalcommitptr = originalnode->commithead;
    commit* newcommitptr = nullptr;
    while (originalcommitptr != nullptr) {
        commit* newcommit = new commit(originalcommitptr->id, originalcommitptr->message, originalcommitptr->timestamp);
        if (newnode->commithead == nullptr) {
            newnode->commithead = newcommit;
            newcommitptr = newcommit;
        }
        else {
            newcommitptr->next = newcommit;
            newcommitptr = newcommitptr->next;
        }
        originalcommitptr = originalcommitptr->next;
    }
}

string repoManager::generateCommitID() {
    string id = "";
    const string chars = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM1234567890";
    const int idLength = 10;
    for (int i = 0; i < idLength; ++i) {
        id += chars[rand() % chars.length()];
    }
    return id;
}

void repoManager::addCommit(repoNode* node, string commit_message) {
    if (node == nullptr) {
        cout << "Repository not found." << endl;
        return;
    }
    string commit_id = generateCommitID();
    time_t timestamp = time(nullptr);
    commit* newcommit = new commit(commit_id, commit_message, timestamp);
    newcommit->next = node->commithead;
    node->commithead = newcommit;
}

void repoManager::saveCommits(string repo_name) {
    repoNode* node = search(root, repo_name);
    if (node == nullptr) {
        cerr << "Repository '" << repo_name << "' not found." << endl;
        return;
    }
    string filename = repo_name + "_commits.csv";
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open the file " << filename << " for repository " << repo_name << endl;
        return;
    }
    file << "Commit ID,Message,Timestamp" << endl;
    commit* commitPtr = node->commithead;
    while (commitPtr != nullptr) {
        file << commitPtr->id << "," << commitPtr->message << "," << commitPtr->timestamp << endl;
        commitPtr = commitPtr->next;
    }
    file.close();
    cout << "Commits for repository '" << repo_name << "' saved to CSV successfully." << endl;
}

void repoManager::loadCommits(string repo_name) {
    repoNode* node = search(root, repo_name);
    if (node == nullptr) {
        cerr << "Repository '" << repo_name << "' not found." << endl;
        return;
    }
    string filename = repo_name + "_commits.csv";
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file " << filename << " for repository " << repo_name << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        istringstream iss(line);
        string commit_id, commit_message, timestampStr;
        time_t timestamp;
        getline(iss, commit_id, ',');
        getline(iss, commit_message, ',');
        getline(iss, timestampStr, ',');
        timestamp = stoi(timestampStr);
        commit* newcommit = new commit(commit_id, commit_message, timestamp);
        newcommit->next = node->commithead;
        node->commithead = newcommit;
    }
    file.close();
    cout << "Commits for repository '" << repo_name << "' loaded from CSV successfully." << endl;
}

void repoManager::addFile(repoNode* node, string filename) {
    if (node == nullptr) {
        cout << "Repository not found." << endl;
        return;
    }
    file* newfile = new file(filename);
    newfile->next = node->filehead;
    node->filehead = newfile;
}

void repoManager::deleteFile(repoNode* node, string filename) {
    if (node == nullptr) {
        cout << "Repository not found." << endl;
        return;
    }
    file* current = node->filehead;
    file* prev = nullptr;
    while (current != nullptr && current->name != filename) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        cout << "File not found in the repository." << endl;
        return;
    }
    if (prev == nullptr) {
        node->filehead = current->next;
    }
    else {
        prev->next = current->next;
    }
    delete current;
    cout << "File '" << filename << "' deleted from the repository." << endl;
}

void repoManager::displayRepoStats(repoNode* node) {
    if (node == nullptr) {
        cout << "Repository not found." << endl;
        return;
    }
    cout << "Repository Name: " << node->name << endl;
    cout << "Owner: " << node->owner << endl;
    cout << "Private: " << (node->isprivate ? "Yes" : "No") << endl;
    cout << "Fork Count: " << node->forkCount << endl;
    int fileCount = 0;
    file* currentFile = node->filehead;
    while (currentFile != nullptr) {
        fileCount++;
        currentFile = currentFile->next;
    }
    cout << "File Count: " << fileCount << endl;
    int commitCount = 0;
    commit* currentCommit = node->commithead;
    while (currentCommit != nullptr) {
        commitCount++;
        currentCommit = currentCommit->next;
    }
    cout << "Commit Count: " << commitCount << endl;
}

void repoManager::displayRepoStats(string repoName) {
    repoNode* node = search(root, repoName);
    displayRepoStats(node);
}

void repoManager::load_csv(string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Unable to open the file " << filename << endl;
        return;
    }
    string line;
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

void repoManager::save_csv(string filename) {
    ofstream file(filename, ios::app);
    if (!file.is_open()) {
        cout << "Unable to open the file " << filename << endl;
        return;
    }
    file << "Owner,Name,IsPrivate,ForkCount" << endl;
    save_csv(root, file);
    file.close();
    cout << "Repositories saved to CSV successfully." << endl;
}

void repoManager::save_csv(repoNode* node, ofstream& file) {
    if (node == nullptr) {
        return;
    }
    save_csv(node->left, file);
    file << node->owner << "," << node->name << "," << (node->isprivate ? "Yes" : "No") << "," << node->forkCount << endl;
    save_csv(node->right, file);
}

void repoManager::displayMenu() {
    cout << "1. Create a repository" << endl;
    cout << "2. Delete a repository" << endl;
    cout << "3. Fork a repository" << endl;
    cout << "4. Add commits" << endl;
    cout << "5. Save repositories to CSV" << endl;
    cout << "6. Load repositories from CSV" << endl;
    cout << "7. Add file to repository" << endl;
    cout << "8. Delete file from repository" << endl;
    cout << "9. View repository stats" << endl;
    cout << "10. Exit" << endl;
    cout << "Enter your choice: ";
}
void repoManager::runGithub() {
    User user;
    string username, password;
    int followers;
    vector<pair<string, bool>> repositories;

    bool logoutRequested = false;  // Flag to indicate logout request

    while (!logoutRequested) {
        cout << "\033[1;33mWelcome to \033[0m";

        // Red color for "GitHub"
        cout << "\033[1;31mGitHub \033[0m";

        // Yellow color for "Simulation"
        cout << "\033[1;36m\n1. Press 1 for new registration.\033[0m" << endl;
        cout << "\033[1;36m2. Press 2 to sign in.\033[0m" << endl;
        cout << "\033[1;36m3. Press 3 to view a profile.\033[0m" << endl;
        cout << "\033[1;36m4. Press 4 to exit.\033[0m" << endl;
        cout << "\033[1;36mEnter the number of your choice: \033[0m";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "\t\t--USER REGISTRATION PAGE--" << endl;
            cout << "Enter username: ";
            cin >> username;

            cout << "Enter password: ";
            cin >> password;

            user.registerUser(username, password);
            break;
        }
        case 2: {
            cout << "\t\t--LOGIN PAGE--" << endl;
            cout << "Enter username: ";
            cin >> username;
            cout << "Enter password: ";
            cin >> password;
            system("cls");
            if (user.Login(username, password)) {

                cout << "Login successful!" << endl;
                system("cls");
                cout << "Press 1 to Repositories page." << endl;
                cout << "Press 2 to Social page." << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                cout << endl;
                if (choice == 1)
                {
                    int choice;
                    string owner, name, commit_message, filename, repoName, fileName;
                    int isPrivate;
                    do {
                        displayMenu();
                        cin >> choice;
                        switch (choice) {
                        case 1: {
                            cout << "Enter owner name (username): ";
                            cin >> owner;
                            cout << "Enter repository name: ";
                            cin >> name;
                            cout << "Is the repository private? ";
                            cout << "\nEnter 1 for Yes and 0 for No: ";
                            cin >> isPrivate;
                            createRepo(owner, name, isPrivate);
                            cout << "Repository created successfully." << endl;
                            cout << endl;
                            break;
                        }
                        case 2: {
                            cout << "Enter repository name to delete: ";
                            cin >> name;
                            deleteRepo(name);
                            cout << "Repository deleted successfully." << endl;
                            break;
                        }
                        case 3: {
                            cout << "Enter the name of the repository to fork: ";
                            cin >> name;
                            cout << "Enter the owner of the forked repository: ";
                            cin >> owner;
                            forkRepo(owner, name);

                            break;
                        }
                        case 4: {
                            cout << "Enter the name of the repository to add commits: ";
                            cin >> name;
                            cout << "Enter the commit message: ";
                            cin.ignore();
                            getline(cin, commit_message);
                            addCommit(search(root, name), commit_message);
                            cout << "Commit added successfully." << endl;
                            break;
                        }
                        case 5: {
                            save_csv("repo.csv");
                            break;
                        }
                        case 6: {
                            load_csv("repo.csv");
                            break;
                        }
                        case 7: {
                            cout << "Enter repository name: ";
                            cin >> repoName;
                            cout << "Enter file name to add: ";
                            cin >> fileName;
                            addFile(search(root, repoName), fileName);
                            cout << "File added to repository." << endl;
                            break;
                        }
                        case 8: {
                            cout << "Enter repository name: ";
                            cin >> repoName;
                            cout << "Enter file name to delete: ";
                            cin >> fileName;
                            deleteFile(search(root, repoName), fileName);
                            break;
                        }
                        case 9: {
                            cout << "Enter repository name: ";
                            cin >> repoName;
                            displayRepoStats(repoName);
                            break;
                        }
                        case 10: {
                            logoutRequested = true;
                            break;

                        }
                        default: {
                            cout << "Invalid choice. Please enter a number between 1 and 12." << endl;
                        }
                        }
                    } while (!logoutRequested);
                    if (logoutRequested) {
                        cout << "Returning to login page..." << endl;

                        system("cls");
                        runGithub();
                    }
                }

                else if (choice == 2)
                {

                    cout << "--";
                    repoStats network;
                    network.loadFromFile("social_network.csv");

                    string command;
                    while (true) {
                        cout << "\n\033[1;36mPlease enter a command:\033[0m";
                        cout << "\n\033[1;35mFollow\033[0m    - Follow a user";
                        cout << "\n\033[1;35mUnfollow\033[0m  - Unfollow a user";
                        cout << "\n\033[1;35mDisplay\033[0m   - Display followers";
                        cout << "\n\033[1;35mSave\033[0m      - Save changes";
                        cout << "\n\033[1;35mExit!\033[0m      - Exit the program\n";
                        cout << "Your choice: ";

                        cin >> command;
                        if (command == "follow") {
                            string user, follower;
                            cout << "Enter the user name: ";
                            cin >> user;
                            cout << "Enter the follower name: ";
                            cin >> follower;
                            network.follow(user, follower);
                        }

                        else if (command == "unfollow") {
                            string user, follower;
                            cout << "Enter the user name: ";
                            cin >> user;
                            cout << "Enter the follower name: ";
                            cin >> follower;
                            network.unfollow(user, follower);
                        }

                        else if (command == "display") {
                            string user;
                            cout << "Enter the user name: ";
                            cin >> user;
                            network.displayFollowers(user);
                        }

                        else if (command == "save") {
                            network.saveToFile("social_network.csv");
                            cout << "Save it into file successfully !! " << endl;
                        }

                        else if (command == "exit") {
                            cout << "Exit successfully.... ";
                            break;
                        }

                        else {
                            cout << "Invalid command. Please try again." << endl;
                        }
                    }

                }
            }
            else {
                cout << "Login failed!" << endl;
            }
            break;
        }
        case 3: {
            cout << "\t\t--Profile--         " << endl;
            cout << "Enter username: ";
            cin >> username;
            system("cls");
            user.viewProfile(username);
            break;
        }
        case 4: {
            system("cls");
            cout << "Exited successfully!" << endl;
            logoutRequested = true;  // Set flag to indicate logout
            break;
        }
        default: {
            cout << "Invalid choice!" << endl;
            break;
        }
        }
    }
}

