
#include <QScrollBar>
#include <QScrollArea>

#include "MatriXMiXWindow.h"
#include "BinaryOpMatrixMatrixWidget.h"
#include "BinaryOpMatrixNumberWidget.h"
#include "UnaryOpWidget.h"
#include "DiagonalisationWidget.h"
#include "ExprEvalWidget.h"
#include "OpChoiceWidget.h"
#include "DecompositionWidget.h"

MatriXMiXWindow:: MatriXMiXWindow(QWidget* parent, const QMatrixLibrary* lib) : QWidget(parent)
{
    library = lib;
    setFunctorTab();
    currentOpLayout = new QVBoxLayout;
    currentOpWidget = nullptr;

    QFont font ("Arial");
    font.setPointSize(16);

    QWidget* mainWidget = new QWidget(this);
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QHBoxLayout* headerLayout = new QHBoxLayout;
    OpChoiceWidget* opChoice = new OpChoiceWidget(this);
    QWidget* currentOpWrapper = new QWidget(this);

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

    headerLayout->addWidget(logo);
    headerLayout->setAlignment(Qt::AlignHCenter);

    currentOpLayout->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    currentOpWrapper->setLayout(currentOpLayout);
    currentOpLayout->setContentsMargins(0,0,0,0);

    imgResult = new ShowMatrixWidget;
    imgResult->setStyleSheet("background-color: white;");

    QScrollArea* scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(imgResult);
    scrollArea->setStyleSheet(".QScrollArea{background-color:white ; "
                              "border-radius: 5px;"
                              "border : 1px solid grey}");
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
    subLayout->addWidget(opChoice, 1, 0, 2, 1);
    subLayout->addWidget(currentOpWrapper, 1, 1);
    subLayout->addWidget(scrollArea, 2, 1);

    mainLayout->setContentsMargins(18, 13, 18, 18);
    mainLayout->addLayout(subLayout);
    mainWidget->setLayout(mainLayout);

    connect(libraryButton, &QPushButton::clicked, this, [this]() -> void {
                emit showLibraryWindow();
            });

    connect(opChoice, &OpChoiceWidget::opSelected, this,
            &MatriXMiXWindow::computeChoice);

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
         return new UnaryOpWidget(UnaryOpWidget::TRANSPOSE, library);
    };
    createWindow[7] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::DETERMINANT, library);
    };
    createWindow[8] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::TRACE, library);
    };
    createWindow[9] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::INVERSE, library);
    };
    createWindow[10] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::ROW_REDUCED_FORM, library);
    };
    createWindow[11] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::KER_IMG_DIM, library);
    };
    createWindow[12] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::CARACTERISTIC_POLYNOMIAL, library);
    };
    createWindow[13] =
    [this] () -> AbstractOperationWidget*
    {
         return new UnaryOpWidget(UnaryOpWidget::EIGEN_PROPERTIES, library);
    };
    createWindow[14] =
    [this] () -> AbstractOperationWidget*
    {
         return new DiagonalisationWidget(DiagonalisationWidget::DIAGONALISATION_R, library);
    };
    createWindow[15] =
    [this] () -> AbstractOperationWidget*
    {
         return new DiagonalisationWidget(DiagonalisationWidget::DIAGONALISATION_C, library);
    };
    createWindow[16] =
    [this] () -> AbstractOperationWidget*
    {
         return new DecompositionWidget(DecompositionWidget::LU, library);
    };
    createWindow[17] =
    [this] () -> AbstractOperationWidget*
    {
         return new DecompositionWidget(DecompositionWidget::QR, library);
    };
    createWindow[18] =
    [this] () -> AbstractOperationWidget*
    {
         return new DecompositionWidget(DecompositionWidget::CHOLESKY, library);
    };
    createWindow[19] =
    [this] () -> AbstractOperationWidget*
    {
         return new ExprEvalWidget(library);
    };
    createWindow[20] =
    [this] () -> AbstractOperationWidget*
    {
         return new BinaryOpMatrixMatrixWidget(BinaryOpMatrixMatrixWidget::SOLVE, library);
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
    currentOpWidget->setStyleSheet("border : none;");
    currentOpLayout->addWidget(currentOpWidget);

    connect(currentOpWidget, &AbstractOperationWidget::newResult,
            this, &MatriXMiXWindow::transferResult);

    connect(currentOpWidget, &AbstractOperationWidget::libraryChanged,
                currentOpWidget, &AbstractOperationWidget::updateViews);

    currentOpWidget->show();
    currentChoice = choice;
}


void MatriXMiXWindow:: transferResult (const QVariant& res)
{
//    if(currentChoice <= 6 || currentChoice == 9
//            || currentChoice == 10 || currentChoice >= 14)
//    {
//        assert(res.canConvert<Matrix>());
//        imgResult->computeImgMatrix(res.value<Matrix>());
//    }
//    else if(currentChoice == 7)
//    {
//        assert(res.canConvert<DoubleResult>());
//        DoubleResult resD = res.value<DoubleResult>();
//        imgResult->computeImgDet(resD.second, resD.first);
//    }
//    else if(currentChoice == 8)
//    {
//        assert(res.canConvert<DoubleResult>());
//        DoubleResult resD = res.value<DoubleResult>();
//        imgResult->computeImgTrace(resD.second, resD.first);
//    }
//    else if(currentChoice == 11)
//    {
//        assert(res.canConvert<KerImgDimResult>());
//        KerImgDimResult resKI = res.value<KerImgDimResult>();
//        imgResult->computeImgDimMatrix(resKI.second, resKI.first);
//    }
//    else if(currentChoice == 12)
//    {
//        assert(res.canConvert<PolynomialResult>());
//        PolynomialResult resP = res.value<PolynomialResult>();
//        imgResult->computeImgPolynomial(std::get<1>(resP), std::get<2>(resP), std::get<0>(resP));
//    }
//    else if(currentChoice == 13)
//    {
//        assert(res.canConvert<EigenResult>());
//        EigenResult resE = res.value<EigenResult>();
//        imgResult->computeImgEigen(resE.second, resE.first);
//    }
//    else
//    {
//        assert(false);
//    }

    if(res.canConvert<Matrix>()) {
        imgResult->computeImgMatrix(res.value<Matrix>());
    }
    else if(res.canConvert<KerImgDimResult>()) {
        KerImgDimResult resKI = res.value<KerImgDimResult>();
        imgResult->computeImgDimMatrix(resKI.second, resKI.first);
    }
    else if(res.canConvert<PolynomialResult>()) {
        PolynomialResult resP = res.value<PolynomialResult>();
        imgResult->computeImgPolynomial(std::get<1>(resP), std::get<2>(resP), std::get<0>(resP));
    }
    else if(res.canConvert<EigenResult>()) {
        EigenResult resE = res.value<EigenResult>();
        imgResult->computeImgEigen(resE.second, resE.first);
    }
    else {
        DoubleResult resD = res.value<DoubleResult>();
        currentChoice == 7
                ? imgResult->computeImgDet(resD.second, resD.first)
                : imgResult->computeImgTrace(resD.second, resD.first);
    }
}

void MatriXMiXWindow::updateCurrentOperationWidget() {
    currentOpWidget->updateViews();
}

