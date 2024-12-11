#pragma once

#include <QMainWindow>
#include <QtCharts>

#include "../hydromodel/hydromodel.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;

/* -------------------------------------------------------------------------- **
 * Watertool : Water Window (Header)                                          *
 * Editor(s) : Alexander Del Brocco, Thomas Onions                            *
 * Module    : COMP2711 - User Interfaces                                     *
** -------------------------------------------------------------------------- */

/* -------------------------------------------------------------------------- **
 * Watertool Waterbody Window :                                               *
 *                                                                            *
 *    Renders the main layout of the appliaction from QMainWindow. The        *
** -------------------------------------------------------------------------- */

class EnviromentalLitter: public QMainWindow
{
  Q_OBJECT

  public:
    EnviromentalLitter();

  private:
    void createMainWidget();
    void createFileSelectors();
    void createButtons();
    void createToolBar();
    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();

    Hydromodel model;          // data model used by table
    QString dataLocation;      // location of CSV data files
    QComboBox* significance;   // selector for quake feed significance level
    QComboBox* period;         // selector for quake feed time period
    QPushButton* loadButton;   // button to load a new CSV file
    QPushButton* filterButton;  // button to display dataset stats
    QChart* chart;
    QBarSet* set0;
    QLineSeries* series;
    QStringList categories;
    QLabel* fileInfo;          // status bar info on current file

  private slots:
    void setDataLocation();
    void openCSV();
    void filter();
    void about();
};
