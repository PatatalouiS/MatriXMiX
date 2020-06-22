#ifndef EXPRLINEEDIT_HPP
#define EXPRLINEEDIT_HPP

#include <QLineEdit>
#include <complex>
#include <mpParser.h>

/**
 * @class The ExprLineEdit class This clas is an implementation of a Matrix text entry
 *      a math parser is included to parse simple math exprsessions to a Complex.
 */

class ExprLineEdit : public QLineEdit {

    Q_OBJECT

    private :

        static constexpr unsigned int DEFAULT_WIDTH = 30;
        static constexpr unsigned int DEFAULT_HEIGHT = 70;
        static constexpr unsigned int MAX_LENGTH = 50;

        static mup::ParserX parser;

    public:

        /**
         * @brief ExprLineEdit the default constructor
         * @param parent the parent of this widget
         * @param width the width of the text entry
         * @param height the height of the text entry
         */
        ExprLineEdit(QWidget* parent = nullptr, const unsigned int width = DEFAULT_WIDTH,
                 const unsigned int height = DEFAULT_HEIGHT);

        /**
         * @brief getComplex return the complex put by the user in text entry (use a math parser)
         * @return the parsed complex<double>
         */
        std::complex<double> getComplex() const;

        /**
         * @brief isValidExpr test if the current user entry is a valid mathematical expression
         * @return true if valid, else false.
         */
        bool isValidExpr() const;
};

#endif // EXPRLINEEDIT_HPP
