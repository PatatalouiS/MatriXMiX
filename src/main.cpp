
#include <QApplication>
#include "MainWindow.h"




using namespace std;


int main (int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    MainWindow* win = new MainWindow;
    win->show();
    return app.exec();
}


