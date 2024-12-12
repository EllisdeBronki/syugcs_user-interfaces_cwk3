#include <QtWidgets>

#include "qtApp/datapage.hpp"
#include "qtApp/dashboard.hpp"
#include "qtApp/pollutant-overview.hpp"
#include "qtApp/persistent-pollutants.hpp"
#include "qtApp/enviroment-litter.hpp"

/* ------------------------------------------------------------------------- **
 * Watertool : Main                                                          *
 * Editor(s) : Alexander Del Brocco, Thomas Onions                           *
 * Module    : COMP2711 - User Interfaces                                    *
** ------------------------------------------------------------------------- */

/* ------------------------------------------------------------------------- **
 * Watertool Main :                                                          *
 *                                                                           *
 *    Loads the applications and shows the dashboard window upon execution   *
** ------------------------------------------------------------------------- */

int main(int argc, char* argv[])
{ // Open Dashboard
  QApplication app(argc, argv);

  // Initialise Qt Application Pages
  Dashboard dashboard;

  // Show Pages (temporary for testing)
  dashboard.show();

  return app.exec();
}
