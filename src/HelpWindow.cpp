#include "HelpWindow.h"

HelpWindow::HelpWindow(QWidget* parent) : QDialog(parent)
{
   QWidget* wind  = new QWidget;
   title = new QLabel("MatriXMiX Guide");

   QPixmap im(":/img/logo.png");
   im = im.scaled(100, 56);

   logo = new QLabel;
   logo->setPixmap(im);
   logo->setMaximumWidth(150);

   QFont fontTitle ("Arial");
   fontTitle.setPointSize(20);
   title->setFont(fontTitle);

   QHBoxLayout* headerLayout = new QHBoxLayout;
   headerLayout->addWidget(logo);
   headerLayout->addWidget(title);

   introduction = new QGroupBox(tr("Introduction"));

   QLabel* def = new QLabel("MatriXMiX est une application destinée aux matimaticiens"
                            "pour faciliter le calcul matriciel. MatriXMiX permet de faire"
                            "des actions binaires,unaires et des actions liés à la diagonalisation.");
   QVBoxLayout* subLayout = new QVBoxLayout;
   subLayout->addWidget(def);
   introduction->setLayout(subLayout);


   QVBoxLayout* mainLayout = new QVBoxLayout;
   mainLayout->addLayout(headerLayout);
   mainLayout->addWidget(introduction);

   wind->setLayout(mainLayout);
   wind->show();
}

HelpWindow::~HelpWindow()
{
}
