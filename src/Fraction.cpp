
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


void Fraction::afficher(ostream& flux) const
{
    flux << numerateur << "/" << denominateur;
}


ostream& operator<<(ostream& flux, Fraction const& fraction)
{
    fraction.afficher(flux) ;
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

    short int i,j;
    double r = d - floor(d);
    cout << r << endl;
    for (i = -1000 ; i < 1001; i++)
    {
        for (j = -1000; j < 1001; j++ )
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




