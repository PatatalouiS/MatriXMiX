/*
 __  __       _        ___  ____  __ ___  __
|  \/  | __ _| |_ _ __(_) \/ /  \/  (_) \/ /
| |\/| |/ _` | __| '__| |\  /| |\/| | |\  /
| |  | | (_| | |_| |  | |/  \| |  | | |/  \
|_|  |_|\__,_|\__|_|  |_/_/\_\_|  |_|_/_/\_\

Copyright (C) 2019-2020, Sebia Hana, Cerbulean Ana-Maria, Boumaza Tarik, Olivié Maxime.

This file is part of MatriXMiX.

MatriXMiX is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

MatriXMiX is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with MatriXMiX.  If not, see <https://www.gnu.org/licenses/>

*/

#include "MatrixLibrary.h"
#include <stack>
#include <iostream>
#include <fstream>
#include <cassert>



MatrixLibrary:: MatrixLibrary () : tab (std::map<std::string,Matrix>())
{
}


MatrixLibrary::  MatrixLibrary (const MatrixLibrary & lib)
{
    for (auto it = lib.tab.begin(); it != lib.tab.end(); it++ )
    {
        addMatrix(it->first,it->second);
    }
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
    return (size() == 0);
}


void MatrixLibrary:: clear ()
{
    tab.clear();
}


bool MatrixLibrary:: exist (const std::string& name) const
{
    return (tab.count(name) != 0);
}


void MatrixLibrary:: print () const
{
    for(const auto& Mat: tab)
    {
        std::cout << "Matrice " << Mat.first << " : ";
        std::cout << std::endl << std::endl << Mat.second << std::endl;;
    }
    std::cout << std::endl;
}


bool MatrixLibrary:: isName(const std::string & chain) const
{
    unsigned long int i = 1, s = chain.length();

    if ( !( ((chain[0] >= 'A') && (chain[0] <= 'Z'))
            || ((chain[0] >= 'a') && (chain[0] <= 'z')) ) )
        return false;

    while (i<s)
    {
        if ( ((chain[i] >= 'A') && (chain[i] <= 'Z'))
             || ((chain[i] >= 'a') && (chain[i] <= 'z'))
             || ((chain[i] >= '0') && (chain[i] <= '9')))
            i++;
        else return false;
    }

    return true;
}



void MatrixLibrary:: addMatrix (const std::string& name, const Matrix & m)
{
    if (isName(name))
        tab.insert({name,m});
    else std::cout <<"Nom de matrice non autorisé, veuillez choisir un autre..."
            <<std::endl;
}


const Matrix* MatrixLibrary:: find (const std::string& name) const
{
    if(tab.count(name) == 0)
    {
        return nullptr;
    }
    return &(tab.at(name));
}


Matrix* MatrixLibrary:: find (const std::string& name)
{
    if(tab.count(name) == 0)
    {
        return nullptr;
    }
    return &(tab.at(name));
}


void MatrixLibrary:: erase (const std::string & name)
{
    tab.erase(name);
    if(exist(name))
    {
        std::cout << "Suppression non effectuée" << std::endl;
    }
}


const std::map<std::string,Matrix>& MatrixLibrary:: data () const
{
    return tab;
}


void MatrixLibrary::copyVector(std::vector<std::string>& expression,
                                const std::vector<std::string>& result)const
{
    for (auto i :result)
    {
        expression.push_back(i);
    }

}


bool MatrixLibrary:: isFloat(const std::string & chain) const
{
    unsigned long int i = 0, s = chain.length();
    unsigned short int nbcoma = 0;

    while (i<s)
    {
        if (chain[i]=='.')
            nbcoma++;
        else if (! ((chain[i]>='0') && (chain[i]<='9')) )
            return false ;

        if (nbcoma > 1)
            return false;

        i++;
    }

    return true;
}


bool MatrixLibrary:: isOperator (const std::string & chain) const
{
    return ( (chain == "+")
             ||  (chain == "-")
             ||  (chain == "/")
             || (chain == "^")
             || (chain == "~")
             || (chain == "*"));
}


bool MatrixLibrary:: isSpecialCaractere(const std::string & chain) const
{
    if (!isName(chain) && !isFloat(chain) &&
            !isOperator(chain))
        return true;
    return false;
}


std::vector<std::string> MatrixLibrary:: explode (const std::string & expression)const
{
    std::vector<std::string> tab;
    std::string c, temp;
    temp="";

    for (auto i : expression)
    {
        c=i;

        if((isOperator(c)) || (c == ")") || (c == "(") || (c == "=") )
        {
            if (temp.length()!=0)
                tab.push_back(temp);
            tab.push_back(c);
            temp.clear();
        }
        else if (!c.empty())
        {
            temp+=c;
        }

    }
    if(temp != "")
    tab.push_back(temp);

    return tab;
}


bool MatrixLibrary:: highEqualPriority (const std::string & opd,
                                          const std::string & opg) const
{
    switch (opd[0])
    {
        case '*':
            return ((opg[0] == '*') || (opg[0] == '/') || (opg[0] == '^')
                || (opg[0] == '~'));

        case '/':
            return ((opg[0] == '*') || (opg[0] == '/') || (opg[0] == '^')
                || (opg[0] == '~'));

        case '+':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*')
                || (opg[0] == '/') || (opg[0] == '^') || (opg[0] == '~'));

        case '-':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*')
                || (opg[0] == '/') || (opg[0] == '^') || (opg[0] == '~'));

        case '^':
            return ((opg[0] == '^') || (opg[0] == '~'));

        case '~':
            return ((opg[0] == '^') || (opg[0] == '~'));

        default: return false;
    }
}


Matrix MatrixLibrary:: calculate (const std::string & op, const std::string & a,
                                  const std::string & b) const
{
    const Matrix* m_a;
    const Matrix* m_b;

    m_a = find(a);
    m_b = find(b);

    if(op == "+")
        return *m_a + *m_b;

    if(op == "-")
        return *m_a - *m_b;

    if(op == "*")
        return *m_a * *m_b;

    if(op == "/")
        return *m_a / *m_b;

    else return *m_a;
}


double MatrixLibrary:: calculateFloat (const std::string & op,
                                       const std::string & a,
                                       const std::string & b) const
{
    if(op == "+")
        return atof(a.c_str()) + atof(b.c_str());

    if(op == "-")
        return atof(a.c_str()) - atof(b.c_str());

    if(op == "*")
        return atof(a.c_str()) * atof(b.c_str());

    if((op == "/") && (atof(b.c_str())!=0.0))
        return atof(a.c_str()) / atof(b.c_str());

    else return 0.0;
}


Matrix MatrixLibrary:: calculateMatrixFloat (const std::string & op,
                                             const std::string & a,
                                             const double & b) const
{
    const Matrix* m_a;
    m_a=find(a);

    Matrix identite(m_a->getNbRows(),m_a->getNbCols(),Matrix::I);
    Matrix bmatrix;
    bmatrix=static_cast<double>(b)*identite;



    if(op == "+")
        return *m_a + bmatrix ;

    if(op == "-")
        return *m_a - bmatrix;

    if(op == "/")
    {
        double scale;
        scale = static_cast<double>(1/b);
        return *m_a * scale;
    }

    else return *m_a;
}


Matrix MatrixLibrary:: calculateFloatMatrix(const std::string &op, const std::string &a,
                                            const float &b)const
{
    const Matrix* m_a;
    m_a = find(a);

    Matrix identite(m_a->getNbRows(),m_a->getNbCols(),Matrix::I);
    Matrix bmatrix;
    bmatrix = static_cast<double>(b)*identite;

    if(op == "+")
        return *m_a + bmatrix ;

    if(op == "-")
        return bmatrix - *m_a;

    else return *m_a;
}


void MatrixLibrary:: polish(const std::string & chain ,
                            std::vector<std::string> & polish_notation)const
{

    std::stack<std::string> p;
    std::vector<std::string> expression;
    copyVector(expression,explode(chain));

    for (auto i : expression)
    {
        if ( (!isOperator(i)) && (i != "(") && (i != ")") && (i != "=") )
        {
            polish_notation.push_back(i);
        }
        else if ( (i == "("))
        {
            p.push(i);

        }
        else if (isOperator(i))
        {
            if (!p.empty())
            {
                while ((!p.empty()) && highEqualPriority(i,p.top()))
                {
                    polish_notation.push_back(p.top());
                    p.pop();
                }
            }

            p.push(i);


        }
        else if (i == ")")
        {
           do
            {
                if (p.top() != "(")
                {
                    polish_notation.push_back(p.top());
                    p.pop();
                }

            }while ((p.top() !=  "(") && (!p.empty()));

            if (p.top() != "")
                p.pop();
        }

    }
    if(polish_notation[polish_notation.size()-1]=="")
        polish_notation.pop_back();


    while (!p.empty())
    {
        polish_notation.push_back(p.top());
        p.pop();
    }

}


std::string MatrixLibrary:: isCalculableExpression(const std::string & expression)const
{
   std::vector<std::string> result = explode(expression);
   unsigned long int i, s = result.size();

   std::string calculable = "calculable";

   if (s == 0)
       return "Expression vide";
   if (s == 1)
   {
       if (isName(result[0]))
       {
           if (find(result[0]) != nullptr)
               return calculable;
           else
               return ("La matrice " + result[0] + " n'existe pas dans la librairie");
       }
       else
           return ("Aucune matrice dans l'expression saisie");
   }

   short int nbp = 0;

   for (i = 0; i < s; i++)
   {
       if (result[i] == "(")
       {
           nbp++;
       }
       else if (result[i] == ")")
       {
           nbp--;
           if (nbp < 0)
           return "Parenthèse fermante détectée..."
                  "\nVeuillez vérifier l'organisation des parenthèses" ;
       }
   }

   if (nbp != 0)
       return "Nombre de parenthèses ouvrantes différent du nombre de parenthèses fermantes" ;

   std::vector<std::string> no_parenthesis;

   for (i = 0; i < s; i++)
   {
       if (result[i] != "(" && result[i] != ")")
       {
           no_parenthesis.push_back(result[i]);
       }

       else if (result[i] == "(")
       {

           if (i == s - 1)
                return ("Impossible de calculer une expression se terminant par '(' ");
            else if (result[i+1] == ")")
            {
                return ("Impossible de calculer '()'");
            }
       }

       else
       {
           if (result[i] == " ")
               return ("Les espaces ne sont pas autorisés");
           if (isSpecialCaractere(result[i]) && result[i] != ")")
               return ("Les caractères spéciaux ne sont pas autorisés comme '" + result[i]
                       + "' ne sont pas autorisés");
       }

   }

    s = no_parenthesis.size();

    std::string error1 = "Expression vide" ;

    if (s == 0)
        return error1;
    if (s == 1)
    {
        if (isName(no_parenthesis[0]))
        {
            if (find(no_parenthesis[0]) != nullptr)
                return calculable;
            else
                return ("La matrice " + no_parenthesis[i] + " n'existe pas dans la librairie");
        }
        else
            return ("Aucune matrice dans l'expression saisie");
    }

    std::string error3a = "Calcul de " ;
    std::string error3b = " impossible" ;
    bool matrix_result = false;

    for(i = 0; i < s; i++)
    {
        if (no_parenthesis[i] == "^")
        {
            if (i == 0)
                return ("Une expression ne peut pas débuter par '^' ");
            else if (!isName(no_parenthesis[i-1]) && no_parenthesis[i-1] != "~")
                return ("On ne peut calculer que les puissances de matrices");
            if (i < s - 1 && isName(no_parenthesis[i+1]) )
                return "On ne peut calculer que les puissances de matrices";
            else if (i == s - 1)
                return "L'opérateur '^' doit être suivi d'un entier";
        }

        else if (no_parenthesis[i] == "~")
        {
            if (i == 0)
                return ("L'expression ne peut pas commencer par '~'"
                        "\nVeuillez saisir 'M~' pour désigner l'inverse d'une matrice");
            else if (!isName(no_parenthesis[i-1]) && no_parenthesis[i-1] != "~")
                    return ("On ne peut calculer que l'inverse d'une matrice");
            if (i == s - 2)
                return ("Calcul de " + no_parenthesis[i-1] + no_parenthesis[i]
                        + no_parenthesis[i+1] + "impossible");
            if (i < s - 1)
                 if (!isOperator(no_parenthesis[i+1]))
                    if (no_parenthesis[i+1] != "^")
                        return "L'opérateur '~' doit être suivi d'un second opérateur";

        }

        else if (isOperator(no_parenthesis[i]))
        {
            if (i == 0)
                return ("L'expression ne peut pas débuter par un opérateur");
            if (i == s - 1)
                return ("Impossible de calculer " + no_parenthesis[i-1] + no_parenthesis[i]);
            if (isOperator(no_parenthesis[i-1]) && no_parenthesis[i-1] != "~")
                return ("Calcul de " + no_parenthesis[i] + no_parenthesis[i+1] + " impossible");
        }

        else if (isName(no_parenthesis[i]))
        {
            matrix_result = true;

            if (find(no_parenthesis[i]) == nullptr)
                return ("La matrice " + no_parenthesis[i] + " n'existe pas dans la librairie");

            if (i == 0)
                continue;
            if (i == 1)
                return (error3a + no_parenthesis[i-1] + no_parenthesis[i] + error3b);
            if (i < s - 1 && no_parenthesis[i+1] == "~")
                    {
                        if ((i < s - 2) && !isOperator(no_parenthesis[i+2]))
                            return "L'opérateur '~' doit être suivi d'un opérateur";
                    }

            if ( (i > 1) && (i < s - 2) )
            {
                if (!isOperator(no_parenthesis[i-1]))
                    return (error3a + no_parenthesis[i-1] + error3b);
                else if ( (!isName(no_parenthesis[i-2])) && (!isFloat(no_parenthesis[i-2])) )
                    return (error3a + no_parenthesis[i-2] + no_parenthesis[i-1]
                            + no_parenthesis[i] + error3b);
                if (no_parenthesis[i+1] == "^")
                {
                    if (!isFloat(no_parenthesis[i+2]))
                        return (error3a + no_parenthesis[i] + no_parenthesis[i+1]
                                + no_parenthesis[i+2] + error3b + "\n"
                                + no_parenthesis[i+2] + " doit être un entier");
                    if (atoi(no_parenthesis[i+2].c_str()) < 0)
                        return (error3a + no_parenthesis[i] + no_parenthesis[i+1]
                                + no_parenthesis[i+2] + error3b
                                + "\nVeuillez utiliser '~' pour désigner l'inverse d'une matrice");
                    if (atoi(no_parenthesis[i+2].c_str()) - atof(no_parenthesis[i+2].c_str()) != 0.0)
                        return (error3a + no_parenthesis[i]
                                + no_parenthesis[i+1] + no_parenthesis[i+2]
                                + error3b + "...\nCalcul d'une puissance réelle impossible");
                        }

                    }

                }

        else if (isFloat(no_parenthesis[i]))
        {
            if (i == 0)
                continue;
            if (i == 1)
                return (error3a + no_parenthesis[i-1] + no_parenthesis[i] + error3b);
            if (i == s - 2)
                return (error3a + no_parenthesis[i] + no_parenthesis[i+1] + error3b);
            if (!isOperator(no_parenthesis[i-1]))
            {
                if (no_parenthesis[i-1] != "^")
                    return (error3a + no_parenthesis[i-1] + no_parenthesis[i] + error3b);
                if (atof(no_parenthesis[i].c_str()) < 0.0)
                    return (error3a + no_parenthesis[i-2] + no_parenthesis[i-1]
                            + no_parenthesis[i] + error3b
                            + "\nVeuillez utiliser 'M~' pour désigner l'inverser d'une matrice M");
                if (atof(no_parenthesis[i].c_str())
                        - atoi(no_parenthesis[i].c_str()) != 0.0)
                    return ("Calcul d'une puissance réelle impossible"
                            "veuillez saisir un entier");
            }
            else if ( (i < s - 1) && isName(no_parenthesis[i+1]) )
                return "L'opération " + no_parenthesis[i] + no_parenthesis[i+1]
                        + " n'est pas définie" ;

        }

    }

    if (!matrix_result)
        return "Le résultat de sortie n'est pas une matrice!" ;

    return calculable;
}


Matrix MatrixLibrary:: calculateExpression(const std::string & chain)const
{

    MatrixLibrary copy(*this);
    std::vector<std::string> polish_not;
    copy.polish(chain,polish_not);      //I write my expression in Polish notation

    std::stack<std::string> pile;
    Matrix temp;
    std::string identify;
    int name=0;

    for (auto i : polish_not)
    {
        if (i == "~")
        {
            /* if the current element is a tilde, I calculate the inverse of the matrix*/

            std::string a = pile.top();
            pile.pop();

            temp= *(copy.find(a))^-1;

            identify = static_cast<char>('0'+ name);
            pile.push("temp" + identify);
            copy.addMatrix("temp" + identify,temp);
            name++;
        }
        else if ((copy.isOperator(i)) && (i != "~"))
        {
            /* In the case of binary operation, I extract both operands from the stack*/

            std::string b = pile.top();
            pile.pop();
            std::string a = pile.top();
            pile.pop();

            /* depending on the type of the two operands I calculate the result */

            if ((copy.isName(b) && copy.isName(a))
                    || (copy.isFloat(a) && copy.isName(b))
                    || (copy.isFloat(b) && copy.isName(a)) )
            {
                if ((copy.isName(b) && copy.isName(a)))
                {
                    temp = copy.calculate(i,a,b);
                }
                else if (copy.isFloat(b) && copy.isName(a))
                {
                    if(i == "*")
                    {
                        temp = *(copy.find(a)) * atof(b.c_str());
                    }
                    else if (i == "^")
                    {
                        temp= *(copy.find(a)) ^ (atoi(b.c_str()));
                    }
                    else
                    {
                        float scale;
                        scale = static_cast<float>(atof(b.c_str()));
                        temp =copy.calculateMatrixFloat(i,a,scale);
                    }
                }
                else if (copy.isFloat(a) && copy.isName(b))
                {
                    if(i == "*")
                    {
                        temp = *(copy.find(b)) * atof(a.c_str());

                    }
                    else
                    {
                        float scale;
                        scale = static_cast<float>(atof(a.c_str()));
                        temp = copy.calculateFloatMatrix(i,b,scale);
                    }
                }

                /* I store the resulting matrix in the library and its name in the stack */

                identify = static_cast<char>('0'+ name);
                pile.push ("temp" + identify);          // i choose different names for the saved matrices
                copy.addMatrix ("temp" + identify, temp);
                name++;
            }
            else if (  copy.isFloat(a) && copy.isFloat(b) )
            {
                /* if both operands are floats i calculate the result diffrently then i store it in the stack */
                std::ostringstream ss;
                ss << copy.calculateFloat (i,a,b);
                std::string res = ss.str();
                pile.push(res);
            }
            else
            {
                return Matrix::matrix_null;
            }
        }
        else
        {
            /* if the current element is not an operator, i store it in the stack  */
            pile.push(i);
        }
    }

    /* the stack contains the name of the resulting matrix */

    const Matrix* res;
    res = copy.find(pile.top());
    Matrix result(*res);

    for(int i = 0; i <= name - 1; i++)
    {
        identify = static_cast<char>('0'+ i);
        copy.erase("temp" + identify);                       // I empty the library from intermediate matrices
    }


    return result;
}



void MatrixLibrary:: saveFile (const std::string & filename) const
{
    std::ofstream file (filename.c_str());

    if(!file.is_open())
    {
        std::cout << "Erreur lors de la lecture du fichier "
                "\nVeuillez vérifier le chemin du fichier" << std::endl;
        exit(EXIT_FAILURE);
    }

    file << "Matrix" << std::endl;

    for (auto it = tab.begin(); it != tab.end(); it++ )
    {
       std::string matrixname = it->first;
       Matrix m(*find(matrixname));

       file << std::endl << matrixname << std::endl;
       file << m.getNbRows() << " " << m.getNbCols() << std::endl;

       for (unsigned int i = 0; i < m.getNbRows(); i++)
       {
           for (unsigned int j = 0; j < m.getNbCols(); j++)
           {

               file << m[i][j] << " ";
           }
           file << std::endl;
       }
    }

    file.close();
}


void MatrixLibrary:: readFile (const std::string & filename)
{
    std::string matrixname;
    unsigned int r,c;
    std::ifstream file (filename.c_str());

    clear();

    if(!file.is_open())
    {
        std::cerr << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << std::endl;
    }

    std::string testfile;
    file >> testfile ;

    if( testfile == "Matrix")
    {
        while(!file.eof())
        {
            file >> matrixname;
            file >> r >> c;

            Matrix m(r,c);

            for (unsigned int i = 0; i < r; i++)
            {
                for (unsigned int j = 0; j < c; j++)
                {
                    file >> m[i][j];
                }

            }
            addMatrix(matrixname,m);
        }

        file.close();

    }
    else
    {
        std::cerr << "Erreur, ce fichier ne contient pas des matrices !" << std::endl ;

    }
}



void MatrixLibrary:: regressionTest() const
{
     std::cout << std::endl << std::endl
                << "****** DEBUT DU TEST DE REGRESSION DE MATRIXLIBRARY ******"
                << std::endl << std::endl << std::endl;

    MatrixLibrary lib;

    Matrix identite(3,3,{1,0,0,0,1,0,0,0,1});
    Matrix a(3,3,{1,2,3,4,5,6,7,8,9});
    Matrix b(3,3,{1,2,3,2,4,5,3,5,1});

    std::string exp1("1+2*14");
    std::string exp2("identite~matrice1");
    std::string exp3("identite~2");
    std::string exp4("+14*marice1-");
    std::string exp5("matrice1++matrice2");
    std::string exp6("matrice2^~6");
    std::string exp7("identite=matrice1");
    std::string exp8("5~+matrice1");
    std::string exp9("matrice1+/matrice2");
    std::string exp10("matrice1*-identite");
    std::string exp11("matrice1*(-identite)");
    std::string exp12("6^2*matrice2");
    std::string exp13("matrice1^identite");
    std::string exp14("20/matrice1");

    std::string exp15("matrice1");
    std::string exp16("matrice1/matrice1");
    std::string exp17("matrice1/2");
    std::string exp18("identite~");
    std::string exp19("identite+5-3");
    std::string exp20("2*3*matrice");
    std::string exp21("matrice2~^2");
    std::string exp22("identite~*4");
    std::string exp23("2-matrice1");



    /* fonction IsName */

    assert(isName("identite"));
    assert(!isName("5identite"));
    assert(!isName("545"));
    assert(isName("Identite12"));
    assert(!isName("~Identite+"));

    /* fonctions size,isEmpty,exist,addMatrix,find,erase */

    assert(lib.size() == 0);
    assert(lib.isEmpty());

    lib.addMatrix("identite",identite);
    lib.addMatrix("matrice1",a);
    lib.addMatrix("matrice2",b);

    assert(!lib.isEmpty());
    assert(lib.exist("matrice1"));

    lib.erase("matrice2");

    assert(!lib.exist("matrice2"));
    assert(*lib.find("identite") == identite);
    assert(*lib.find("matrice1") == a);
    assert(lib.size() == 2);



    /* fonctions isCalculableExpression */


    /* fonctions calculateExpression */

    // the calculateExpression function is used to test several functions such as polish

    lib.addMatrix("matrice2",b);

    Matrix res;
    Matrix resultat1(3,3,{2,0,0,0,2,0,0,0,2});
    Matrix resultat2(3,3,{7,2,3,4,11,6,7,8,15});
    Matrix resultat3(3,3,{45360,55728,66096,102708,126198,
                          149688,160056,196668,233280});
    Matrix resultat4(3,3,{33,-13,2,-13,20,-1,2,-1,12});
    Matrix resultat5(3,3,{615,-379,55,-379,235,-34,55,-34,6});
    Matrix resultat6(3,3,0);
    Matrix resultat7(3,3,{5,0,0,0,5,0,0,0,5});


    res = lib.calculateExpression("identite+identite~");
    assert(res == resultat1);


    res = lib.calculateExpression("identite+identite~*5+matrice1");
    assert(res == resultat2);


    res = lib.calculateExpression("3*2*matrice1^4");
    assert(res == resultat3);


    res = lib.calculateExpression("matrice2~+6*2");
    assert(res == resultat4);


    res = lib.calculateExpression("1+(matrice2~)^2");
    assert(res == resultat5);


    res = lib.calculateExpression("2*matrice2*matrice2*(matrice2*matrice2)~-2");
    assert(res == resultat6);


    res = lib.calculateExpression("matrice1*2/2-1+1");
    assert(res == a);


    res = lib.calculateExpression("matrice2/matrice2");
    assert(res == identite);


    res = lib.calculateExpression("2+3*identite/identite~^3");
    assert(res == resultat7);


    res = lib.calculateExpression("identite~~");
    assert(res == identite);


    std::cout << "! Test isCalculable" << std::endl << std::endl;

    std::cout << "Expressions non calculable..." << std::endl << std::endl;
    std::cout << exp1 << "  :  " << isCalculableExpression(exp1) << std::endl;
    std::cout << exp2 << "  :  " << isCalculableExpression(exp2) << std::endl;
    std::cout << exp3 << "  :  " << isCalculableExpression(exp3) << std::endl;
    std::cout << exp4 << "  :  " << isCalculableExpression(exp4) << std::endl;
    std::cout << exp5 << "  :  " << isCalculableExpression(exp5) << std::endl;
    std::cout << exp6 << "  :  " << isCalculableExpression(exp6) << std::endl;
    std::cout << exp7 << "  :  " << isCalculableExpression(exp7) << std::endl;
    std::cout << exp8 << "  :  " << isCalculableExpression(exp8) << std::endl;
    std::cout << exp9 << "  :  " << isCalculableExpression(exp9) << std::endl;
    std::cout << exp10 << "  :  " << isCalculableExpression(exp10) << std::endl;
    std::cout << exp11 << "  :  " << isCalculableExpression(exp11) << std::endl;
    std::cout << exp12 << "  :  " << isCalculableExpression(exp12) << std::endl;
    std::cout << exp13 << "  :  " << isCalculableExpression(exp13) << std::endl << std::endl << std::endl;
    std::cout << "Expressions calculable" << std::endl << std::endl;
    std::cout << exp14 << "  :  " << isCalculableExpression(exp14) << std::endl;
    std::cout << exp15 << "  :  " << isCalculableExpression(exp15) << std::endl;
    std::cout << exp16 << "  :  " << isCalculableExpression(exp16) << std::endl;
    std::cout << exp17 << "  :  " << isCalculableExpression(exp17) << std::endl;
    std::cout << exp18 << "  :  " << isCalculableExpression(exp18) << std::endl;
    std::cout << exp19 << "  :  " << isCalculableExpression(exp19) << std::endl;
    std::cout << exp20 << "  :  " << isCalculableExpression(exp20) << std::endl;
    std::cout << exp21 << "  :  " << isCalculableExpression(exp21) << std::endl;
    std::cout << exp22 << "  :  " << isCalculableExpression(exp22) << std::endl;
    std::cout << exp23 << "  :  " << isCalculableExpression(exp23) << std::endl;

    std::cout << std::endl << std::endl << std::endl
                << "****** FIN DU TEST DE REGRESSION DE MATRIXLIBRARY******"
                << std::endl << std::endl ;
}
