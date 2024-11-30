#include <iostream>
using namespace std;

#include "matrix.hpp"
#include "vector.hpp" // Include the vector class
using namespace mat_lib;

int main(int arc, char *argv[]) try {
  cout << "This is testing_mat_lib!" << endl;

  // --- Matrix tests ---
  matrix a{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};
  cout << "a=" << a << endl;

  matrix b{a};
  cout << "b=" << b << endl;

  a += b;
  cout << "a=" << a << endl;

  matrix c = 3 * (a - b);
  cout << "c=" << c << endl;

  matrix d = a * 3 - b;
  cout << "d=" << d << endl;

  matrix e = -a;
  cout << "e=" << e << endl;

  matrix f = a.make_transpose();
  cout << "f=" << f << endl;

  a /= 2;
  cout << "a=" << a << endl;

  matrix a2 = a * a.make_transpose();
  cout << "a2=" << a2 << endl;

  matrix l{1, 2, 3, 4, 5, 6};
  cout << "l=" << l << endl;

  cout << "l*lt=" << l * ~l << endl;

  cout << "lt*l=" << ~l * l << endl;

  matrix at = ~a;
  cout << "at=" << at << endl;
  cout << "at*a=" << ~a * a << endl;
  cout << "a*at=" << a * ~a << endl;

  a.save_as("a.matrix");
  at.save_as("at.matrix");
  (~l * l).save_as("ltl.matrix");

  matrix g{"ltl.matrix"};
  cout << "g=" << g << endl;

  cout << ~matrix{"at.matrix"} << endl;

  cout << boolalpha << (at == matrix{"at.matrix"}) << endl;

  // --- Vector tests ---
  // Create and display a vector
  vector v{1, 2, 3, 4};
  cout << "v=" << v << endl;

  // Scalar multiplication
  vector v_scaled = v * 2.5;
  cout << "v * 2.5=" << v_scaled << endl;

  v_scaled /= 2.5;
  cout << "v_scaled / 2.5=" << v_scaled << endl;

  // Negation operator
  vector v_neg = -v;
  cout << "-v=" << v_neg << endl;

  // Element access
  cout << "v[2]=" << v.at(2) << endl;

  try {
    cout << "v[10] (out of range)=" << v.at(10) << endl;
  } catch (const exception &e) {
    cout << "[EXPECTED EXCEPTION] " << e.what() << endl;
  }

  // Vector addition and subtraction
  vector v_add = v + vector{4, 3, 2, 1};
  cout << "v + {4, 3, 2, 1}=" << v_add << endl;

  vector v_sub = v - vector{1, 1, 1, 1};
  cout << "v - {1, 1, 1, 1}=" << v_sub << endl;

  // Dot product
  vector v2{5, 6, 7, 8};
  double dot_product = dot(v, v2);
  cout << "dot(v, v2)=" << dot_product << endl;

  // Save and load a vector from file
  v.save_as("v.vector");
  vector v_loaded{"v.vector"};
  cout << "v_loaded=" << v_loaded << endl;

  // --- Matrix-vector multiplication tests ---
  // Matrix * Vector (column vector multiplication)
  vector mv = a * v;
  cout << "a * v=" << mv << endl;

  // Vector * Matrix (row vector multiplication)
  vector vm = vector{1, 2, 3} * a;
  cout << "vector{1, 2, 3} * a=" << vm << endl;

  // --- Advanced matrix tests ---
  // Test get_row and get_column
  cout << "Row 1 of a: " << a.get_row(1) << endl;
  cout << "Column 2 of a: " << a.get_column(2) << endl;

  // Check out-of-range access for get_row and get_column
  try {
    cout << "Invalid row of a: " << a.get_row(10) << endl;
  } catch (const exception &e) {
    cout << "[EXPECTED EXCEPTION] " << e.what() << endl;
  }

  try {
    cout << "Invalid column of a: " << a.get_column(5) << endl;
  } catch (const exception &e) {
    cout << "[EXPECTED EXCEPTION] " << e.what() << endl;
  }

  return 0;
} catch (exception &e) {
  cerr << "[EXCEPTION] " << e.what() << endl;
}
