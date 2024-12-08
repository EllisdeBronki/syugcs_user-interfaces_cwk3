#include <stdexcept>
#include <sstream>
#include "waterbody.hpp"

using namespace std;

/* -------------------------------------- **
 * Watertool : Waterbody                  *
 * Editor(s) : Alexander Del Brocco, Tom O*
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

Waterbody::Waterbody(const std::string& location, const std::string& tm, const std::string& pollutant, const std::string& pollutantInfo, const std::string& pollutantNotation, char resQualifier, const std::string& res, const std::string& unit, const std::string& matType, const std::string& compliant):
  //time(tm), latitude(lat), longitude(lon), depth(dep), magnitude(mag)
  samplingPoint(location), time(tm), determinand(pollutant), determinandDefinition(pollutantInfo), determinandNotation(pollutantNotation), resultQualifier(resQualifier), result(res), determinandUnit(unit), sampledMaterialType(matType), sampleCompliant(compliant)
{
  ostringstream error;
  error << "Error Found";
  // Add any error checking in here - I'm sure we will find out what are the errors later :)
}


ostream& operator<<(ostream& out, const Waterbody& waterbody)
{
  return out << "Location: " << waterbody.getSamplingPoint()
             << "\nTime: " << waterbody.getTime()
             << "\nPollutant: " << waterbody.getDeterminand()
             << "\nPollutant Info: " << waterbody.getDeterminandDefinition() 
             << "\nPollutant Code: " << waterbody.getDeterminandNotation() 
             << "\nResult Qualifier: " << waterbody.getResultQualifier()
             << "\nResult: " << waterbody.getResult() << " " << waterbody.getDeterminandUnit()
             << "\nMaterial Sampled: " << waterbody.getSampledMaterialType()
             << "\nCompliant?: " << waterbody.getSampleCompliant()
             << endl;
}
