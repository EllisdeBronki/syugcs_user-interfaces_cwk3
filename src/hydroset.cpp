#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "hydroset.hpp"
#include "csv.hpp"

static const std::string SAMPLE_TIME      = "sample.sampleDateTime";
static const std::string SAMPLING_POINT   = "sample.samplingPointLabel";
static const std::string SAMPLED_MATERIAL = "sample.sampledMaterialType.label";

static const std::string DETERMINAND           = "determinand.label";
static const std::string DETERMINAND_DEFINTION = "determinand.definition";
static const std::string DETERMINAND_NOTATION  = "determinand.notation";
static const std::string RESULT_QUANTIFIER     = "resultQuantifier.notation";
static const std::string RESULT                = "result";
static const std::string DETERMINAND_UNIT      = "determinand.unit.label";
static const std::string SAMPLE_COMPLIANT      = "sample.isCompliantSample";

using namespace std;

/* ------------------------------------------------------------------------- **
 * Watertool : Hydroset ~ Class methods                                      *
 * Editor(s) : Alexander Del Brocco                                          *
 * Module    : COMP2711 - User Interfaces                                    *
** ------------------------------------------------------------------------- */

void Hydroset::loadData(const string& filename)
{ // Loads CSV data into Hydroset Object, with each row in a Waterbody Vector
  csv::CSVReader reader(filename);
  data.clear(); // Preps for CSV read

  // Collects each row of the CSV, storing the following
  for (const auto& row: reader) {
    Waterbody waterbody{
      row[SAMPLING_POINT].get<>(),          // Location Name
      row[SAMPLE_TIME].get<>(),             // Time of Sample
      row[DETERMINAND].get<>(),             // Pollutant Name
      row[DETERMINAND_DEFINTION].get<>(),   // Pollutant Information
      row[DETERMINAND_NOTATION].get<int>(), // Pollutant Notation
      row[RESULT_QUANTIFIER].get<char>(),   // Qunatifier? (>)
      row[RESULT].get<double>(),            // Pollutant Level
      row[DETERMINAND_UNIT].get<>(),        // Units of Pollutant Level
      row[SAMPLED_MATERIAL].get<>(),        // Type of Waterbody
      row[SAMPLE_COMPLIANT].get<bool>(),    // Compliance
    };
    data.push_back(waterbody);
  }
}

Waterbody Hydroset::highest() const
{ // Returns the row with the highest result (in future, per pollutant)
  checkDataExists();

  auto waterbody = max_element(data.begin(), data.end(),
    [](Waterbody a, Waterbody b) { return a.getResult() < b.getResult(); });

  return *waterbody;
}

Waterbody Hydroset::lowest() const
{ // Returns the row with the lowest result (in future, per pollutant)
  checkDataExists();

  auto waterbody = min_element(data.begin(), data.end(),
    [](Waterbody a, Waterbody b) { return a.getResult() < b.getResult(); });

  return *waterbody;
}

double Hydroset::meanResult() const
{ // Returns the mean result of all rows (in future, per pollutant)
  checkDataExists();

  auto sum = accumulate(data.begin(), data.end(), 0.0,
    [](double total, Waterbody q) { return total + q.getResult(); });

  return sum / data.size();
}

void Hydroset::checkDataExists() const
{ // Checks if CSV data has been read into the object
  if (size() == 0) {
    throw std::runtime_error("Dataset is empty!");
  }
}
