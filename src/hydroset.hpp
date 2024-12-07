#pragma once

#include <vector>
#include "waterbody.hpp"

/* ------------------------------------------------------------------------- **
 * Watertool : Hydroset (Header)                                             *
 * Editor(s) : Alexander Del Brocco                                          *
 * Module    : COMP2711 - User Interfaces                                    *
** ------------------------------------------------------------------------- */

class Hydroset
{ // Hydroset class contains waterbody objects within a vector
  public:
    Hydroset() { }
    Hydroset(const std::string& filename) { loadData(filename); }
    void loadData(const std::string&);
    int size() const { return data.size(); }
    Waterbody operator[](int index) const { return data.at(index); }
    Waterbody highest() const;
    Waterbody lowest() const;
    double meanResult() const;

  private:
    std::vector<Waterbody> data;
    void checkDataExists() const;
};
