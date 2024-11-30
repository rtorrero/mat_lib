// matrix.cpp
// author: Antonio C. Domínguez Brito <antonio.dominguez@ulpgc.es>
// creation date: september 20th 2020
// Description: This is the header file of class matrix which is a
// 2D matrix

#include "matrix.hpp"
#include "vector.hpp"

#define MATRIX_CPP

namespace mat_lib
{

  matrix::matrix(initializer_list<initializer_list<matrix::element_t>> init)
  {
    if(!check_initilizer_list__(init))
    {
      ostringstream str_stream;
      str_stream<<"column length mismatch! ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    rows__=init.size(); columns__=init.begin()->size();
    elements__=new element_t[rows__*columns__];

    for(size_t i=0; i<init.size(); i++)
      for(size_t j=0; j<init.begin()[i].size(); j++)
        elements__[offset__(i,j)]=init.begin()[i].begin()[j];
  }

  matrix::matrix(const string& file_name) // constructor from a file
  : rows__{0},
    columns__{0},
    elements__{nullptr}
  {
    ifstream ifs(file_name);
    if(!ifs)
    {
      ostringstream str_stream;
      str_stream<<"cannot open file \""<<file_name<<"\"! ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw logic_error(str_stream.str());
    }

    ifs>>rows__>>columns__;
    elements__=new element_t[rows__*columns__];

    for(size_t i=0; i<rows__; i++)
      for(size_t j=0; j<columns__; j++)
        ifs>>elements__[offset__(i,j)];
  }

  matrix::matrix(const vector &v)
  : rows__{1},
    columns__{v.size()},
    elements__{new element_t[rows__*columns__]}
  {
    for(size_t i=0; i<v.size(); i++) elements__[i]=v[i];
  }

  matrix::element_t matrix::at(size_t i, size_t j) const
  {
    if((i>=rows__) || (j>=columns__))
    {
      ostringstream str_stream;
      str_stream<<"out_of range exception ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw out_of_range(str_stream.str());
    }

    return elements__[offset__(i,j)];
  }


  bool matrix::operator==(const matrix& m) const
  {
    if((rows__!=m.rows()) || (columns__!=m.columns())) return false;

    for(size_t i=0; i<rows__; i++)
      for(size_t j=0; j<columns__; j++)
        if(elements__[offset__(i,j)]!=m[i][j]) return false;

    return true;
  }

  matrix& matrix::operator+=(const matrix& m)
  {
    if((rows__!=m.rows()) || (columns__!=m.columns()))
    {
      ostringstream str_stream;
      str_stream<<"size mismatch! cannot add matrices ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    for(size_t i=0; i<rows__; i++)
      for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]+=m[i][j];

    return *this;
  }

  matrix& matrix::operator-=(const matrix& m)
  {
    if((rows()!=m.rows()) || (columns()!=m.columns()))
    {
      ostringstream str_stream;
      str_stream<<"size mismatch! cannot substract matrices ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    for(size_t i=0; i<rows__; i++)
      for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]-=m[i][j];

    return *this;
  }

  matrix& matrix::operator/=(float scalar)
  {
    if(scalar==0)
    {
      ostringstream str_stream;
      str_stream<<"divide by zero! bad scalar provided ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }
    for(size_t i=0; i<rows__; i++)
      for(size_t j=0; j<columns__; j++) elements__[offset__(i,j)]/=scalar;

    return *this;
  }

  vector matrix::get_row(size_t row_index) const
  {
    if (row_index >= rows__)
    {
      ostringstream str_stream;
      str_stream << "Row index out of bounds (" << __func__ << "() in "
        << __FILE__ << ":" << __LINE__ << ")";
      throw out_of_range(str_stream.str());
    }

    vector row(columns__);
    for (size_t j = 0; j < columns__; ++j)
    {
      row[j] = elements__[offset__(row_index, j)];
    }

    return row;
  }

  vector matrix::get_column(size_t column_index) const
  {
    if (column_index >= columns__)
    {
      ostringstream str_stream;
      str_stream << "Column index out of bounds (" << __func__ << "() in "
        << __FILE__ << ":" << __LINE__ << ")";
      throw out_of_range(str_stream.str());
    }

    vector column(rows__);
    for (size_t i = 0; i < rows__; ++i)
    {
      column[i] = elements__[offset__(i, column_index)];
    }

    return column;
  }

  void matrix::save_as(const string& file_name) const
  {
    ofstream ofs(file_name);
    if(!ofs)
    {
      ostringstream str_stream;
      str_stream<<"cannot open file \""<<file_name<<"\"! ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw logic_error(str_stream.str());
    }

    ofs<<rows__<<" "<<columns__<<"\n";
    for(size_t i=0; i<rows__; i++)
    {
      for(size_t j=0; j<columns__; j++) ofs<<elements__[offset__(i,j)]<<" ";
      ofs<<"\n";
    }
  }

  matrix operator+(const matrix& a, const matrix& b)
  {
    if((a.rows()!=b.rows()) || (a.columns()!=b.columns()))
    {
      ostringstream str_stream;
      str_stream<<"size mismatch! cannot add matrices ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    matrix c{a};
    return c+=b;
  }

  matrix operator-(const matrix& a, const matrix& b)
  {
    if((a.rows()!=b.rows()) || (a.columns()!=b.columns()))
    {
      ostringstream str_stream;
      str_stream<<"size mismatch! cannot substract matrices ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    matrix c{a};
    return c-=b;
  }

  ostream& operator<<(ostream& os, const matrix& m)
  {
    static const char* prefix="  ";
    size_t i,j;

    os<<"mat_lib::matrix["<<m.rows()<<"x"<<m.columns()<<"]{";
    for(i=0; i<m.rows(); i++)
    {
      os<<"\n"<<prefix;
      for(j=0; j<m.columns()-1; j++) os<<m[i][j]<<", ";
      os<<m[i][j];
      //os<<((i==m.rows()-1)? "}":"},");
    }
    os<<"\n}";

    return os;
  }

  matrix operator*(const matrix& a, const matrix& b)
  {
    if(a.columns()!=b.rows())
    {
      ostringstream str_stream;
      str_stream<<"size mismatch! cannot multiple matrices ("
        <<__func__<<"() in "<<__FILE__<<":"<<__LINE__<<")";
      throw invalid_argument(str_stream.str());
    }

    matrix c(a.rows(),b.columns());

    for(size_t i=0; i<c.rows(); i++)
      for(size_t j=0; j<c.columns(); j++)
      {
        c[i][j]=0;
        for(size_t k=0; k<a.columns(); k++)
          c[i][j]+=a[i][k]*b[k][j];
      }

    return c;
  }

} // namespace mat_lib

