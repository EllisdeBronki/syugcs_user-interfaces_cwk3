#pragma once

#include <QMainWindow>
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

class PollutantWindow: public QMainWindow
{
  Q_OBJECT

  public:
    PollutantWindow();

  private:
    void createMainWidget();
    void createFileSelectors();
    void createButtons();
    void createToolBar();
    void filter();
    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();

    Hydromodel model;          // data model used by table
    QString dataLocation;      // location of CSV data files
    QComboBox* significance;   // selector for quake feed significance level
    QComboBox* period;         // selector for quake feed time period
    QPushButton* loadButton;   // button to load a new CSV file
    QPushButton* filterButton;  // button to display dataset stats
    QTableView* table;         // table of quake data
    QLabel* fileInfo;          // status bar info on current file

  private slots:
    void setDataLocation();
    void openCSV();
    void about();
};
