#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
    private:
        int userID;
        string name;
        string email;
        int currentBikeID;

    public:
        User(int id, string name, string email);
        int getUserID() const;
        string getName() const;
        string getEmail() const;
        void displayUser() const;

        void assignBike(int bikeID);
        void returnBike();
        bool hasBike() const;
        int getCurrentBike() const;
};

#endif