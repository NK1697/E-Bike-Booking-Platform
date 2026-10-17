#include "../../include/models/User.h"
#include <iostream>
using namespace std;

User::User(int id, string name, string email) {
    userID = id;
    this->name = name;
    this->email = email;
    currentBikeID = -1;
}

int User::getUserID() const {
    return userID;
}

string User::getName() const {
    return name;
}

string User::getEmail() const {
    return email;
}

void User::displayUser() const {
    cout << "User ID: " << userID << '\n';
    cout << "Name: " << name << '\n';
    cout << "Email: " << email << '\n';
}

void User::assignBike(int bikeID){
    currentBikeID = bikeID;
}

void User::returnBike() {
    currentBikeID = -1;
}

bool User::hasBike() const{
    return currentBikeID != -1;
}

int User::getCurrentBike() const{
    return currentBikeID;
}