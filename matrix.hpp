// matrix.hpp
// author: Antonio C. Domínguez Brito <antonio.dominguez@ulpgc.es>
// creation date: september 20th 2020
// Description: This is the header file of class matrix which is a
// 2D matrix

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <initializer_list>
#include <exception>
#include <stdexcept>
#include <system_error>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>

using namespace std;

namespace mat_lib
{
  class vector;
  class matrix
  {
    public:

      using element_t=double;

      matrix() // default constructor
      : rows__{0},
        columns__{0},
        elements__{nullptr}
      {}

      matrix(size_t rows, size_t columns)
      : rows__{rows},
        columns__{columns},
        elements__{new element_t[rows*columns]}
      {}

      matrix(initializer_list<initializer_list<element_t>> init);

      matrix(initializer_list<element_t> init)
      {
        rows__=1; columns__=init.size();
        elements__=new element_t[rows__*columns__];

        for(size_t i=0; i<init.size(); i++) elements__[i]=init.begin()[i];
      }

      matrix(const matrix& m) // copy constructor
      : elements__{new element_t[m.size()]}
      { copy_elements__(m); }

      matrix(matrix&& m)// move constructor
      : rows__{m.rows__},
        columns__{m.columns__},
        elements__{m.elements__}
      {
        m.rows__=m.columns__=0;
        m.elements__=nullptr;
      }

      // constructor from a vector
      matrix(const vector& v);

      explicit matrix(const string& file_name); // constructor from a file

      ~matrix() { delete [] elements__; }

      matrix& operator=(const matrix& m) // copy assigment
      {
        if(size()!=m.size())
        {
          delete [] elements__;
          elements__=((m.size())? new element_t[m.size()]: nullptr);
        }
        copy_elements__(m);
        return *this;
      }

      matrix& operator=(matrix&& m) // move assigment
      {
        delete [] elements__;

        elements__=m.elements__;
        rows__=m.rows__; columns__=m.columns__;

        m.elements__=nullptr;
        m.rows__=m.columns__=0;

        return *this;
      }

      size_t size() const { return rows__*columns__; }
      size_t rows() const { return rows__; }
      size_t columns() const { return columns__; }

      element_t at(size_t i, size_t j) const;

      element_t* operator[](size_t i) { return &(elements__[row_offset__(i)]); }
      const element_t* operator[](size_t i) const { return &(elements__[row_offset__(i)]); }

      bool operator==(const matrix& m) const;

      matrix& operator+=(const matrix& m);
      matrix& operator-=(const matrix& m);

      matrix& operator*=(element_t scalar)
      {
        for(size_t i=0; i<rows__; i++)
          for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]*=scalar;

        return *this;
      }

      matrix& operator/=(float scalar);

      matrix make_transpose() const
      {
        matrix t(columns__,rows__);

        for(size_t i=0; i<t.rows(); i++)
          for(size_t j=0; j<t.columns(); j++)
            t[i][j]=elements__[offset__(j,i)];

        return t;
      }


      vector get_row(size_t row) const;

      vector get_column(size_t column) const;

      void save_as(const string& file_name) const;

    private:

      size_t rows__;
      size_t columns__;
      element_t* elements__;

      bool check_initilizer_list__(const initializer_list<initializer_list<element_t>>& init)
      {
        auto column_size=init.begin()[0].size();
        for(size_t i=1; i<init.size(); i++)
          if(init.begin()[i].size()!=column_size) return false;
        return true;
      }

      void copy_elements__(const matrix& m)
      {
        rows__=m.rows__; columns__=m.columns__;
        for(size_t i=0; i<rows__; i++)
          for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]=m.elements__[offset__(i,j)];
      }

      size_t row_offset__(size_t i) const { return i*columns__; }
      size_t offset__(size_t i,int j) const { return row_offset__(i)+j; }
  };

  inline matrix operator~(const matrix& m) { return m.make_transpose(); }

  inline matrix operator-(const matrix& m)
  {
    matrix r{m};

    for(size_t i=0; i<r.rows(); i++)
      for(size_t j=0; j<r.columns(); j++) r[i][j]=-m[i][j];

    return r;
  }

  matrix operator+(const matrix& a, const matrix& b);
  matrix operator-(const matrix& a, const matrix& b);

  inline matrix operator*(const matrix& m, matrix::element_t scalar)
  { matrix r{m}; r*=scalar; return r; }

  inline matrix operator*(matrix::element_t scalar, const matrix& m)
  { matrix r{m}; r*=scalar; return r; }

  inline matrix operator/(const matrix& m, matrix::element_t scalar)
  { matrix r{m}; r/=scalar; return r; }

  matrix operator*(const matrix& a, const matrix& b);

  ostream& operator<<(ostream& os, const matrix& mat);

} // namespace mat_lib

#endif //MATRIX_HPP
