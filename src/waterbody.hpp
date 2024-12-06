#pragma once

#include <string>
#include <iostream>

static const double MIN_LATITUDE = -90.0;
static const double MAX_LATITUDE = 90.0;
static const double MIN_LONGITUDE = -180.0;
static const double MAX_LONGITUDE = 180.0;

/* -------------------------------------- **
 * Watertool : Waterbody (Header)         *
 * Editor(s) : Alexander Del Brocco, Tom O*
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

class Waterbody
{
  public:
    Waterbody(const std::string&, const std::string&, const std::string&, const std::string&, int, char, double, const std::string&, const std::string&, bool);
    string getSamplingPoint() const { return samplingPoint; }
    string getTime() const { return time; }
    string getDeterminand() const { return determinand; }
    string getDeterminandDefinition() const { return determinandDefinition; }

    int getDeterminandNotation() const { return determinandNotation; }

    char getResultQualifier() const { return resultQualifier; }
    double getResult() const { return result; }
    std::string getDeterminandUnit() const { return determinandUnit; }
    std::string getSampledMaterialType() const { return sampledMaterialType; }
    bool getSampleCompliant() const { return sampleCompliant; }

  private:
    std::string samplingPoint;
    std::string time;
    std::string determinand;
    std::string determinandDefinition;

    int determinandNotation;
    char resultQualifier;
    double result;

    std::string determinandUnit;
    std::string sampledMaterialType;
    bool sampleCompliant;

};

std::ostream& operator << (std::ostream&, const Waterbody&);
