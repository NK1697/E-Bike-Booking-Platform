#ifndef BIKE_H
#define BIKE_H

class Bike {
    private:
        int bikeID;
        bool available;
        bool needsMaintenance;

    public:
        Bike(int id);
        int getBikeID() const;
        void rentBike();
        void returnBike();
        bool sendForMaintenance();
        void completeMaintenance();
        bool isAvailable() const;
        bool isUnderMaintenance() const;
        void displayBike() const;
};

#endif
