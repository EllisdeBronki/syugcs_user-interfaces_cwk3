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
    Waterbody(const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&, const std::string&);
    std::string getSamplingPoint() const { return samplingPoint; }
    std::string getTime() const { return time; }
    std::string getDeterminand() const { return determinand; }
    std::string getDeterminandDefinition() const { return determinandDefinition; }

    std::string getDeterminandNotation() const { return determinandNotation; }

    std::string getResultQualifier() const { return resultQualifier; }
    std::string getResult() const { return result; }
    std::string getDeterminandUnit() const { return determinandUnit; }
    std::string getSampledMaterialType() const { return sampledMaterialType; }
    std::string getSampleCompliant() const { return sampleCompliant; }

  private:
    std::string samplingPoint;
    std::string time;
    std::string determinand;
    std::string determinandDefinition;

    std::string determinandNotation;
    std::string resultQualifier;
    std::string result;

    std::string determinandUnit;
    std::string sampledMaterialType;
    std::string sampleCompliant;

};

std::ostream& operator << (std::ostream&, const Waterbody&);
