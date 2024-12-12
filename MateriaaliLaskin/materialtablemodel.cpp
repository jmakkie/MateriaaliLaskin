#include "materialtablemodel.h"

materialtablemodel::materialtablemodel(QVector<addedmaterial*> *materials, QObject *parent)
    :QAbstractTableModel(parent), materials(materials)
{

}

int materialtablemodel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return materials -> size();
}

int materialtablemodel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return 6;
}

QVariant materialtablemodel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    addedmaterial *material = materials -> at(index.row());

    switch (index.column()) {
        case 0: return material -> getName();
        case 1: return material -> getLength();
        case 2: return material -> getPrice();
        case 3: return material -> getAmount();
        case 4: return material -> getLisaName();
        case 5: return material -> getLisaValue();
    default: return QVariant();
    }
}

QVariant materialtablemodel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal) {
        switch (section) {
            case 0: return "name";
            case 1: return "length";
            case 2: return "price";
            case 3: return "amount";
            case 4: return "lisaName";
            case 5: return "lisaValue";
        default: return QVariant();
        }
    }
    return QVariant();
}

void materialtablemodel::addMaterial(addedmaterial *material) {
    beginInsertRows(QModelIndex(), materials -> size() - 1, materials -> size() -1);

    materials -> append(material);

    endInsertRows();
}
