#include "Matrix.h"
#include <cmath>
#include <iostream>

#define SIZE_ERROR "matrix's sizes are not fit to elementwise multiplication"
#define INDEX_ERROR "error trying to access index that is not in matrix range"
#define BAD_ARGUMENTS "number of rows or columns is invalid"
#define STREAM_SIZE_ERROR "the given stream do not fit the matrix sizes"
#define MIN 0.1
#define RUN_ERROR "error with input stream"
/**
 * receives a row in the matrix and initiates all it's values to zero
 * @param array is a row in the matrix
 * @param size the number of columns in matrix
 */
void zero_initiate (float *array, int size)
{
  for (int i = 0; i < size; i++)
    {
      array[i] = 0;
    }
}

/**
 *
 * @param m1 zero initiated matrix to input in it's values the multiplied
 * matrix m2 by the scalar c
 * @param m2 the matrix to be multiplied by c scalar
 * @param c the scalar
 * @param rows num of rows in m2
 * @param cols num of cols in m1
 */
void
scalar_multiply (float **m1, const float **m2, float c, int rows, int cols)
{
  for (int i = 0; i < rows; ++i)
    {
      for (int j = 0; j < cols; j++)
        {
          m1[i][j] = m2[i][j] * c;
        }
    }
}

/**
 *
 * @param matrix to delete
 * @param rows num of rows in the matrix
 * @param cols num of cols in the matrix
 */
void delete_matrix (float **matrix, int num_of_rows)
{
  for (int i = 0; i < num_of_rows; i++)
    {
      delete[] matrix[i];
    }
  delete[] matrix;
}

/**
 *
 * @param m_1 matrix to fill
 * @param m_2 matrix to copy from
 * @param rows of m1 (and m2)
 * @param cols of m1 (and m2)
 */
void copy_matrix_content (float **m_1, const float **m_2, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          m_1[i][j] = m_2[i][j];
        }
    }
}

/**
 *
 * @param m_1 the matrix to be the transpose of m2
 * @param m_2 matrix to transpose
 * @param rows of m1 (or m2)
 * @param cols of m1 (or m2)
 */
void copy_transposed_mat (float **m_1, const float **m_2, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          m_1[i][j] = m_2[j][i];
        }
    }
}

/**
 * allocates the inner dimension of a two dimensional matrix
 * @param matrix the outer dimension of the matrix. a pointer.
 * @param rows number of rows in matrix
 * @param cols number of cols in matrix
 * @return the allocated matrix in case of success
 */
float **allocate_matrix (float **matrix, int rows, int cols)
{
  for (int i = 0; i < rows; i++)
    {
      matrix[i] = new float[cols];
      if (!matrix[i])
        {
          delete_matrix (matrix, i);
        }
      zero_initiate (matrix[i], cols);
    }
  return matrix;
}

/**
 * constructor to allocate rows*cols matrix with zeros initiated in it's values
 * two dimensional metrix
 * @param rows num of rows to allocate
 * @param cols num of cols to allocate
 */
Matrix::Matrix (int rows, int cols)
{
  if (rows <= 0 || cols <= 0)
    {
      throw (std::length_error) BAD_ARGUMENTS;
    }
  _rows = rows;
  _cols = cols;
  _matrix = new float *[rows];
  _matrix = allocate_matrix (_matrix, _rows, _cols);
}

/**
 * copy constructor
 * @param m matrix to copy from
 */
Matrix::Matrix (const Matrix &m) : Matrix (m._rows, m._cols)
{
  copy_matrix_content (_matrix, (const float **) m._matrix, m._rows, m._cols);
}

/**
 * destructor.
 * delete matrix is the function which delete the allocated memory of *this.
 */
Matrix::~Matrix ()
{
  delete_matrix (_matrix, _rows);
}

/**
 * transposes *this matrix
 * @return the transposed *this matrix
 */
Matrix &Matrix::transpose ()
{
  int tmp_rows = _rows;
  _rows = _cols;
  _cols = tmp_rows;
  auto **temp = new float *[_rows];
  allocate_matrix (temp, _rows, _cols);
  copy_transposed_mat (temp, (const float **) _matrix, _rows, _cols);
  delete_matrix (_matrix, _cols);
  _matrix = new float *[_rows];
  allocate_matrix (_matrix, _rows, _cols);
  copy_matrix_content (_matrix, (const float **) temp, _rows, _cols);
  delete_matrix (temp, _rows);
  return *this;
}

/**
 * prints the matrix row after row in right to left order
 */
void Matrix::plain_print () const
{
  for (int i = 0; i < _rows; i++)
    {
      for (int j = 0; j < _cols; j++)
        {
          std::cout << _matrix[i][j] << " ";
        }
      std::cout << std::endl;
    }
}

/**
 * Transforms a matrix into a column vector.
 * Supports function calling concatenation.
 * @return the matrix by a column vector
 */
Matrix &Matrix::vectorize ()
{
  auto **temp = new float *[_rows * _cols];
  allocate_matrix (temp, _rows * _cols, 1);
  for (int i = 0; i < _rows; ++i)
    {
      for (int j = 0; j < _cols; ++j)
        {
          temp[i * _cols + j][0] = _matrix[i][j];
        }
    }
  delete_matrix (_matrix, _rows);
  _rows = _cols * _rows;
  _cols = 1;
  _matrix = temp;
  return *this;
}

/**
 * Returns a matrix which is the elementwise
   multiplication(Hadamard product) of this matrix and
   another matrix m:
   ∀i, j : (A.dot(B))ij = Aij · Bij
 * @param m the other matrix to elementwise multiply with *this matrix
 * @return the Hadamard product
 */
Matrix Matrix::dot (const Matrix &m) const
{
  if (_rows != m._rows || _cols != m._cols)
    {
      throw (std::length_error) SIZE_ERROR;
    }
  Matrix new_mat (_rows, _cols);
  for (int i = 0; i < _rows; i++)
    {
      for (int j = 0; j < _cols; j++)
        {
          new_mat._matrix[i][j] = _matrix[i][j] * m._matrix[i][j];
        }
    }
  return new_mat;
}

/**
 * @return the Frobenius norm of the given matrix
 */
float Matrix::norm () const
{
  float ret = 0;
  for (int i = 0; i < _rows; i++)
    {
      for (int j = 0; j < _cols; j++)
        {
          ret += _matrix[i][j] * _matrix[i][j];
        }
    }
  return std::sqrt (ret);
}

/**
 * assigment operator
 * @param m is the matrix that will be assigned in *this matrix
 * @return *this matrix
 */
Matrix &Matrix::operator= (const Matrix &m)
{
  if (this == &m)
    {
      return *this;
    }
  delete_matrix (_matrix, _rows);
  _rows = m._rows;
  _cols = m._cols;
  _matrix = new float *[_rows];
  allocate_matrix (_matrix, _rows, _cols);
  copy_matrix_content (_matrix, (const float **) m._matrix, _rows, _cols);
  return *this;
}

/**
 * @param a matrix
 * @param b matrix
 * @returns the addition of a matrix and b matrix
 */
Matrix operator+ (const Matrix &a, const Matrix &b)
{
  if (a._rows != b._rows || a._cols != b._cols)
    {
      throw (std::length_error) SIZE_ERROR;
    }
  Matrix summed_mat (a._rows, a._cols);
  for (int i = 0; i < a._rows; i++)
    {
      for (int j = 0; j < a._cols; j++)
        {
          summed_mat._matrix[i][j] = a._matrix[i][j] + b._matrix[i][j];
        }
    }
  return summed_mat;
}

/**
 * Regular multiplication of two matrices.
 * multiply a single row in matrix a with a single col in matrix b
 * @param a matrix
 * @param b matrix
 * @param row the row in matrix a
 * @param col the col in matrix b
 * @param size num of cols in matrix a (or num of rows in matrix b)
 * @return the result of multiplication a single row in matrix a with a
   single col in matrix b
 */
float multiply_col_by_row (float **a, float **b, int row, int col, int size)
{
  float sum = 0;
  for (int i = 0; i < size; i++)
    {
      sum += a[row][i] * b[i][col];
    }
  return sum;
}

/**
 * Regular matrix multiplication
 * @param a matrix in the left side
 * @param b matrix in the right
 * @return the result of multiplication a*b
 */
Matrix operator* (const Matrix &a, const Matrix &b)
{
  if (a._cols != b._rows)
    {
      throw (std::length_error) SIZE_ERROR;
    }
  Matrix multiplied_mat (a._rows, b._cols);
  for (int i = 0; i < a._rows; i++)
    {
      for (int j = 0; j < b._cols; j++)
        {
          multiplied_mat._matrix[i][j] = multiply_col_by_row (a._matrix, b
              ._matrix, i, j, a._cols);
        }
    }
  return multiplied_mat;
}

/**
 * Scalar multiplication on the right
 * @param m matrix
 * @param c scalar
 * @return the matrix after multiplication with scalar c
 */
Matrix operator* (const Matrix &m, float c)
{
  Matrix scalar_mult_mat (m._rows, m._cols);
  scalar_multiply (scalar_mult_mat._matrix, (const float **) m._matrix, c, m
      ._rows, m._cols);
  return scalar_mult_mat;
}

/**
 * Scalar multiplication on the left
 * @param c scalar
 * @param m matrix
 * @return the matrix after multiplication with scalar c
 */
Matrix operator* (float c, const Matrix &m)
{
  Matrix scalar_mult_mat (m._rows, m._cols);
  scalar_multiply (scalar_mult_mat._matrix, (const float **) m._matrix, c, m
      ._rows, m._cols);
  return scalar_mult_mat;
}

/**
 * Matrix addition accumulation
 * @param m matrix to be addition with
 * @return *this matrix after addition with m
 */
Matrix &Matrix::operator+= (const Matrix &m)
{
  if (_rows != m._rows || _cols != m._cols)
    {
      throw (std::length_error) SIZE_ERROR;
    }
  for (int i = 0; i < _rows; i++)
    {
      for (int j = 0; j < _cols; j++)
        {
          _matrix[i][j] += m._matrix[i][j];
        }
    }
  return *this;
}

/** -----can be accessed with writing into the element-----
 * For i,j indices, Matrix m: m(i,j) will return the i,j element in the matrix
 * @param r_coord = i a.k.a the specific row coordinate in the matrix
 * @param c_coord = j a.k.a the specific col coordinate in the matrix
 * @return the i,j element in the matrix
 */
float &Matrix::operator() (const unsigned short r_coord, const unsigned
short c_coord)
{
  if (r_coord >= _rows || c_coord >= _cols)
    {
      throw (std::out_of_range) INDEX_ERROR;
    }
  return _matrix[r_coord][c_coord];
}

/** -----can be accessed with writing into the element-----
 * For i index, Matrix m: m[i] will return the i'th element
 * @param coord the i'th element
 * @return the value in the i'th element
 */
float &Matrix::operator[] (const int coord)
{
  if (coord >= (_rows * _cols))
    {
      throw (std::out_of_range) INDEX_ERROR;
    }
  unsigned int col = coord % _cols; // math calculate in order to find the
  unsigned int row = (coord - col) / _cols; // .. element in the 2-dim matrix
  return _matrix[row][col];
}

/** -----can only be accessed with reading the element-----
 * For i,j indices, Matrix m: m(i,j) will return the i,j element in the matrix
 * @param r_coord = i a.k.a the specific row coordinate in the matrix
 * @param c_coord = j a.k.a the specific col coordinate in the matrix
 * @return the i,j element in the matrix
 */
const float &Matrix::operator() (const unsigned short r_coord, const unsigned
short c_coord) const
{
  if (r_coord >= _rows || c_coord >= _cols)
    {
      throw (std::out_of_range) INDEX_ERROR;
    }
  return _matrix[r_coord][c_coord];
}

/** -----can only be accessed with reading the element-----
 * For i index, Matrix m: m[i] will return the i'th element
 * @param coord the i'th element
 * @return the value in the i'th element
 */
const float &Matrix::operator[] (const unsigned short coord) const
{
  if (coord >= _rows * _cols)
    {
      throw (std::out_of_range) INDEX_ERROR;
    }
  int col = coord % _cols;
  int row = (coord - col) / _cols;
  return _matrix[row][col];
}

/**
 * Pretty export of matrix as per section
 * @param s stream to save the output
 * @param m matrix to print
 * @return the stream with the export of matrix
 */
std::ostream &operator<< (std::ostream &s, const Matrix &m)
{
  for (int i = 0; i < m._rows; i++)
    {
      for (int j = 0; j < m._cols; j++)
        {
          if (m._matrix[i][j] > MIN)
            {
              s << "**";
            }
          else
            {
              s << "  ";
            }
        }
      s << std::endl;
    }
  return s;
}

/**
 *Fills matrix elements: has to read input stream fully,otherwise it's an error
 * @param s stream to collect the values from
 * @param m matrix to fill
 * @return the stream
 */
std::istream &operator>> (std::istream &s, Matrix &m)
{
  if(!s)
    {
      throw std::runtime_error (RUN_ERROR);
    }
  s.seekg (0, std::istream::end);
  long length = s.tellg ();
  s.seekg (0, std::istream::beg);
  long mat_byte_size = (long int) (m.get_cols () * m.get_rows ()
                                * sizeof (float));
  if (mat_byte_size != length)
    {
      throw (std::length_error) STREAM_SIZE_ERROR;
    }
  float f = 0;
  for (int i = 0; i < m._rows * m._cols; i++)
    {
      if (s.read (reinterpret_cast<char *>(&f), sizeof (float)))
        {
          m[i] = f;
        }

    }
  return s;
}
