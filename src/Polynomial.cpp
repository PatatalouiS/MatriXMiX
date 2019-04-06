

#include <iostream>
#include <vector>
#include <math.h>
#include "VectorX.h"
#include "Polynomial.h"

using namespace std;


const double EPSILON=0.00001;


Polynomial :: Polynomial() : tab (1,0)
{
    degree=0;
}


Polynomial :: Polynomial(const unsigned int & d) : tab(d,1)
{
    degree=d;
}


Polynomial :: Polynomial(const unsigned int & d, const VectorX & values)
{
    if ( values.size() != d+1 )
    {
        cout << "Erreur : Pas le nombre de coefficients" << endl;
        exit ( EXIT_FAILURE );
    }

    this->degree = d;

    for ( unsigned int i=0; i<d+1; i++ )
    {
        tab.push_back(values[i]);
    }

}


Polynomial::Polynomial(const Polynomial &p) : tab (vector<double>(p.tab))
{
    degree = p.degree;
}


Polynomial::~Polynomial()
{
}


void Polynomial:: check()
{
    for(unsigned int i=0; i<=degree; i++)
    {
        if(abs(tab[i])<EPSILON)
        {
            tab[i]=0;
        }

    }
}


ostream& operator << (ostream& flux, const Polynomial & p)
{
    unsigned int i;

    for (i=0; i<=p.degree; i++)
    {
        flux << p.tab[i] << " ";
    }
    cout << endl;
    return flux;
}


Polynomial& Polynomial:: operator = (const Polynomial & p)
{
    degree=p.degree;
    unsigned int i;
    for (i=0; i<=degree; i++)
    {
        tab[i]=p.tab[i];
    }

    return (*this);
}


const Polynomial Polynomial:: operator + (const Polynomial & p)
{

    unsigned int i;

    if (degree>p.degree)
    {
        Polynomial resultat(*this);

        for (i=0; i<=p.degree;i++)
        {
            resultat.tab[i]+=p.tab[i];
        }

        return resultat;

    }
    else
    {
        Polynomial resultat(p);

        for (i=0; i<=degree;i++)
        {
            resultat.tab[i]+=tab[i];
        }

        return resultat;
    }

}


const Polynomial Polynomial:: operator - (const Polynomial & p)
{
    unsigned int i, mindegree;

    Polynomial resultat(*this);

    if(degree>p.degree)
        mindegree=p.degree;
    else
        mindegree=degree;

    for(i=0; i<=mindegree; i++)
    {
        resultat.tab[i]-=p.tab[i];
    }

    if(mindegree==degree)
    {
        for(i=mindegree+1; i<=p.degree; i++)
        {
            resultat.tab.push_back(-p.tab[i]);
            resultat.degree++;
        }
    }

    return resultat;
}


const Polynomial Polynomial:: operator *(const Polynomial & p)
{
    unsigned int i,j,k,d=degree+p.degree;
    Polynomial result(d);

    for(i=0; i<=d; i++)
        result.tab[i]=0;

    for(i=0; i<=d; i++)
    {
        for(j=0; j<=degree; j++)
        {
            for(k=0; k<=p.degree; k++)
            {
                if(j+k==i)
                {
                    result.tab[i]+=tab[j]*p.tab[k];
                }
            }
        }
    }
    result.check();
    return result;
}


const Polynomial Polynomial:: operator *(const float & scale)
{
    unsigned int i;
    for (i=0; i<=degree; i++)
    {
        tab[i]*=scale;
    }
    check();
    return (*this);
}


void Polynomial:: equation2degre (unsigned int  & nbsolution, double & x1, double & x2)
{
    if (degree!=2)
    {
        cout << "C'est pas du second degré ça :/" << endl;
        exit(EXIT_FAILURE);
    }

    double a,b,c;
    Polynomial copie(*this);
    copie.check();
    a=copie.tab[2];
    b=copie.tab[1];
    c=copie.tab[0];

    double delta=b*b-4*a*c;

    if(delta<0)
    {
        nbsolution=0;
    }
        else if (delta==0)
        {
            nbsolution=1;
            x1=-b/(2*a);
        }
        else
            {
                nbsolution=2;
                double r=sqrt(delta);
                x1=(-b-r)/(2*a);
                x2=(-b+r)/(2*a);
            }

}