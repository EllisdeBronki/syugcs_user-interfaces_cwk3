#include <QtWidgets>
#include <QScreen>
#include <QString>
#include <QGridLayout>
#include <QPushButton>
#include <stdexcept>
#include <iostream>

#include "dashboard.hpp"
#include "datapage.hpp"
#include "pollutant-overview.hpp"
#include "persistent-pollutants.hpp"
#include "enviroment-litter.hpp"

static const int MIN_WIDTH  = 1000;
static const int MIN_HEIGHT = 1000;
static const QString TITLE = "Water Quality Monitor - Dashboard";

static QString POP   = "Pollutants Overview Page";
static QString PORGP = "Persistant Organic Pollutants Page";
static QString ELIP  = "Enviromental Litter Indicators Page";
static QString FCP   = "Flourinated Compounds Page";
static QString CD    = "Compliance Dashboard";
static QString GHP   = "Geographical Hotspots Page";

static QString POP_TXT   = "Pollutant concentrations\n at sample points.";
static QString PORGP_TXT = "Search natural pollutants\n that remain overtime.";
static QString ELIP_TXT  = "View indications of enviromental\n wastage and litter.";
static QString FCP_TXT   = "View trends of flourine based\n pollutants, possibly caused by\n water treatment.";
static QString CD_TXT    = "View current policy stances\n and standards on the pollutants\n detected in sampled locations.";
static QString GHP_TXT   = "See a digital map\n visualisation on pollutant\n levels across your\n country and abroad";

static QString QLB_STYLE = "padding: 10px; border: 1px solid #CCC;";

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
  setWindowTitle(TITLE);
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

  QPushButton* pop   = new QPushButton(POP_TXT, dashboard);
  pop->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* popL = new QLabel(POP, pop);
  popL->setStyleSheet(QLB_STYLE);
  connect(pop, &QPushButton::clicked, this, &Dashboard::showPop);

  QPushButton* porgp = new QPushButton(PORGP_TXT, dashboard);
  porgp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* porgpL = new QLabel(PORGP, porgp);
  porgpL->setStyleSheet(QLB_STYLE);
  connect(porgp, &QPushButton::clicked, this, &Dashboard::showPorgp);

  QPushButton* elip  = new QPushButton(ELIP_TXT, dashboard);
  elip->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* elipL = new QLabel(ELIP, elip);
  elipL->setStyleSheet(QLB_STYLE);
  connect(elip, &QPushButton::clicked, this, &Dashboard::showElip);

  QPushButton* fcp   = new QPushButton(FCP_TXT, dashboard);
  fcp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* fcpL = new QLabel(FCP, fcp);
  fcpL->setStyleSheet(QLB_STYLE);
  connect(fcp, &QPushButton::clicked, this, &Dashboard::showFcp);

  QPushButton* cd    = new QPushButton(CD_TXT, dashboard);
  cd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* cdL = new QLabel(CD, cd);
  cdL->setStyleSheet(QLB_STYLE);
  connect(cd, &QPushButton::clicked, this, &Dashboard::showCd);

  QPushButton* ghp   = new QPushButton(GHP_TXT, dashboard);
  ghp->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  QLabel* ghpL = new QLabel(GHP, ghp);
  ghpL->setStyleSheet(QLB_STYLE);
  connect(ghp, &QPushButton::clicked, this, &Dashboard::showGhp);

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

void Dashboard::showPop()
{
  popPage = new PollutantOverview();
  popPage->show();
}

void Dashboard::showPorgp()
{
  porgpPage = new PersistentPollutants();
  porgpPage->show();
}

void Dashboard::showElip()
{
  elipPage = new EnviromentalLitter();
  elipPage->show();
}

void Dashboard::showFcp()
{
  return;
}

void Dashboard::showCd()
{
  cdPage = new DataPage();
  cdPage->show();
}

void Dashboard::showGhp()
{
  return;
}