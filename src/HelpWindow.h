
#ifndef HELPWINDOW_H
#define HELPWINDOW_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>

/**
@class HelpWindow The class HelpWindow generate a new Window that must to
inform the user about the goal of the application MatriXMiX and about the
particularities of usage.
*/
class HelpWindow : public QDialog
{
    Q_OBJECT

private:
    QLabel* title;
    QLabel* logo;
    QGroupBox* introduction;
    QGroupBox* utilisation;
    QGroupBox* maths;

public:
    /**
     * @brief Default constructor
     * @param [in] parent (\e pointer of QWidget)
     */
    HelpWindow(QWidget* parent);
    /**
     * @brief Default destructor
     */
    ~HelpWindow();
};

#endif // HELPWIDGET_H
