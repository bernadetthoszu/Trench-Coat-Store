#include "TrenchCoatStore.h"
#include <QtWidgets/QApplication>

#include "GUI.h"
#include "Repository.h"
#include "ControllerAdmin.h"
#include "ControllerUser.h"
#include "Tests.h"
#include <iostream>
#include <fstream>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    //Tests t = Tests();
    //t.runAllTests();

    Repo repo{ "repository.txt" };
    repo.load();   //load repo at application startup

    ServiceAdmin srv_a{ repo };
    ServiceUser srv_u{ repo };

    GUI gui{ srv_a, srv_u, a };
    gui.show();
    return a.exec();
}
