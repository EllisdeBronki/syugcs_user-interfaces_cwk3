#include <QtWidgets>
#include <QtCharts>
#include <stdexcept>
#include <iostream>

#include "persistent-pollutants.hpp"
#include "dashboard.hpp"
#include "datapage.hpp"
#include "pollutant-overview.hpp"
#include "enviroment-litter.hpp"

static const int MIN_WIDTH = 1200;
static const QString TITLE = "Water Quality Monitor - Pollutant Overview";

static const QModelIndex NUL;
static const QVariant    SELECT_BY    = "Mn- Filtered";

static const int         READ         = 0;

static const int         SAMPLE_POINT = 0;
static const int         DETERMINAND  = 2;
static const int         RESULT       = 6;

/* -------------------------------------------------------------------------- **
 * Watertool : Water Window (Header)                                          *
 * Editor(s) : Alexander Del Brocco, Thomas Onions                            *
 * Module    : COMP2711 - User Interfaces                                     *
** -------------------------------------------------------------------------- */

PollutantOverview::PollutantOverview(): QMainWindow()
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


void PollutantOverview::createMainWidget()
{
  chart = new QChart();
  set0 = new QBarSet("Data");
}

int* PollutantOverview::deduceWindowSize() 
{
  QScreen* screen = QGuiApplication::primaryScreen();
  QRect screenMax = screen->availableGeometry();

  int* screenDims = new int[2];
  screenDims[0] = screenMax.width();
  screenDims[1] = screenMax.height();

  return screenDims;
}

void PollutantOverview::createButtons()
{
  loadButton = new QPushButton("Load");

  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}


void PollutantOverview::createToolBar()
{
  QToolBar* toolBar = new QToolBar();

  toolBar->addSeparator();

  toolBar->addWidget(loadButton);

  addToolBar(Qt::LeftToolBarArea, toolBar);
}

void PollutantOverview::createStatusBar()
{
  fileInfo = new QLabel("Current file: <none>");
  QStatusBar* status = statusBar();
  status->addWidget(fileInfo);
}


void PollutantOverview::addFileMenu()
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


void PollutantOverview::addHelpMenu()
{
  QAction* aboutAction = new QAction("&About", this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction* aboutQtAction = new QAction("About &Qt", this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu* helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void PollutantOverview::addNavMenu()
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

void PollutantOverview::toDashboard()
{
  Dashboard* dash = new Dashboard();
  dash->show();
}

void PollutantOverview::toPollutantOverview()
{
  PollutantOverview* poll = new PollutantOverview();
  poll->show();
}

void PollutantOverview::toPersistentPollutants()
{
  PersistentPollutants* pers = new PersistentPollutants();
  pers->show();
}

void PollutantOverview::toEnviromentalLitter() 
{
  EnviromentalLitter* enir = new EnviromentalLitter();
  enir->show(); 
}

void PollutantOverview::toComplianceData()
{
  DataPage* data = new DataPage();
  data->show();
}

void PollutantOverview::setDataLocation()
{
  QString directory = QFileDialog::getExistingDirectory(
    this, "Data Location", ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0) {
    dataLocation = directory;
  }
}


void PollutantOverview::openCSV()
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

    if (determinand == SELECT_BY) {
      double barVal = model.data(model.index(row, RESULT), READ).toDouble();

      set0->append(barVal);

      categories.append(model.data(model.index(row, SAMPLE_POINT), READ).toString());
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

void PollutantOverview::about()
{
  QMessageBox::about(this, "About Pollutant Overview",
    "This tool allows you view the current levels of pollutants in specific "
    "to give you a quick overview, as well as helpful colour coding of the "
    "bars which give an indication on where these levels stand against EU/UK "
    "regulation."
    );
}
