#include "TableModel.h"

TableModel::TableModel(AdoptionList& adoptionList, QObject *parent) : adoptionList{ adoptionList }, 
QAbstractTableModel{ parent }{}

int TableModel::rowCount(const QModelIndex & parent) const
{
	return this->adoptionList.getDogs().size();
}

int TableModel::columnCount(const QModelIndex & parent) const
{
	return 4;
}

QVariant TableModel::data(const QModelIndex & index, int role) const
{
	int row = index.row();
	int column = index.column();

	vector<Dog> dogs = this->adoptionList.getDogs();
	Dog dog = dogs[row];
	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(dog.get_name());
		case 1:
			return QString::fromStdString(dog.get_breed());
		case 2:
			return QString::number(dog.get_age());
		case 3:
			return QString::fromStdString(dog.get_photo());
		default:
			break;
		}
	}
	return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const 
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal) {
		switch (section) 
		{
		case 0: 
			return QString("Breed");
		case 1: 
			return QString("Name");
		case 2: 
			return QString("Age");
		case 3: 
			return QString("Photo link");
		default: 
			return QVariant();
		}
	}
	return QVariant();
}