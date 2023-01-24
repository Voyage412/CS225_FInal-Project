#pragma once
#include <vector>
#include <string>

class Route{
    public:
        // Default constructor
        Route();

        /**
         * Constructor with the given information of an route
         * @param AirlineID
         * @param Airline
         * @param srcID
         * @param dstID
         * @param stop
         */
        Route(int AirlineID, std::string Airline, int srcID, int dstID, int stop);

        // get the airline ID
        int getAirlineID();

        // get the source airport ID
        int getsrcID();

        // get the destination airport ID
        int getdstID();

        /**
         * set the airline ID
         * @param airlineId
        */
        void setAirlineID(int airlineId);
        
        /**
         * set the airline name
         * @param airline
        */
        void setAirline(std::string airline);

        /**
         * set the source airport ID
         * @param srcId
        */
        void setSrcID(int srcId);

        /**
         * set the destination airport ID
         * @param dstId
        */
        void setDstID(int dstId);

        /**
         * set the number of stop
         * @param s
        */
        void setStop(int s);

        // equality operator
        bool operator==(const Route & other) const;
    private:
        int AirlineID_;
        std::string Airline_;
        int srcID_; 
        int dstID_;
        int stop_;
        



};

