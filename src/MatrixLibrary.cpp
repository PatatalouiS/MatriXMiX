
#include "MatrixLibrary.h"
#include <iostream>


using namespace std;


MatrixLibrary:: MatrixLibrary () : tab (map<string, Matrix>())
{
}


MatrixLibrary:: ~MatrixLibrary()
{
}


unsigned long int MatrixLibrary:: size () const
{
    return tab.size();
}


bool MatrixLibrary:: isEmpty () const
{
    return size() == 0;
}


bool MatrixLibrary:: exist (const string& name) const
{
    return (tab.count(name) != 0);
}


void MatrixLibrary:: print () const
{
    for(const auto& Mat: tab)
    { 
        cout << "Matrice " << Mat.first << " : ";
        cout << endl << endl << Mat.second << endl;;
    }
    cout << endl;
}


void MatrixLibrary:: addMatrix (const string& name, const Matrix& m)
{
    tab.insert({name, m});
}


const Matrix* MatrixLibrary:: find (const string& name) const
{
    if (tab.count(name) == 0)
    {
        return nullptr;
    }
    return &tab.at(name);
}


void MatrixLibrary:: erase (const string & name)
{
    if(tab.erase(name)!=1)
    {
        cout << "Suppression non effectuée" << endl;
    }
}


bool MatrixLibrary:: isOperator (const string & chaine)
{
    return ( (chaine == "+")
             ||  (chaine == "-")
             ||  (chaine == "/")
             || (chaine == "^")
             || (chaine == "*"));
}


vector<string> MatrixLibrary:: decoupe (const string & expression)
{
    unsigned int i;
    unsigned  long taille =expression.length();
    vector<string> tab;
    string c, temp;
    temp="";

    for (i=0; i<taille; i++)
    {
        c=expression[i];

        if((isOperator(c)) || (c == ")") || (c == "(") || (c == "=") )
        {
            if (temp.length()!=0) tab.push_back(temp);
            tab.push_back(c);
            temp="";
        }
        else if (!c.empty())
        {
            temp+=c;
        }

    }
    tab.push_back(temp);

    return tab;
}


Matrix MatrixLibrary:: calculate (const string & op, const string & a, const string & b)
{
    Matrix m_a;
    Matrix m_b;

    m_a=*(find(a));
    cout<<m_a;
    m_b=*(find(b));
    cout<<m_b;
    if(op=="+")
        return m_a+m_b;

    if(op=="-")
        return m_a-m_b;

    if(op=="*")
        return m_a*m_b;

    if(op=="/")
        return m_a/m_b;

}


bool MatrixLibrary:: priorite_sup_egal (const string & opd,const string & opg)
{
    switch (opd[0])
    {
        case '*':
            return ((opg[0] == '*') || (opg[0] == '/'));

        case '/':
            return ((opg[0] == '*') || (opg[0] == '/'));

        case '+':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*') || (opg[0] == '/'));

        case '-':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*') || (opg[0] == '/'));
        default: return false;
    }
}


