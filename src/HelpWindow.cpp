#include "HelpWindow.h"

HelpWindow::HelpWindow(QWidget* parent) : QDialog(parent)
{
   QWidget* wind  = new QWidget;
   title = new QLabel("Pade d'aide");

   QVBoxLayout* mainLayout = new QVBoxLayout;
   mainLayout->addWidget(title);

   wind->setLayout(mainLayout);
   wind->show();
}

HelpWindow::~HelpWindow()
{
}
