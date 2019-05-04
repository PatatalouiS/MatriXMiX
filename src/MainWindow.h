
#include <QMainWindow>
#include <QFileDialog>

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
          void showFileTool (enum QFileDialog::AcceptMode type);
          void transferResult (const QVariant& res);
          void computeChoice (const unsigned int choice);

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

        void computeLoadOrRead(QFileDialog* fileTool, enum QFileDialog::AcceptMode type);

    signals :

        void libraryChanged();
};
