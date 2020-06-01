
#include <QApplication>
#include "MatriXMiXWindow.h"


int main (int argc, char* argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/img/icons/MatriXMiX.png"));
    MatriXMiXWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
