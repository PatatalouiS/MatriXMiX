
#include <QApplication>
#include "MainWindow.h"


int main (int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    MainWindow* win = new MainWindow;
    win->show();
    return app.exec();
}


