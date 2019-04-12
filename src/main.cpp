
#include <QApplication>
#include <iostream>
#include <QDir>
#include <QDebug>
#include "MainWindow.h"
#include "LibraryWindow.h"
#include <Dense>


using namespace std;


extern const string APP_PATH = QDir(QApplication::applicationDirPath() + "/../../../").absolutePath().toStdString();

int main (int argc, char* argv[])
{
    QApplication app(argc, argv);

    QDir(QApplication::applicationDirPath() + "/../../../").absolutePath().toStdString();
    //MainWindow* win = new MainWindow;
    LibraryWindow* win = new LibraryWindow(nullptr);
    win->show();

    return app.exec();

}


