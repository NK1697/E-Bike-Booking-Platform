#include "../../include/managers/UserManager.h"
#include <iostream>
using namespace std;

void UserManager::addUser(int userID, string name, string email) {
    if (users.contains(userID)) {
        cout << "User " << userID << " already exists.\n";
        return;
    }
    users.insert(userID, User(userID, name, email));
    cout << "User " << userID << " registered successfully.\n";
}

User* UserManager::getUser(int userID) {
    return users.find(userID);
}

void UserManager::displayAllUsers() const {
    if (users.empty()) {
        cout << "No users registered.\n";
        return;
    }
    users.forEach([](int, const User& user) {
        user.displayUser();
        cout << '\n';
    });
}
