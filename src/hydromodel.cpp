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
      case 4: return QVariant(q.getDeterminandNotation().c_str());
      case 5: return QVariant(q.getResultQualifier());
      case 6: return QVariant(q.getResult().c_str());
      case 7: return QVariant(q.getDeterminandUnit().c_str());
      case 8: return QVariant(q.getSampledMaterialType().c_str());
      case 9: return QVariant(q.getSampleCompliant().c_str());
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
    case 0: return QString("Sample Point");
    case 1: return QString("Time");
    case 2: return QString("Determinand");
    case 3: return QString("Definition");
    case 4: return QString("Notation");
    case 5: return QString("Qualifier");
    case 6: return QString("Result");
    case 7: return QString("Unit");
    case 8: return QString("Type");
    case 9: return QString("Compliant");
    default: return QVariant();
  }
}
