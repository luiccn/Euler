#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <list>
#include <set>
#include <math.h>
#include <iomanip>
#include <string>
#include <algorithm>
#include <iterator>
#include <strstream>


using namespace std;




// Conway_Positive_All.cc    June 2014



//  g++  -o     Conway_Positive_All     Conway_Positive_All.cc  -lm




void insert_primitive_reps(unsigned int a, unsigned int h, unsigned int b, unsigned int M,  set<unsigned int>  *setPtr)
{
  cout << setw(12) << a  << setw(12) << h  << setw(12) << b << "   insert_primitive_reps"    << endl;
  if ( a <= M )
  {
    (*setPtr).insert(a);
    if ( b <= M )
    {
      (*setPtr).insert(b);
      if ( a <= M - b && h <= M - a - b)
      {
        if( a <= M - a - h ) insert_primitive_reps(a, h + 2 * a, a + b + h, M, setPtr);
        if( b <= M - b - h ) insert_primitive_reps(a + b + h, h + 2 * b,b, M, setPtr);
         // comment: once a+b+h <= M, min(2a+h, 2b+h) <= M
      }  // if a + b + h
    } // if  b
  } // if a

} // end insert_primitive_rep



int IntSqrt(int i)
{
  // cerr << "called intsqrt  with   " << i << endl;
  if ( i <= 0 ) return 0;
  else if ( i <= 3) return 1;
  else if ( i >= 2147395600) return 46340;
  else
  {
    float r;
    r = 1.0 * i;
    r = sqrt(r);
    int root = (int) ceil(r);
    while ( root * root   <= i ) ++root;
    while ( root * root   > i ) --root;
    return  root ;
  }
}


string stringify(int x)
 {
   ostringstream o;
   o << x  ;
   return o.str();
 }


string Factored(unsigned int i)
{
  string fac;
  fac = " = ";
  int p = 2;
 unsigned int temp = i;
  if (temp < 0 )
  {
    temp *= -1;
    fac += " -1 * ";
  }

  if ( 1 == temp) fac += " 1 ";
  if ( temp > 1)
  {
    int primefac = 0;
    while( temp > 1 && p * p <= temp)
    {
      if (temp % p == 0)
      {
        ++primefac;
        if (primefac > 1) fac += " * ";
         fac += stringify( p) ;
        temp /= p;
        int exponent = 1;
        while (temp % p == 0)
        {
          temp /= p;
          ++exponent;
        } // while p is fac
        if ( exponent > 1)
        {
          fac += "^" ;
          fac += stringify( exponent) ;
        }
      }  // if p is factor
      ++p;
    } // while p
    if (temp > 1 && primefac >= 1) fac += " * ";
    if (temp > 1 ) fac += stringify( temp)  ;
  } // temp > 1
  return fac;
} // Factored




int main(int argc, char *argv[])
{
  if ( argc != 5) cout << "Usage: ./Conway_Positive_All A B C       M " << endl;
  else {



  int a,b,c, discr;
     int N,M;
    a = atoi(argv[1]);
        b = atoi(argv[2]);
    c = atoi(argv[3]);
   M = atoi(argv[4]);

  cout << setw(12) << atoi(argv[1])  << setw(12) << atoi(argv[2])  << setw(12) << atoi(argv[3]) << "   original form " << endl    << endl;
      int d = b * b - 4 * a * c ;
      int droot = IntSqrt(d) ;


      if ( d <= 0) cout << "nonpositive discriminant  " << d << endl << endl;
       if (d == droot * droot) cout << "square discriminant  " << d << endl << endl;


      if (d > 0 && d != droot * droot)
      {



      int aa,bb,cc;
      while ( a <= 0 || c >= 0 || b <= abs(a+c) )
      {
        int delta, cAbs;
       cAbs = c;
        if (cAbs < 0) cAbs *= -1;

       delta =   (b + droot)/( 2 * cAbs)  ;
  if (c < 0) delta *= -1;
     aa = c ; bb = 2 * c * delta - b ; cc =  c * delta * delta - b * delta + a ;
       a = aa; b = bb; c = cc;
       } // while not reduced with a > 0


  cout << setw(12) << a  << setw(12) << b  << setw(12) << c << "   Lagrange-Gauss reduced " << endl    << endl;


        int a_old = a;
        int b_old = b;
        int c_old = c;

        int goon = 1;


set<unsigned int>  S;





        while (goon )
        {


         int newval = a+b+c;

          if ( newval > 0 )
          {
       //      cout << setw(65) << b + 2 * a << endl;
             insert_primitive_reps(a, b + 2 * a,newval ,M,  &S); // note ampersand
             b+= 2 * c ;

             a = newval;

           } // newval > 0
         else if ( newval < 0 )
          {
     //        cout << setw(5) << -1 * ( b + 2 * c) << endl;

             b+= 2 * a ;
             c = newval;

           } // newval < 0


         goon = (a != a_old)  || (b != b_old)  || (c != c_old)  ;

        } // while goon


  cout << endl << endl << " ALL represented positive integers up to  " << M << endl << endl;



    set<unsigned int> T;
 set<unsigned int>::iterator iterU;
 for(iterU = S.begin() ;   iterU != S.end() ; ++iterU)
    {

      unsigned int p = *iterU;
     //  cout << setw(12) << p << Factored(p) << endl;
      for(int t = 1; t * t <= M / p; ++t) T.insert( t * t * p);

    }

      for(iterU = T.begin() ;   iterU != T.end() ; ++iterU)
    {

      unsigned int p = *iterU;
       cout << setw(12) << p << Factored(p) << endl;


    }








  cout << endl << endl << " ALL represented positive integers up to  " << M << endl << endl;
 cout << setw(12) << atoi(argv[1])  << setw(12) << atoi(argv[2])  << setw(12) << atoi(argv[3]) << "   original form " << endl    << endl;
       } // not square


    } // else argc
    return 0 ;
}






//  g++  -o     Conway_Positive_All     Conway_Positive_All.cc  -lm



