#include "../../include/managers/UserManager.h"
#include <iostream>
using namespace std;

void UserManager::addUser(int userID, string name, string email) {
    if (users.find(userID) != users.end()) {
        cout << "User " << userID << " already exists.\n";
        return;
    }
    users.emplace(userID, User(userID, name, email));
    cout << "User " << userID << " registered successfully.\n";
}

User* UserManager::getUser(int userID) {
    auto it = users.find(userID);
    if (it == users.end()) {
        return nullptr;
    }
    return &(it->second);
}

void UserManager::displayAllUsers() const {
    if (users.empty()) {
        cout << "No users registered.\n";
        return;
    }
    for (const auto& pair : users) {
        pair.second.displayUser();
        cout << '\n';
    }
}