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

   QFont font ("Arial Bold");
   font.setWeight(QFont::Bold);
   fontTitle.setPointSize(16);

   introduction = new QGroupBox(tr("Introduction"));
   introduction->setFont(font);
   introduction -> setStyleSheet(
               "QGroupBox { border: 1px solid silver;"
               "background-color:white;"
               "margin-top: 32px;"
               "border-radius:6px;}"
               "QGroupBox::title { subcontrol-origin:margin;"
               "subcontrol-position:top left;"
               "font-weight: 75; color: #283676;}");

   QLabel* def = new QLabel("MatriXMiX est une application destinée aux matimaticiens "
                            "pour faciliter le calcul matriciel. ");
   QLabel* def2 = new QLabel("MatriXMiX permet de faire des opérations binaires,unaires et des "
                             "opérations liés à la diagonalisation.");
   def->setMaximumWidth(650);
   QVBoxLayout* subLayout = new QVBoxLayout;
   subLayout->addWidget(def);
   subLayout->addWidget(def2);
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
