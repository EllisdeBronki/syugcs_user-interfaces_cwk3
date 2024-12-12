#pragma once

#include <QMainWindow>
#include "../hydromodel/hydromodel.hpp"

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;

class ComplianceDashboardWindow : public QMainWindow
{
    Q_OBJECT

public:
    ComplianceDashboardWindow();

private:
    void createMainWidget();
    void createFilters();
    void createButtons();
    void createToolBar();
    void createStatusBar();
    void addFileMenu();
    void addHelpMenu();
    void applyFilters();

    Hydromodel* model;               // Original data model for the table
    QString dataLocation;            // Directory for CSV files
    QTableView* summaryTable;        // Table view for compliance data
    QComboBox* locationFilter;       // Filter for sample place
    QComboBox* pollutantFilter;      // Filter for pollutant type
    QComboBox* complianceFilter;     // Filter for compliance status
    QPushButton* applyButton;        // Button to apply filters

private slots:
    void setDataLocation();
    void openCSV();
    void about();
};
