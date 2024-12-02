#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "hydroset.hpp"
#include "csv.hpp"

using namespace std;

/* -------------------------------------- **
 * Watertool : Hydroset                   *
 * Editor(s) : Alexander Del Brocco       *
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

void Hydroset::loadData(const string& filename)
{
  csv::CSVReader reader(filename);

  data.clear();

  for (const auto& row: reader) {
    Waterbody waterbody{
      row["time"].get<>(),
      row["latitude"].get<double>(),
      row["longitude"].get<double>(),
      row["depth"].get<double>(),
      row["mag"].get<double>()
    };
    data.push_back(waterbody);
  }
}


Waterbody Hydroset::strongest() const
{
  checkDataExists();

  auto waterbody = max_element(data.begin(), data.end(),
    [](Waterbody a, Waterbody b) { return a.getMagnitude() < b.getMagnitude(); });

  return *waterbody;
}


Waterbody Hydroset::shallowest() const
{
  checkDataExists();

  auto waterbody = min_element(data.begin(), data.end(),
    [](Waterbody a, Waterbody b) { return a.getDepth() < b.getDepth(); });

  return *waterbody;
}


double Hydroset::meanDepth() const
{
  checkDataExists();

  auto sum = accumulate(data.begin(), data.end(), 0.0,
    [](double total, Waterbody q) { return total + q.getDepth(); });

  return sum / data.size();
}


double Hydroset::meanMagnitude() const
{
  checkDataExists();

  auto sum = accumulate(data.begin(), data.end(), 0.0,
    [](double total, Waterbody q) { return total + q.getMagnitude(); });

  return sum / data.size();
}


void Hydroset::checkDataExists() const
{
  if (size() == 0) {
    throw std::runtime_error("Dataset is empty!");
  }
}
