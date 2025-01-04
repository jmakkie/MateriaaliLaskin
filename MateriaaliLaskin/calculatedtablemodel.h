#ifndef CALCULATEDTABLEMODEL_H
#define CALCULATEDTABLEMODEL_H

#include <QAbstractTableModel>
#include <Qvector>
#include "workerscalculated.h"

class calculatedtablemodel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit calculatedtablemodel(QVector<workersCalculated*> *workers, QObject *parent = nullptr);
    void addWorker(workersCalculated *worker);

    //overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QVector<workersCalculated*> *workers;
};

#endif // CALCULATEDTABLEMODEL_H
