
#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include <QMenuBar>
#include <QLinearGradient>
#include <QGroupBox>
#include "MenuBar.h"
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
    
    private:

        // members
    
        MenuBar* menuBar;
        MatrixLibrary lib;
        std::function<QWidget*(MatrixLibrary*, QWidget*)> createWindow [15];

        // functions

        void setFunctorTab ();
        void show_library ();
        QGroupBox *initBinaryOp();
        QGroupBox *initUnaryOp();
        QGroupBox *initDiagonalisationOp();
};
