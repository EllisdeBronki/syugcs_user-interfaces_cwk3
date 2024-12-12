#include <QtWidgets>
#include <QColor>
#include <QPainter>
#include <stdexcept>
#include <iostream>

#include "persistent-pollutants.hpp"
#include "dashboard.hpp"
#include "datapage.hpp"
#include "pollutant-overview.hpp"
#include "enviroment-litter.hpp"
#include "stats.hpp"

static const int MIN_WIDTH = 1200;
static const QString TITLE = "Water Quality Monitor - Data Viewing";

static const int SAMPLE_COMPIANT = 9;
static const QModelIndex NUL;
static const int READ = 0;

/* -------------------------------------- **
 * Watertool : Water Window               *
 * Editor(s) : Alexander Del Brocco, Tom O*
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

DataPage::DataPage(): QMainWindow(), statsDialog(nullptr)
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

void DataPage::createMainWidget()
{
  table = new QTableView();
  table->setModel(&model);

  QFont tableFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  table->setFont(tableFont);

  setCentralWidget(table); 
}

int* DataPage::deduceWindowSize() 
{
  QScreen* screen = QGuiApplication::primaryScreen();
  QRect screenMax = screen->availableGeometry();

  int* screenDims = new int[2];
  screenDims[0] = screenMax.width();
  screenDims[1] = screenMax.height();

  return screenDims;
}

void DataPage::createButtons()
{
  loadButton = new QPushButton("Load");

  connect(loadButton, SIGNAL(clicked()), this, SLOT(openCSV()));
}

void DataPage::createToolBar()
{
  QToolBar* toolBar = new QToolBar();

  toolBar->addSeparator();

  toolBar->addWidget(loadButton);

  addToolBar(Qt::LeftToolBarArea, toolBar);
}


void DataPage::createStatusBar()
{
  fileInfo = new QLabel("Current file: <none>");
  QStatusBar* status = statusBar();
  status->addWidget(fileInfo);
}

void DataPage::addFileMenu()
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

void DataPage::addHelpMenu()
{
  QAction* aboutAction = new QAction("&About", this);
  connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));

  QAction* aboutQtAction = new QAction("About &Qt", this);
  connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

  QMenu* helpMenu = menuBar()->addMenu("&Help");
  helpMenu->addAction(aboutAction);
  helpMenu->addAction(aboutQtAction);
}

void DataPage::addNavMenu()
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

void DataPage::toDashboard()
{
  Dashboard* dash = new Dashboard();
  dash->show();
}

void DataPage::toPollutantOverview()
{
  PollutantOverview* poll = new PollutantOverview();
  poll->show();
}

void DataPage::toPersistentPollutants()
{
  PersistentPollutants* pers = new PersistentPollutants();
  pers->show();
}

void DataPage::toEnviromentalLitter() 
{
  EnviromentalLitter* enir = new EnviromentalLitter();
  enir->show(); 
}

void DataPage::toComplianceData()
{
  DataPage* data = new DataPage();
  data->show();
}

void DataPage::setDataLocation()
{
  QString directory = QFileDialog::getExistingDirectory(
    this, "Data Location", ".",
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (directory.length() > 0) {
    dataLocation = directory;
  }
}

void DataPage::openCSV()
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
  table->resizeColumnsToContents();
  table->viewport()->update();

  if (statsDialog != nullptr && statsDialog->isVisible()) {
    statsDialog->update(model.meanResult(), model.meanResult());
  }
}

void DataPage::about()
{
  QMessageBox::about(this, "About Compliance Data Page",
    "This tool allows you to load in a formatted CSV from government websites "
    "and view the raw data for yourself. It also comes with helpful colour "
    "indicators that help you quickly distinguish which rows meet EU/UK "
    "regulation, and which ones don't. "
    );
}
