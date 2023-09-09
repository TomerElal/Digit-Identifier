//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
    unsigned int value;
    float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
                                    {64,  128},
                                    {20,  64},
                                    {10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
                                 {64,  1},
                                 {20,  1},
                                 {10,  1}};

/**
 * this class will run the whole network with a given weights biases and a
 * binary file which presents an img of number.
 */
class MlpNetwork {
  Matrix _weights[4];
  Matrix _biases[4];

 public:
  MlpNetwork (Matrix weights[4], Matrix biases[4]);
  digit operator() (const Matrix &m) const;
};

#endif // MLPNETWORK_H