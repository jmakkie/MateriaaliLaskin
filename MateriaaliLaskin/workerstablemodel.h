#ifndef WORKERSTABLEMODEL_H
#define WORKERSTABLEMODEL_H

#include <QAbstractTableModel>
#include <Qvector>
#include "workers.h"

class workerstablemodel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit workerstablemodel (QVector<workers*> *worker, QObject *parent = nullptr);

    void addWorker(workers *worker);

    //overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QVector<workers*> *worker;
};

#endif // WORKERSTABLEMODEL_H
