
#include <QMainWindow>
#include <QPushButton>
#include <QList>
#include <QMenuBar>
#include <QLinearGradient>
#include <QGroupBox>
#include "MenuBar.h"
#include "LibraryWindow.h"
#include "AbstractOperationWidget.h"

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
        AbstractOperationWidget* currentOpWidget;
        QVBoxLayout* currentOpLayout;
        unsigned int currentChoice;
        ShowMatrixWidget* imgResult;
        std::function<AbstractOperationWidget*(void)> createWindow [15];

        // functions

        void setFunctorTab ();
        void show_library ();
        void transferResult (const QVariant& res);
        QGroupBox *initBinaryOp();
        QGroupBox *initUnaryOp();
        QGroupBox *initDiagonalisationOp();
};
