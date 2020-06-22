
############                          ##############
############ Project File - MatriXMiX ##############
############                          ##############

# Config QMAKE
TEMPLATE = app
CONFIG += release c++17

QT += svg

# names and dirnames
MAKEFILE= MakefileQt
DESTDIR = ./bin
OBJECTS_DIR = ./obj/
MOC_DIR = ./moc
RCC_DIR = ./resources
TARGET = MatriXMiX

# icon
macx:ICON = data/icons/MatriXMiX.icns

# sources for jkqtmathtext
include(ext/latex/jkqtmathtext.pri)

# external headers
INCLUDEPATH += ext/Eigen/ ext/muparserx/parser

# conditionals for link static libraries
unix:!macx {
    LIBS += -Lext/muparserx/lib/unix -lm -lmuparserx
}

macx: {
    LIBS += -Lext/muparserx/lib/macos -lm -lmuparserx
}

DEFINES += QT_DEPRECATED_WARNINGS

# Input

HEADERS += src/maths/Matrix.h \
        src/maths/Utils.hpp \
        src/maths/VectorX.h \
        src/maths/Polynomial.h \
        src/maths/Fraction.h \
        src/maths/Gauss.h \
        src/maths/MatrixLibrary.h \
        src/qt/DecompositionWidget.h \
        src/qt/ExprLineEdit.hpp \
        src/qt/LibraryWindow.h \
        src/qt/MainWindow.hpp \
        src/qt/MatriXMiXWindow.h \
        src/qt/OpChoiceWidget.h \
        src/qt/QMatrixLibrary.hpp \
        src/qt/ResultAdderWidget.h \
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
        src/qt/HelpWindowQt.h \
        src/qt/UserInputs.hpp \
        src/qt/UserMatrix.hpp


SOURCES += src/qt/main.cpp \
        src/maths/Matrix.cpp \
        src/maths/Utils.cpp \
        src/maths/VectorX.cpp \
        src/maths/Polynomial.cpp \
        src/maths/Fraction.cpp \
        src/maths/Gauss.cpp \
        src/maths/MatrixLibrary.cpp \
        src/qt/DecompositionWidget.cpp \
        src/qt/ExprLineEdit.cpp \
        src/qt/LibraryWindow.cpp \
        src/qt/MainWindow.cpp \
        src/qt/MatriXMiXWindow.cpp \
        src/qt/MatrixViewWidget.cpp \
        src/qt/Error.cpp \
        src/qt/MenuBar.cpp \
        src/qt/AbstractOperationWidget.cpp \
        src/qt/BinaryOpMatrixMatrixWidget.cpp \
        src/qt/BinaryOpMatrixNumberWidget.cpp \
        src/qt/OpChoiceWidget.cpp \
        src/qt/QMatrixLibrary.cpp \
        src/qt/ResultAdderWidget.cpp \
        src/qt/UnaryOpWidget.cpp \
        src/qt/DiagonalisationWidget.cpp \
        src/qt/ExprEvalWidget.cpp \
        src/qt/SetMatrixWidget.cpp \
        src/qt/ShowMatrixWidget.cpp \
        src/qt/HelpWindow.cpp \
        src/qt/HelpWindowQt.cpp \
        src/qt/UserInputs.cpp \
        src/qt/UserMatrix.cpp

RESOURCES += \
    data/data.qrc

DISTFILES += \
    data/icons/MatriXMiX.png
