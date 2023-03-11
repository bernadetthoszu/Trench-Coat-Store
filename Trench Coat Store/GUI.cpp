#include "GUI.h"

GUI::GUI(ServiceAdmin& _admin, ServiceUser& _user, QApplication& _app, QWidget* parent) : QWidget{ parent }, admin{ _admin }, user{ _user }, app{ _app }
{
    this->initGUI();
    this->connectSignalsAndSlots();
    admin.loadRepo();
    std::vector<TrenchCoat> allCoats = admin.getAllCoats();
    this->populateRepoList(allCoats);
}

GUI::~GUI()
{
    delete adminMenuWindow;
    delete userMenuWindow;
    //delete basketWindow;

    delete adminModeButton;
    delete userModeButton;
    delete mainExitButton;

    //the rest is destroyed by de destructos of these objects
}

void GUI::initGUI()
{
    //START WINDOW
    this->setWindowTitle("Trench Store");

    QHBoxLayout* mainL = new QHBoxLayout(this);
    QVBoxLayout* mainLeftL = new QVBoxLayout{};
    QVBoxLayout* mainRightL = new QVBoxLayout{};
    //mainL->setAlignment(Qt::AlignCenter);


    QPixmap pix{ "C:/Users/Berni/Documents/GitHub/OOP/a11-12-913-Hoszu-Bernadett/GUITrench/trench_logo1.jpg" };
    QLabel* startPic = new QLabel{};
    startPic->setPixmap(pix.scaled(pix.width() / 3, pix.height() / 3, Qt::KeepAspectRatio));
    //mainL->setAlignment(welcome, Qt::AlignCenter);
    mainLeftL->addWidget(startPic);

    QLabel* welcome = new QLabel{ "Welcome to the Trench Store!" };
    adminModeButton = new QPushButton{ "Administrator" }; // QMenu inherits QWidget
    userModeButton = new QPushButton{ "User" };
    mainExitButton = new QPushButton{ "Exit" };
    mainRightL->addWidget(welcome);
    mainRightL->setAlignment(welcome, Qt::AlignCenter);
    mainRightL->addWidget(adminModeButton);
    mainRightL->setAlignment(adminModeButton, Qt::AlignCenter);
    mainRightL->addWidget(userModeButton);
    mainRightL->setAlignment(userModeButton, Qt::AlignCenter);
    mainRightL->addWidget(mainExitButton);
    mainRightL->setAlignment(mainExitButton, Qt::AlignCenter);

    mainL->addLayout(mainLeftL);
    mainL->addLayout(mainRightL);
    mainL->setAlignment(mainRightL, Qt::AlignCenter);

    this->setFixedWidth(800);
    this->setFixedHeight(500);


    //ADMIN WINDOW
    adminMenuWindow = new QWidget{};
    QHBoxLayout* adminWindowL = new QHBoxLayout{ adminMenuWindow };
    adminMenuWindow->setWindowTitle("Administrator");

    //left side
    QFormLayout* adminLeftL = new QFormLayout{};
    QLabel* emptyLabel = new QLabel{ " " };
    QLabel* sizeLabel = new QLabel{ "Size: " };
    QLabel* colourLabel = new QLabel{ "Colour: " };
    QLabel* priceLabel = new QLabel{ "Price: " };
    QLabel* quantityLabel = new QLabel{ "Quantity: " };
    QLabel* photoLabel = new QLabel{ "Picture link: " };
    adminSizeEdit = new QLineEdit{};
    adminColourEdit = new QLineEdit{};
    adminPriceEdit = new QLineEdit{};
    adminQuantityEdit = new QLineEdit{};
    adminPhotographEdit = new QLineEdit{};
    sizeLabel->setBuddy(adminSizeEdit);
    colourLabel->setBuddy(adminColourEdit);
    priceLabel->setBuddy(adminPriceEdit);
    quantityLabel->setBuddy(adminQuantityEdit);
    photoLabel->setBuddy(adminPhotographEdit);
    adminLeftL->addRow(emptyLabel);
    adminLeftL->addRow(sizeLabel, adminSizeEdit);
    adminLeftL->addRow(colourLabel, adminColourEdit);
    adminLeftL->addRow(priceLabel, adminPriceEdit);
    adminLeftL->addRow(quantityLabel, adminQuantityEdit);
    adminLeftL->addRow(photoLabel, adminPhotographEdit);
    adminLeftL->addRow(emptyLabel);
    adminLeftL->addRow(emptyLabel);
    adminAddButton = new QPushButton{ "Add" };
    adminUpdateButton = new QPushButton{ "Update" };
    adminRemoveButton = new QPushButton{ "Remove" };
    QHBoxLayout* buttons1L = new QHBoxLayout{};
    buttons1L->addWidget(adminAddButton);
    buttons1L->addWidget(adminUpdateButton);
    buttons1L->addWidget(adminRemoveButton);
    adminLeftL->addRow(buttons1L);

    //right side
    QVBoxLayout* adminRightL = new QVBoxLayout{};
    QHBoxLayout* filterL = new QHBoxLayout{};
    QLabel* filterLabel = new QLabel{ "Filter: " };
    adminFilterEdit = new QLineEdit{};
    filterLabel->setBuddy(adminFilterEdit);
    filterL->addWidget(filterLabel);
    filterL->addWidget(adminFilterEdit);
    adminRightL->addLayout(filterL, Qt::AlignTop);
    QLabel* repoLabel = new QLabel{ "All coats" };
    adminRepoList = new QListWidget{};
    adminRepoList->setSelectionMode(QAbstractItemView::SingleSelection);
    //...
    //addintional requirement lab 12
    QLinearGradient gradient = QLinearGradient(adminRepoList->rect().topLeft(), adminRepoList->rect().bottomRight());
    QColor colour = QColor(255, 51, 218, 100);
    gradient.setColorAt(0, colour);
    gradient.setColorAt(1, Qt::white);
    QBrush brush = QBrush(gradient);
    QPalette palette = QPalette();
    palette.setBrush(QPalette::Base, brush);
    adminRepoList->setPalette(palette);
    //...
    QHBoxLayout* buttons2L = new QHBoxLayout{};
    adminBackButton = new QPushButton{ "Back" };
    adminExitButton = new QPushButton{ "Exit" };
    buttons2L->addWidget(adminBackButton);
    buttons2L->addWidget(adminExitButton);
    adminRightL->addWidget(repoLabel);
    adminRightL->addWidget(adminRepoList);
    adminRightL->addLayout(buttons2L);

    //embed in main layout
    adminWindowL->addLayout(adminLeftL);
    adminWindowL->addLayout(adminRightL);

    adminMenuWindow->setFixedWidth(800);
    adminMenuWindow->setFixedHeight(500);



    //USER WINDOW
    userMenuWindow = new QWidget{};
    QHBoxLayout* userWindowL = new QHBoxLayout{ userMenuWindow };
    userMenuWindow->setWindowTitle("User");

    //left side
    QVBoxLayout* userLeftL = new QVBoxLayout{};
    userLeftL->addStretch(2);
    QHBoxLayout* storeL = new QHBoxLayout{};
    QLabel* storingOption = new QLabel{ "Save basket as: " };
    userStoreOptionEdit = new QLineEdit{};
    storingOption->setBuddy(userStoreOptionEdit);
    storeL->addWidget(storingOption, Qt::AlignTop);
    storeL->addWidget(userStoreOptionEdit, Qt::AlignTop);
    userLeftL->addLayout(storeL, Qt::AlignTop);
    QGridLayout* sortingL = new QGridLayout{};
    QLabel* sortLabel = new QLabel{ "Sort: " };
    QButtonGroup* sortingRadioGroup = new QButtonGroup{};
    sortAscendingPriceRButton = new QRadioButton{ "Ascending by price" };
    sortDescendingSizeRButton = new QRadioButton{ "Descending by size" };
    noSortRButton = new QRadioButton{ "No sort" };
    sortingRadioGroup->addButton(sortAscendingPriceRButton, 1);
    sortingRadioGroup->addButton(sortDescendingSizeRButton, 2);
    sortingRadioGroup->addButton(noSortRButton, 3);
    sortingL->addWidget(sortLabel, 0, 0, Qt::AlignTop);
    sortingL->addWidget(sortAscendingPriceRButton, 0, 1, Qt::AlignTop);
    sortingL->addWidget(sortDescendingSizeRButton, 1, 1, Qt::AlignTop);
    sortingL->addWidget(noSortRButton, 2, 1, Qt::AlignTop);
    userLeftL->addLayout(sortingL, Qt::AlignTop);
    QHBoxLayout* searchL = new QHBoxLayout{};
    userSizeEdit = new QLineEdit{};
    QLabel* userSizeLabel1 = new QLabel{ "Size: " };
    userSizeLabel1->setBuddy(userSizeEdit);
    userSearchButton = new QPushButton{ "Search" };
    searchL->addWidget(userSizeLabel1, Qt::AlignTop);
    searchL->addWidget(userSizeEdit, Qt::AlignTop);
    searchL->addWidget(userSearchButton, Qt::AlignTop);
    userLeftL->addLayout(searchL, Qt::AlignTop);
    userLeftL->addStretch(200);
    QHBoxLayout* backExitL = new QHBoxLayout{};
    userBackButton = new QPushButton{ "Back" };
    userExitButton = new QPushButton{ "Exit" };
    backExitL->addWidget(userBackButton);
    backExitL->addWidget(userExitButton);
    userLeftL->addLayout(backExitL, Qt::AlignBottom);

    //right side
    QVBoxLayout* userRightL = new QVBoxLayout{};
    QLabel* coatLabel = new QLabel{ "Coat: " };
    userRightL->addStretch(1);
    userRightL->addWidget(coatLabel, 2, Qt::AlignTop);
    QFormLayout* showCoatL = new QFormLayout{};
    userSeeSizeEdit = new QLineEdit{};
    userSeeColourEdit = new QLineEdit{};
    userSeePriceEdit = new QLineEdit{};
    userSeeQuantityEdit = new QLineEdit{};
    userSeePhotographEdit = new QLineEdit{};
    userSeeSizeEdit->setDisabled(true);
    userSeeColourEdit->setDisabled(true);
    userSeePriceEdit->setDisabled(true);
    userSeeQuantityEdit->setDisabled(true);
    userSeePhotographEdit->setDisabled(true);
    QLabel* userSizeLabel = new QLabel{ "Size: " };
    QLabel* userColourLabel = new QLabel{ "Colour: " };
    QLabel* userPriceLabel = new QLabel{ "Price: " };
    QLabel* userQuantityLabel = new QLabel{ "Quantity: " };
    QLabel* userPhotoLabel = new QLabel{ "Picture link: " };
    showCoatL->addRow(userSizeLabel, userSeeSizeEdit);
    showCoatL->addRow(userColourLabel, userSeeColourEdit);
    showCoatL->addRow(userPriceLabel, userSeePriceEdit);
    showCoatL->addRow(userQuantityLabel, userSeeQuantityEdit);
    showCoatL->addRow(userPhotoLabel, userSeePhotographEdit);
    QHBoxLayout* nextBuyL = new QHBoxLayout{};
    userNextButton = new QPushButton{ "Next" };
    userBuyButton = new QPushButton{ "Buy" };
    nextBuyL->addWidget(userNextButton);
    nextBuyL->addWidget(userBuyButton);
    showCoatL->addRow(nextBuyL);
    userRightL->addLayout(showCoatL, Qt::AlignTop);
    userSeeBasketButton = new QPushButton{ "Basket" };
    userRightL->addWidget(userSeeBasketButton, Qt::AlignBottom);

    //embed in main layout
    userWindowL->addLayout(userLeftL);
    userWindowL->addLayout(userRightL);

    userMenuWindow->setFixedWidth(800);
    userMenuWindow->setFixedHeight(500);



    //Basket Window
    /*basketWindow = new QWidget{};
    QVBoxLayout* basketWindowL = new QVBoxLayout{ basketWindow };
    basketWindow->setWindowTitle("Basket");

    QLabel* basketLabel = new QLabel{ "Your items: " };
    basketWindowL->addWidget(basketLabel, 3, Qt::AlignTop);
    userBasketList = new QListWidget{};
    userBasketList->setSelectionMode(QAbstractItemView::NoSelection);
    QFont f{ "Courier" , 12 };
    f.setItalic(true);
    userBasketList->setFont(f);
    basketWindowL->addWidget(userBasketList, Qt::AlignTop);
    QHBoxLayout* basketButtonsL = new QHBoxLayout{};
    basketBackButton = new QPushButton{"Back"};
    basketExitButton = new QPushButton{"Exit"};
    basketButtonsL->addWidget(basketBackButton);
    basketButtonsL->addWidget(basketExitButton);
    basketButtonsL->setStretch(1, 3);
    basketButtonsL->setStretch(0, 3);
    basketWindowL->addLayout(basketButtonsL, Qt::AlignBottom);

    basketWindow->setFixedWidth(800);
    basketWindow->setFixedHeight(500);*/


    //basketWindow->show();
    userMenuWindow->show();
    adminMenuWindow->show();

}

void GUI::connectSignalsAndSlots()
{
    /*
    connect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method, Qt::ConnectionType type)
    */
    QObject::connect(adminFilterEdit, &QLineEdit::textChanged, this, &GUI::filterEditedHandler);
    QObject::connect(adminModeButton, &QPushButton::clicked, this, &GUI::adminModeButtonClicked);
    QObject::connect(userModeButton, &QPushButton::clicked, this, &GUI::userModeButtonClicked);
    QObject::connect(mainExitButton, &QPushButton::clicked, this, &GUI::exitApp);
    QObject::connect(adminAddButton, &QPushButton::clicked, this, &GUI::adminAddButtonClicked);
    QObject::connect(adminUpdateButton, &QPushButton::clicked, this, &GUI::adminUpdateButtonClicked);
    QObject::connect(adminRepoList, &QListWidget::itemClicked, this, &GUI::adminRepoListItemSelected);
    QObject::connect(adminRemoveButton, &QPushButton::clicked, this, &GUI::adminRemoveButtonClicked);
    QObject::connect(adminBackButton, &QPushButton::clicked, this, &GUI::backButtonClicked);
    QObject::connect(adminExitButton, &QPushButton::clicked, this, &GUI::exitApp);

    QObject::connect(userStoreOptionEdit, &QLineEdit::editingFinished, this, &GUI::userStoreOptionEditingFinished);
    QObject::connect(userSearchButton, &QPushButton::clicked, this, &GUI::userSearchButtonClicked);
    QObject::connect(userNextButton, &QPushButton::clicked, this, &GUI::userNextButtonClicked);
    QObject::connect(userBuyButton, &QPushButton::clicked, this, &GUI::userBuyButtonClicked);
    QObject::connect(userSeeBasketButton, &QPushButton::clicked, this, &GUI::userBasketButtonClicked);
    QObject::connect(userBackButton, &QPushButton::clicked, this, &GUI::backButtonClicked);
    QObject::connect(userExitButton, &QPushButton::clicked, this, &GUI::exitApp);

    //QObject::connect(basketBackButton, &QPushButton::clicked, this, &GUI::backButtonClicked);
    //QObject::connect(basketExitButton, &QPushButton::clicked, this, &GUI::exitApp);
}

void GUI::populateRepoList(std::vector<TrenchCoat> v)
{

    if (adminRepoList->count() > 0)
        adminRepoList->clear();

    for (auto t : v)
    {
        QString itemInList = QString::fromStdString(t.toSring());
        QFont f{ "Courier" , 12 };
        f.setItalic(true);
        QListWidgetItem* item = new QListWidgetItem{ itemInList };
        item->setFont(f);
        adminRepoList->addItem(item);
    }

    if (v.size() > 0)
        adminRepoList->setCurrentRow(0);
}

void GUI::filterEditedHandler()
{
    std::string newText = adminFilterEdit->text().toStdString();
    std::vector<TrenchCoat> found;
    if (newText.size() == 0)
        populateRepoList(admin.getAllCoats());
    else
    {
        found = admin.searchRepo(newText);
        populateRepoList(found);
    }
}

void GUI::adminModeButtonClicked()
{
    //void QWidget::setWindowState(Qt::WindowStates windowState)
    //windowState ->  Qt::WindowMinimized, Qt::WindowMaximized, Qt::WindowFullScreen, and Qt::WindowActive
    userNextButton->setDisabled(true);
    userBuyButton->setDisabled(true);
    userSearchButton->setDisabled(true);
    userSeeBasketButton->setDisabled(true);
    adminMenuWindow->activateWindow();
}

void GUI::userModeButtonClicked()
{
    userSizeEdit->clear();
    userStoreOptionEdit->clear();
    sortAscendingPriceRButton->setChecked(false);
    sortDescendingSizeRButton->setChecked(false);
    noSortRButton->setChecked(false);
    userSeeSizeEdit->clear();
    userSeeColourEdit->clear();
    userSeePriceEdit->clear();
    userSeeQuantityEdit->clear();
    userSeePhotographEdit->clear();

    userMenuWindow->activateWindow();
}

void GUI::adminAddButtonClicked()
{
    int ID = adminRepoList->count() + 1;
    std::string size = adminSizeEdit->text().toStdString();
    std::string colour = adminColourEdit->text().toStdString();
    int price = adminPriceEdit->text().toInt();
    int quantity = adminQuantityEdit->text().toInt();
    std::string photograph = adminPhotographEdit->text().toStdString();
    try {
        admin.add(ID, size, colour, price, quantity, photograph);
    }
    catch (ValidationError& ve)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Validation error");
        msgBox.setText(ve.what());
        msgBox.exec();
        return;
    }
    catch (RepoError& re)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Repository error");
        msgBox.setText(re.what());
        msgBox.exec();
        return;
    }

    TrenchCoat t = admin.getByID(ID);
    QString itemInList = QString::fromStdString(t.toSring());
    QFont f{ "Courier" , 12 };
    f.setItalic(true);
    QListWidgetItem* item = new QListWidgetItem{ itemInList };
    item->setFont(f);
    adminRepoList->addItem(item);

    adminSizeEdit->clear();
    adminColourEdit->clear();
    adminPriceEdit->clear();
    adminQuantityEdit->clear();
    adminPhotographEdit->clear();
}

void GUI::adminRepoListItemSelected()
{
    //element we want to update must be selected
    QModelIndexList index_list = adminRepoList->selectionModel()->selectedIndexes();
    if (index_list.size() == 0)
        return;

    QListWidgetItem* elem = adminRepoList->currentItem();
    std::string elem_str = elem->text().toStdString();

    std::string ID, size, colour, quantity, price, photograph, prop, garbage;

    std::stringstream tokenize;
    tokenize << elem_str;
    getline(tokenize, garbage, ':');
    getline(tokenize, ID, ',');
    ID = trim(ID);
    getline(tokenize, garbage, ':');
    getline(tokenize, size, ',');
    size = trim(size);
    getline(tokenize, garbage, ':');
    getline(tokenize, colour, ',');
    colour = trim(colour);
    getline(tokenize, garbage, ':');
    getline(tokenize, quantity, ',');
    quantity = trim(quantity);
    getline(tokenize, garbage, ':');
    getline(tokenize, price, ',');
    price = trim(price);
    getline(tokenize, garbage, ':');
    getline(tokenize, photograph, ',');
    photograph = trim(photograph);

    adminSizeEdit->setText(QString::fromStdString(size));
    adminColourEdit->setText(QString::fromStdString(colour));
    adminPriceEdit->setText(QString::fromStdString(price));
    adminQuantityEdit->setText(QString::fromStdString(quantity));
    adminPhotographEdit->setText(QString::fromStdString(photograph));
}

void GUI::adminUpdateButtonClicked()
{
    //element we want to update must be selected
    QModelIndexList index_list = adminRepoList->selectionModel()->selectedIndexes();
    if (index_list.size() == 0)
        return;

    QListWidgetItem* elem = adminRepoList->currentItem();
    int ID = adminRepoList->row(elem) + 1;

    std::string size = adminSizeEdit->text().toStdString();
    std::string colour = adminColourEdit->text().toStdString();
    int price = adminPriceEdit->text().toInt();
    int quantity = adminQuantityEdit->text().toInt();
    std::string photograph = adminPhotographEdit->text().toStdString();

    try
    {
        admin.updateSize(ID, size);
        admin.updateColour(ID, colour);
        admin.updatePrice(ID, price);
        admin.updateQuantity(ID, quantity);
        admin.updatePhotograph(ID, photograph);
    }
    catch (ValidationError& ve)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Validation error");
        msgBox.setText(ve.what());
        msgBox.exec();
        return;
    }
    catch (RepoError& re)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Repository error");
        msgBox.setText(re.what());
        msgBox.exec();
        return;
    }

    adminRepoList->takeItem(ID - 1); //Removes and returns the item from the given row in the list widget; otherwise returns nullptr.
    //ID -1 because  ID >= 1 while list indexing starts at 0
    QString itemInList = QString::fromStdString(admin.getByID(ID).toSring());
    QFont f{ "Courier" , 12 };
    f.setItalic(true);
    QListWidgetItem* item = new QListWidgetItem{ itemInList };
    item->setFont(f);
    adminRepoList->insertItem(ID - 1, item);

    adminSizeEdit->clear();
    adminColourEdit->clear();
    adminPriceEdit->clear();
    adminQuantityEdit->clear();
    adminPhotographEdit->clear();
}

void GUI::adminRemoveButtonClicked()
{
    QModelIndexList index_list = adminRepoList->selectionModel()->selectedIndexes();
    if (index_list.size() == 0)
        return;

    QListWidgetItem* elem = adminRepoList->currentItem();
    int ID = adminRepoList->row(elem) + 1;

    try {
        admin.remove(ID);
    }
    catch (ValidationError& ve)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Validation error");
        msgBox.setText(ve.what());
        msgBox.exec();
        return;
    }
    catch (RepoError& re)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Repository error");
        msgBox.setText(re.what());
        msgBox.exec();
        return;
    }

    adminRepoList->takeItem(ID - 1);

    adminSizeEdit->clear();
    adminColourEdit->clear();
    adminPriceEdit->clear();
    adminQuantityEdit->clear();
    adminPhotographEdit->clear();
}

void GUI::userStoreOptionEditingFinished()
{
    user.newBasket(userStoreOptionEdit->text().toStdString());
    userSearchButton->setEnabled(true);
}

void GUI::userSearchButtonClicked()
{
    try {
        user.search(userSizeEdit->text().toStdString());
    }
    catch (ValidationError& ve)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Validation error");
        msgBox.setText(ve.what());
        msgBox.exec();
        return;
    }

    if (user.nrFoundCoats() == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("No coats found");
        msgBox.setText("Sorry, we do not currently store coats of the given size!");
        msgBox.exec();
        return;
    }

    if (!sortAscendingPriceRButton->isChecked() && !sortDescendingSizeRButton->isChecked() && !noSortRButton->isChecked())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("I'm confused");
        msgBox.setText("I kindly ask you to state your sorting option!");
        msgBox.exec();
        return;
    }

    if (sortAscendingPriceRButton->isChecked())
    {
        ComparatorAscendingByPrice* c = new ComparatorAscendingByPrice();
        user.sortSearchResult(c);
        delete c;
    }
    else
    {
        ComparatorDescendingBySize* c = new ComparatorDescendingBySize();
        user.sortSearchResult(c);
        delete c;
    }

    user.startParse();
    TrenchCoat t = user.getCurrent();
    userSeeSizeEdit->setText(QString::fromStdString(t.getSize()));
    userSeeColourEdit->setText(QString::fromStdString(t.getColour()));
    userSeePriceEdit->setText(QString::number(t.getPrice()));
    userSeeQuantityEdit->setText(QString::number(t.getQuantity()));
    userSeePhotographEdit->setText(QString::fromStdString(t.getPhotograph()));

    userNextButton->setEnabled(true);
    userBuyButton->setEnabled(true);
    userSeeBasketButton->setEnabled(true);
}

void GUI::userNextButtonClicked()
{
    user.next();
    TrenchCoat t = user.getCurrent();
    userSeeSizeEdit->setText(QString::fromStdString(t.getSize()));
    userSeeColourEdit->setText(QString::fromStdString(t.getColour()));
    userSeePriceEdit->setText(QString::number(t.getPrice()));
    userSeeQuantityEdit->setText(QString::number(t.getQuantity()));
    userSeePhotographEdit->setText(QString::fromStdString(t.getPhotograph()));
}

void GUI::userBuyButtonClicked()
{
    user.addToBasket(user.getCurrent());
    QString sum_qstr = QString::number(user.getSum());

    QMessageBox msgBox;
    msgBox.setWindowTitle("Basket");
    msgBox.setText(QString("Coat added to your basket!\nYour current sum: %1").arg(sum_qstr));
    msgBox.exec();
}

void GUI::userBasketButtonClicked()
{
    user.showBasket();
}

//void GUI::populateBasketList(std::vector<TrenchCoat> v)
//{
//
//    if (userBasketList->count() > 0)
//        adminRepoList->clear();
//
//    for (auto t : v)
//    {
//        QString itemInList = QString::fromStdString(t.toSring());
//        QFont f{ "Courier" , 12 };
//        f.setItalic(true);
//        QListWidgetItem* item = new QListWidgetItem{ itemInList };
//        item->setFont(f);
//        userBasketList->addItem(item);
//    }
//
//}

void GUI::backButtonClicked()
{
    this->activateWindow();
}

void GUI::exitApp()
{
    app.quit();
}
