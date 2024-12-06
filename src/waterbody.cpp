#include <stdexcept>
#include <sstream>
#include "waterbody.hpp"

using namespace std;

/* -------------------------------------- **
 * Watertool : Waterbody                  *
 * Editor(s) : Alexander Del Brocco       *
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

Waterbody::Waterbody(const string& tm, double lat, double lon, double dep, double mag):
  time(tm), latitude(lat), longitude(lon), depth(dep), magnitude(mag)
{
  ostringstream error;

  if (latitude < MIN_LATITUDE or latitude > MAX_LATITUDE) {
    error << "Invalid latitude: " << latitude;
    throw out_of_range(error.str());
  }

  if (longitude < MIN_LONGITUDE or longitude > MAX_LONGITUDE) {
    error << "Invalid longitude: " << longitude;
    throw out_of_range(error.str());
  }

  if (depth < 0.0) {
    error << "Invalid depth: " << depth;
    throw out_of_range(error.str());
  }

  if (magnitude < 0.0) {
    error << "Invalid magnitude: " << magnitude;
    throw out_of_range(error.str());
  }

  name = "";
  type = "";
  coords = "";
  time = "";

  pollutant = "";
  result = 0.0;
  unit = "";
}


ostream& operator<<(ostream& out, const Waterbody& waterbody)
{
  return out << "Time: " << waterbody.getTime()
             << "\nLatitude: " << waterbody.getLatitude() << " deg"
             << "\nLongitude: " << waterbody.getLongitude() << " deg"
             << "\nDepth: " << waterbody.getDepth() << " km"
             << "\nMagnitude: " << waterbody.getMagnitude() << endl;
}
