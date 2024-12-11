#pragma once

#include <QMainWindow>

#include "../hydromodel/hydromodel.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;

/* -------------------------------------- **
 * Watertool : Water Window (Header)      *
 * Editor(s) : Alexander Del Brocco, Tom O*
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

/* ----------------------------------------------------------------------- **
 * Watertool Waterbody Window :                                            *
 *                                                                         *
 *    Renders the main layout of the appliaction from QMainWindow. The     *
** ----------------------------------------------------------------------- */

class DataPage: public QMainWindow
{
  Q_OBJECT

  public:
    DataPage();

  private:
    void createMainWidget();
    int* deduceWindowSize();
    void createFileSelectors();
    void createButtons();
    void createToolBar();
    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();

    Hydromodel model;          // data model used by table
    QString dataLocation;      // location of CSV data files
    QPushButton* loadButton;   // button to load a new CSV file
    QTableView* table;         // table of quake data
    QLabel* fileInfo;          // status bar info on current file
    StatsDialog* statsDialog;  // dialog to display stats

  private slots:
    void setDataLocation();
    void openCSV();
    void about();
};
