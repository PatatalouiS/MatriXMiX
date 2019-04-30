#ifndef HELPWINDOW_H
#define HELPWINDOW_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QGroupBox>

class HelpWindow : public QDialog
{
    Q_OBJECT

private:
    QLabel* title;
    QLabel* logo;
    QGroupBox* introduction;

public: HelpWindow(QWidget* parent);
        ~HelpWindow();
};

#endif // HELPWIDGET_H
