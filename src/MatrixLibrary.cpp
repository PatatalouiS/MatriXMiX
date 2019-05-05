
#include "MatrixLibrary.h"
#include "Matrix.h"
#include <stack>
#include <iostream>
#include <fstream>
#include <cassert>
#include <QDebug>
using namespace std;

const string PATH = "../data/sauvegarde.txt";


MatrixLibrary:: MatrixLibrary () : tab (map<string, Matrix>())
{
}


MatrixLibrary:: ~MatrixLibrary()
{
}


MatrixLibrary::  MatrixLibrary (const MatrixLibrary & lib)
{
    for (auto it = lib.tab.begin(); it != lib.tab.end(); it++ )
    {
        addMatrix(it->first,it->second);
    }
}


unsigned long int MatrixLibrary:: size () const
{
    return tab.size();
}


bool MatrixLibrary:: isEmpty () const
{
    return size() == 0;
}


void MatrixLibrary:: clear ()
{
    tab.clear();
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
    if (isName(name))
        tab.insert({name, m});
    else cout<<"Nom de matrice non autorisé, veuillez choisir un autre..."<<endl;
}


const Matrix* MatrixLibrary:: find (const string& name) const
{
    if(tab.count(name) == 0)
    {
        return nullptr;
    }
    return &tab.at(name);
}


Matrix* MatrixLibrary:: find (const string& name)
{
    if(tab.count(name) == 0)
    {
        return nullptr;
    }
    return &tab.at(name);
}


void MatrixLibrary:: erase (const string & name)
{
    tab.erase(name);
    if(exist(name))
    {
        cout << "Suppression non effectuée" << endl;
    }
}


const std::map<std::string, Matrix>& MatrixLibrary:: data () const
{
    return tab;
}


void MatrixLibrary::copy_vector(std::vector<std::string>& expression,const std::vector<std::string>& result)const
{
    for (auto i :result)
    {
        expression.push_back(i);
    }

}


bool MatrixLibrary:: isName(const string & chain) const
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


bool MatrixLibrary:: isFloat(const string & chain) const
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


bool MatrixLibrary:: isOperator (const string & chain) const
{
    return ( (chain == "+")
             ||  (chain == "-")
             ||  (chain == "/")
             || (chain == "^")
             || (chain == "~")
             || (chain == "*"));
}


bool MatrixLibrary:: isSpecialCaractere(const std::string &chaine) const
{
    if (!isName(chaine) && !isFloat(chaine) &&
            !isOperator(chaine))
        return true;
    return false;
}


vector<string> MatrixLibrary:: explode (const string & expression)const
{
    vector<string> tab;
    string c, temp;
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


bool MatrixLibrary:: high_equal_priority (const string & opd,const string & opg) const
{
    switch (opd[0])
    {
        case '*':
            return ((opg[0] == '*') || (opg[0] == '/') || (opg[0] == '^') || (opg[0] == '~'));

        case '/':
            return ((opg[0] == '*') || (opg[0] == '/') || (opg[0] == '^') || (opg[0] == '~'));

        case '+':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*') || (opg[0] == '/') || (opg[0] == '^') || (opg[0] == '~'));

        case '-':
            return ((opg[0] == '+') || (opg[0] == '-') || (opg[0] == '*') || (opg[0] == '/') || (opg[0] == '^') || (opg[0] == '~'));

        case '^':
            return ((opg[0] == '^') || (opg[0] == '~'));

        case '~':
            return ((opg[0] == '^') || (opg[0] == '~'));

        default: return false;
    }
}


Matrix MatrixLibrary:: calculate (const string & op, const string & a, const string & b) const
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


double MatrixLibrary:: calculateFloat (const std::string & op, const std::string & a, const std::string & b) const
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


Matrix MatrixLibrary:: calculateMatrixFloat (const std::string & op, const std::string & a, const float & b)const
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


Matrix MatrixLibrary:: calculateFloatMatrix(const std::string &op, const std::string &a, const float &b)const
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


void MatrixLibrary:: polish(const std::string & chain , std::vector<std::string> & polish_notation)const
{
    stack<string> p;
    vector<string> expression;
    copy_vector(expression,explode(chain));

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
                while ((!p.empty()) && high_equal_priority(i,p.top()))
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
                polish_notation.push_back(p.top());
                p.pop();

            }while ((p.top() !=  "(") && (!p.empty()));
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


string MatrixLibrary:: isCalculableExpression(const string & expression)const
{
   vector<string> result = explode(expression);
   unsigned long int i, s = result.size();

   string calculable = "calculable";

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

   vector<string> no_parenthesis;

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


    string error1 = "Expression vide" ;

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

    string error3a = "Calcul de " ;
    string error3b = " impossible" ;
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
            else if (!isName(no_parenthesis[i-1]))
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
                return ("Calcul de " + no_parenthesis[i] + no_parenthesis[i+1] + " impossible!");
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
                            + no_parenthesis[i] + error3b + "\nVeuillez utiliser 'M~' pour désigner l'inverser d'une matrice M");
                if (atof(no_parenthesis[i].c_str()) - atoi(no_parenthesis[i].c_str()) != 0.0)
                    return ("Calcul d'une puissance réelle impossible, veuillez saisir un entier");
            }
            else if ( (i < s - 1) && isName(no_parenthesis[i+1]) )
                return "L'opération " + no_parenthesis[i] + no_parenthesis[i+1] + " n'est pas définie" ;

        }

    }

    if (!matrix_result)
        return "Le résultat de sortie n'est pas une matrice!" ;

    //cout << "Calculable" << endl << endl;
    return calculable;
}


Matrix MatrixLibrary:: expressionCalcul(const std::string & chain)const
{

    MatrixLibrary copy(*this);
    vector<string> polish_not;
    copy.polish(chain,polish_not);        //I write my expression in Polish notation

    stack<string> pile;
    Matrix temp;
    string identify;
    int name=0;

    for (auto i : polish_not)
    {
        if (i == "~")
        {
            /* if the current element is a tilde, I calculate the inverse of the matrix*/

            string a = pile.top();
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

            string b = pile.top();
            pile.pop();
            string a = pile.top();
            pile.pop();

            /* depending on the type of the two operands I calculate the result */

            if ((copy.isName(b) && copy.isName(a)) || (copy.isFloat(a) && copy.isName(b)) || (copy.isFloat(b) && copy.isName(a)) )
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
                ostringstream ss;
                ss << copy.calculateFloat (i,a,b);
                string res = ss.str();
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


void MatrixLibrary:: saveFile (const string & filename)const
{
    ofstream file (filename.c_str());

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du fichier "
                "\nVeuillez vérifier le chemin du fichier" << endl;
        exit(EXIT_FAILURE);
    }

    file << "Matrix" << endl;

    for (auto it = tab.begin(); it != tab.end(); it++ )
    {
       string matrixname = it->first;
       Matrix m(*find(matrixname));

       file << endl << matrixname << endl;
       file << m.getNbRows() << " " << m.getNbCols() << endl;

       for (unsigned int i = 0; i < m.getNbRows(); i++)
       {
           for (unsigned int j = 0; j < m.getNbCols(); j++)
           {

               file << m[i][j] << " ";
           }
           file << endl;
       }
       cout << "La sauvegarde de la matrice " << matrixname << " est réussie" << endl << endl;
    }

    file.close();
}


void MatrixLibrary:: readFile (const string & filename)
{
    string matrixname;
    unsigned int r,c;
    ifstream file (filename.c_str());

    empty();

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
    }

    string testfile;
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
        cout << "Erreur, ce fichier ne contient pas des matrices !" << endl ;

    }
}


void MatrixLibrary:: testRegression()
{
     cout << endl << endl << "****** DEBUT DU TEST DE REGRESSION ******" << endl << endl << endl;

    MatrixLibrary lib;

    Matrix identite(3,3,{1,0,0,0,1,0,0,0,1});
    Matrix a(3,3,{1,2,3,4,5,6,7,8,9});
    Matrix b(3,3,{1,2,3,2,4,5,3,5,1});

    string exp1("1+2*14");
    string exp2("identite~matrice1");
    string exp3("identite~2");
    string exp4("+14*marice1-");
    string exp5("matrice1++matrice2");
    string exp6("matrice2^~6");
    string exp7("identite=matrice1");
    string exp8("5~+matrice1");
    string exp9("matrice1+/matrice2");
    string exp10("matrice1*-identite");
    string exp11("matrice1*(-identite)");
    string exp12("6^2*matrice2");
    string exp13("matrice1^identite");
    string exp14("20/matrice1");

    string exp15("matrice1");
    string exp16("matrice1/matrice1");
    string exp17("matrice1/2");
    string exp18("identite~");
    string exp19("identite+5-3");
    string exp20("2*3*matrice");
    string exp21("matrice2~^2");
    string exp22("identite~*4");
    string exp23("2-matrice1");



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


    /* fonctions expressionCalcul */

    // the expressionCalcul function is used to test several functions such as polish

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


    res = lib.expressionCalcul("identite+identite~");
    assert(res == resultat1);


    res = lib.expressionCalcul("identite+identite~*5+matrice1");
    assert(res == resultat2);


    res = lib.expressionCalcul("3*2*matrice1^4");
    assert(res == resultat3);


    res = lib.expressionCalcul("matrice2~+6*2");
    assert(res == resultat4);


    res = lib.expressionCalcul("1+(matrice2~)^2");
    assert(res == resultat5);


    res = lib.expressionCalcul("2*matrice2*matrice2*(matrice2*matrice2)~-2");
    assert(res == resultat6);


    res = lib.expressionCalcul("matrice1*2/2-1+1");
    assert(res == a);


    res = lib.expressionCalcul("matrice2/matrice2");
    assert(res == identite);


    res = lib.expressionCalcul("2+3*identite/identite~^3");
    assert(res == resultat7);


    res = lib.expressionCalcul("identite~~");
    assert(res == identite);

<<<<<<< HEAD
    cout << endl << endl << endl << "****** FIN DU TEST DE REGRESSION ******" << endl << endl ;
}


void MatrixLibrary:: saveFile (const string& filename)const
{
    ofstream file (filename.c_str());

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du fichier "
                "\nVeuillez vérifier le chemin du fichier" << endl;
        exit(EXIT_FAILURE);
    }

    file << "Matrix" << endl;
=======
>>>>>>> origin/calcul_matriciel_tarik

    cout << "! Test isCalculable" << endl << endl;
    {
        cout << "Expressions non calculable..." << endl << endl;
        cout << exp1 << "  :  " << isCalculableExpression(exp1) << endl;
        cout << exp2 << "  :  " << isCalculableExpression(exp2) << endl;
        cout << exp3 << "  :  " << isCalculableExpression(exp3) << endl;
        cout << exp4 << "  :  " << isCalculableExpression(exp4) << endl;
        cout << exp5 << "  :  " << isCalculableExpression(exp5) << endl;
        cout << exp6 << "  :  " << isCalculableExpression(exp6) << endl;
        cout << exp7 << "  :  " << isCalculableExpression(exp7) << endl;
        cout << exp8 << "  :  " << isCalculableExpression(exp8) << endl;
        cout << exp9 << "  :  " << isCalculableExpression(exp9) << endl;
        cout << exp10 << "  :  " << isCalculableExpression(exp10) << endl;
        cout << exp11 << "  :  " << isCalculableExpression(exp11) << endl;
        cout << exp12 << "  :  " << isCalculableExpression(exp12) << endl;
        cout << exp13 << "  :  " << isCalculableExpression(exp13) << endl << endl << endl;
        cout << "Expressions calculable" << endl << endl;
        cout << exp14 << "  :  " << isCalculableExpression(exp14) << endl;
        cout << exp15 << "  :  " << isCalculableExpression(exp15) << endl;
        cout << exp16 << "  :  " << isCalculableExpression(exp16) << endl;
        cout << exp17 << "  :  " << isCalculableExpression(exp17) << endl;
        cout << exp18 << "  :  " << isCalculableExpression(exp18) << endl;
        cout << exp19 << "  :  " << isCalculableExpression(exp19) << endl;
        cout << exp20 << "  :  " << isCalculableExpression(exp20) << endl;
        cout << exp21 << "  :  " << isCalculableExpression(exp21) << endl;
        cout << exp22 << "  :  " << isCalculableExpression(exp22) << endl;
        cout << exp23 << "  :  " << isCalculableExpression(exp23) << endl;

<<<<<<< HEAD
void MatrixLibrary:: readFile (const string& filename)
{
    string matrixname;
    unsigned int r,c;
    ifstream file (filename.c_str());

    clear();

    if(!file.is_open())
    {
        cout << "Erreur lors de la lecture du file \nVeuillez vérifier le chemin du file" << endl;
=======
>>>>>>> origin/calcul_matriciel_tarik
    }



<<<<<<< HEAD
            }
            addMatrix(matrixname,m);
        }
        file.close();
    }
    else
    {
        cout << "Erreur, ce fichier ne contient pas des matrices !" << endl ;
=======

    cout << endl << endl << endl << "****** FIN DU TEST DE REGRESSION ******" << endl << endl ;
}

>>>>>>> origin/calcul_matriciel_tarik



