
#include <QFileDialog>

#include "MenuBar.h"
#include "LibraryWindow.h"
#include "AbstractOperationWidget.h"

/**
@class MatriXMiXWindow The class MatriXMiXWindow generate the main page of the application
MatriXMiX. This window contains all the operation buttons grouped in QGroupBox,
the view of consulting operation and the view of result.
*/

class MatriXMiXWindow : public QWidget
{
    Q_OBJECT
    
    public:
        /**
        * @brief Default constructor
        */
        MatriXMiXWindow (QWidget* parent, const QMatrixLibrary* lib);

    public slots:

          void updateCurrentOperationWidget();
       
    private slots:
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
        const QMatrixLibrary* library;
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

    signals :

        void showLibraryWindow();
};
