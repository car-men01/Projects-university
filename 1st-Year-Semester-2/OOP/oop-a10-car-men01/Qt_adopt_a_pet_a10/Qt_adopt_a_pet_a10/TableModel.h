#pragma once
#include <qabstractitemmodel.h>
#include "AdoptionList.h"

class TableModel : public QAbstractTableModel
{
private:
    AdoptionList& adoptionList;

public:
    TableModel(AdoptionList& adoptionList, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
};

