#ifndef BIKE_H
#define BIKE_H

class Bike {
    private:
        int bikeID;
        bool available;

    public:
        Bike(int id);
        int getBikeID() const;
        void rentBike();
        void returnBike();
        bool isAvailable() const;
        void displayBike() const;
};

#endif