#pragma once

#include <vector>
#include "waterbody.hpp"

/* -------------------------------------- **
 * Watertool : Hydroset (Header)          *
 * Editor(s) : Alexander Del Brocco       *
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

class Hydroset
{
  public:
    Hydroset() {}
    Hydroset(const std::string& filename) { loadData(filename); }
    void loadData(const std::string&);
    int size() const { return data.size(); }
    Waterbody operator[](int index) const { return data.at(index); }
    Waterbody strongest() const;
    Waterbody shallowest() const;
    double meanDepth() const;
    double meanMagnitude() const;

  private:
    std::vector<Waterbody> data;
    void checkDataExists() const;
};
