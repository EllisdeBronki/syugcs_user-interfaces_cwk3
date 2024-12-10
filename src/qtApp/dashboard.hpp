#pragma once

#include <QMainWindow>
#include <QString>
#include <QtWidgets>
#include "../hydromodel/hydromodel.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;

/* ------------------------------------------------------------------------- **
 * Watertool : Dashboard (Header)                                            *
 * Author(s) : Alexander Del Brocco, Tom Onions                              *
 * Module    : COMP2711 - User Interfaces                                    *
** ------------------------------------------------------------------------- */

class Dashboard: public QMainWindow
{
  public:
    Dashboard();

  private:
    int* deduceWindowSize();
    void createMainWidget(int*);
};