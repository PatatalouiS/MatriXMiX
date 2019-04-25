
#include <iostream>
#include <math.h>
#include "Fraction.h"
using namespace std;


const double EPSILON = 0.0001;
const double SHORT_EPSILON = 0.001;
const int EPSILON_INVERSE = 1000;


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
    if (f.denominateur!=1)
        flux << f.numerateur << "/" << f.denominateur;
    else
        flux << f.numerateur;
    return flux;
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


void Fraction::simplifie()
{
    long int diviseur = pgcd(numerateur,denominateur);
    numerateur = numerateur/diviseur;
    denominateur = denominateur/diviseur;

    if(denominateur<0)
    {
        denominateur *= -1;
        numerateur *= -1;
    }


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


Fraction operator+ (const long int & d, const Fraction & f)
{
    Fraction res (d*f.denominateur+f.numerateur,f.denominateur);
    return res;
}


Fraction Fraction:: inverse()
{
    Fraction f (denominateur,numerateur);
    return f;
}


Fraction Fraction:: attal(const double & d)
{
    double d0;
    if (d < 0.0)
        d0 = -d;
    else
        d0 = d;

    double reste0;
    long int integer0;

    integer0 = static_cast<long int>(floor(d0));
    reste0 = d - integer0;

    if (abs(reste0) < 0.001)
    {
        Fraction f (static_cast<long int>(d),1);

        return f;
    }

    double div1, reste1;
    long int integer1;

    div1 = 1/d;
    integer1 = static_cast<long int>(floor(div1));
    reste1 = div1 - integer1;

    if (reste1 < 0.001)
    {
        Fraction f(1,1000);
        f = integer0 + f;
        if (d - d0 != 0.0)
            f = f * -1;
        return f;
    }

    long int integer2;
    double div2, reste2;

    div2 = 1/reste1;
    integer2 = static_cast<long int>(floor(div2));
    reste2 = div2 - integer2;

    if (reste2 < 0.001)
    {
        Fraction f (1,1000);
        f = integer2 + f;
        f = f.inverse();
        f = integer0 + integer1 + f;
        if (d - d0 != 0.0)
            f = f * -1;
        return f;
    }

    double div3, reste3;
    long int integer3;

    div3 = 1/reste2;
    integer3 = static_cast<long int>(floor(div3));
    reste3 = div3 - integer3;

    if (reste3 < 0.001 )
    {

        Fraction f (1,1000);
        f = integer3 + f;
        f = f.inverse();
        f = integer2 + f;
        f = f.inverse();
        f = integer0 + integer1 + f;
        f.simplifie();
        if (d - d0 != 0.0)
            f = f * -1;
        return f;
    }


    double div4, reste4;
    long int integer4;

    div4 = 1/reste3;
    integer4 = static_cast<long int>(floor(div4));
    reste4 = div4 - integer4;

    if (reste3 < 0.001 )
    {
        Fraction f (1,1000);
        f = integer4 + f;
        f = f.inverse();
        f = integer3 + f;
        f = f.inverse();
        f = integer2 + f;
        f = f.inverse();
        f = integer0 + integer1 + f;
        f.simplifie();
        if (d - d0 != 0.0)
            f = f * -1;
        return f;
    }


    double div5, reste5;
    long int integer5;

    div5 = 1/reste4;
    integer5 = static_cast<long int>(floor(div5));
    reste5 = div5 - integer5;

    Fraction f (1,1000);
    f = integer5 + f;
    f = f.inverse();
    f = integer4 + f;
    f = f.inverse();
    f = integer3 + f;
    f = f.inverse();
    f = integer2 + f;
    f = f.inverse();
    f = integer0 + integer1 + f;
    f.simplifie();
    if (d - d0 != 0.0)
        f = f * -1;
    return f;
}


