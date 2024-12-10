#ifndef MATERIALTABLEMODEL_H
#define MATERIALTABLEMODEL_H

#include <QAbstractTableModel>
#include <Qvector>
#include "addedmaterial.h"

class materialtablemodel : public QAbstractTableModel
{
    Q_OBJECT

public:
    materialtablemodel();
};

#endif // MATERIALTABLEMODEL_H
