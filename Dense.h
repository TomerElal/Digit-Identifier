#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"

class Dense {
  Matrix _weights;
  Matrix _bias;
  activation_func _activation_function;

 public:
  Dense (const Matrix &weights, const Matrix &bias, activation_func
  ActivationFunction);
  Matrix get_weights () const;
  Matrix get_bias () const;
  activation_func get_activation () const;

  Matrix operator() (const Matrix &m) const;
};

#endif //DENSE_H
