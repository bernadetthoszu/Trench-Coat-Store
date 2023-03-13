#include "BasketListModel.h"
#include <QFont>
#include <QBrush>


BasketListModel::BasketListModel(Basket* _basket, QObject* parent) : QAbstractListModel{ parent }, basket{ _basket }
{
}

BasketListModel::~BasketListModel()
{
}

int BasketListModel::rowCount(const QModelIndex& parent) const
{
	int nrOfBasketItems = this->basket->nrCoats();
	return nrOfBasketItems;
}

QVariant BasketListModel::data(const QModelIndex& index, int role) const
{
	int row = index.row();

	std::vector<TrenchCoat> coats = this->basket->getElements();

	//Get coat from the current row (indexes correspond)
	TrenchCoat t = coats[row];

	if (role == Qt::DisplayRole)
		return QString::fromStdString(t.toSring());

	if (role == Qt::FontRole)
	{
		QFont font{ "Courier" , 12 };
		font.setItalic(true);
		return font;
	}

	return QVariant();
}

QVariant BasketListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	return QVariant();
}

void BasketListModel::addElement(const TrenchCoat& elem)
{
	this->beginInsertRows(QModelIndex{}, basket->nrCoats(), basket->nrCoats());
	basket->addToBasket(elem);
	this->endInsertRows();
}
