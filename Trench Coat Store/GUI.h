#pragma once
#include <QtWidgets/QApplication>
#include <vector>
#include <qwidget.h>
#include "BasketListModel.h"
#include "BasketWindow.h"
#include "ControllerAdmin.h"
#include "ControllerUser.h"
#include "Utils.h"
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QPixmap>
#include <QFormLayout>
#include <QButtonGroup>
#include <QMessageBox>
#include <QShortcut>

class GUI : public QWidget
{
    Q_OBJECT
public:

    GUI(ServiceAdmin& _admin, ServiceUser& _user, QApplication& _app, QWidget* parent = 0);
    ~GUI();

    void showWindows();

private:
    ServiceAdmin& admin;
    ServiceUser& user;
    QApplication& app;

    //Windows
    QWidget* adminMenuWindow;
    QWidget* userMenuWindow;
    BasketWindow* basketWindow;  //QAbstractItemView inherits from QWidget
    BasketListModel* basketModel;

    //Main Window : 'this'
    QPushButton* adminModeButton;
    QPushButton* userModeButton;
    QPushButton* mainExitButton;

    //Admin
    QLineEdit* adminSizeEdit;
    QLineEdit* adminColourEdit;
    QLineEdit* adminPriceEdit;
    QLineEdit* adminQuantityEdit;
    QLineEdit* adminPhotographEdit;
    QPushButton* adminAddButton;
    QPushButton* adminUpdateButton;
    QPushButton* adminRemoveButton;
    QLineEdit* adminFilterEdit;
    QListWidget* adminRepoList;
    QPushButton* adminBackButton;
    QPushButton* adminExitButton;
    QPushButton* adminUndoButton;
    QPushButton* adminRedoButton;
    QShortcut* adminUndoShortcut;
    QShortcut* adminRedoShortcut;

    //User
    QLineEdit* userStoreOptionEdit;
    QLineEdit* userSizeEdit;
    QRadioButton* sortAscendingPriceRButton;
    QRadioButton* sortDescendingSizeRButton;
    QRadioButton* noSortRButton;
    QPushButton* userSearchButton;
    QPushButton* userNextButton;
    QPushButton* userBuyButton;
    QLineEdit* userSeeSizeEdit;
    QLineEdit* userSeeColourEdit;
    QLineEdit* userSeePriceEdit;
    QLineEdit* userSeeQuantityEdit;
    QLineEdit* userSeePhotographEdit;
    QPushButton* userSeeBasketButton;
    QPushButton* userBackButton;
    QPushButton* userExitButton;

    //basket
   /* QListWidget* userBasketList;
    QPushButton* basketBackButton;
    QPushButton* basketExitButton;*/

    void initGUI();
    void connectSignalsAndSlots();
    void populateRepoList(std::vector<TrenchCoat> v);
    //void populateBasketList(std::vector<TrenchCoat> v);

    void filterEditedHandler();
    void adminModeButtonClicked();
    void userModeButtonClicked();

    void adminAddButtonClicked();
    void adminRepoListItemSelected();
    void adminUpdateButtonClicked();
    void adminRemoveButtonClicked();
    void adminUndoButtonClicked();
    void adminRedoButtonClicked();

    void userStoreOptionEditingFinished();
    void userSearchButtonClicked();
    void userNextButtonClicked();
    void userBuyButtonClicked();
    void userBasketButtonClicked();

    void backButtonClicked();
    void exitApp();
};

//choose admin-user mode
//ADMIN
// add
// remove
// update
// see all coats
// main menu (back)
//USER
// how should the basket be stored?
// search (parse)
//  how do you want your coats to be sorted?
//  next, buy, stop
// see basket
// main menu (back)
