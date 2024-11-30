#include "vector.hpp"
#include <fstream>
#include <sstream>

namespace mat_lib {

// Initializer list constructor
vector::vector(initializer_list<element_t> init)
    : size__{init.size()}, elements__{new element_t[init.size()]} {
  for (size_t i = 0; i < init.size(); i++)
    elements__[i] = init.begin()[i];
}

// Constructor from a file
vector::vector(const string &file_name) : size__{0}, elements__{nullptr} {
  ifstream ifs(file_name);
  if (!ifs) {
    ostringstream str_stream;
    str_stream << "cannot open file \"" << file_name << "\"! (" << __func__
               << "() in " << __FILE__ << ":" << __LINE__ << ")";
    throw logic_error(str_stream.str());
  }

  ifs >> size__;
  elements__ = new element_t[size__];

  for (size_t i = 0; i < size__; i++)
    ifs >> elements__[i];
}

// access element
vector::element_t vector::at(size_t i) const {
  if (i >= size__) {
    ostringstream str_stream;
    str_stream << "out_of range exception (" << __func__ << "() in " << __FILE__
               << ":" << __LINE__ << ")";
    throw out_of_range(str_stream.str());
  }
  return elements__[i];
}

// comparison operator
bool vector::operator==(const vector &v) const {
  if (size__ != v.size__)
    return false;

  for (size_t i = 0; i < size__; i++)
    if (elements__[i] != v.elements__[i])
      return false;

  return true;
}

// add vector to a vector and assign to the current vector
vector &vector::operator+=(const vector &v) {
  if (size__ != v.size__) {
    ostringstream str_stream;
    str_stream << "size mismatch! cannot add vectors (" << __func__ << "() in "
               << __FILE__ << ":" << __LINE__ << ")";
    throw invalid_argument(str_stream.str());
  }

  for (size_t i = 0; i < size__; i++)
    elements__[i] += v.elements__[i];

  return *this;
}

// subtract vector from a vector and assign to the current vector
vector &vector::operator-=(const vector &v) {
  if (size__ != v.size__) {
    ostringstream str_stream;
    str_stream << "size mismatch! cannot subtract vectors (" << __func__
               << "() in " << __FILE__ << ":" << __LINE__ << ")";
    throw invalid_argument(str_stream.str());
  }

  for (size_t i = 0; i < size__; i++)
    elements__[i] -= v.elements__[i];

  return *this;
}

// divide vector by a scalar and assign to the current vector
vector &vector::operator/=(element_t scalar) {
  if (scalar == 0) {
    ostringstream str_stream;
    str_stream << "divide by zero! bad scalar provided (" << __func__
               << "() in " << __FILE__ << ":" << __LINE__ << ")";
    throw invalid_argument(str_stream.str());
  }

  for (size_t i = 0; i < size__; i++)
    elements__[i] /= scalar;

  return *this;
}

void vector::save_as(const string &file_name) const {
  ofstream ofs(file_name);
  if (!ofs) {
    ostringstream str_stream;
    str_stream << "cannot open file \"" << file_name << "\"! (" << __func__
               << "() in " << __FILE__ << ":" << __LINE__ << ")";
    throw logic_error(str_stream.str());
  }

  ofs << size__ << "\n";
  for (size_t i = 0; i < size__; i++)
    ofs << elements__[i] << " ";
  ofs << "\n";
}

// Matrix * Vector (column vector)
vector operator*(const matrix &m, const vector &v) {
  if (m.columns() != v.size()) {
    ostringstream str_stream;
    str_stream << "size mismatch! cannot multiply matrix and vector ("
               << __func__ << "() in " << __FILE__ << ":" << __LINE__ << ")";
    throw invalid_argument(str_stream.str());
  }

  vector result(m.rows());
  for (size_t i = 0; i < m.rows(); i++) {
    const vector row = m.get_row(i);
    result[i] = dot(row, v);
  }

  return result;
}

// Vector * Matrix (row vector)
vector operator*(const vector &v, const matrix &m) {
  if (v.size() != m.rows()) {
    ostringstream str_stream;
    str_stream << "size mismatch! cannot multiply vector and matrix ("
               << __func__ << "() in " << __FILE__ << ":" << __LINE__ << ")";
    throw invalid_argument(str_stream.str());
  }

  vector result(m.columns());
  for (size_t j = 0; j < m.columns(); j++) {
    const vector column = m.get_column(j);
    result[j] = dot(v, column);
  }

  return result;
}

// Dot product
vector::element_t dot(const vector &a, const vector &b) {
  if (a.size() != b.size()) {
    ostringstream str_stream;
    str_stream << "size mismatch! cannot calculate dot product (" << __func__
               << "() in " << __FILE__ << ":" << __LINE__ << ")";
    throw invalid_argument(str_stream.str());
  }

  vector::element_t result = 0;
  for (size_t i = 0; i < a.size(); i++) {
    result += a[i] * b[i];
  }

  return result;
}

ostream &operator<<(ostream &os, const vector &v) {
  os << "mat_lib::vector[" << v.size() << "]{";
  for (size_t i = 0; i < v.size() - 1; i++)
    os << v[i] << ", ";
  if (v.size() > 0)
    os << v[v.size() - 1];
  os << "}";
  return os;
}

} // namespace mat_lib