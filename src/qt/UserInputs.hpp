#ifndef USERINPUTS_HPP
#define USERINPUTS_HPP

#include <QVector>
#include <QString>

class UserInputs {

    public :


    UserInputs(const unsigned int nRows = 0, const unsigned int nCols = 0 );

    unsigned int getRows() const;

    unsigned int getCols() const;

    QVector<QString>::const_iterator begin() const;

    QVector<QString>::const_iterator end() const;

    const QString& put(const QString& input);

    const QString& operator[] (const unsigned int ind) const;


    //private :


    unsigned int rows;

    unsigned int cols;

    QVector<QString> inputs;
};




#endif // USERINPUTS_HPP
