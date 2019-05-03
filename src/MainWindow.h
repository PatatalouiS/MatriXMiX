
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
       
    private slots:

          void showLibraryWindow ();
          void execSaveTool ();
          void execLoadTool ();
          void transferResult (const QVariant& res);
          void compute_choice (const unsigned int choice);

    private:

        // members
    
        MenuBar* menuBar;
        MatrixLibrary library;
        LibraryWindow* libraryWindow;
        AbstractOperationWidget* currentOpWidget;
        QVBoxLayout* currentOpLayout;
        unsigned int currentChoice;
        ShowMatrixWidget* imgResult;
        std::function<AbstractOperationWidget*(void)> createWindow [15];

        // functions

        void setFunctorTab ();
        QGroupBox* initBinaryOp();
        QGroupBox* initUnaryOp();
        QGroupBox* initDiagonalisationOp();

    signals :

        void libraryChanged();
};
