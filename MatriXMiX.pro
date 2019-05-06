######################################################################
# Automatically generated by qmake (3.1) Wed Mar 6 22:16:58 2019
######################################################################

TEMPLATE = app
CONFIG += release

DESTDIR = ./bin
OBJECTS_DIR = ./obj/
MOC_DIR = ./moc
RCC_DIR = ./resources
TARGET = MatriXMiX
macx:ICON = data/icons/MatriXMiX.icns

include(ext/latex/jkqtmathtext.pri);
INCLUDEPATH += ext/Eigen/

DEFINES += QT_DEPRECATED_WARNINGS

# Input

HEADERS += src/maths/Matrix.h \
        src/maths/VectorX.h \
        src/maths/Polynomial.h \
        src/maths/Fraction.h \
        src/maths/Gauss.h \
        src/maths/MatrixLibrary.h \
        src/txt/MatriXMiXTXT.h \
        src/qt/MainWindow.h \
        src/qt/LibraryWindow.h \
        src/qt/ShowMatrixWidget.h \
        src/qt/Error.h \
        src/qt/MatrixViewWidget.h \
        src/qt/MenuBar.h \
        src/qt/AbstractOperationWidget.h \
        src/qt/BinaryOpMatrixMatrixWidget.h \
        src/qt/BinaryOpMatrixNumberWidget.h \
        src/qt/UnaryOpWidget.h \
        src/qt/DiagonalisationWidget.h \
        src/qt/ExprEvalWidget.h \
        src/qt/SetMatrixWidget.h \
        src/qt/HelpWindow.h \
        src/qt/HelpWindowQt.h


SOURCES += src/qt/main.cpp \
        src/maths/Matrix.cpp \
        src/maths/VectorX.cpp \
        src/maths/Polynomial.cpp \
        src/maths/Fraction.cpp \
        src/maths/Gauss.cpp \
        src/maths/MatrixLibrary.cpp \
        src/txt/MatriXMiXTXT.cpp \
        src/qt/MainWindow.cpp \
        src/qt/LibraryWindow.cpp \
        src/qt/MatrixViewWidget.cpp \
        src/qt/Error.cpp \
        src/qt/MenuBar.cpp \
        src/qt/AbstractOperationWidget.cpp \
        src/qt/BinaryOpMatrixMatrixWidget.cpp \
        src/qt/BinaryOpMatrixNumberWidget.cpp \
        src/qt/UnaryOpWidget.cpp \
        src/qt/DiagonalisationWidget.cpp \
        src/qt/ExprEvalWidget.cpp \
        src/qt/SetMatrixWidget.cpp \
        src/qt/ShowMatrixWidget.cpp \
        src/qt/HelpWindow.cpp \
        src/qt/HelpWindowQt.cpp

RESOURCES += \
    data/data.qrc



