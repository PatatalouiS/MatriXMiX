
#include <QApplication>
#include "MainWindow.h"

int main (int argc, char* argv[])
{
    QApplication app(argc, argv);
<<<<<<< HEAD
    MainWindow win;
    win.show();
=======
    app.setQuitOnLastWindowClosed(false);
    MainWindow* win = new MainWindow;
    win->show();
>>>>>>> origin/version_graph_ana
    return app.exec();
}

