#pragma once

#include <QWidget>
#include <QShortcut>
#include <QMessageBox>
#include "BasketListModel.h" 
#include "ui_BasketWindow.h"

class BasketWindow : public QWidget
{
	Q_OBJECT

public:
	BasketWindow(QWidget* _user, QWidget* parent = Q_NULLPTR);
	~BasketWindow();

	void setModel(QAbstractListModel* model);
	//void setModel(BasketListModel* model);
	//void resetModel(BasketListModel* model);

	void setSum(int sum);

private:
	QWidget* user;
	Ui::BasketWindow ui;
	BasketListModel* model;

	QShortcut* undoShortcut;
	QShortcut* redoShortcut;

	void backButtonClicked();
	//void undoButtonClicked();
	//void redoButtonClicked();
};
