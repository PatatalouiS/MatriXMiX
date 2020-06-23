
#include <QApplication>
#include "MainWindow.hpp"

int main (int argc, char* argv[])
{
    qputenv("Q_STYLE_OVERRIDE", 0);
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/img/icons/MatriXMiX.png"));
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}
