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

	undoShortcut = new QShortcut{ QKeySequence(tr("Ctrl+U")), ui.undoButton };
	redoShortcut = new QShortcut{ QKeySequence(tr("Ctrl+R")), ui.redoButton };
	//QObject::connect(ui.undoButton, &QPushButton::clicked, this, &BasketWindow::undoButtonClicked);
	//QObject::connect(ui.redoButton, &QPushButton::clicked, this, &BasketWindow::redoButtonClicked);
	//QObject::connect(undoShortcut, &QShortcut::activated, this, &BasketWindow::undoButtonClicked);
	//QObject::connect(redoShortcut, &QShortcut::activated, this, &BasketWindow::redoButtonClicked);

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

//void BasketWindow::undoButtonClicked()
//{
//	try {
//		model->undoAddToBasket();
//	}
//	catch (UndoRedoError& ure)
//	{
//		QMessageBox msgBox;
//		msgBox.setWindowTitle("Error");
//		msgBox.setText(ure.what());
//		msgBox.exec();
//	}
//}

//void BasketWindow::redoButtonClicked()
//{
//	try {
//		model->redoAddToBasket();
//	}
//	catch (UndoRedoError& ure)
//	{
//		QMessageBox msgBox;
//		msgBox.setWindowTitle("Error");
//		msgBox.setText(ure.what());
//		msgBox.exec();
//	}
//}
