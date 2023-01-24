#pragma once
#include <string>

class Airport {
    private:
        int id_;
        std::string name_;
        std::string city_;
        std::string country_;
        double latitude_;
        double longitude_;
    public:
        // Default Constructor  
        Airport();
        /**
         * Constructor with the given information of an airport
         * @param id
         * @param name
         * @param city
         * @param country_
         * @param latitude
         * @param longitude
        */
        Airport(int id, std::string name, std::string city, std::string country_, double latitude, double longitude);

        /**
         * Copy Constructor with the another airport object
         * @param other
        */
        Airport(const Airport& other);

        // Get Airport ID
        int getID();

        // get Airport name
        std::string getName();

        /**
         * Equality operator 
         * @param other
        */
        bool operator==(const Airport & other) const;

        /**
         * Assignment operator
         * @param other
        */
        Airport operator=(const Airport & other);
    
};


