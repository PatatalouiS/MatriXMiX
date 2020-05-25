
#include <QMainWindow>
#include <QFileDialog>

#include "MenuBar.h"
#include "LibraryWindow.h"
#include "AbstractOperationWidget.h"

/**
@class MainWindow The class MainWindow generate the main page of the application
MatriXMiX. This window contains all the operation buttons grouped in QGroupBox,
the view of consulting operation and the view of result.
*/


class MainWindow : public QMainWindow
{
    Q_OBJECT
    
    public:
        /**
        * @brief Default constructor
        */
        MainWindow ();
        /**
        * @brief Default destructor
        */
        ~MainWindow ();
       
    private slots:
          /**
          *@brief Show the library window and all the updates generated for MainWindow
          */
          void showLibraryWindow ();
          /**
          * @brief Show the load and save tool
          * @param [in] type (\e enum \e QFileDialog::AcceptMode)
          */
          void showFileTool (enum QFileDialog::AcceptMode type);
          /**
          * @brief Verify if the result of the operation have a good format
          * @param [in] res (\e QVariant)
          */
          void transferResult (const QVariant& res);
          /**
          * @brief Show the selected operation in a widget
          * @param [in] choice ( \e unsigned \e int)
          */
          void computeChoice (const unsigned int choice);

    private:

        // members
    
        MenuBar* menuBar;
        QMatrixLibrary library;
        LibraryWindow* libraryWindow;
        AbstractOperationWidget* currentOpWidget;
        QVBoxLayout* currentOpLayout;
        unsigned int currentChoice;
        ShowMatrixWidget* imgResult;
        std::function<AbstractOperationWidget*(void)> createWindow [15];

        // functions
        /**
        * @brief Fill the table of createWindow with the good function
        */
        void setFunctorTab ();
        /**
        * @brief Initialize the GroupBox of binary operation buttons
        * @return QGroupBox*
        */
        QGroupBox* initBinaryOp();
        /**
        * @brief Initialize the GroupBox of unary operation buttons
        * @return QGroupBox*
        */
        QGroupBox* initUnaryOp();
        /**
        * @brief Initialize the GroupBox of operation buttons for the diagonalisation
        * @return QGroupBox*
        */
        QGroupBox* initDiagonalisationOp();
        /**
        * @brief Differentiate which tool is selected: save or load
        * @param [in] fileTool ( \e QFileDialog)
        * @param [in] type (\e enum \e QFileDialog::AcceptMode)
        */
        void computeLoadOrRead(QFileDialog* fileTool, enum QFileDialog::AcceptMode type);

    signals :
        /**
        * @brief libraryChanged this signal is emitted when a modification on the library happen
        */
        void libraryChanged();
};
