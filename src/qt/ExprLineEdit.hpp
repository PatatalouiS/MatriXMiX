#ifndef EXPRLINEEDIT_HPP
#define EXPRLINEEDIT_HPP

#include <QLineEdit>
#include <complex>
#include <mpParser.h>

class ExprLineEdit : public QLineEdit {

    Q_OBJECT

    private :

        static constexpr unsigned int DEFAULT_WIDTH = 30;
        static constexpr unsigned int DEFAULT_HEIGHT = 70;
        static constexpr unsigned int MAX_LENGTH = 50;

        static mup::ParserX parser;

    public:

        ExprLineEdit(QWidget* parent = nullptr, const unsigned int width = DEFAULT_WIDTH,
                 const unsigned int height = DEFAULT_HEIGHT);

        std::complex<double> getComplex() const;

        bool isValidExpr() const;
};

#endif // EXPRLINEEDIT_HPP
