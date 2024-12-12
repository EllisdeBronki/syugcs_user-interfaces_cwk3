#include <QtWidgets>
#include <stdexcept>
#include <iostream>

#include "persistent-pollutants.hpp"
#include "dashboard.hpp"
#include "datapage.hpp"
#include "pollutant-overview.hpp"
#include "enviroment-litter.hpp"


static const int MIN_WIDTH = 1200;
static const QString TITLE = "Water Quality Monitor - Persistent Organic Pollutants";

static const QModelIndex NUL;
const QVariant SELECT_DETERMINAND  = "Mn- Filtered";
const QVariant SELECT_SAMPLE_POINT = "MALHAM TARN";

static const int         READ         = 0;

static const int         SAMPLE_POINT = 0;
static const int         TIME         = 1;
static const int         DETERMINAND  = 2;
static const int         RESULT       = 6;

/* -------------------------------------------------------------------------- **
 * Watertool : Water Window (Header)                                          *
 * Editor(s) : Alexander Del Brocco, Thomas Onions                            *
 * Module    : COMP2711 - User Interfaces                                     *
** -------------------------------------------------------------------------- */

PersistentPollutants::PersistentPollutants(): QMainWindow()
{
  createMainWidget();
  createButtons();
  createToolBar();
  createStatusBar();
  addFileMenu();
  addHelpMenu();
  addNavMenu();

  int* screenSize = deduceWindowSize();
  setMinimumWidth(screenSize[0] * .5);
  setMinimumHeight(screenSize[1] * .5);
  setWindowTitle(TITLE);
}


void PersistentPollutants::createMainWidget()
{
  chart = new QChart();
  set0 = new QBarSet("Data");
}

int* PersistentPollutants::deduceWindowSize() 
{
  QScreen* screen = QGuiApplication::primaryScreen();
  QRect screenMax = screen->availableGeometry();

  int* screenDims = new int[2];
  screenDims[0] = screenMax.width();
  screenDims[1] = screenMax.height();

  return screenDims;
}


void PersistentPollutants::createButtons()
{
  loadButton = new QPushButton("Load");

  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}


void PersistentPollutants::createToolBar()
{
  QToolBar* toolBar = new QToolBar();

  toolBar->addSeparator();

  toolBar->addWidget(loadButton);

  addToolBar(Qt::LeftToolBarArea, toolBar);
}

void PersistentPollutants::createStatusBar()
{
  fileInfo = new QLabel("Current file: <none>");
  QStatusBar* status = statusBar();
  status->addWidget(fileInfo);
}


void PersistentPollutants::addFileMenu()
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

void PersistentPollutants::addHelpMenu()
{
  QAction* aboutAction = new QAction("&About", this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction* aboutQtAction = new QAction("About &Qt", this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu* helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void PersistentPollutants::addNavMenu()
{
  QAction* dashboard = new QAction("&Dashboard", this);
  connect(dashboard, SIGNAL(triggered()), this, SLOT(toDashboard()));

  QAction* pop = new QAction("Pollutant Overview", this);
  connect(pop, SIGNAL(triggered()), this, SLOT(toPollutantOverview()));

  QAction* porgp = new QAction("Persistant Organic Pollutants", this);
  connect(porgp, SIGNAL(triggered()), this, SLOT(toPersistantPollutents()));

  QAction* elip = new QAction("Enviromental Litter Indicators", this);
  connect(elip, SIGNAL(triggered()), this, SLOT(toEnviromentalLitter()));

  QAction* cd = new QAction("Compliance Data", this);
  connect(cd, SIGNAL(triggered()), this, SLOT(toComplianceData()));


  QMenu* navMenu = menuBar()->addMenu("Nav");
  navMenu->addAction(dashboard);
  navMenu->addAction(pop);
  navMenu->addAction(porgp);
  navMenu->addAction(elip);
  navMenu->addAction(cd);
}

void PersistentPollutants::toDashboard()
{
  Dashboard* dash = new Dashboard();
  dash->show();
}

void PersistentPollutants::toPollutantOverview()
{
  PollutantOverview* poll = new PollutantOverview();
  poll->show();
}

void PersistentPollutants::toPersistentPollutants()
{
  PersistentPollutants* pers = new PersistentPollutants();
  pers->show();
}

void PersistentPollutants::toEnviromentalLitter() 
{
  EnviromentalLitter* enir = new EnviromentalLitter();
  enir->show(); 
}

void PersistentPollutants::toComplianceData()
{
  DataPage* data = new DataPage();
  data->show();
}

void PersistentPollutants::setDataLocation()
{
  QString directory = QFileDialog::getExistingDirectory(
    this, "Data Location", ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0) {
    dataLocation = directory;
  }
}


void PersistentPollutants::openCSV()
{
  if (dataLocation == "") {
    QMessageBox::critical(this, "Data Location Error",
      "Data location has not been set!\n\n"
      "You can specify this via the File menu."
    );
    return;
  }

  auto filename = QString("Y-2024.csv");

  auto path = dataLocation + "/" + filename;

  try {
    model.updateFromFile(path);
  }
  catch (const std::exception& error) {
    QMessageBox::critical(this, "CSV File Error", error.what());
    return;
  }

  fileInfo->setText(QString("Current file: <kbd>%1</kbd>").arg(filename));

  for (int row = 0; row < model.rowCount(NUL); ++row) {
    QVariant determinand = model.data(model.index(row, DETERMINAND), READ);
    QVariant samplePoint = model.data(model.index(row, SAMPLE_POINT), READ);

    if (determinand == SELECT_DETERMINAND && samplePoint == SELECT_SAMPLE_POINT) {
      double barVal = model.data(model.index(row, RESULT), READ).toDouble();

      set0->append(barVal);

      categories.append(model.data(model.index(row, TIME), READ).toString());
    }
  }

  if (set0->count() > 0) {
    QBarSeries *series = new QBarSeries();
    series->append(set0);

    chart->addSeries(series);

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setTitleText("Timestamp")
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 20);
    axisY->setTitleText("Persistant Pollutant Level")
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    setCentralWidget(chartView);
  } else {
    QMessageBox::information(this, "No Data", "No rows match the condition.");
  }

}

void PersistentPollutants::about()
{
  QMessageBox::about(this, "About Persistant Organic Pollutants",
    "This tool plots the level of specific pollutants over time, giving a "
    "possible indication on the change of the amount, and types of industrial "
    "chemcials that are present in the area, potentially from the use of "
    "pesticides, chemicals or other potential sources that pose a risk of "
    "polluting the enviroment, and possible the food chain."
    );
}
