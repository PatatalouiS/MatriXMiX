
#include "MatrixLibrary.h"
#include <stack>
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


void MatrixLibrary::copy_vector(std::vector<std::string>& expression,const std::vector<std::string>& resultat)
{
    unsigned int i;
    long int length = resultat.size();
    for (i=0; i<length; i++)
    {
        expression.push_back(resultat[i]);
    }

}


void MatrixLibrary:: addMatrix (const string& name, const Matrix& m)
{
    tab.insert({name, m});
}


const Matrix* MatrixLibrary:: find (const string& name) const
{
    if (tab.count(name) == 0)
    {
        cout<<"la matrice n'existe pas dans la libraire";
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
    const Matrix* m_a;
    const Matrix* m_b;

    m_a=find(a);
    m_b=find(b);

    if(op=="+")
        return *m_a+*m_b;

    if(op=="-")
        return *m_a-*m_b;

    if(op=="*")
        return *m_a * *m_b;

    if(op=="/")
        return *m_a / *m_b;

    else return *m_a;
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


void MatrixLibrary:: polonaise(const std::string & chaine , std::vector<std::string> & notation_polonaise)
{
    stack<string> p;
    vector<string> expression;
    copy_vector(expression,decoupe(chaine));

    int i;

    for (i = 0; i < expression.size(); i++)
    {
        if ( (!isOperator(expression[i])) && (expression[i] != "(") && (expression[i] != ")") && (expression[i] != "=") )
        {
            notation_polonaise.push_back(expression[i]);
        }
        else if ( (expression[i] == "(") || (expression[i] == "=") )
        {
            p.push(expression[i]);
        }
        else if (isOperator(expression[i]))
        {
            if (!p.empty())
            {
                while (priorite_sup_egal(expression[i],p.top()))
                {
                    notation_polonaise.push_back(p.top());
                    p.pop();
                }
            }

            p.push(expression[i]);

        }
        else if (expression[i] == ")")
        {
            do
            {
                notation_polonaise.push_back(p.top());
                p.pop();

            }while (p.top() !=  "(");
            p.pop();
        }
    }

    while (!p.empty())
    {
        notation_polonaise.push_back(p.top());
        p.pop();
    }
}

Matrix MatrixLibrary:: expressionCalcul(const std::string & chaine)
{
    vector<string> polish;
    polonaise(chaine,polish);
    stack<string> pile;
    Matrix temp;
    string identify;
    int nom=0;
    addMatrix("temp",temp);
    unsigned int i;
    long int taille=polish.size();

    for (i = 0; i < taille; i++ )
    {
        if (isOperator(polish[i]))
        {
            string b = pile.top();
            pile.pop();
            string a=pile.top();
            pile.pop();
            identify='0'+ nom;
            temp=calculate(polish[i],a,b);
            pile.push("temp" + identify);
            addMatrix("temp" + identify,temp);
            nom++;
        }
        else
        {
            pile.push(polish[i]);
        }
    }

    const Matrix* res;
    res=find(pile.top());
    return *res;
}


