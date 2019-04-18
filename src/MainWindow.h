
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
    
        void addNewMatrix(const QString name, const Matrix matrix);
        void compute_choice (const unsigned int choice);
        void show_library ();
    
    private:
    
        QList<QPushButton*> operations;
        MatrixLibrary lib;
        std::function<QWidget*(MatrixLibrary*, QWidget*)> createWindow [10];

        void setFunctorTab ();
};
