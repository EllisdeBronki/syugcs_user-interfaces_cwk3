#include <QtWidgets>
#include "qtApp/window.hpp"
#include "qtApp/dashboard.hpp"
#include "qtApp/pollutant.hpp"
#include "qtApp/litter.hpp"

/* -------------------------------------- **
 * Watertool : Main                       *
 * Editor(s) : Alexander Del Brocco, Tom O*
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

/* ----------------------------------------------------------------------- **
 * Watertool Main :                                                        *
 *                                                                         *
 *    Loads the applications and shows the dashboard window upon execution *
** ----------------------------------------------------------------------- */

int main(int argc, char* argv[])
{ // Open Dashboard
  QApplication app(argc, argv);

  WaterbodyWindow window;
  Dashboard dashboard;
  PollutantWindow pollutant;
  LitterWindow litter;
  dashboard.show();
  window.show();
  pollutant.show();
  litter.show();

  return app.exec();
}
