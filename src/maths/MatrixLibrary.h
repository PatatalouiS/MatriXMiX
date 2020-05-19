
#ifndef MATRIX_LIBRARY
#define MATRIX_LIBRARY

#include "Matrix.h"
#include <map>
#include <complex>

/**
 * @class The MatrixLibrary class
 */
class MatrixLibrary
{
    private:

    std::map<std::string, std::pair<Matrix,std::complex<double>>> tab;

    public:
/**
 * @brief Default constructor
 */
    MatrixLibrary ();

/**
 * @brief Copy constructor
 * @param [in] lib (\e MatrixLibrary)
 */
    MatrixLibrary (const MatrixLibrary & lib);

/**
 * @brief Default destructor
 */
    ~MatrixLibrary ();

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
    bool exist (const std::string& name) const;

/**
 * @brief Print all the matrices of the library
 */
    void print () const;

/**
 * @brief Returns if the chain can be accepted as name
 * @return \e bool
 */
    bool isName(const std::string & chain) const;


/**
 * @brief Add a matrix to the library
 * @param [in] name (\e string)
 * @param [in] m (\e Matrix)
 */
    void addMatrix (const std::string& name, const Matrix& m);

/**
 * @brief Find a matrix in the library using its name
 * @param [in] name (\e string)
 * @return \e Matrix*
 */
    const Matrix* find_matrix (const std::string& name) const;

/**
 * @brief Find a matrix in the library using its name
 * @param [in] name (\e string)
 * @return \e Matrix*
 */
    Matrix* find_matrix (const std::string& name);


    /**
     * @brief Find a matrix determiant in the library using its name
     * @param [in] name (\e string)
     * @return \e std::complex<double>*
     */
        const std::complex<double>* find_determinant (const std::string& name) const;

    /**
     * @brief Find the matrix determinant in the library using its name
     * @param [in] name (\e string)
     * @return \e std::complex<double>*
     */
        std::complex<double>* find_determinant (const std::string& name);

/**
 * @brief Erase a matrix from the library
 * @param [in] name (\e string)
 */
    void erase (const std:: string & name);

/**
 * @brief Return the map of matrices
 * @return \e std::map<std::string, Matrix>
 */
    const std::map<std::string, std::pair<Matrix,std::complex<double>>> & data () const;

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
