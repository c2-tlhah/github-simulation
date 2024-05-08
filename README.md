# GitHub Simulation Console Application

## Project Description

The GitHub Simulation Console Application enables users to create accounts, manage repositories, make commits, and interact with other users. It is a command-line based application, focusing on the utilization of data structures such as linked lists, trees, graphs, and hash tables.

### Key Features

1. **User Accounts**
   - Registration: Users can create new accounts with unique usernames and passwords.
   - Login/Logout: Users can login and logout from their accounts.
   - Profile View: Users can view their own or others' profiles, displaying usernames, followers, repositories, and files in specific repositories if they are public.

2. **Repositories**
   - Creation: Users can create new repositories.
   - Deletion: Users have the option to delete their repositories.
   - Fork: Users can copy public repositories, including files and commits, from other users.
   - Visibility: Users can set their repositories as private or public during creation.
   - Commit: Users can add commits to their repositories.
   - View Stats: Users can view repository statistics such as repository name, files, commits, and fork count.

   **Files in repositories**
   - Add Files: Users can add or push files to specific repositories.
   - Delete Files: Users can delete files from specific repositories.

3. **Social Features**
   - Follow/Unfollow: Users can follow or unfollow other users.

### Feature Details

1. **User Accounts**
   - **Data Structure:** Hash Table
   - **Usage:** Hash tables facilitate efficient user management, including registration, login, and profile viewing functionalities.
   - **Management:** User information is stored in the hash table with usernames as keys during registration. Login credentials are verified by querying the hash table. User profiles are retrieved from the hash table for display.

2. **Repositories**
   - **Data Structures:** Trees, Linked Lists
   - **Trees:**
     - **Usage:** Trees represent the hierarchical structure of repositories.
     - **Management:** Each repository is a node in a tree, with operations like creation and deletion modifying the tree structure.
   - **Linked Lists:**
     - **Usage:** Linked lists store commits and files associated with repositories.
     - **Management:** Separate linked lists are maintained for commits and files, with new commits added to the head of the list to preserve chronological order.

3. **Social Features**
   - **Data Structure:** Graphs
   - **Usage:** Graphs represent the network of users, where vertices represent users and edges represent follow relationships.
   - **Management:** Following another user creates an edge between their vertices, while unfollowing removes the edge.

## Project Team
- Muhammad Talha Ramzan

## How to Run the Application
1. Clone the repository to your local machine.
2. Navigate to the project directory.
3. Compile the source code using a C++ compiler.
4. Run the compiled executable file or sln file.
5. Follow the on-screen instructions to navigate through the application's functionalities.
