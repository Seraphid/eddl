/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/


#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cuda.h>

#include "gpu_nn_kernels.h"
#include "../gpu_kernels.h"


__global__ void cent(float* a, float* b, float* c, long int size)
{

 long int thread_id_x = threadIdx.x+blockIdx.x*blockDim.x;

 if (thread_id_x < size){
   c[thread_id_x]=0;
   if (a[thread_id_x]) c[thread_id_x]-=a[thread_id_x]*logf(b[thread_id_x]+0.00001);
   if (a[thread_id_x]!=1.0) c[thread_id_x]-=(1.0-a[thread_id_x])*logf(1.0-b[thread_id_x]+0.00001);
  }
}
