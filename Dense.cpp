#include "Dense.h"

Dense::Dense (const Matrix &weights, const Matrix &bias, activation_func
ActivationFunction)
{
  _weights = weights;
  _bias = bias;
  _activation_function = ActivationFunction;
}

Matrix Dense::get_weights () const
{
  return _weights;
}

Matrix Dense::get_bias () const
{
  return _bias;
}

activation_func Dense::get_activation () const
{
  return _activation_function;
}

Matrix Dense::operator() (const Matrix &m) const
{
  Matrix ret = (_weights * m) + _bias;
  return _activation_function (ret);
}
