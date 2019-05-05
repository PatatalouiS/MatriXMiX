#ifndef HELPWINDOWQT_H
#define HELPWINDOWQT_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>

/**
@class HelpWindowQT The class HelpWindowQT generate a new Window that must to
inform the user about the extern library QT used to generate the
graphic interface.
*/
class HelpWindowQt : public QDialog
{
    Q_OBJECT

private:
    QLabel* title;
    QLabel* logo;
    QGroupBox* introduction;
    QGroupBox* documentation;

public:
    /**
     * @brief Default constructor
     * @param [in] parent (\e pointer of QWidget)
     */
    HelpWindowQt(QWidget* parent);
    /**
     * @brief Default destructor
     */
    ~HelpWindowQt();
};

#endif
