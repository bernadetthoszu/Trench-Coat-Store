#include "BasketListModel.h"
#include <QFont>
#include <QBrush>

//void BasketListModel::removeElement(const TrenchCoat& elem)
//{
//	this->beginRemoveRows(QModelIndex{}, basket->nrCoats(), basket->nrCoats());
//	basket->removeFromBasket(elem);
//	this->endRemoveRows();
//}

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

	//this->undoStack.push_back(std::make_unique<ActionBasketAdd>(elem, this));
	//this->redoStack.clear();
}

//void BasketListModel::undoAddToBasket()
//{
//	if (undoStack.size() == 0)
//		throw UndoRedoError("No more undo's allowed!");
//
//	std::unique_ptr<ActionBasket> a = std::move(undoStack[undoStack.size() - 1]);
//	a->executeUndo();
//	redoStack.push_back(std::move(a));
//	undoStack.pop_back();
//}

//void BasketListModel::redoAddToBasket()
//{
//	if (redoStack.size() == 0)
//		throw UndoRedoError("No more undo's allowed!");
//
//	std::unique_ptr<ActionBasket> a = std::move(redoStack[redoStack.size() - 1]);
//	a->executeUndo();
//	undoStack.push_back(std::move(a));
//	redoStack.pop_back();
//}
