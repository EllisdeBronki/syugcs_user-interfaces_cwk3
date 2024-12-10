#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "pollutant.hpp"

static const int MIN_WIDTH = 1200;

static const QModelIndex nullIndex;

const QVariant determinand = "Mn- Filtered";
const QVariant samplePoint = "MALHAM TARN";

/* -------------------------------------------------------------------------- **
 * Watertool : Water Window (Header)                                          *
 * Editor(s) : Alexander Del Brocco, Thomas Onions                            *
 * Module    : COMP2711 - User Interfaces                                     *
** -------------------------------------------------------------------------- */

PollutantWindow::PollutantWindow(): QMainWindow()
{
  createMainWidget();
  createFileSelectors();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();

  setMinimumWidth(MIN_WIDTH);
  setWindowTitle("Pollutant Tool");
}


void PollutantWindow::createMainWidget()
{
  chart = new QChart();
  set0 = new QBarSet("Data");
}


void PollutantWindow::createFileSelectors()
{
  QStringList significanceOptions;
  significanceOptions << "significant" << "4.5" << "2.5" << "1.0" << "all";
  significance = new QComboBox();
  significance->addItems(significanceOptions);

  QStringList periodOptions;
  periodOptions << "hour" << "day" << "week" << "month";
  period = new QComboBox();
  period->addItems(periodOptions);
}


void PollutantWindow::createButtons()
{
  loadButton = new QPushButton("Load");
  filterButton = new QPushButton("Filter");

  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
  connect(filterButton, SIGNAL(clicked()), this, SLOT(filter()));
}


void PollutantWindow::createToolBar()
{
  QToolBar* toolBar = new QToolBar();

  QLabel* significanceLabel = new QLabel("Significance");
  significanceLabel->setAlignment(Qt::AlignVCenter);
  toolBar->addWidget(significanceLabel);
  toolBar->addWidget(significance);

  QLabel* periodLabel = new QLabel("Period");
  periodLabel->setAlignment(Qt::AlignVCenter);
  toolBar->addWidget(periodLabel);
  toolBar->addWidget(period);

  toolBar->addSeparator();

  toolBar->addWidget(loadButton);
  toolBar->addWidget(filterButton);

  addToolBar(Qt::LeftToolBarArea, toolBar);
}

void PollutantWindow::filter()
{
      if (dataLocation == "") {
    QMessageBox::critical(this, "Data Location Error",
      "Data location has not been set!\n\n"
      "You can specify this via the File menu."
    );
    return;
  }

  auto filename = QString("%1_%2.csv")
    .arg(significance->currentText()).arg(period->currentText());

  auto path = dataLocation + "/" + "Y-2024.csv";

  try {
    model.updateFromFile(path);
  }
  catch (const std::exception& error) {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }
  
}

void PollutantWindow::createStatusBar()
{
  fileInfo = new QLabel("Current file: <none>");
  QStatusBar* status = statusBar();
  status->addWidget(fileInfo);
}


void PollutantWindow::addFileMenu()
{
  QAction* locAction = new QAction("Set Data &Location", this);
  locAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_L));
  connect(locAction, SIGNAL(triggered()), this, SLOT(setDataLocation()));

  QAction* closeAction = new QAction("Quit", this);
  closeAction->setShortcut(QKeySequence::Close);
  connect(closeAction, SIGNAL(triggered()), this, SLOT(close()));

  QMenu* fileMenu = menuBar()->addMenu("&File");
  fileMenu->addAction(locAction);
  fileMenu->addAction(closeAction);
}


void PollutantWindow::addHelpMenu()
{
  QAction* aboutAction = new QAction("&About", this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction* aboutQtAction = new QAction("About &Qt", this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu* helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}


void PollutantWindow::setDataLocation()
{
  QString directory = QFileDialog::getExistingDirectory(
    this, "Data Location", ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0) {
    dataLocation = directory;
  }
}


void PollutantWindow::openCSV()
{
  if (dataLocation == "") {
    QMessageBox::critical(this, "Data Location Error",
      "Data location has not been set!\n\n"
      "You can specify this via the File menu."
    );
    return;
  }

  auto filename = QString("%1_%2.csv")
    .arg(significance->currentText()).arg(period->currentText());

  auto path = dataLocation + "/" + "Y-2024.csv";

  try {
    model.updateFromFile(path);
  }
  catch (const std::exception& error) {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }

  fileInfo->setText(QString("Current file: <kbd>%1</kbd>").arg(filename));

  for (int row = 0; row < model.rowCount(nullIndex); ++row) {
    QVariant column2Val = model.data(model.index(row, 2), 0);
    QVariant column0Val = model.data(model.index(row, 0), 0);

    // Condition has been changed to sampling point and pollutant
    if (column2Val == determinand && column0Val == samplePoint) {
      double barVal = model.data(model.index(row, 6), 0).toDouble();

      set0->append(barVal);

      categories.append(model.data(model.index(row, 1), 0).toString());
    }
  }

  if (set0->count() > 0) {
    QBarSeries *series = new QBarSeries();
    series->append(set0);

    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 20);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
  } else {
    QMessageBox::information(this, "No Data", "No rows match the condition.");
  }

}

void PollutantWindow::about()
{
  QMessageBox::about(this, "About Waterbody Tool",
    "Waterbody Tool displays and analyzes earthquake data loaded from"
    "a CSV file produced by the USGS Earthquake Hazards Program.\n\n"
    "(c) 2024 Nick Efford");
}
