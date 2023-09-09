// Matrix.h
#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims {
    int rows, cols;
} matrix_dims;

/**
 * @struct matrix
 * @brief Matrix with various functions and methods. more details in matrix.cpp
 */
class Matrix {
  int _rows;
  int _cols;
  float **_matrix;

 public:
  Matrix (int rows, int cols);
  Matrix () : Matrix (1, 1)
  {}
  Matrix (const Matrix &m);
  ~Matrix ();
  int get_rows () const
  { return _rows; }
  int get_cols () const
  { return _cols; }
  Matrix &transpose ();
  void plain_print () const;
  Matrix &vectorize ();
  Matrix dot (const Matrix &m) const;
  Matrix &operator= (const Matrix &m);
  Matrix &operator+= (const Matrix &m);
  float &operator() (unsigned short r_coord, unsigned short c_coord);
  float &operator[] (int coord);
  const float &operator() (unsigned short r_coord, unsigned short c_coord)
  const;
  const float &operator[] (unsigned short coord) const;
  float norm () const;

  friend Matrix operator+ (const Matrix &a, const Matrix &b);
  friend Matrix operator* (const Matrix &a, const Matrix &b);
  friend Matrix operator* (const Matrix &m, float c);
  friend Matrix operator* (float c, const Matrix &m);
  friend std::ostream &operator<< (std::ostream &s, const Matrix &m);
  friend std::istream &operator>> (std::istream &s, Matrix &m);

};

#endif //MATRIX_H