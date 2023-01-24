#include "Airport.h"

    // Default Constructor
Airport::Airport(){
    id_ = 0;
    name_ = "";
    city_ = "";
    latitude_ = 0.0;
    longitude_ = 0.0;

}
// Constructor with the given information of an airport
Airport::Airport(int id, std::string name, std::string city, std::string country, double latitude, double longitude) {
    id_ = id;
    name_ = name;
    city_ = city;
    country_ = country;
    latitude_ = latitude;
    longitude_ = longitude;
}

// Copy Constructor with the another airport object
Airport::Airport(const Airport& other){
    id_ = other.id_;
    name_ = other.name_;
    city_ = other.city_;
    latitude_ = other.latitude_;
    longitude_ = other.longitude_;
}

// Equality operator 
bool Airport::operator==(const Airport & other) const{
    if(id_ != other.id_)return false;
    if(name_ != other.name_) return false;
    if(city_ != other.city_) return false;
    if(latitude_ != other.latitude_) return false;
    if(longitude_ != other.longitude_) return false;
    return true;

}

// Assignment operator with the given airport
Airport Airport::operator=(const Airport & other) {
    id_ = other.id_;
    name_ = other.name_;
    city_ = other.city_;
    latitude_ = other.latitude_;
    longitude_ = other.longitude_;
    return *this;
}

// Get Airport ID
int Airport::getID() {
    return id_;
}
// get Airport name
std::string Airport::getName() {
    return name_;
}