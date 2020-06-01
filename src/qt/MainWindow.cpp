#include "MainWindow.hpp"

#include <QStackedWidget>

MainWindow::MainWindow() : QMainWindow()
{
    //Aide pour le Debug
    Matrix a (3,3,
    {
        {1, 2}, 2, 0,
        4, {0, -3}, {0, 1},
        {0, -1}, 8, {2, 0}

                         });

    library.addMatrix("A", a);
    // Nouvelles matrices

    libraryWindow = new LibraryWindow(this, &library);
    matrixmixWindow = new MatriXMiXWindow(this, &library);

    menuBar = new MenuBar(this);
    setMenuBar(menuBar);
    QFont fontTitle ("Arial");
    fontTitle.setPointSize(20);
    QPixmap im(":/img/logo.png");
    im = im.scaled(330, 60);
    QLabel* logo = new QLabel;
    logo->setPixmap(im);
    logo->setMaximumWidth(330);

    QStackedWidget* windowSwitcher = new QStackedWidget(this);
    windowSwitcher->addWidget(matrixmixWindow);
    windowSwitcher->addWidget(libraryWindow);

    connect(menuBar, &MenuBar::openSaveTool,
            [this]() -> void
            {
                showFileTool(QFileDialog::AcceptSave);
            });
    connect(menuBar, &MenuBar::openLoadTool,
            [this]() -> void
            {
                showFileTool(QFileDialog::AcceptOpen);
            });

    connect(matrixmixWindow, &MatriXMiXWindow::showLibraryWindow,[=] () -> void {
                windowSwitcher->setCurrentWidget(libraryWindow);

            });

    connect(libraryWindow, &LibraryWindow::showMatrixmixWindow, [=] () -> void {
                windowSwitcher->setCurrentWidget(matrixmixWindow);
        });

    connect(libraryWindow, &LibraryWindow::libraryChanged,
                   matrixmixWindow, &MatriXMiXWindow::updateCurrentOperationWidget);

    setStyleSheet(".QMainWindow {border-image:url(:/img/background.png) 0 0 0 0 stretch stretch;}");

    setCentralWidget(windowSwitcher);
}


void MainWindow:: showFileTool(enum QFileDialog::AcceptMode type)
{
    QUrl savePath;
    menuBar->setEnabled(false);
    QFileDialog* fileTool = new QFileDialog(this, Qt::Dialog);
    fileTool->setDefaultSuffix("mtmx");
    fileTool->setNameFilter("*.mtmx");
    fileTool->setWindowModality(Qt::ApplicationModal);
    fileTool->setAcceptMode(QFileDialog::AcceptSave);
    fileTool->setAttribute(Qt::WA_DeleteOnClose);
    fileTool->setAcceptMode(type);

    connect(fileTool, &QFileDialog::accepted,
            [=]() -> void
            {
                computeLoadOrRead(fileTool, type);
            });

    connect(fileTool, &QFileDialog::rejected,
            [=]() -> void
            {
                fileTool->close();
                menuBar->setEnabled(true);
            });

    fileTool->open();
}

void MainWindow:: computeLoadOrRead (QFileDialog* fileTool, enum QFileDialog::AcceptMode type)
{
    QUrl selectedPath = fileTool->selectedUrls()[0];

    if(selectedPath.isValid())
    {
        if(type == QFileDialog::AcceptSave)
        {
            library.saveFile(selectedPath.path().toStdString());
        }
        else
        {
            library.readFile(selectedPath.path().toStdString());
            matrixmixWindow->updateCurrentOperationWidget();
        }
    }

    fileTool->close();
    menuBar->setEnabled(true);
}


