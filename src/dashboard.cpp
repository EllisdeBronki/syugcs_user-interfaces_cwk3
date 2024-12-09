#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "dashboard.hpp"

static const int MIN_WIDTH = 1200;

/* ------------------------------------------------------------------------- **
 * Watertool : Dashboard                                                     *
 * Author(s) : Alexander Del Brocco                                          *
 * Module    : COMP2711 - User Interfaces                                    *
** ------------------------------------------------------------------------- */

Dashboard::Dashboard(): QMainWindow(), statsDialog(nullptr)
{
  createMainWidget();
  setMinimumWidth(MIN_WIDTH);
  setWindowTitle("Water Quality Monitor - Dashboard");
}

void Dashboard::createMainWidget()
{
  QWidget* widget = new QWidget();

  QFont dashboardFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  widget->setFont(dashboardFont);
}