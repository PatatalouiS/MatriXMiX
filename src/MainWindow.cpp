
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


MainWindow:: MainWindow() : QMainWindow()
{
    QWidget* mainWidget = new QWidget(this);
    QWidget* headerWidget = new QWidget;
    QVBoxLayout* mainLayout = new QVBoxLayout;
    QVBoxLayout* headerLayout = new QVBoxLayout;
    QGridLayout* operationLayout = new QGridLayout;
    QFont font ("Arial");
    font.setPointSize(16);

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
    
    //Suppression du bouton temporaire

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

    //Ajout du menu et des actions pour ouvrir la librarie

    QString  menuStyle(
              "QMenuBar{"
              "background-color: lightBlue;"
              "}"
           );

    this->setStyleSheet(menuStyle);

    QMenu *menuFile = menuBar() -> addMenu("Fichier");
    menuBar() -> setFont(font);
    menuFile -> setFont(font);

    QAction *actionSave = new QAction("Sauvegarder" , this);
    menuFile -> addAction(actionSave);

    menuFile -> addSeparator();

    QAction *actionLoad = new QAction("Créer", this);
    menuFile -> addAction(actionLoad);

    QMenu *menuMatrix = menuBar() -> addMenu("Matrice");
    menuMatrix -> setFont(font);

    menuMatrix = menuMatrix -> addMenu(tr("Librarie"));

    QAction *createMatrix = new QAction("Ajouter" , this);
    menuMatrix -> addAction(createMatrix);
    menuMatrix ->setFont(font);

    menuMatrix -> addSeparator();

    connect(createMatrix, &QAction::triggered, this, &MainWindow::show_library);

    QAction *showMatrix = new QAction("Visualiser" , this);
    menuMatrix -> addAction(showMatrix);
    menuMatrix ->setFont(font);
    connect(showMatrix, &QAction::triggered, this, &MainWindow::show_library);

    QMenu *menuHelp = menuBar() -> addMenu("Aide");
    menuHelp -> setFont(font);

    QMenu *menuQuit = menuBar() -> addMenu("Quitter");
    menuQuit -> setFont(font);


    setFunctorTab();
    setCentralWidget(mainWidget);




    // Aide pour le Debug

    Matrix a (3,3, Matrix::I);
    Matrix b (3,3, {1,1,1,1,1,1,1,1,1});
    Matrix c (3,4, {1,2,3,4,5,6,7,8,9,10,11,12});
    Matrix d (3,4, {1,1,1,1,0,0,0,0,0,0,0,0});
    addNewMatrix("A", a);
    addNewMatrix("B", b);
    addNewMatrix("C", c);
    addNewMatrix("D", d);
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
         return new MultiplicationWindow(lib, parent);
    };
    createWindow[3] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
         return new DivisionWindow(lib, parent);
    };
    createWindow[4] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
         return new PowerWindow(lib, parent);
    };
    createWindow[5] =
    [] (MatrixLibrary* lib, QWidget* parent) -> QWidget*
    {
        return new ScalarMultiplicationWindow(lib, parent);
    };
    createWindow[6] =
    [] (MatrixLibrary*lib, QWidget* parent) -> QWidget*
    {
        return new DeterminantWindow(lib, parent);
    };
}

void MainWindow:: compute_choice (const unsigned int choice)
{
    QWidget* newWindow = createWindow[choice](&lib, this);
    newWindow->setAttribute(Qt::WA_DeleteOnClose);
    newWindow->show();
}

void MainWindow:: show_library()
{
    LibraryWindow* libWindow = new LibraryWindow(this, &lib);
    libWindow->setAttribute(Qt::WA_DeleteOnClose);
    libWindow->show();
    hide();
}


void MainWindow:: addNewMatrix(const QString name, const Matrix matrix)
{
    lib.addMatrix(name.toStdString(), matrix);
}


MainWindow:: ~MainWindow()
{
}

