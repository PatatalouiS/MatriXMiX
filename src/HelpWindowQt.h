#ifndef HELPWINDOWQT_H
#define HELPWINDOWQT_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>

class HelpWindowQt : public QDialog
{
    Q_OBJECT

private:
    QLabel* title;
    QLabel* logo;
    QGroupBox* introduction;
    QGroupBox* documentation;

public:
    HelpWindowQt(QWidget* parent);
    ~HelpWindowQt();
};

#endif // HELPWINDOWQT_H
