#pragma once

#include <QMainWindow>
#include <QString>
#include <QtWidgets>

#include "../hydromodel/hydromodel.hpp"
#include "dashboard.hpp"
#include "datapage.hpp"
#include "dashboard.hpp"
#include "pollutant-overview.hpp"
#include "persistent-pollutants.hpp"
#include "enviroment-litter.hpp"

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

    PollutantOverview* popPage;
    PersistentPollutants* porgpPage;
    EnviromentalLitter* elipPage;
    DataPage* cdPage;
  
  public slots:
    void showPop();
    void showPorgp();
    void showElip();
    void showFcp();
    void showCd();
    void showGhp();
};