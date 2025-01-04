#include "calculatedtablemodel.h"

calculatedtablemodel::calculatedtablemodel(QVector<workersCalculated*> *workers, QObject *parent)
    :QAbstractTableModel(parent), workers(workers)
{}

int calculatedtablemodel::rowCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return workers -> size();
}

int calculatedtablemodel::columnCount(const QModelIndex &parent) const {
    if (parent.isValid())
        return 0;
    return 4;
}

QVariant calculatedtablemodel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    workersCalculated *worker = workers -> at(index.row());

    switch (index.column()) {
    case 0: return worker -> getWorker();
    case 1: return worker -> getHours();
    case 2: return worker -> getSalary();
    case 3: return worker -> getToPayment();
    default: return QVariant();
    }
}

QVariant calculatedtablemodel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if(orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "worker";
        case 1: return "hours";
        case 2: return "salary";
        case 3: return "toPayment";
        default: return QVariant();
        }
    }
    return QVariant();
}

void calculatedtablemodel::addWorker(workersCalculated *worker) {
    beginInsertRows(QModelIndex(), workers -> size() - 1, workers -> size() -1);

    workers -> append(worker);

    endInsertRows();
}
