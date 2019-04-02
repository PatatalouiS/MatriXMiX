


#include <QMainWindow>
#include <QPushButton>
#include <QList>
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
    
        QList<QPushButton*> operations;
        LibraryWindow* lib;
};