#include "Activation.h"
#include <cmath>

Matrix activation::relu (const Matrix &m)
{
  int rows = m.get_rows (), cols = m.get_cols ();
  Matrix ret (rows, cols);
  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          float coord = m (i, j);
          if (coord >= 0)
            {
              ret (i, j) = coord;
            }
          else
            {
              ret (i, j) = 0;
            }
        }
    }
  return ret;
}

Matrix activation::softmax (Matrix &m)
{
  float res = 0;
  for (int i = 0; i < m.get_rows (); i++)
    {
      for (int j = 0; j < m.get_cols (); j++)
        {
          float add = (float) std::exp (m (i, j));
          res += add;
          m (i, j) = add;
        }
    }
  return (1 / res) * m;
}