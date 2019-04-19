
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
    ~MatrixLibrary ();
    
    unsigned int long size () const;
    bool isEmpty () const;
	bool exist (const std::string& name) const;
    void print () const;
    void copy_vector(std::vector<std::string>& expression,const std::vector<std::string>&resultat);
	void addMatrix (const std::string& name, const Matrix& m);
	const Matrix* find (const std::string& name) const;
	void erase (const std:: string & name);
	const std::map<std::string, Matrix>& data () const;
    bool isName(const std::string & chaine) const;
    bool isFloat(const std::string & chaine) const;
    bool isOperator (const std::string & chaine) const;
    std::vector<std::string> decoupe (const std::string & expression) const;
    std::string isCalculableExpression(const std::string & expression) const;
	Matrix calculate (const std::string & op, const std::string & a, const std::string & b); 
	bool priorite_sup_egal (const std::string & opd,const std::string & opg);
	void polonaise(const std::string & chaine, std::vector<std::string> & notation_polonaise);
	Matrix expressionCalcul(const std::string & chaine);
    const std::string saveRights(const std::string & matrixname);
    void saveMatrix (const std::string & matrixname);
    void cleanSaves();
    Matrix readMatrix(const std::string & matrixname);

};


#endif
