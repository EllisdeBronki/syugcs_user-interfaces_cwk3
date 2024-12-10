#include <QtWidgets>
#include "window.hpp"
#include "dashboard.hpp"

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
  dashboard.show();
  window.show();

  return app.exec();
}
