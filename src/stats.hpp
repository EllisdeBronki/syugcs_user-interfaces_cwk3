#pragma once

#include <QDialog>

class QLineEdit;
class QPushButton;

/* -------------------------------------- **
 * Watertool : Statistics (Header)        *
 * Editor(s) : Alexander Del Brocco, Tom O*
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

class StatsDialog: public QDialog
{
  public:
    StatsDialog(QWidget*);
    void update(double, double);

  private:
    QLineEdit* meanDepth;
    QLineEdit* meanMagnitude;
    QPushButton* closeButton;
    void createWidgets();
    void arrangeWidgets();
};
