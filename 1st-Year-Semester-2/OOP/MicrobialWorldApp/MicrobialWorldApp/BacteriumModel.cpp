#include "BacteriumModel.h"

BacteriumModel::BacteriumModel(Repository& repo) : repo{ repo } {}

int BacteriumModel::rowCount(const QModelIndex& parent) const
{
	return this->repo.getBacteria().size();
}

int BacteriumModel::columnCount(const QModelIndex& parent) const
{
	return 4;
}

QVariant BacteriumModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();
	int column = index.column();

	vector<Bacterium> bacteria = this->repo.getBacteria();
	Bacterium b = bacteria[row];

	if (role == Qt::DisplayRole)
	{
		switch (column)
		{
		case 0:
			return QString::fromStdString(b.getName());
		case 1:
			return QString::fromStdString(b.getSpecies());
		case 2:
			return QString::fromStdString(to_string(b.getSize()));
		case 3: {
			string diseases = "";
			for (auto d : b.getListOfDiseases())
				diseases += d + ", ";
			return QString::fromStdString(diseases);
		}
		default:
			break;
		}
	}

	return QVariant();
}

QVariant BacteriumModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role == Qt::DisplayRole)
	{
		if (orientation == Qt::Horizontal)
		{
			switch (section)
			{
			case 0:
				return QString{ "Name" };
			case 1:
				return QString{ "Species" };
			case 2:
				return QString{ "Size" };
			case 3:
				return QString{ "List of diseases" };
			default:
				break;
			}
		}
	}

	return QVariant();
}

//bool BacteriumModel::setData(const QModelIndex& index, const QVariant& value, int role)
//{
//	int row = index.row();
//	int column = index.column();
//
//	Bacterium& b = this->repo.getBacteria()[row];
//
//	if (role == Qt::EditRole || role == Qt::DisplayRole)
//	{
//		switch (column)
//		{
//		case 0:
//
//		}
//	}
//
//
//
//	return false;
//}