#ifndef USER_MANAGER_H
#define USER_MANAGER_H

#include "../ds/HashTable.h"
#include "../models/User.h"
using namespace std;

class UserManager {
private:
    HashTable<User> users;

public:
    void addUser(int userID, string name, string email);
    User* getUser(int userID);
    void displayAllUsers() const;
};

#endif
