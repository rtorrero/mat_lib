// testing_mat_lib.hpp 
// author: Antonio C. Domínguez Brito <antonio.dominguez@ulpgc.es>  
// creation date: october 3rd 2020
// Description: This is a problem for testing mat_lib library

#include <iostream>
using namespace std;

#include "matrix.hpp"
using namespace mat_lib;

int main(int arc, char* argv[])
try
{
  cout<<"This is testing_mat_lib!"<<endl;

  matrix a{
    {1,  2,  3,  4},
    {5,  6,  7,  8},
    {9, 10, 11, 12}
  };
  cout<<"a="<<a<<endl;

  matrix b{a};
  cout<<"b="<<b<<endl;

  a+=b;
  cout<<"a="<<a<<endl;

  matrix  c=3*(a-b);
  cout<<"c="<<c<<endl;

  matrix d=a*3-b;
  cout<<"d="<<d<<endl;

  matrix e=-a;
  cout<<"e="<<e<<endl;

  matrix f=a.make_transpose();
  cout<<"f="<<f<<endl;

  a/=2;
  cout<<"a="<<a<<endl;

  matrix a2=a*a.make_transpose();
  cout<<"a2="<<a2<<endl;

  matrix l{1, 2, 3, 4, 5, 6};
  cout<<"l="<<l<<endl;

  cout<<"l*lt="<<l*~l<<endl;

  cout<<"lt*l="<<~l*l<<endl;

  matrix at=~a;
  cout<<"at="<<at<<endl;
  cout<<"at*a="<<~a*a<<endl;
  cout<<"a*at="<<a*~a<<endl;

  a.save_as("a.matrix");
  at.save_as("at.matrix");
  (~l*l).save_as("ltl.matrix");

  matrix g{"ltl.matrix"};
  cout<<"g="<<g<<endl;

  cout<<~matrix{"at.matrix"}<<endl;

  cout<<boolalpha<<(at==matrix{"at.matrix"})<<endl;
  return 0; 
}
catch(exception& e)
{ cerr<<"[EXCEPTION] "<<e.what()<<endl; }
