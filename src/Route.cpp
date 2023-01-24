#include "Route.h"

// Default constructor
Route::Route() {
    AirlineID_ = 0;
    Airline_ = "";
    srcID_ = 0; 
    dstID_ = 0;
    stop_ = 0;
}

/**
 * Constructor with the given information of an route
 * @param AirlineID
 * @param Airline
 * @param srcID
 * @param dstID
 * @param stop
 */
Route::Route(int AirlineID, std::string Airline, int srcID, int dstID, int stop) {
    AirlineID_ = AirlineID;
    Airline_ = Airline ;
    srcID_ = srcID; 
    dstID_ = dstID;
    stop_ = stop;
}

/**
 * set the airline ID
 * @param airlineId
 */
void Route::setAirlineID(int airlineId) {
    AirlineID_ = airlineId;
}

/**
 * set the airline name
 * @param airline
 */
void Route::setAirline(std::string airline) {
    Airline_ = airline;
}

/**
 * set the destination airport ID
 * @param dstId
 */
void Route::setDstID(int dstId) {
    dstID_ = dstId;
}

/**
 * set the source airport ID
 * @param srcId
 */
void Route::setSrcID(int srcId) {
    srcID_ = srcId;
}

/**
 * set the number of stop
 * @param stop
 */
void Route::setStop(int stop) {
    stop_ = stop;
}

// get the source airport ID
int Route::getsrcID() {
    return srcID_;
}

// get the destination airport ID
int Route::getdstID() {
    return dstID_;
}

// get the airline ID
int Route::getAirlineID() {
    return AirlineID_;
}

// equality operator
bool Route::operator==(const Route & other) const {
    if(AirlineID_ != other.AirlineID_) return false;
    if(Airline_ != other.Airline_) return false;
    if(srcID_ != other.srcID_) return false;
    if(dstID_ != other.dstID_) return false;
    if(stop_ != other.stop_) return false;
    return true;
}