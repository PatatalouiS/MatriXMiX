
#include <iostream>
#include <math.h>
#include "Fraction.h"
using namespace std;


const double EPSILON = 0.0001;


Fraction::Fraction()
{
    numerateur=0 ;
    denominateur=1;
}


Fraction::Fraction(const long int & n)
{
    numerateur = n;
    denominateur = 1;
}


Fraction::Fraction(const long int & n, const long int & m)
{
    numerateur = n;
    denominateur = m;
}


ostream& operator<<(ostream& flux, Fraction const & f)
{

        flux << f.numerateur << "/" << f.denominateur;

    return flux;
}


Fraction& Fraction:: operator=(const Fraction &f)
{
    numerateur = f.numerateur;
    denominateur = f.denominateur;

    return *this;
}


long int Fraction::pgcd(long int a, long int b)
{
    while (b!=0)
    {
        long int t = b;
        b = a%b;
        a = t;
    }

    return a;

}


Fraction Fraction::simplifie()
{
    long int div, num, den;
    div = pgcd(numerateur,denominateur);
    num = numerateur/div;
    den = denominateur/div;

    if(den < 0)
    {
        den *= -1;
        num *= -1;
    }

    Fraction f (num,den);

    return f;

}


bool Fraction::estEgal(const Fraction & f) const
{
    double f1 = numerateur*f.denominateur;
    double f2 = denominateur*f.numerateur;

    double resultat = f1/f2;

    if (resultat == 1.0)
        return true;
    return false;
}


bool operator==(const Fraction & f1, const Fraction & f2)
{
    return (f1.estEgal(f2));
}


bool Fraction::estPlusPetitQue(const Fraction & f) const
{
    double f1 = numerateur/denominateur;
    double f2 = f.numerateur/f.denominateur;

    return (f1<f2);
}


bool operator<(const Fraction & f1, const Fraction & f2)
{
    return (f1<f2);
}


Fraction& Fraction::operator+=(const Fraction & f)
{
    numerateur = numerateur*f.denominateur + denominateur*f.numerateur;
    denominateur = denominateur*f.denominateur;

    return *this;
}


Fraction operator+(const Fraction & f1, const Fraction & f2)
{
    Fraction copie(f1);
    copie+=f2;
    return copie;
}


Fraction operator* (const Fraction & f1, const Fraction & f2)
{
    long int num, den;
    num = f1.numerateur * f2.numerateur;
    den = f1.denominateur * f2.denominateur;
    Fraction f(num,den);
    return f;
}


Fraction operator/ (const Fraction & f1, const Fraction & f2)
{
    long int num, den;
    num = f1.numerateur * f2.denominateur;
    den = f1.denominateur * f2.numerateur;
    Fraction f(num,den);
    return f;
}


bool Fraction:: isFraction(const double & d)
{
    long int integer = static_cast<long int>(d);
    double r = d - integer;
    if (r == 0.0)
        return false;

    return true;
}


Fraction Fraction::double2Fraction(const double & d)
{
    int i,j;
    double r = d - floor(d);
    for (i = 1 ; i < 10001; i++)
    {
        for (j = -500; j < 500; j++ )
        {
            if ( abs(j - i * r) < EPSILON && i!= 0)
            {
                double num = floor(i * r + 2 * EPSILON) + i * floor(d);
                Fraction f (static_cast<long int>(num),i);
                f.simplifie();
                return f;
            }

        }

    }

    i=1;
    long int num=1, den=1;
    double f2=d*10;
    while(i<10)
    {
        if ( num - static_cast<long int>(f2*pow(10,i)) < EPSILON)
        {
            num = static_cast<long int>(f2*pow(10,i-1)) ;
            den *= 10;
        }
        i++;
    }
    Fraction fraction(num,den);

    fraction.simplifie();
    return fraction;
}


Fraction Fraction:: operator+ (const long int &f)
{
    long int temp = f * denominateur;
    temp = temp + numerateur;
    Fraction res (temp, denominateur);
    return res;
}


Fraction Fraction:: inverse()
{
    Fraction f (denominateur,numerateur);
    return f;
}


void Fraction:: recursive (vector<long int> &tab, const double &rest)
{
    if ( tab.size() < 20 && rest > EPSILON)
    {
        double div, rest2;
        long int integer;
        div = 1 / rest;
        integer = static_cast<long int>(floor(div));
        rest2 = div - integer;
        tab.push_back(integer);
        recursive(tab,rest2);
    }

}


Fraction Fraction:: hanattal(const double &d)
{
    double abs_d = abs(d);
    vector <long int> tab;

    double rest;
    long int integer;
    unsigned long int size;

    integer = static_cast<long int>(floor(abs_d));
    rest = abs_d - integer;

    tab.push_back(integer);
    recursive(tab,rest);

    size = tab.size();

    if (size == 1)
    {
        Fraction f (tab[0],1);
        return f;
    }
    if (size == 2)
    {
        Fraction f (1,tab[1]);
        f = f + tab[0];
        return f;
    }

    Fraction f (1,tab[size-2]);

    for (unsigned long int i = size - 2 ; i > 0 ; i--)
    {
        f = f + tab[i];
        f = f.inverse();
    }

    f = f + tab[0];
    f = f.simplifie();

    return f;

}
