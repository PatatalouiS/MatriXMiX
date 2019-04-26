

#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
#include "MainWindow.h"

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
#include "DiagonalisationWindow.h"
#include "ExprEvalWindow.h"


MainWindow:: MainWindow() : QMainWindow()
{
  // Aide pour le Debug
    Matrix a (3,3, Matrix::I);
    Matrix b (3,3, {1,1,1,1,1,1,1,1,1});
    Matrix c (3,4, {1,2,3,4,5,6,7,8,9,10,11,12});
    Matrix d (3,4, {1,1,1,1,0,0,0,0,0,0,0,0});
    Matrix e (10,10, {15488,1545497,1679885,1654974,1524654,145464,1465464,12464,1264,14464,
              1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,
              1,1,1,1,1,1,1,1,1,1,});

    addNewMatrix("A", a);
    addNewMatrix("B", b);
    addNewMatrix("C", c);
    addNewMatrix("D", d);
    addNewMatrix("E", e);
  // Nouvelles matrices

    setFunctorTab();
    currentOpLayout = new QVBoxLayout;

    QWidget* mainWidget = new QWidget(this);
    QWidget* headerWidget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* headerSubLayout = new QHBoxLayout;
    QVBoxLayout* headerLayout = new QVBoxLayout;
    QVBoxLayout* opChoiceLayout = new QVBoxLayout;
    QGroupBox* opBox = new QGroupBox(tr("Choisissez l'opération à effectuer : "));
    QGroupBox* opShowBox = new QGroupBox(tr("Vous avez choisi:"));

    QFont font ("Arial");
    font.setPointSize(16);

    menuBar = new MenuBar(this);
    setMenuBar(menuBar);
    menuBar -> setFont(font);
    QFont fontTitle ("Arial");
    fontTitle.setPointSize(20);
    QPixmap im(":/img/logo.png");
    im = im.scaled(100, 56);
    QLabel* logo = new QLabel;
    logo->setPixmap(im);
    logo->setMaximumWidth(150);
    logo->setStyleSheet("background-color: QColor(0,0,0,0); border:0px;");
    QLabel* title = new QLabel("Bienvenue sur MatriXMiX!");
    title->setStyleSheet("font-size: 20px; font:bold; background-color: QColor(0,0,0,0);"
                         "border:0px;");
    title->setAlignment(Qt::AlignCenter);

    headerWidget->setStyleSheet("QWidget {background-color: qlineargradient(x1 : 0 , y1 : 0  "
                                ", x2: 0 , y2:1 , "
                                "stop : 0 white , stop : 1 lightBlue);"
                                "border: 2px solid silver;"
                                "border-radius: 6px;}");
    headerSubLayout->addWidget(logo);
    headerSubLayout->addWidget(title);
    headerSubLayout->setAlignment(Qt::AlignCenter);

    headerWidget->setLayout(headerSubLayout);
    headerWidget->setMaximumWidth(500);

    headerLayout->addWidget(headerWidget);
    headerLayout->setAlignment(Qt::AlignCenter);

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
    opBox->setContentsMargins(10,10,10,10);
    opBox->setFont(font);
    opBox->setLayout(opChoiceLayout);

    currentOpWidget = new AdditionWindow(&lib, this);
    currentOpWidget->setStyleSheet("background-color:white;");
    currentOpLayout->addWidget(currentOpWidget);
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
    opShowBox->setLayout(currentOpLayout);
    currentOpLayout->setSizeConstraint(QLayout::SetMinimumSize);
    currentOpLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    QVBoxLayout *subLayout2 = new QVBoxLayout;

    QWidget* showMatrixWidget = new QWidget;
    showMatrixWidget->setStyleSheet("QWidget {background-color: white; "
                                  "border: 2px solid silver;"
                                  "border-radius: 6px;}");
    showMatrixWidget->setLayout(subLayout2);
    showMatrixWidget->setContentsMargins(20,20,0,20);

    QVBoxLayout *subLayout3 = new QVBoxLayout;
    subLayout3->addWidget(opShowBox);
    subLayout3->addWidget(showMatrixWidget);

    QHBoxLayout* subLayot = new QHBoxLayout;
    subLayot->addWidget(opBox);
    subLayot->addLayout(subLayout3);

    mainLayout->setContentsMargins(0, 10, 10, 15);
    mainLayout->addLayout(headerLayout);
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
        return new InverseWindow(lib, parent);

    };
    createWindow[8] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new TraceWindow(lib, parent);
    };
    createWindow[9] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new RowReducedWindow(lib, parent);
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
    createWindow[13] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new DiagonalisationWindow(lib, parent);
    };
    createWindow[14] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new ExprEvalWindow(lib, parent);
    };
}


void MainWindow:: compute_choice (const unsigned int choice)
{
    currentOpLayout->removeWidget(currentOpWidget);
    currentOpWidget->deleteLater();
    currentOpWidget = createWindow[choice](&lib, this);
    currentOpWidget->setStyleSheet("background-color:white;");
    currentOpLayout->addWidget(currentOpWidget);
    currentOpWidget->show();
}


QGroupBox* MainWindow::initBinaryOp ()
{
    QFont font ("Arial");
    font.setPointSize(13);

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
                "font: bold ; color:black;}");
    BinaryOpBox->setMinimumSize(300,200);

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

QGroupBox* MainWindow::initUnaryOp ()
{
    QGroupBox *UnaryOpBox = new QGroupBox(tr("Opérations unaires (A)"));
    QVBoxLayout *UnaryOpVBox = new QVBoxLayout;
    QFont font ("Arial");
    font.setPointSize(13);

    UnaryOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 Blue);"
                "border-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ; color:back;}");
    UnaryOpBox->setMinimumSize(300,180);

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
    font.setPointSize(13);

    DiaOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 lightBlue, stop: 1 Blue);"
                "border-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ; color:black;"
                "}");
    DiaOpBox->setMinimumSize(300,130);
    DiaOpBox->setFont(font);

    const QString tabDiaOp [4] =
    {
        "Polynôme caractéristique",
        "Valeurs/Vecteurs propres",
        "Diagonalisation",
        "Evaluation d'expression"
    };

    QPushButton* DiaOpButtons;

    for(unsigned int i = 11; i < 15; ++i)
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

