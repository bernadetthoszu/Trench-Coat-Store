#include "BasketWindow.h"

BasketWindow::BasketWindow(QWidget* _user, QWidget* parent) : QWidget(parent), user{ _user }
{
	ui.setupUi(this);

	model = nullptr;
	this->ui.basketListView->setModel(nullptr);

	QLinearGradient gradient = QLinearGradient(this->rect().topLeft(), this->rect().bottomRight());
	QColor colour = QColor(255, 51, 218, 100);
	gradient.setColorAt(0, colour);
	gradient.setColorAt(1, Qt::white);
	QBrush brush = QBrush(gradient);
	QPalette palette = QPalette();
	palette.setBrush(QPalette::Base, brush);
	this->setPalette(palette);

	QObject::connect(ui.basketBackButton, &QPushButton::clicked, this, &BasketWindow::backButtonClicked);

}

BasketWindow::~BasketWindow()
{
}

void BasketWindow::setModel(QAbstractListModel* model)
{
	this->ui.totalSumEdit->clear();
	this->ui.basketListView->setModel(model);
}

void BasketWindow::setSum(int sum)
{
	this->ui.totalSumEdit->setText(QString::number(sum));
}

void BasketWindow::backButtonClicked()
{
	user->activateWindow();
}
