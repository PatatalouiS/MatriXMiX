
#ifndef MATRIX_LIBRARY
#define MATRIX_LIBRARY

#include "Matrix.h"
#include <map>


class MatrixLibrary
{
private:
	
	std::map<std::string, Matrix> tab;
	
public:
	
    MatrixLibrary ();
    MatrixLibrary (const MatrixLibrary & lib);
    ~MatrixLibrary ();
    
    unsigned int long size () const;
    bool isEmpty () const;
    void empty ();
	bool exist (const std::string& name) const;
    void print () const;

	void addMatrix (const std::string& name, const Matrix& m);
	const Matrix* find (const std::string& name) const;
    Matrix* find(const std::string& name);
	void erase (const std:: string & name);
	const std::map<std::string, Matrix>& data () const;


private:

    void copy_vector(std::vector<std::string> & expression, const std::vector<std::string> & result)const;

    bool isName(const std::string & chaine) const;
    bool isFloat(const std::string & chaine) const;
    bool isOperator(const std::string & chaine) const;
    bool isSpecialCaractere(const std::string & chaine) const;

    std::vector<std::string> decoupe (const std::string & expression)const;
    bool high_equal_priority (const std::string & opd,const std::string & opg) const;

    Matrix calculate (const std::string & op, const std::string & a, const std::string & b) const;
    double calculateFloat (const std::string & op, const std::string & a, const std::string & b)const;
    Matrix calculateMatrixFloat (const std::string & op, const std::string & a, const float & b)const;
    Matrix calculateFloatMatrix (const std::string & op, const std::string & a, const float & b)const;

    void polish(const std::string & chaine, std::vector<std::string> & polish_notation)const;

public:
    std::string isCalculableExpression(const std::string & expression)const;
    Matrix expressionCalcul(const std::string & chaine)const;

    void saveFile (const std::string filename)const;
    void readFile (const std::string filename);

    void testRegression();


};


#endif
