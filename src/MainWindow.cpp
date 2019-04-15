
#include "MainWindow.h"
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QDebug>
#include <QApplication>
#include <QFileInfo>


MainWindow:: MainWindow() : QMainWindow()
{
    QWidget* mainWidget = new QWidget(this);
    QWidget* headerWidget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QVBoxLayout* headerLayout = new QVBoxLayout;
    QGridLayout* operationLayout = new QGridLayout;
    QFont font ("Arial");
    font.setPointSize(16);
	
	QPixmap im (QDir::currentPath() + "/data/Logo_maths.jpg");
    im = im.scaled(200, 100);
    QLabel* logo = new QLabel;
    logo->setPixmap(im);
    QLabel* instruction = new QLabel ("Choisissez l'opération à effectuer : ");
    
    headerLayout->setAlignment(Qt::AlignHCenter);
    headerLayout->addWidget(logo);
    headerLayout->addWidget(instruction);
    headerWidget->setLayout(headerLayout);
    headerWidget->setMaximumHeight(300);

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
        connect(tempWidget, &QPushButton::clicked,
                [i, this] () -> void
                {
                    this->compute_choice(i);
                });
        operations.append(tempWidget);
        operationLayout->addWidget(tempWidget, i/3, i%3);
    }
    
    //bouton temporaire :
    QPushButton* openLibrary = new QPushButton("Ouvrir la librairie");
    operationLayout->addWidget(openLibrary, 3, 2);
    operations.append(openLibrary);
    connect(openLibrary, &QPushButton::clicked, this, &MainWindow::show_library);
    // fin bouton temporaire
    
    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addWidget(headerWidget);
    mainLayout->addLayout(operationLayout);
    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
}


void MainWindow:: compute_choice (const unsigned int choice)
{
    createWindow[choice]();
}

void MainWindow:: show_library()
{
    LibraryWindow* libWindow = new LibraryWindow(this, &lib);
    libWindow->show();
    hide();
}


MainWindow:: ~MainWindow()
{
}

