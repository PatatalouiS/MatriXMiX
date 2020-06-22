#ifndef USERINPUTS_HPP
#define USERINPUTS_HPP

#include <QVector>
#include <QString>

/**
 * @brief The UserInputs class It's a Matrix Represantation of a user Input.
 */
class UserInputs {

    public :

        /**
         * @brief UserInputs the constructor
         * @param nRows the number of rows
         * @param nCols the number of cols
         */
        UserInputs(const unsigned int nRows = 0, const unsigned int nCols = 0 );

        /**
         * @brief getRows getter for the number of rows of the UserInputs
         * @return the number of rows
         */
        unsigned int getRows() const;

        /**
         * @brief getCols getter for the number of cols of the UserInputs
         * @return the number of cols
         */
        unsigned int getCols() const;

        /**
         * @brief begin allow range-based for by returning an iterator to the first user entry.
         * @return a const iterator
         */
        QVector<QString>::const_iterator begin() const;

        /**
         * @brief begin allow range-based for by returning an iterator to the first user entry.
         * @return a const iterator
         */
        QVector<QString>::const_iterator end() const;

        /**
         * @brief put add a new user input to the UserInputs instance
         * @param input the new input to add
         * @return a reference to the added input
         */
        const QString& put(const QString& input);

        /**
         * @brief operator [] operator[] implementation
         * @param ind the index to acess
         * @return the user input at given index
         */
        const QString& operator[] (const unsigned int ind) const;


    private :

        unsigned int rows;

        unsigned int cols;

        QVector<QString> inputs;
};




#endif // USERINPUTS_HPP
