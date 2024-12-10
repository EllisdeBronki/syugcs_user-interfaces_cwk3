#include <QtWidgets>

#include "qtApp/datapage.hpp"
#include "qtApp/dashboard.hpp"
#include "qtApp/pollutant-overview.hpp"
#include "qtApp/persistant-pollutants.hpp"

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
  DataPage dataPage;
  Dashboard dashboard;
  PollutantOverview pollutantOverview;
  PersistantPollutants persistantPollutants;

  // Show Pages (temporary for testing)
  dashboard.show();
  dataPage.show();
  pollutantOverview.show();
  persistantPollutants.show();

  return app.exec();
}
