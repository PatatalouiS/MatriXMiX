
#include <QScrollBar>
#include <QScrollArea>

#include "MatriXMiXWindow.h"
#include "BinaryOpMatrixMatrixWidget.h"
#include "BinaryOpMatrixNumberWidget.h"
#include "UnaryOpWidget.h"
#include "DiagonalisationWidget.h"
#include "ExprEvalWidget.h"

MatriXMiXWindow:: MatriXMiXWindow(QWidget* parent, const QMatrixLibrary* lib) : QWidget(parent)
{
    library = lib;
    setFunctorTab();
    currentOpLayout = new QVBoxLayout;
    currentOpWidget = nullptr;

    QFont font ("Arial");
    font.setPointSize(16);

    QWidget* mainWidget = new QWidget(this);
    QWidget* headerWidget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* headerSubLayout = new QHBoxLayout;
    QVBoxLayout* headerLayout = new QVBoxLayout;
    QVBoxLayout* opChoiceLayout = new QVBoxLayout;
    QGroupBox* opBox = new QGroupBox(tr("Choisissez l'opération à effectuer : "));
    QGroupBox* opShowBox = new QGroupBox(tr("Vous avez choisi:"));

    QPixmap im(":/img/logo.png");
    im = im.scaled(330, 60);
    QLabel* logo = new QLabel;
    logo->setPixmap(im);
    logo->setMaximumWidth(330);

    QPushButton* libraryButton = new QPushButton("      Librairie", this);
    QPixmap imLibraryButton(":/img/library.png");
    im = im.scaled(30, 30);
    libraryButton->setIcon(imLibraryButton);
    libraryButton->setMinimumSize(100,30);
    libraryButton->setIconSize(QSize(25, 25));
    libraryButton->setCursor(Qt::PointingHandCursor);

    libraryButton->setStyleSheet("QPushButton {"
                                 "height: 50px;"
                                 "width : 100px;"
                                 "border-style: solid;"
                                 "border-radius : 3px;"
                                 "background-color:rgb(210, 210, 210);"

                                 "}"
                                 "QPushButton:pressed{ background-color : grey; }");
    libraryButton->setToolTip("Accéder à la librarie de matrices pour édition, "
                              "suppression...");

    connect(libraryButton, &QPushButton::clicked, this, [this]() -> void {
                emit showLibraryWindow();
            });


    headerSubLayout->addWidget(logo);
    headerSubLayout->setAlignment(Qt::AlignHCenter);

    headerWidget->setLayout(headerSubLayout);
    //headerWidget->setFixedWidth();  //340

    headerLayout->addWidget(headerWidget);
    headerLayout->setAlignment(Qt::AlignHCenter);

    opChoiceLayout->addWidget(initBinaryOp());
    opChoiceLayout->addWidget(initUnaryOp());
    opChoiceLayout->addWidget(initDiagonalisationOp());
    opBox -> setStyleSheet(
                "QGroupBox { border: 1px solid grey;"
                "background-color:white;"
                "margin-top: 32px;"
                "border-radius:3px;}"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ; color:white; }");
    opBox->setContentsMargins(10,10,10,10);
    opBox->setFont(font);
    opBox->setLayout(opChoiceLayout);
    opShowBox -> setStyleSheet(
                "QGroupBox { border: 1px solid grey;"
                "background-color: white;"
                "margin-top: 32px;"
                "border-radius:3px;}"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ;color:white; }");
    opShowBox->setFont(font);
    opShowBox->setLayout(currentOpLayout);
    currentOpLayout->setSizeConstraint(QLayout::SetMinimumSize);
    currentOpLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);

    imgResult = new ShowMatrixWidget;
    imgResult->setStyleSheet("background-color: white;");
    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(imgResult);
    scrollArea->setStyleSheet("background-color:white ; "
                              "border-radius: 3px;");
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
    scrollArea->resize(300,300);

    QGridLayout* subLayout = new QGridLayout;

    subLayout->addWidget(libraryButton, 0, 0);
    subLayout->addLayout(headerLayout, 0, 1);
    subLayout->addWidget(opBox, 1, 0, 2, 1);
    subLayout->addWidget(opShowBox, 1, 1);
    subLayout->addWidget(scrollArea, 2, 1);
    mainLayout->setContentsMargins(30, 10, 25, 30);
    mainLayout->addLayout(subLayout);
    mainWidget->setLayout(mainLayout);
    imgResult->show();

    setLayout(mainLayout);

    computeChoice(0);
}


void MatriXMiXWindow::setFunctorTab()
{
    createWindow[0] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::ADDITION, library);
    };
    createWindow[1] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::SOUSTRACTION, library);
    };
    createWindow[2] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::MULTIPLICATION, library);
    };
    createWindow[3] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::DIVISION, library);
    };
    createWindow[4] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixNumberWidget(BinaryOpMatrixNumberWidget::SCALAR_MULTIPLICATION, library);
    };
    createWindow[5] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixNumberWidget(BinaryOpMatrixNumberWidget::POWER, library);
    };
    createWindow[6] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::DETERMINANT, library);
    };
    createWindow[7] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::TRACE, library);
    };
    createWindow[8] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::INVERSE, library);
    };
    createWindow[9] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::ROW_REDUCED_FORM, library);
    };
    createWindow[10] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::KER_IMG_DIM, library);
    };
    createWindow[11] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::CARACTERISTIC_POLYNOMIAL, library);
    };
    createWindow[12] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::EIGEN_PROPERTIES, library);
    };
    createWindow[13] =
    [this] () -> AbstractOperationWidget*
    {
         return new DiagonalisationWidget(library);
    };
    createWindow[14] =
    [this] () -> AbstractOperationWidget*
    {
         return new ExprEvalWidget(library);
    };

}


void MatriXMiXWindow:: computeChoice (const unsigned int choice)
{
    imgResult->clear();
    if(currentOpWidget != nullptr)
    {
        currentOpLayout->removeWidget(currentOpWidget);
        currentOpWidget->deleteLater();
    }

    currentOpWidget = createWindow[choice]();
    currentOpLayout->addWidget(currentOpWidget);
    connect(currentOpWidget, &AbstractOperationWidget::newResult, this, &MatriXMiXWindow::transferResult);

//    if(libraryWindow != nullptr)
//    {
//        connect(libraryWindow, &LibraryWindow::libraryChanged,
//                currentOpWidget, &AbstractOperationWidget::updateViews);
//    }

    currentOpWidget->show();
    currentChoice = choice;
}


void MatriXMiXWindow:: transferResult (const QVariant& res)
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
}


QGroupBox* MatriXMiXWindow::initBinaryOp ()
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
                "font: bold ; color: black;}");
    BinaryOpBox->setMinimumSize(300,180);

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
        BinaryOpButtons->setStyleSheet("QPushButton{ background-color: lightGrey } "
                                       "QPushButton:hover{ background-color: lightBlue }");
        BinaryOpButtons->setMinimumSize(100,20);
        BinaryOpButtons->setMaximumSize(600,80);

        connect(BinaryOpButtons, &QPushButton::clicked,
                [i, this] () -> void
                {
                    this->computeChoice(i);
                });

        BinaryOpLayout -> addWidget(BinaryOpButtons);
    }

    BinaryOpBox->setLayout(BinaryOpLayout);

    return BinaryOpBox;
}

QGroupBox* MatriXMiXWindow::initUnaryOp ()
{
    QGroupBox *UnaryOpBox = new QGroupBox(tr("Opérations unaires (A)"));
    QVBoxLayout *UnaryOpVBox = new QVBoxLayout;
    QFont font ("Arial");
    font.setPointSize(13);

    UnaryOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background: qlineargradient(x1: 0, y1: 0, x2: 0, "
                "y2: 1, stop: 0 lightBlue, stop: 1 Blue);"
                "border-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ; color: black;}");
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
                    this->computeChoice(i);
                });

    }
    UnaryOpBox->setLayout(UnaryOpVBox);

    return UnaryOpBox;
}

QGroupBox* MatriXMiXWindow::initDiagonalisationOp()
{
    QGroupBox *DiaOpBox = new QGroupBox(tr("Opérations pour la diagonalisation"));
    QVBoxLayout *DiaOpVBox = new QVBoxLayout;

    QFont font ("Arial");
    font.setPointSize(13);

    DiaOpBox -> setStyleSheet(
                "QGroupBox { border: 1px solid silver;"
                "background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,"
                " stop: 0 lightBlue, stop: 1 Blue);"
                "border-radius: 6px;"
                "margin-top: 25px; }"
                "QGroupBox::title { subcontrol-origin:margin;"
                "subcontrol-position:top center;"
                "font: bold ; color:black;}");
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

        DiaOpVBox -> addWidget(DiaOpButtons);
          connect(DiaOpButtons, &QPushButton::clicked,
                [i, this] () -> void
                {
                    this->computeChoice(i);
                });
    }

    DiaOpBox->setLayout(DiaOpVBox);

    return DiaOpBox;
}

void MatriXMiXWindow::updateCurrentOperationWidget() {
    currentOpWidget->updateViews();
}

