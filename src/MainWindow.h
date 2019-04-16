
#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include <QMenuBar>
#include <QLinearGradient>
#include "LibraryWindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
    
        MainWindow ();
        ~MainWindow ();
    
    signals:
    
    public slots:
    
        void compute_choice (const unsigned int choice);
        void show_library ();
    
    private:
    
        void setFunctorTab ();
        QList<QPushButton*> operations;
        MatrixLibrary lib;
        std::function<QWidget*(void)> createWindow [10];
};
