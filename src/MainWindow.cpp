
#include "MainWindow.h"
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QFileInfo>
#include "BinaryOpWindow.h"


MainWindow:: MainWindow() : QMainWindow()
{
    QWidget* mainWidget = new QWidget(this);
    QWidget* headerWidget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QVBoxLayout* headerLayout = new QVBoxLayout;
    QGridLayout* operationLayout = new QGridLayout;

    QFont font ("Arial");
    font.setPointSize(16);

    menu = new MenuBar(this);
    setMenuBar(menu);
    menu -> setFont(font);

    QFont fontTitle ("Arial");
    fontTitle.setPointSize(20);
	
	QPixmap im (QDir::currentPath() + "/data/Logo_maths.jpg");
    im = im.scaled(200, 100);
    QLabel* logo = new QLabel;
    logo->setPixmap(im);
    QLabel* instruction = new QLabel ("Choisissez l'opération à effectuer : ");
    instruction -> setFont(fontTitle);
    instruction -> setStyleSheet("QLabel {color:white}");
    
    headerLayout->setAlignment(Qt::AlignHCenter);
    headerLayout->addWidget(logo);
    headerLayout->addWidget(instruction);
    headerWidget->setLayout(headerLayout);
    headerWidget->setMaximumHeight(300);
    headerWidget->setStyleSheet("QWidget {background-color: QColor(0,0,0,0)}");

    const QString tab [9] =
    {
        "Addition (A+B)",
        "Soustraction (A-B)",
        "Puissance (A^n)",
        "Multiplication (A*B)",
        "Multiplication (A*lambda)",
        "Division (A/B)",
        "Determinant",
        "Inverse",
        "Trace",
    };

    QPushButton* tempWidget;
    operationLayout->setContentsMargins(40, 40, 40, 40);
    operationLayout->QLayout::setSpacing(20);
    
    for(unsigned int i = 0; i < 9; ++i)
    {
        tempWidget = new QPushButton(tab[i]);
        tempWidget->setMinimumSize(200, 100);
        tempWidget->setMaximumSize(400 ,175);
        tempWidget->setCursor(Qt::PointingHandCursor);
        tempWidget->setFont(font);
        //Ajout du style pour les boutons
        tempWidget->setStyleSheet("QPushButton{ background-color: lightGrey } QPushButton:hover{ background-color: lightBlue }");
        connect(tempWidget, &QPushButton::clicked,
                [i, this] () -> void
                {
                    this->compute_choice(i);
                });
        operations.append(tempWidget);
        operationLayout->addWidget(tempWidget, i/3, i%3);
    }
    
    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addWidget(headerWidget);
    mainLayout->addLayout(operationLayout);
    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("QWidget {background-color : qlineargradient(x1 : 0 , y1 : 0  , x2: 0 , y2:1 , "
                              "stop : 0 #000033 , stop : 1 #0099FF)}");
    setFunctorTab();
    setCentralWidget(mainWidget);
}


void MainWindow::setFunctorTab()
{
    createWindow[0] =
    [this] () -> QWidget*
    {
         auto validator = [] (const Matrix* a, const Matrix* b) -> bool
         {
            return((a->getNbCols() == b->getNbCols()) && (a->getNbRows() == b->getNbRows()));
         };

         return new BinaryOpWindow(&lib, "Addition", "+", validator, this);
    };
}

void MainWindow:: compute_choice (const unsigned int choice)
{
    QWidget* newWindow = createWindow[choice]();
    newWindow->setAttribute(Qt::WA_DeleteOnClose);
    newWindow->show();
}

MainWindow:: ~MainWindow()
{
}

