#ifndef HELPWINDOW_H
#define HELPWINDOW_H
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

class HelpWindow : public QDialog
{
    Q_OBJECT

private:
    QLabel* title;

public: HelpWindow(QWidget* parent);
        ~HelpWindow();
};

#endif // HELPWIDGET_H
