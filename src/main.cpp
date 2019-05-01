
#include <QApplication>
#include "MainWindow.h"


#include <iostream>
#include <sstream>
#include <QString>
#include <QDebug>
#include <cmath>


using namespace std;






int main (int argc, char* argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();


//   double a = 1244776836434675647;

//   QString str;

//   if(floor(a) == a)
//   str.setNum(a, 'f', 0);
//   else str.setNum(a, 'f', 10);

//   qDebug() <<(str);




//    return 0;
}

