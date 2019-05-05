
#include <iostream>
#include <vector>
#include <math.h>
#include<cassert>
#include "VectorX.h"
#include "Polynomial.h"

using namespace std;


const double EPSILON=0.0001;
const Polynomial Polynomial:: polynomial_null = Polynomial();
const Polynomial Polynomial:: polynomial_noEigen = Polynomial();



Polynomial :: Polynomial() : tab (vector<double>(1,0))
{
    this->degree = 0;
}


Polynomial :: Polynomial(const unsigned int & d) : tab(vector<double>(d+1,1))
{
    this->degree = d;
}


Polynomial :: Polynomial(const unsigned int & d, const VectorX & values)
{
    if ( values.size() != d + 1 )
    {
        cerr << "Erreur : Pas le nombre de coefficients" << endl;
        return;
    }

    this->degree = d;

    for (auto i : values)
    {
        tab.push_back(i);
    }

}


Polynomial::Polynomial(const Polynomial &p) : tab (vector<double>(p.tab))
{
    degree = p.degree;
}


Polynomial Polynomial:: check() const
{
    Polynomial res(*this);
    unsigned int i, d;
    int l;
    d = degree;
    for (i =0; i < d + 1; i++)
    {
        for (l = -150 ; l < 150; l++)
        {
            if ( abs(tab[i] - l) < EPSILON )
            {
                res.tab[i] = l;
            }
        }

    }

    return res;
}


ostream& operator << (ostream& flux, const Polynomial & p)
{
    unsigned int i;
    bool notfirst = false;

    if (p.degree == 0)
        flux << p.tab[0];
    else
    {
        for (i = 0; i <= p.degree; i++)
        {
            if(p.tab[i] > 0 && notfirst)
                flux << " + " ;
            else if(p.tab[i] < 0 && notfirst)
                flux << " " ;

            if (p.tab[i] != 0.0)
            {
                notfirst = true;
                if (p.tab[i] == 1.0)
                {
                    if (i == 0)
                        flux << 1 ;
                    else if (i == 1)
                        flux << "X";
                        else
                            flux << "X^" << i ;
                }
                else if (-p.tab[i] ==1.0)
                {
                    if (i == 0)
                        flux << -1 ;
                    else if (i == 1)
                        flux << "- X" ;
                        else
                            flux << "- X^" << i ;
                }
                    else
                    {
                        if (i == 0)
                            flux << p.tab[i] ;
                        else if (i == 1)
                            flux << p.tab[i] << "X" ;
                            else
                                flux << p.tab[i] << "X^" << i ;
                    }

            }
        }
    }

    cout << endl;
    return flux;
}


Polynomial& Polynomial:: operator = (const Polynomial & p)
{
    this->degree = p.degree;
    tab=vector<double>(this->degree + 1,0);
    unsigned int i;
    for (i = 0; i <= degree; i++)
    {
        tab[i]=p.tab[i];
    }

    return (*this);
}


bool Polynomial:: operator == (const Polynomial & p) const
{
    if(degree != p.degree)
        return false;
    unsigned int i;
    for(i = 0; i < degree; i++)
        if (tab[i] - p.tab[i] != 0.0)
            return false;

    return true;
}


const Polynomial Polynomial:: operator + (const Polynomial & p)const
{
    unsigned int i;
    if (degree > p.degree)
    {
        Polynomial result(*this);

        for (i = 0; i <= p.degree; i++)
        {
            result.tab[i] += p.tab[i];
        }

        return result;

    }
    else
    {
        Polynomial result(p);

        for (i = 0; i <= degree;i++)
        {
            result.tab[i] += tab[i];
        }

        return result;
    }

}


const Polynomial Polynomial:: operator - (const Polynomial & p)const
{
    unsigned int i, mindegree,k,tampon;

    Polynomial result(*this);

    if (degree > p.degree)
    {
        mindegree = p.degree;
    }
    else
    {
        mindegree = degree;
    }
    for(i = 0; i <= mindegree; i++)
    {
        result.tab[i] -= p.tab[i];
    }

    if (mindegree == degree)
    {
        for(i = mindegree + 1; i <= p.degree; i++)
        {
            result.tab.push_back(-p.tab[i]);
            result.degree++;
        }
    }

    tampon = 0;
    k = result.degree;

    while (result.tab[k] == 0.0 && k > 0)
    {
        tampon++;
        k--;
    }
    result.degree = result.degree-tampon;


    return result;
}


const Polynomial Polynomial:: operator * (const Polynomial & p)const
{
    unsigned int i,j,k,d = degree + p.degree;
    Polynomial result(d);

    for (i = 0; i <= d; i++)
        result.tab[i] = 0;

    for (i = 0; i <= d; i++)
    {
        for (j = 0; j <= degree; j++)
        {
            for (k = 0; k <= p.degree; k++)
            {
                if (j+k==i)
                {
                    result.tab[i] += tab[j] * p.tab[k];
                }
            }
        }
    }
    return result;
}


const Polynomial Polynomial:: operator * (const double & scale)const
{
    unsigned int i;
    Polynomial p(*this);
    for (i = 0; i <= degree; i++)
    {
        p.tab[i] *= scale;
    }
    return p;
}


const Polynomial Polynomial:: division(const Polynomial & divisor, Polynomial & rest)
{
    Polynomial quotient(degree - divisor.degree);
    Polynomial copy(*this);

    unsigned int i = 0, j, tampon;
    unsigned long k;

    while ((copy.degree - i >= divisor.degree)
           && (static_cast<int>(copy.degree - i) >= 0))
    {
        quotient.tab[copy.degree - divisor.degree - i] =
                                                    copy.tab[copy.degree - i]
        											/ divisor.tab[divisor.degree];
        for (j = i; j <= divisor.degree; j++)
        {
            copy.tab[copy.degree - j] = copy.tab[copy.degree - j]
            							- divisor.tab[divisor.degree - (j - i)]
            							* quotient.tab[copy.degree - divisor.degree - i];

        }
        i++;
    }

    copy = quotient * divisor;
    rest = (*this) - copy;


    tampon = 0;
    k = rest.degree;
    while ((rest.tab[k] == 0.0) && (k != 0))
    {
        tampon++;
        k--;
    }
    rest.degree = rest.degree - tampon;

    if (rest.degree > divisor.degree)
    {

        Polynomial quotient2 (rest.degree - divisor.degree);
        quotient2 = rest.division(divisor,rest);
        quotient = quotient+quotient2;
    }

    return quotient;
}


void Polynomial:: equation2degre (unsigned int  & nbsolution, 
                                    double & x1, double & x2)const
{
    if (degree != 2)
    {
        cout << "Equation de degré différent de 2" << endl;
        exit(EXIT_FAILURE);
    }

    double a,b,c;
    Polynomial copie(*this);
    a = copie.tab[2];
    b = copie.tab[1];
    c = copie.tab[0];
    double delta = (b * b) - (4 * a * c);

    if (delta < 0)
    {
        nbsolution = 0;
    }
        else if (delta == 0.0)
        {
            nbsolution = 1;
            x1 = - b / (2 * a);
        }
        else
            {
                nbsolution = 2;
                double r = sqrt(delta);
                x1=(-b - r) / (2 * a);
                x2=(-b + r) / (2 * a);
            }

}


void Polynomial:: regressionTest()const
{
    Polynomial p1(1,{0,1});
    Polynomial p2(1,{1,1});
    Polynomial p3(2,{6,5,1});
    Polynomial p4(2,{2,3,1});
    Polynomial p5(5,{1,2,0,0,3,0.5});
    Polynomial p6(2,{-1,0,1});
    Polynomial p7(0,{1});

    Polynomial res1(1,{1,2});
    Polynomial res2(1,{4,2});
    Polynomial res3(3,{1,3,3,1});
    Polynomial res4(4,{0,0,6,5,1});
    Polynomial res5(5,{2,4,0,0,6,1});
    Polynomial res6(3,{18,34,18,3});
    Polynomial res7(1,{-1,1});
    Polynomial res8(1,{2,1});
    Polynomial res9(4,{2,0,0,3,0.5});
    Polynomial res10;
    Polynomial rest7(0);
    Polynomial rest9(0,{1});


    Polynomial result;
    Polynomial rest;

    result = p1 + p2;
    assert(result == res1);
    assert(result.degree == res1.degree);

    result = p3 - p4;
    assert(result == res2);
    assert(result.degree == res2.degree);

    result = p1 * p4 + p2;
    assert(result == res3);
    assert(result.degree == res3.degree);

    result = p1 * p1 * p3;
    assert(result == res4);
    assert(result.degree == res4.degree);

    result = p1 * p1 * p3;
    assert(result == res4);
    assert(result.degree == res4.degree);

    result = p5 * 2;
    assert(result == res5);
    assert(result.degree == res5.degree);

    result = p1 + p2 * p3 * 3;
    assert(result == res6);
    assert(result.degree == res6.degree);

    result = p6.division(p2,rest);
    assert(result == res7);
    assert(result.degree == res7.degree);
    assert(rest == rest7);
    assert(rest.degree == rest7.degree);

    result = p4.division(p2,rest);
    assert(result == res8);
    assert(result.degree == res8.degree);
    assert(rest == rest7);
    assert(rest.degree == rest7.degree);

    result = p5.division(p1,rest);
    assert(result == res9);
    assert(result.degree == res9.degree);
    assert(rest == rest9);
    assert(rest.degree == rest9.degree);


    result = p3.division(p7,rest);
    assert(result == p3);
    assert(result.degree == p3.degree);
    assert(rest == rest7);
    assert(rest.degree == rest7.degree);

    unsigned int nbsolutions;
    double x1,x2;

    p3.equation2degre(nbsolutions,x1,x2);
    assert(nbsolutions == 2);
    assert(x1 + 3.0 == 0.0);
    assert(x2 + 2.0 == 0.0);


    p4.equation2degre(nbsolutions,x1,x2);
    assert(nbsolutions == 2);
    assert(x1 + 2.0 == 0.0);
    assert(x2 + 1.0 == 0.0);



}
