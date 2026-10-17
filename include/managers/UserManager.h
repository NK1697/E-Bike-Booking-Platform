#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include <unordered_map>
#include "../models/User.h"
using namespace std;

class UserManager {
private:
    unordered_map<int, User> users;

public:
    void addUser(int userID, string name, string email);
    User* getUser(int userID);
    void displayAllUsers() const;
};

#endif