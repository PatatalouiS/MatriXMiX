
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
    headerLayout->setAlignment(Qt::AlignHCenter);
    headerLayout->addWidget(logo);
    headerLayout->addWidget(instruction);
    headerWidget->setLayout(headerLayout);
    headerWidget->setMaximumHeight(300);
    headerWidget->setStyleSheet("QWidget {background-color: QColor(0,0,0,0)}");

    operationLayout->setContentsMargins(40, 40, 40, 40);
    operationLayout->QLayout::setSpacing(20);

    operationLayout->addWidget(initBinaryOp() , 0 , 0);
    operationLayout->addWidget(UnaryOp() , 0 ,1);
    operationLayout->addWidget(DiagonalisationOp() , 0 ,2);

    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addWidget(headerWidget);
    mainLayout->addLayout(operationLayout);
    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("QWidget {background-color : qlineargradient(x1 : 0 , y1 : 0  "
                              ", x2: 0 , y2:1 , "
                              "stop : 0 #fcf9f2 , stop : 1 #f7fcf2)}");
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

QGroupBox* MainWindow::initBinaryOp()
{
    QFont font ("Arial");
    font.setPointSize(16);

    QGroupBox *BinaryOpBox = new QGroupBox(tr("Opérations binaires (AxB)"));
    QVBoxLayout *BinaryOpVBox = new QVBoxLayout;

    BinaryOpBox->setStyleSheet("background-color:white");
    BinaryOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background-color:#eaf1ff;"
                "border-bottom-left-radius: 6px;"
                "border-bottom-right-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ;"
                "border-top-left-radius:6px;"
                "border-top-right-radius:6px;}");
    BinaryOpBox->setMinimumSize(300,350);

    BinaryOpBox->setFont(font);

    const QString tabBinaryOp [6] =
    {
        "Addition (A+B)",
        "Soustraction (A-B)",
        "Puissance (A^n)",
        "Multiplication (A*B)",
        "Multiplication (A*lambda)",
        "Division (A/B)"
    };

    QPushButton* BinaryOpButtons;

    for(unsigned int i = 0; i < 6; ++i)
    {
        BinaryOpButtons = new QPushButton(tabBinaryOp[i]);
        BinaryOpButtons->setCursor(Qt::PointingHandCursor);
        //Ajout du style pour les boutons
        BinaryOpButtons->setStyleSheet("QPushButton{ background-color: lightGrey } "
                                       "QPushButton:hover{ background-color: lightBlue }");
        BinaryOpButtons->setMinimumSize(200,40);
        BinaryOpButtons->setMaximumSize(600,80);

        connect(BinaryOpButtons, &QPushButton::clicked,
                [i, this] () -> void
                {
                    this->compute_choice(i);
                });
        operations.append(BinaryOpButtons);

        BinaryOpVBox -> addWidget(BinaryOpButtons);

    }

    BinaryOpBox->setLayout(BinaryOpVBox);

    return BinaryOpBox;
}

QGroupBox* MainWindow::UnaryOp()
{
    QGroupBox *UnaryOpBox = new QGroupBox(tr("Opérations unaires (A)"));
    QVBoxLayout *UnaryOpVBox = new QVBoxLayout;
    QFont font ("Arial");
    font.setPointSize(16);

    UnaryOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background-color:#eaf1ff;"
                "border-bottom-left-radius: 6px;"
                "border-bottom-right-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ;"
                "border-top-left-radius:6px;"
                "border-top-right-radius:6px;}");
    UnaryOpBox->setMinimumSize(300,350);

    UnaryOpBox->setFont(font);

    const QString tabUnaryOp [5] =
    {
        "Déterminant",
        "Inverse",
        "Trace",
        "Echelonnage",
        "Etudes des dimensions",
    };

    QPushButton* UnaryOpButtons;

    for(unsigned int i = 0; i < 5; ++i)
    {
        UnaryOpButtons = new QPushButton(tabUnaryOp[i]);
        UnaryOpButtons->setCursor(Qt::PointingHandCursor);
        //Ajout du style pour les boutons
        UnaryOpButtons->setStyleSheet("QPushButton{ background-color: lightGrey } "
                                      "QPushButton:hover{ background-color: lightBlue }");
        UnaryOpButtons->setMinimumSize(200,40);
        UnaryOpButtons->setMaximumSize(600,80);

        UnaryOpVBox -> addWidget(UnaryOpButtons);

    }
    UnaryOpBox->setLayout(UnaryOpVBox);

    return UnaryOpBox;
}

QGroupBox* MainWindow::DiagonalisationOp()
{
    QGroupBox *DiaOpBox = new QGroupBox(tr("Opérations pour la diagonalisation"));
    QVBoxLayout *DiaOpVBox = new QVBoxLayout;

    QFont font ("Arial");
    font.setPointSize(16);

    DiaOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background-color:#eaf1ff;"
                "border-bottom-left-radius: 6px;"
                "border-bottom-right-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ;"
                "border-top-left-radius:6px;"
                "border-top-right-radius:6px;"
                "}");
    DiaOpBox->setMinimumSize(300,350);
    DiaOpBox->setFont(font);

    const QString tabDiaOp [4] =
    {
        "Polynôme caractéristique",
        "Valeurs propres",
        "Vecteurs propres",
        "Diagonalisation"
    };

    QPushButton* DiaOpButtons;

    for(unsigned int i = 0; i < 4; ++i)
    {
        DiaOpButtons = new QPushButton(tabDiaOp[i]);
        DiaOpButtons->setCursor(Qt::PointingHandCursor);
        //Ajout du style pour les boutons
        DiaOpButtons->setStyleSheet("QPushButton{ background-color: lightGrey } "
                                    "QPushButton:hover{ background-color: lightBlue }");
        DiaOpButtons->setMinimumSize(200,40);
        DiaOpButtons->setMaximumSize(600,80);

        DiaOpVBox -> addWidget(DiaOpButtons);

    }
    DiaOpBox->setLayout(DiaOpVBox);

    return DiaOpBox;
}

MainWindow:: ~MainWindow()
{
}

