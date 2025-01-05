#include "workerstablemodel.h"

workerstablemodel::workerstablemodel(QVector<workers*> *worker, QObject *parent)
    :QAbstractTableModel(parent), worker(worker)
{

}

int workerstablemodel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return worker -> size();
}

int workerstablemodel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return 2;
}

QVariant workerstablemodel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    workers *worker1 = worker -> at(index.row());

    switch (index.column()) {
        case 0: return worker1 -> getWorker();
        case 1: return worker1 -> getHours();
    default: return QVariant();
    }
}

QVariant workerstablemodel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "worker";
        case 1: return "hours";
        default: return QVariant();
        }
    }
    return QVariant();
}

void workerstablemodel::addWorker(workers *worker1) {
    beginInsertRows(QModelIndex(), worker -> size() - 1, worker -> size() -1);

    worker -> append(worker1);

    endInsertRows();
}
