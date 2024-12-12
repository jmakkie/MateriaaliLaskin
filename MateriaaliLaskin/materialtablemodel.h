#ifndef MATERIALTABLEMODEL_H
#define MATERIALTABLEMODEL_H

#include <QAbstractTableModel>
#include <Qvector>
#include "addedmaterial.h"

class materialtablemodel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit materialtablemodel(QVector<addedmaterial*> *materials, QObject *parent = nullptr);

    void addMaterial(addedmaterial *material);

    //overrides
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
    QVector<addedmaterial*> *materials;
};

#endif // MATERIALTABLEMODEL_H
