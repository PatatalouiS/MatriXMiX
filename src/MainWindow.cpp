
#include "MainWindow.h"
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDir>
#include <QDebug>

#include "AdditionWindow.h"
#include "SoustractionWindow.h"
#include "MultiplicationWindow.h"
#include "DivisionWindow.h"
#include "PowerWindow.h"
#include "ScalarMultiplicationWindow.h"

#include "DeterminantWindow.h"
#include "TraceWindow.h"
#include "RowReducedWindow.h"
#include "InverseWindow.h"
#include "KerImgDimWindow.h"
#include "PolynomialWindow.h"
#include "EigenWindow.h"

MainWindow:: MainWindow() : QMainWindow()
{
  // Aide pour le Debug
    Matrix a (3,3, Matrix::I);
    Matrix b (3,3, {1,1,1,1,1,1,1,1,1});
    Matrix c (3,4, {1,2,3,4,5,6,7,8,9,10,11,12});
    Matrix d (3,4, {1,1,1,1,0,0,0,0,0,0,0,0});
    Matrix e (10,10, {1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,
                      1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,
                      1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,
                      1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,
                      1,1,1,1,1,0,0,0,0,0,
                      0,0,0,0,0,1,1,1,1,1,});
    addNewMatrix("A", a);
    addNewMatrix("B", b);
    addNewMatrix("C", c);
    addNewMatrix("D", d);
    addNewMatrix("E", e);
  // Nouvelles matrices

    setFunctorTab();
    QWidget* mainWidget = new QWidget(this);
    QWidget* headerWidget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QVBoxLayout* headerLayout = new QVBoxLayout;
    QVBoxLayout* opChoiceLayout = new QVBoxLayout;
    QVBoxLayout* opShowLayout = new QVBoxLayout;
    QGroupBox* opBox = new QGroupBox(tr("Choisissez l'opération à effectuer : "));
    QGroupBox* opShowBox = new QGroupBox(tr("Vous avez choisi:"));

    QFont font ("Arial");
    font.setPointSize(16);

    menuBar = new MenuBar(this);
    setMenuBar(menuBar);
    menuBar -> setFont(font);

    QFont fontTitle ("Arial");
    fontTitle.setPointSize(20);
	
    QPixmap im (QDir::currentPath() + "/data/Logo_maths.jpg");
    im = im.scaled(200, 100);
    QLabel* logo = new QLabel;
    logo->setPixmap(im);
    headerLayout->setAlignment(Qt::AlignHCenter);
    headerLayout->addWidget(logo);
    headerWidget->setLayout(headerLayout);
    headerWidget->setMaximumHeight(300);
    headerWidget->setStyleSheet("QWidget {background-color: QColor(0,0,0,0)}");

    opChoiceLayout->setContentsMargins(40, 40, 40, 40);
    opChoiceLayout->QLayout::setSpacing(20);
    opChoiceLayout->addWidget(initBinaryOp());
    opChoiceLayout->addWidget(initUnaryOp());
    opChoiceLayout->addWidget(initDiagonalisationOp());
    opBox -> setStyleSheet(
                "QGroupBox { border: 3px solid silver;"
                "background-color:white;"
                "margin-top: 32px;"
                "margin-left:30px; margin-right:30px;"
                "border-radius:6px;}"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ; color:white; }");
    opBox->setContentsMargins(20,20,20,20);
    opBox->setFont(fontTitle);
    opBox->setLayout(opChoiceLayout);

    QWidget* choixWidget= createWindow[0](&lib, this);

    choixWidget->setStyleSheet("background-color:white;");
    opShowLayout->addWidget(choixWidget);
    opShowBox -> setStyleSheet(
                "QGroupBox { border: 3px solid silver;"
                "background-color:white;"
                "margin-top: 32px;"
                "margin-right:30px;"
                "border-radius:6px;}"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ;color:white; }");
    opShowBox->setContentsMargins(20,20,20,20);
    opShowBox->setFont(fontTitle);
    opShowBox->setLayout(opShowLayout);

    opShowLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    QHBoxLayout* subLayot = new QHBoxLayout;
    subLayot->addWidget(opBox);
    subLayot->addWidget(opShowBox);

    mainLayout->setContentsMargins(0, 25, 0, 0);
    mainLayout->addWidget(headerWidget);
    mainLayout->addLayout(subLayot);
    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("QWidget {background-color : qlineargradient(x1 : 0 , y1 : 0  "
                              ", x2: 0 , y2:1 , "
                              "stop : 0 #283676 , stop : 1 #000066)}");
    connect(menuBar, &MenuBar::openLibrary, this, &MainWindow::show_library);

    setCentralWidget(mainWidget);
}


void MainWindow::setFunctorTab()
{
    createWindow[0] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
         return new AdditionWindow(lib, parent);
    };
    createWindow[1] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
         return new SoustractionWindow(lib, parent);
    };
    createWindow[2] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
         return new PowerWindow(lib, parent);
    };
    createWindow[3] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
         return new MultiplicationWindow(lib, parent);
    };
    createWindow[4] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
         return new ScalarMultiplicationWindow(lib, parent);
    };
    createWindow[5] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new DivisionWindow(lib, parent);
    };
    createWindow[6] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new DeterminantWindow(lib, parent);
    };
    createWindow[7] =
    [] (MatrixLibrary*lib, QWidget* parent) -> QWidget*
    {
        return new TraceWindow(lib, parent);
    };
    createWindow[8] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new RowReducedWindow(lib, parent);
    };
    createWindow[9] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new InverseWindow(lib, parent);
    };
    createWindow[10] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new KerImgDimWindow(lib, parent);
    };
    createWindow[11] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new PolynomialWindow(lib, parent);
    };
    createWindow[12] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new EigenWindow(lib, parent);
    };
}


void MainWindow:: compute_choice (const unsigned int choice)
{
    QWidget* newWindow = createWindow[choice](&lib, nullptr);
    newWindow->setAttribute(Qt::WA_DeleteOnClose);
    newWindow->show();
}


QGroupBox* MainWindow::initBinaryOp()
{
    QFont font ("Arial");
    font.setPointSize(16);

    QGroupBox *BinaryOpBox = new QGroupBox(tr("Opérations binaires (AxB)"));
    QVBoxLayout *BinaryOpLayout = new QVBoxLayout;

    BinaryOpBox->setStyleSheet("background-color:white");
    BinaryOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 Blue);"
                "border-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ; }");
    BinaryOpBox->setMinimumSize(325,250);
    BinaryOpBox->setMaximumSize(425,250);

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
        BinaryOpButtons->setMinimumSize(100,20);
        BinaryOpButtons->setMaximumSize(600,80);

        connect(BinaryOpButtons, &QPushButton::clicked,
                [i, this] () -> void
                {
                    this->compute_choice(i);
                });

        BinaryOpLayout -> addWidget(BinaryOpButtons);

    }

    BinaryOpBox->setLayout(BinaryOpLayout);

    return BinaryOpBox;
}

QGroupBox* MainWindow::initUnaryOp()
{
    QGroupBox *UnaryOpBox = new QGroupBox(tr("Opérations unaires (A)"));
    QVBoxLayout *UnaryOpVBox = new QVBoxLayout;
    QFont font ("Arial");
    font.setPointSize(16);

    UnaryOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 Blue);"
                "border-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ; }");
    UnaryOpBox->setMinimumSize(325,250);
    UnaryOpBox->setMaximumSize(425,250);

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

    for(unsigned int i = 6; i < 11; ++i)
    {
        UnaryOpButtons = new QPushButton(tabUnaryOp[i-6]);
        UnaryOpButtons->setCursor(Qt::PointingHandCursor);
        UnaryOpButtons->setStyleSheet("QPushButton{ background-color: lightGrey } "
                                      "QPushButton:hover{ background-color: lightBlue }");
        UnaryOpButtons->setMinimumSize(100,20);
        UnaryOpButtons->setMaximumSize(600,80);

        UnaryOpVBox -> addWidget(UnaryOpButtons);

        connect(UnaryOpButtons, &QPushButton::clicked,
                [i, this] () -> void
                {
                    this->compute_choice(i);
                });

    }
    UnaryOpBox->setLayout(UnaryOpVBox);

    return UnaryOpBox;
}

QGroupBox* MainWindow::initDiagonalisationOp()
{
    QGroupBox *DiaOpBox = new QGroupBox(tr("Opérations pour la diagonalisation"));
    QVBoxLayout *DiaOpVBox = new QVBoxLayout;

    QFont font ("Arial");
    font.setPointSize(16);

    DiaOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 Blue);"
                "border-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ;"
                "}");
    DiaOpBox->setMinimumSize(325,250);
    DiaOpBox->setMaximumSize(425,250);
    DiaOpBox->setFont(font);

    const QString tabDiaOp [3] =
    {
        "Polynôme caractéristique",
        "Valeurs/Vecteurs propres",
        "Diagonalisation"
    };

    QPushButton* DiaOpButtons;

    for(unsigned int i = 11; i < 14; ++i)
    {
        DiaOpButtons = new QPushButton(tabDiaOp[i-11]);
        DiaOpButtons->setCursor(Qt::PointingHandCursor);
        DiaOpButtons->setStyleSheet("QPushButton{ background-color: lightGrey } "
                                    "QPushButton:hover{ background-color: lightBlue }");
        DiaOpButtons->setMinimumSize(100,20);
        DiaOpButtons->setMaximumSize(600,80);

        DiaOpVBox -> addWidget(DiaOpButtons);
          connect(DiaOpButtons, &QPushButton::clicked,
                [i, this] () -> void
                {
                    this->compute_choice(i);
                });

    }
    DiaOpBox->setLayout(DiaOpVBox);

    return DiaOpBox;
}

void MainWindow:: addNewMatrix(const QString name, const Matrix matrix)
{
    lib.addMatrix(name.toStdString(), matrix);
}


void MainWindow:: show_library()
{
    LibraryWindow* libWindow = new LibraryWindow(this, &lib);
    libWindow->setAttribute(Qt::WA_DeleteOnClose);
    libWindow->show();
    hide();
}


MainWindow:: ~MainWindow()
{
}

