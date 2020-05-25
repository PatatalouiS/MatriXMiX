
#ifndef MATRIX_LIBRARY
#define MATRIX_LIBRARY

#include "../maths/Matrix.h"
#include <QMap>
#include <complex>
#include <mpParser.h>
#include "UserMatrix.hpp"

/**
 * @class The MatrixLibrary class
 */

class QMatrixLibrary
{
    private:

    static mup::ParserX parser;

    QMap<QString, UserMatrix> tab;

    public:
/**
 * @brief Default constructor
 */
    QMatrixLibrary ();

/**
 * @brief Copy constructor
 * @param [in] lib (\e MatrixLibrary)
 */
   QMatrixLibrary (const QMatrixLibrary & lib);

/**
 * @brief Returns the size of the library
 * @return \e unsigned \e int
 */
    unsigned int long size () const;

/**
 * @brief Returns true if the library is empty
 * @return \e bool
 */
    bool isEmpty () const;

/**
 * @brief Clear the library
 */
    void clear ();

/**
 * @brief Returns the existance of a matrix in the library
 * @param [in] name (\e string)
 * @return \e bool
 */
    bool exist (const QString& name) const;

/**
 * @brief Returns if the chain can be accepted as name
 * @return \e bool
 */
    bool isName(const QString & chain) const;


/**
 * @brief Add a matrix to the library
 * @param [in] name (\e string)
 * @param [in] m (\e Matrix)
 */
    const Matrix& addMatrix (const QString& name, const UserInputs& m);


    void addMatrix(const QString& name, const Matrix& m);

/**
 * @brief Find a matrix in the library using its name
 * @param [in] name (\e string)
 * @return \e Matrix*
 */
    const Matrix* find_matrix (const QString& name) const;

/**
 * @brief Find a matrix in the library using its name
 * @param [in] name (\e string)
 * @return \e Matrix*
 */
    Matrix* find_matrix (const QString& name);

/**
 * @brief Find a matrix determiant in the library using its name
 * @param [in] name (\e string)
 * @return \e std::complex<double>*
 */
    const Value* find_determinant (const QString& name) const;

/**
 * @brief Find the matrix determinant in the library using its name
 * @param [in] name (\e string)
 * @return \e std::complex<double>*
 */
    Value* find_determinant (const QString& name);

    const UserInputs* find_inputs(const QString& name) const;

    UserInputs* find_inputs(const QString& name);

    const UserMatrix* find_all(const QString& name) const;

    UserMatrix* find_all(const QString& name);

/**
 * @brief Erase a matrix from the library
 * @param [in] name (\e string)
 */
    void erase (const QString & name);

/**
 * @brief Return the map of matrices
 * @return \e std::map<std::string, Matrix>
 */
    const QMap<QString, UserMatrix>& data () const;

    QMap<QString, UserMatrix>::const_key_value_iterator begin() const;

    QMap<QString, UserMatrix>::const_key_value_iterator end() const;


/**
 * @brief Saves the matrix library in \e mtmx format
 */
    void saveFile (const std::string & filename)const;

/**
 * @brief Reads a mtmx file to load the matrix library
 * @details The string contains the path of the file
 * @param [in] filename (\e string)
 */
    void readFile (const std::string & filename);

/**
 * @brief Regression test
 */
    void regressionTest() const;
};


#endif
