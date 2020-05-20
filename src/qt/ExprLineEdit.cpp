#include "ExprLineEdit.hpp"

mup::ParserX ExprLineEdit::parser = mup::ParserX();

ExprLineEdit::ExprLineEdit(QWidget* parent, const unsigned int width,
                           const unsigned int height) : QLineEdit(parent) {
    setMinimumWidth(width);
    setMaximumHeight(height);
    setMaxLength(MAX_LENGTH);
}

std::complex<double> ExprLineEdit::getComplex() const {
    parser.SetExpr(text().toStdString());
    return parser.Eval().GetComplex();
}

bool ExprLineEdit::isValidExpr() const {
    try {
        getComplex();
        return true;
    }
    catch(const mup::ParserError& err) {
        return false;
    }
}


