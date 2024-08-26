#pragma once
#include "Repository.h"
#include <qabstractitemmodel.h>

class BacteriumModel : public QAbstractTableModel
{
private:
	Repository& repo;
public:

	BacteriumModel(Repository& repo);
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;
	int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	//bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;
};

