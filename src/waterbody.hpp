#pragma once

#include <string>
#include <iostream>

static const double MIN_LATITUDE = -90.0;
static const double MAX_LATITUDE = 90.0;
static const double MIN_LONGITUDE = -180.0;
static const double MAX_LONGITUDE = 180.0;

/* -------------------------------------- **
 * Watertool : Waterbody (Header)         *
 * Editor(s) : Alexander Del Brocco       *
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

class Waterbody
{
  public:
    Waterbody(const std::string&, double, double, double, double);
    double getLatitude() const { return latitude; }
    double getLongitude() const { return longitude; }
    double getDepth() const { return depth; }
    double getMagnitude() const { return magnitude; }

    std::string getName() const { return name; }
    std::string getType() const { return type; }
    std::string getCoords() const { return coords; }
    std::string getTime() const { return time; }
    std::string getPollutant() const { return pollutant; }
    float getResult() const { return result; }
    std::string getUnit() const { return unit; }

  private:
    double latitude;
    double longitude;
    double depth;
    double magnitude;

    std::string name;
    std::string type;
    std::string coords;
    std::string time;

    std::string pollutant;
    float result;
    std::string unit;

};

std::ostream& operator << (std::ostream&, const Waterbody&);
