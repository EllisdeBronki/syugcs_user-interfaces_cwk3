#pragma once

#include <QMainWindow>
#include "hydromodel.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;

/* ------------------------------------------------------------------------- **
 * Watertool : Dashboard (Header)                                            *
 * Author(s) : Alexander Del Brocco                                          *
 * Module    : COMP2711 - User Interfaces                                    *
** ------------------------------------------------------------------------- */

class Dashboard: public QMainWindow
{
  Q_OBJECT

  public:
    Dashboard();

  private:
    void createMainWidget();
};