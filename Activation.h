#include "Matrix.h"

#ifndef ACTIVATION_H
#define ACTIVATION_H

typedef Matrix (*activation_func) (Matrix &);

namespace activation
{
    Matrix relu (const Matrix &m) ;
    Matrix softmax (Matrix &m);
}
#endif //ACTIVATION_H