
#ifndef _MATRIX_LIBRARY_
#define _MATRIX_LIBRARY_

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
	bool isOperator (const std::string & chaine);
	std::vector<std::string> decoupe (const std::string & expression);
	Matrix calculate (const std::string & op, const std::string & a, const std::string & b);
	bool priorite_sup_egal (const std::string & opd,const std::string & opg);
	void polonaise(const std::string & chaine, std::vector<std::string> & notation_polonaise);
	Matrix expressionCalcul(const std::string & chaine);
};


#endif
