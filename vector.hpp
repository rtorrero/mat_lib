// vector.hpp
// author: Rubén Torrero Marijnissen <ruben.torrero101@ulpgc.es>
// creation date: november 26 2024
// Description: This is the header file of class vector

#ifndef VECTOR_HPP
#define VECTOR_HPP

#include "matrix.hpp"
#include <cstring>
#include <string>

using namespace std;

namespace mat_lib {

class vector {
public:
  using element_t = double;

  vector() : size__{0}, elements__{nullptr} {}

  vector(size_t size) : size__{size}, elements__{new element_t[size]} {}

  vector(initializer_list<element_t> init);

  vector(const vector &v) // copy constructor
      : elements__{new element_t[v.size()]} {
    copy_elements__(v);
  }

  vector(vector &&v) // move constructor
      : size__{v.size__}, elements__{v.elements__} {
    v.size__ = 0;
    v.elements__ = nullptr;
  }

  explicit vector(const string &file_name); // constructor from a file

  ~vector() { delete[] elements__; }

  vector &operator=(const vector &v) // copy assigment
  {
    if (size__ != v.size__) {
      delete[] elements__;
      elements__ = ((v.size__) ? new element_t[v.size()] : nullptr);
    }
    copy_elements__(v);
    return *this;
  }

  vector &operator=(vector &&v) // move assigment
  {
    delete[] elements__;

    elements__ = v.elements__;
    size__ = v.size__;

    v.elements__ = nullptr;
    v.size__ = 0;

    return *this;
  }

  size_t size() const { return size__; }

  element_t at(size_t i) const;

  element_t &operator[](size_t i) { return elements__[i]; }
  const element_t &operator[](size_t i) const { return elements__[i]; }

  bool operator==(const vector &m) const;

  vector &operator+=(const vector &v);
  vector &operator-=(const vector &v);

  vector &operator*=(element_t scalar) {
    for (size_t i = 0; i < size__; i++)
      elements__[i] *= scalar;

    return *this;
  }

  vector &operator/=(float scalar);

  void save_as(const string &file_name) const;

private:
  size_t size__;
  element_t *elements__;

  bool check_initilizer_list__(const initializer_list<element_t> &init) {
    for (size_t i = 0; i < init.size(); i++)
      if (init.begin()[i] != 0)
        return false;
    return true;
  }

  void copy_elements__(const vector &v) {
    size__ = v.size__;
    for (size_t i = 0; i < size__; i++)
      elements__[i] = v.elements__[i];
  }
};

vector operator*(const matrix &m, const vector &v);
vector operator*(const vector &v, const matrix &m);
vector::element_t dot(const vector &v1, const vector &v2);

ostream &operator<<(ostream &os, const vector &v);
} // namespace mat_lib

#endif // VECTOR_HPP