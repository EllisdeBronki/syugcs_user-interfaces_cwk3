#include <QtWidgets>
#include <QScreen>
#include <QGridLayout>
#include <QPushButton>
#include <stdexcept>
#include <iostream>
#include "dashboard.hpp"

static const int MIN_WIDTH  = 1000;
static const int MIN_HEIGHT = 1000;

static const std::string POP   = "Pollutants Overview Page";
static const std::string PORGP = "Persistant Organic Pollutants Page";
static const std::string ELIP  = "Enviromental Litter Indicators Page";
static const std::string FCP   = "Flourinated Compounds Page";
static const std::string CD    = "Compliance Dashboard";
static const std::string GHP   = "Geographical Hotspots Page";

/* ------------------------------------------------------------------------- **
 * Watertool : Dashboard                                                     *
 * Author(s) : Alexander Del Brocco, Tom Onions                              *
 * Module    : COMP2711 - User Interfaces                                    *
** ------------------------------------------------------------------------- */

Dashboard::Dashboard(): QMainWindow()
{
  int* screenSize = deduceWindowSize();
  createMainWidget(screenSize);
  setMinimumWidth(screenSize[0] * .5);
  setMinimumHeight(screenSize[1] * .5);
  setWindowTitle("Water Quality Monitor - Dashboard");
}

int* Dashboard::deduceWindowSize() 
{
  QScreen* screen = QGuiApplication::primaryScreen();
  QRect screenMax = screen->availableGeometry();

  int* screenDims = new int[2];
  screenDims[0] = screenMax.width();
  screenDims[1] = screenMax.height();

  return screenDims;
}

void Dashboard::createMainWidget(int* dimensions)
{
  QWidget* dashboard = new QWidget(this);

  QPushButton* pop   = new QPushButton("Pollutant concentrations\n at sample points.", dashboard);
  pop->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* popL = new QLabel("Pollutant Overview Page", pop);
  popL->setStyleSheet("padding: 10px; border: 1px solid #ccc;");

  QPushButton* porgp = new QPushButton("Search natural pollutants\n that remain overtime.", dashboard);
  porgp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* porgpL = new QLabel("Persistant Organic Pollutants Page", porgp);
  porgpL->setStyleSheet("padding: 10px; border: 1px solid #ccc;");

  QPushButton* elip  = new QPushButton("View indications of enviromental\n wastage and litter.", dashboard);
  elip->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* elipL = new QLabel("Enviromental Litter Indicator Page", elip);
  elipL->setStyleSheet("padding: 10px; border: 1px solid #ccc;");

  QPushButton* fcp   = new QPushButton("View trends of flourine based\n pollutants, possibly caused by\n water treatment.", dashboard);
  fcp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* fcpL = new QLabel("Flourinated Compounds Page", fcp);
  fcpL->setStyleSheet("padding: 10px; border: 1px solid #ccc;");

  QPushButton* cd    = new QPushButton("View current policy stances\n and standards on the pollutants\n detected in sampled locations.", dashboard);
  cd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* cdL = new QLabel("Compliance Dashboard", cd);
  cdL->setStyleSheet("padding: 10px; border: 1px solid #ccc;");

  QPushButton* ghp   = new QPushButton("See a digital map\n visualisation on pollutant\n levels across your\n country and abroad", dashboard);
  ghp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* ghpL = new QLabel("Geographical Hotspots Page", ghp);
  ghpL->setStyleSheet("padding: 10px; border: 1px solid #ccc;");

  QGridLayout* grid = new QGridLayout;

  grid->addWidget(pop,   0, 0);
  grid->addWidget(porgp, 0, 1);
  grid->addWidget(elip , 0, 2);
  grid->addWidget(fcp  , 1, 0);
  grid->addWidget(cd   , 1, 1);
  grid->addWidget(ghp  , 1, 2);

  grid->setRowStretch(0, 1);
  grid->setRowStretch(1, 1);

  grid->setColumnStretch(0, 1);
  grid->setColumnStretch(1, 1);
  grid->setColumnStretch(2, 1);

  dashboard->setLayout(grid);

  QFont dashboardFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  dashboard->setFont(dashboardFont);
  dashboard->setMinimumSize(dimensions[0] * .5, dimensions[1] * .5);
}