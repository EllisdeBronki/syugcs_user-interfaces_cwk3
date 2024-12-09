#include <QtWidgets>
#include <QScreen>
#include <QPushButton>
#include <stdexcept>
#include <iostream>
#include "dashboard.hpp"

static const int MIN_WIDTH  = 1000;
static const int MIN_HEIGHT = 1000;

/* ------------------------------------------------------------------------- **
 * Watertool : Dashboard                                                     *
 * Author(s) : Alexander Del Brocco                                          *
 * Module    : COMP2711 - User Interfaces                                    *
** ------------------------------------------------------------------------- */

Dashboard::Dashboard(): QMainWindow()
{
  int* screenSize = deduceWindowSize();
  createMainWidget();
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

void Dashboard::createMainWidget()
{
  QWidget* widget = new QWidget(this);

  QPushButton* testButton = new QPushButton("Testing", widget);
  testButton->setGeometry(10, 10, 200, 200);
  testButton->setVisible(true);

  QFont dashboardFont = QFontDatabase::systemFont(QFontDatabase::FixedFont);
  widget->setFont(dashboardFont);
  widget->setFixedSize(MIN_WIDTH, MIN_HEIGHT);
}