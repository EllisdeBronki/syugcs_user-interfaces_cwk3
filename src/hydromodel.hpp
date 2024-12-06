#pragma once

#include <QAbstractTableModel>
#include "hydroset.hpp"

/* -------------------------------------- **
 * Watertool : Hydromodel (Header)        *
 * Editor(s) : Alexander Del Brocco       *
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

class Hydromodel: public QAbstractTableModel
{
  public:
    Hydromodel(QObject* parent = nullptr): QAbstractTableModel(parent) {}
    void updateFromFile(const QString&);
    bool hasData() const { return hydroset.size() > 0; }

    int rowCount(const QModelIndex& index) const { return hydroset.size(); }
    int columnCount(const QModelIndex& index) const { return 5; }
    QVariant data(const QModelIndex&, int) const;
    QVariant headerData(int, Qt::Orientation, int) const;

    double meanDepth() const { return hydroset.meanDepth(); }
    double meanMagnitude() const { return hydroset.meanMagnitude(); }

  private:
    Hydroset hydroset;
};
