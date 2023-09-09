#include "MlpNetwork.h"
#include <iostream>

/**
 * function to ind the highest value in a matrix's elements
 * @param m matrix
 * @return the highest value and in location of this value
 */
std::pair<unsigned int, float> mat_max_val (Matrix &m)
{
  float max_val = 0;
  unsigned int index = 0;
  for (int i = 0; i < m.get_rows (); i++)
    {
      for (int j = 0; j < m.get_cols (); j++)
        {
          if (m (i, j) > max_val)
            {
              max_val = m (i, j);
              index = (i * m.get_cols ()) + j;
            }
        }
    }
  std::pair<unsigned int, float> pair = {index, max_val};
  return pair;
}

/**
 * this operation will run the whole program in order to find out which
 * number is presented in the img
 * @param m the matrix which represents the img with a number
 * @return
 */
digit MlpNetwork::operator() (const Matrix &m) const
{
  Dense first_dense (_weights[0], _biases[0], reinterpret_cast<activation_func>(activation::relu));
  Matrix res1 = first_dense (m);
  for (int i = 1; i < 3; i++)
    {
      Dense d23 (_weights[i], _biases[i], reinterpret_cast<activation_func>(activation::relu));
      Matrix res23 = d23 (res1);
      res1 = res23;
    }
  Dense last (_weights[3], _biases[3], activation::softmax);
  Matrix last_res = last (res1);
  std::pair<unsigned int, float> max_val = mat_max_val (last_res);
  digit dig = {max_val.first, max_val.second};
  return dig;
}

/**
 * constructor to initiate the weights and biases
 */
MlpNetwork::MlpNetwork (Matrix *weights, Matrix *biases)
{
  for (int i = 0; i < 4; i++)
    {
      _weights[i] = weights[i];
      _biases[i] = biases[i];
    }
}
