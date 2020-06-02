
#ifndef MATRIX_LIBRARY
#define MATRIX_LIBRARY

#include "Matrix.h"
#include <map>
#include <complex>

/**
 * @brief Matrix library where the matrices are stored, linked with their names
 */
class MatrixLibrary
{

private:

    std::map<std::string, Matrix> tab;  /*< tree, where matrices are linked with their names*/


public:
    /**
     * @brief Default constructor
     */
    MatrixLibrary ();

    /**
     * @brief Copy constructor
     * @param[in] lib (\e MatrixLibrary)
     */
    MatrixLibrary (const MatrixLibrary & lib);

    /**
     * @brief Default destructor
     */
    ~MatrixLibrary ();

    /**
     * @brief Returns the size of the library
     * @return \e unsigned \e int \e long
     */
    unsigned int long size () const;

    /**
     * @brief Returns true if the library is empty
     * @return \e bool
     */
    bool isEmpty () const;

    /**
     * @brief Clears the library
     */
    void clear ();

    /**
     * @brief Returns the existance of a matrix in the library
     * @param[in] name (\e std::string)
     * @return \e bool
     */
    bool exist (const std::string& name) const;

    /**
     * @brief Print all the matrices of the library
     */
    void print () const;

    /**
     * @brief Returns if a std::string can be accepted as name
     * @param[in] \e std::string
     * @return \e bool
     */
    bool isName(const std::string & str) const;


    /**
     * @brief Add a matrix to the library
     * @param[in] name (\e std::string)
     * @param[in] m (\e Matrix)
     */
    void addMatrix (const std::string& name, const Matrix& m);

    /**
     * @brief Find the matrix in the library using its name
     * @param[in] name (\e std::string)
     * @return \e Matrix*
     */
    const Matrix* find (const std::string& name) const;

    /**
     * @brief Find a matrix in the library using its name
     * @param[in] name (\e std::string)
     * @return \e Matrix*
     */
    Matrix* find (const std::string& name);

    /**
     * @brief Erase a matrix from the library
     * @param[in] name (\e std::string)
     */
    void erase (const std::string & name);

    /**
     * @brief Return the map of matrices
     * @return \e std::map<std::string, Matrix>&
     */
    const std::map<std::string,Matrix>& data () const;



private:

    /**
     * @brief Copy a vector of std::string in another
     * @param[out] expression (\e std::vector<std::string>)
     * @param[in] resultat (\e std::vector<std::string>)
     */
    void copyVector(std::vector<std::string>& expression,
                     const std::vector<std::string>&resultat)const;

    /**
     * @brief Returns true if the parameter is a float
     * @param[in] chain (\e std::string)
     * @return \e bool
     */
    bool isFloat(const std::string & chain) const;

    /**
     * @brief Returns true if the parameter is an operator
     * @param[in] chain (\e std::string)
     * @return \e bool
     */
    bool isOperator (const std::string & chain) const;

    /**
     * @brief Test if the caracthere is tolerated in function calculateExpression
     * @details Returns true if the caractere is not tolerated
     * @param[in] chain (\e std::string)
     * @return \e bool
     */
    bool isSpecialCaractere(const std::string & chain) const;

    /**
     * @brief Separates matrices and operators
     * @param[in] expression (\e std::string)
     * @return \e std::vector<std::string>
     */
    std::vector<std::string> explode (const std::string & expression)const;

    /**
     * @brief Returns true if both operators have equal priority or one of them have a higher priority than the other
     * @param[in] opr (\e std::string) : right operator
     * @param[in] opl (\e std::string) : left operator
     * @return \e bool
     */
    bool highEqualPriority (const std::string & opr,
                              const std::string & opl) const;

    /**
     * @brief Returns the result of binary operation between two matrices
     * @param[in] op (\e std::string) : operator
     * @param[in] a (\e std::string) : first matrix name
     * @param[in} b (\e std::string) : second matrix name
     * @return \e Matrix
     */
    Matrix calculate (const std::string & op, const std::string & a,
                      const std::string & b) const;

    /**
     * @brief Returns the results of a binary operation of doubles
     * @param[in] op (\e std::string) : operator
     * @param[in] a (\e std::string) : first double
     * @param[in] b (\e std::string) : second double
     * @return \e double
     */
    double calculateFloat (const std::string & op, const std::string & a,
                           const std::string & b)const;

    /**
     * @brief Returns the results of a binary operation between a matrix and a float
     * @param[in] op (\e std::string) : operator
     * @param[in] a (\e std::string) : matrix name
     * @param[in] b (\e std::string) : double
     * @return \e Matrix
     */
    Matrix calculateMatrixFloat (const std::string & op, const std::string & a,
                                 const double & b)const;

    /**
     * @brief Returns the results of a binary operation between a matrix and a float
     * @param[in] op (\e std::string) : operator
     * @param[in] a (\e std::string) : first matrix name
     * @param[in] b (\e std::string) : second matrix name
     * @return \e Matrix
     */
    Matrix calculateFloatMatrix (const std::string & op, const std::string & a,
                                 const float & b)const;

    /**
     * @brief Write a std::string in a Polish notation
     * @param[in] chain (\e std::string)
     * @param[out] polish_notation (\e std::vector<std::string>)
     */
    void polish(const std::string & chain, std::vector<std::string> & polish_notation)const;



public:

    /**
     * @brief Tests if the expression is computable
     * @details Returns "computable" if the expression is computable, otherwise returns a std::string to guide the user
     * @param[in] expression (\e std::string)
     * @return \e std::string
     */
    std::string isCalculableExpression(const std::string & expression)const;

    /**
     * @brief Evaluates the result of a matrix expression
     * @param[in] chain (\e std::string)
     * @return \e Matrix
     */
    Matrix calculateExpression(const std::string & chain) const;


    /**
     * @brief Saves the matrix library in \e mtmx format
     */
    void saveFile (const std::string & filename)const;

    /**
     * @brief Reads a mtmx file to load the matrix library
     * @details The std::string contains the path of the file
     * @param[in] filename (\e std::string)
     */
    void readFile (const std::string & filename);

    /**
     * @brief Regression test
     */
    void regressionTest() const;
};


#endif
