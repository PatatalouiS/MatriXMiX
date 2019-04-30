
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QDebug>
#include <QScrollBar>
#include "MainWindow.h"
#include "BinaryOpMatrixMatrixWidget.h"
#include "BinaryOpMatrixNumberWidget.h"
#include "UnaryOpWidget.h"
#include "DiagonalisationWidget.h"
#include "ExprEvalWidget.h"

MainWindow:: MainWindow() : QMainWindow()
{
   //Aide pour le Debug
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

    library.addMatrix("A", a);
    library.addMatrix("B", b);
    library.addMatrix("C", c);
    library.addMatrix("D", d);
    library.addMatrix("E", e);
  // Nouvelles matrices

    setFunctorTab();
    currentOpLayout = new QVBoxLayout;
    currentOpWidget = nullptr;
    libraryWindow = nullptr;

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
    QLabel* title = new QLabel(" MatriXMiX");
    title->setStyleSheet("font-size: 20px; font:bold; background-color: "
                         "QColor(0,0,0,0); border:0px;");
    title->setAlignment(Qt::AlignCenter);

    headerWidget->setStyleSheet("QWidget {background-color: qlineargradient"
                                "(x1 : 0 , y1 : 0 , x2: 0 , y2:1 , "
                                "stop : 0 white , stop : 1 lightBlue);"
                                "border: 2px solid silver;"
                                "border-radius: 6px;}");
    headerSubLayout->addWidget(logo);
    headerSubLayout->addWidget(title);
    headerSubLayout->setAlignment(Qt::AlignHCenter);

    headerWidget->setLayout(headerSubLayout);
    headerWidget->setFixedWidth(300);

    headerLayout->addWidget(headerWidget);
    headerLayout->setAlignment(Qt::AlignHCenter);

    opChoiceLayout->addWidget(initBinaryOp());
    opChoiceLayout->addWidget(initUnaryOp());
    opChoiceLayout->addWidget(initDiagonalisationOp());
    opBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
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
    opShowBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background-color:white;"
                "margin-top: 32px;"
                "border-radius:6px;}"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ;color:white; }");
    opShowBox->setFont(fontTitle);
    opShowBox->setLayout(currentOpLayout);
    currentOpLayout->setSizeConstraint(QLayout::SetMinimumSize);
    currentOpLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    imgResult = new ShowMatrixWidget;
    imgResult->setStyleSheet("background-color: white;");

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(imgResult);
    scrollArea->setStyleSheet("background-color:white ; border-radius:6px;");
    scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar:vertical "
               "{border: 1px solid #999999; background:white;"
               "width:15px; margin: 0px 0px 0px 0px;}"
               "QScrollBar::handle:vertical { background: qlineargradient"
               "(x1:0, y1:0, x2:1, y2:0,stop: 0 lightBlue, stop:1 Blue);"
               "border-radius:6px;}"
               "QScrollBar::add-line:vertical {height: 0px;}"
               "QScrollBar::sub-line:vertical {height: 0 px;}");
    scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar:horizontal "
               "{border: 1px solid #999999; background:white; height:15px;}"
               "QScrollBar::handle:horizontal {background: qlineargradient"
               "(x1:0, y1:0, x2:0, y2:1,stop: 0 lightBlue, stop:1 Blue);"
               "border-radius:6px;}"
               "QScrollBar::add-line:horizontal {height: 0px;}"
               "QScrollBar::sub-line:horizontal {height: 0 px;}");

    QGridLayout* subLayout = new QGridLayout;
    subLayout->addWidget(opBox, 0, 0, 2, 1);
    subLayout->addWidget(opShowBox, 0, 1);
    subLayout->addWidget(scrollArea, 1, 1);
    subLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    subLayout->setContentsMargins(0,0,20,0);

    mainLayout->setContentsMargins(0, 10, 0, 15);
    mainLayout->addLayout(headerLayout);
    mainLayout->addLayout(subLayout);
    mainWidget->setLayout(mainLayout);
    mainWidget->setStyleSheet("QWidget {background-color : qlineargradient(x1 : 0 , y1 : 0  "
                              ", x2: 0 , y2:1 , "
                              "stop : 0 #283676 , stop : 1 #000066)}");
    connect(menuBar, &MenuBar::openLibrary, this, &MainWindow::show_library);
    compute_choice(0);
    setCentralWidget(mainWidget);
}

void MainWindow::setFunctorTab()
{
    createWindow[0] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::ADDITION, &library);
    };
    createWindow[1] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::SOUSTRACTION, &library);
    };
    createWindow[2] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::MULTIPLICATION, &library);
    };
    createWindow[3] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::DIVISION, &library);
    };
    createWindow[4] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixNumberWidget(BinaryOpMatrixNumberWidget::SCALAR_MULTIPLICATION, &library);
    };
    createWindow[5] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixNumberWidget(BinaryOpMatrixNumberWidget::POWER, &library);
    };
    createWindow[6] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::DETERMINANT, &library);
    };
    createWindow[7] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::TRACE, &library);
    };
    createWindow[8] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::INVERSE, &library);
    };
    createWindow[9] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::ROW_REDUCED_FORM, &library);
    };
    createWindow[10] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::KER_IMG_DIM, &library);
    };
    createWindow[11] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::CARACTERISTIC_POLYNOMIAL, &library);
    };
    createWindow[12] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::EIGEN_PROPERTIES, &library);
    };
    createWindow[13] =
    [this] () -> AbstractOperationWidget*
    {
         return new DiagonalisationWidget(&library);
    };
    createWindow[14] =
    [this] () -> AbstractOperationWidget*
    {
         return new ExprEvalWidget(&library);
    };

}


void MainWindow:: compute_choice (const unsigned int choice)
{
    if(currentOpWidget != nullptr)
    {
        currentOpLayout->removeWidget(currentOpWidget);
        currentOpWidget->deleteLater();
    }

    currentOpWidget = createWindow[choice]();
    currentOpLayout->addWidget(currentOpWidget);
    connect(currentOpWidget, &AbstractOperationWidget::newResult, this, &MainWindow::transferResult);

    if(libraryWindow != nullptr)
    {
        connect(libraryWindow, &LibraryWindow::libraryChanged,
                currentOpWidget, &AbstractOperationWidget::updateViews);
    }

    currentOpWidget->show();
    imgResult->hide();
    currentChoice = choice;
}


void MainWindow:: transferResult (const QVariant& res)
{
    if(currentChoice <= 5 || currentChoice == 8 || currentChoice == 9 || currentChoice == 13 || currentChoice==14)
    {
        assert(res.canConvert<Matrix>());
        imgResult->computeImgMatrix(res.value<Matrix>());
    }
    else if(currentChoice == 6)
    {
        assert(res.canConvert<DoubleResult>());
        DoubleResult resD = res.value<DoubleResult>();
        imgResult->computeImgDet(resD.second, resD.first);
    }
    else if(currentChoice == 7)
    {
        assert(res.canConvert<DoubleResult>());
        DoubleResult resD = res.value<DoubleResult>();
        imgResult->computeImgTrace(resD.second, resD.first);
    }
    else if(currentChoice == 10)
    {
        assert(res.canConvert<KerImgDimResult>());
        KerImgDimResult resKI = res.value<KerImgDimResult>();
        imgResult->computeImgDimMatrix(resKI.second, resKI.first);
    }
    else if(currentChoice == 11)
    {
        assert(res.canConvert<PolynomialResult>());
        PolynomialResult resP = res.value<PolynomialResult>();
        imgResult->computeImgPolynomial(std::get<1>(resP), std::get<2>(resP), std::get<0>(resP));
    }
    else if(currentChoice == 12)
    {
        assert(res.canConvert<EigenResult>());
        EigenResult resE = res.value<EigenResult>();
        imgResult->computeImgEigen(resE.second, resE.first);
    }
    else
    {
        assert(false);
    }

    imgResult->show();
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
        "Multiplication (A*B)",
        "Division (A/B)",
        "Multiplication (A*lambda)",
        "Puissance (A^n)"
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
        "Trace",
        "Inverse",
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
        "Evaluation d'expression",

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

        //DiaOpBox->setToolTip("Matrice de Passage/Matrice Diagonale");

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


void MainWindow:: show_library()
{
    libraryWindow = new LibraryWindow(this, &library);
    connect(libraryWindow, &LibraryWindow::libraryChanged,
            currentOpWidget,&AbstractOperationWidget::updateViews);
    connect(libraryWindow, &LibraryWindow::destroyed, [this](){libraryWindow = nullptr;});
    libraryWindow->setAttribute(Qt::WA_DeleteOnClose);
    libraryWindow->show();
}


MainWindow:: ~MainWindow()
{
}

