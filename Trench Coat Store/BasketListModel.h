#pragma once
#include <qabstractitemmodel.h>
#include "Basket.h"
#include <memory>

class BasketListModel : public QAbstractListModel
{

private:

	Basket* basket;

public:
	BasketListModel(Basket* _basket, QObject* parent = NULL);
	~BasketListModel();

	//nr of rows
	int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

	//Note that in QAbstractListModel class, columnCount() has a default implementation (as in a list, the column count is 1)

	//value at a given position
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

	//add header data
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

	void addElement(const TrenchCoat& elem);

	int getBasketSum() { return basket->getSum(); }

};

