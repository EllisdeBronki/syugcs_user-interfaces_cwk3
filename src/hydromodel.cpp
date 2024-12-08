#include "hydromodel.hpp"

/* -------------------------------------- **
 * Watertool : Hydromodel                 *
 * Editor(s) : Alexander Del Brocco       *
 * Module    : COMP2711 - User Interfaces *
** -------------------------------------- */

void Hydromodel::updateFromFile(const QString& filename)
{
  beginResetModel();
  hydroset.loadData(filename.toStdString());
  endResetModel();
}

QVariant Hydromodel::data(const QModelIndex& index, int role) const
{
  if (!index.isValid()) {
    return QVariant();
  }

  if (role == Qt::TextAlignmentRole) {
    return int(Qt::AlignRight | Qt::AlignVCenter);
  }
  else if (role == Qt::DisplayRole) {
    Waterbody q = hydroset[index.row()];
    switch (index.column()) { // Loads Columns of Waterbody
      case 0: return QVariant(q.getSamplingPoint().c_str());
      case 1: return QVariant(q.getTime().c_str());
      case 2: return QVariant(q.getDeterminand().c_str());
      case 3: return QVariant(q.getDeterminandDefinition().c_str());
      case 4: return QVariant(q.getDeterminandNotation());
      case 5: return QVariant(q.getResultQualifier().c_str());
      case 6: return QVariant(q.getResult());
      case 7: return QVariant(q.getDeterminandUnit().c_str());
      case 7: return QVariant(q.getSampledMaterialType().c_str());
      case 8: return QVariant(q.getSampleCompliant());
    }
  }

  return QVariant();
}


QVariant Hydromodel::headerData(int section, Qt::Orientation orientation, int role) const
{
  if (role != Qt::DisplayRole) {
    return QVariant();
  }

  if (orientation == Qt::Vertical) {
    return QVariant(section + 1);
  }

  switch (section) {
    case 0: return QString("Time");
    case 1: return QString("Latitude");
    case 2: return QString("Longitude");
    case 3: return QString("Depth");
    case 4: return QString("Magnitude");
    default: return QVariant();
  }
}
