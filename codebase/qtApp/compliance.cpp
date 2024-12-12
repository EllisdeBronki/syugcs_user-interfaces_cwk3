#include "compliance.hpp"
#include <QtWidgets>
#include <stdexcept>
#include <iostream>

static const int MIN_WIDTH = 1200;
static const QModelIndex NUL;

/* -------------------------------------- **
 * Compliance Dashboard                   *
 * Editor(s): Alexander Del Brocco, Tom O *
 * Module   : COMP2711 - User Interfaces  *
** -------------------------------------- */

ComplianceDashboardWindow::ComplianceDashboardWindow() : QMainWindow()
{
    createMainWidget();
    createFilters();
    createButtons();
    createToolBar();
    createStatusBar();
    addFileMenu();
    addHelpMenu();

    setMinimumWidth(MIN_WIDTH);
    setWindowTitle("Compliance Dashboard");
}

void ComplianceDashboardWindow::createMainWidget() {
    summaryTable = new QTableView(this);
    summaryTable->setModel(model); // Directly associate with model
    setCentralWidget(summaryTable);
}


void ComplianceDashboardWindow::createFilters() {
    locationFilter = new QComboBox(this);
    locationFilter->addItem("All Locations");
    locationFilter->addItems(model->getUniqueValues(0)); // Get unique values from column 0

    pollutantFilter = new QComboBox(this);
    pollutantFilter->addItem("All Pollutants");
    pollutantFilter->addItems(model->getUniqueValues(2)); // Get unique values from column 2

    complianceFilter = new QComboBox(this);
    complianceFilter->addItem("All");
    complianceFilter->addItem("Compliant");
    complianceFilter->addItem("Non-Compliant");
}
void ComplianceDashboardWindow::applyFilters() {
    QString locationCriteria = locationFilter->currentText();
    QString pollutantCriteria = pollutantFilter->currentText();
    QString complianceCriteria = complianceFilter->currentText();

    // Iterate through all rows in the model
    for (int row = 0; row < model.rowCount(NUL); ++row) {
        bool matches = true;

        // Location filter
        if (locationCriteria != "All Locations" &&
            model->data(model->index(row, 0), Qt::DisplayRole).toString() != locationCriteria) {
            matches = false;
        }

        // Pollutant filter
        if (pollutantCriteria != "All Pollutants" &&
            model->data(model->index(row, 2), Qt::DisplayRole).toString() != pollutantCriteria) {
            matches = false;
        }

        // Compliance filter
        QString complianceValue = model->data(model->index(row, 9), Qt::DisplayRole).toString();
        if (complianceCriteria == "Compliant" && complianceValue != "true") {
            matches = false;
        } else if (complianceCriteria == "Non-Compliant" && complianceValue != "false") {
            matches = false;
        }

        // Hide or show rows based on match status
        summaryTable->setRowHidden(row, !matches);
    }
}


void ComplianceDashboardWindow::createButtons() {
    applyButton = new QPushButton("Apply Filters", this);
    connect(applyButton, &QPushButton::clicked, this, &ComplianceDashboardWindow::applyFilters);
}


void ComplianceDashboardWindow::createToolBar() {
    QToolBar* toolBar = new QToolBar(this);

    toolBar->addWidget(new QLabel("Location:"));
    toolBar->addWidget(locationFilter);

    toolBar->addWidget(new QLabel("Pollutant:"));
    toolBar->addWidget(pollutantFilter);

    toolBar->addWidget(new QLabel("Compliance:"));
    toolBar->addWidget(complianceFilter);

    toolBar->addWidget(applyButton);

    addToolBar(Qt::TopToolBarArea, toolBar);
}


void ComplianceDashboardWindow::createStatusBar()
{
    fileInfo = new QLabel("Data location: <none>");
    statusBar()->addWidget(fileInfo);
}

void ComplianceDashboardWindow::addFileMenu()
{
    QAction* setLocationAction = new QAction("Set Data Location", this);
    connect(setLocationAction, &QAction::triggered, this, &ComplianceDashboardWindow::setDataLocation);

    QAction* quitAction = new QAction("Quit", this);
    connect(quitAction, &QAction::triggered, this, &ComplianceDashboardWindow::close);

    QMenu* fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(setLocationAction);
    fileMenu->addAction(quitAction);
}

void ComplianceDashboardWindow::addHelpMenu()
{
    QAction* aboutAction = new QAction("About", this);
    connect(aboutAction, &QAction::triggered, this, &ComplianceDashboardWindow::about);

    QAction* aboutQtAction = new QAction("About Qt", this);
    connect(aboutQtAction, &QAction::triggered, qApp, &QApplication::aboutQt);

    QMenu* helpMenu = menuBar()->addMenu("&Help");
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);
}

void ComplianceDashboardWindow::setDataLocation()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Select Data Location");
    if (!directory.isEmpty()) {
        dataLocation = directory;
        fileInfo->setText("Data location: " + dataLocation);
    }
}


void ComplianceDashboardWindow::showDetails(const QString& pollutant)
{
    QString details = QString("Details for pollutant: %1\n\nNon-compliance reasons:\n...\nHistorical trends:\n...").arg(pollutant);
    QMessageBox::information(this, "Pollutant Details", details);
}

void ComplianceDashboardWindow::about()
{
    QMessageBox::about(this, "About Compliance Dashboard",
        "This tool provides an overview of compliance across pollutants.\n\n"
        "(c) 2024 Regulatory Compliance Team.");
}
/*
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    ComplianceDashboardWindow window;
    window.show();

    return app.exec();
}
*/