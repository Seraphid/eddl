/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/



#ifndef _TENSOR_CUDA_KERNELS_
#define _TENSOR_CUDA_KERNELS_

#include <cuda.h>

/* we need these includes for CUDA's random number stuff */
#include <curand.h>
#include <curand_kernel.h>

// GPU: Comparison

// GPU: Create
__global__ void range(float* a, float start, float step, long int size);
__global__ void eye(float* a, long int rows, long int cols, int offset);

// GPU: Core (static)
__global__ void fill(float *aptr,float *bptr,int t,int aini,int at,int bini,int bt,int tot,int inc);
__global__ void fill_(float* a, float v, long int size);
__global__ void mask(float* a, float v, long int size);
__global__ void select(float* A, float* B, int size, int* indices);
__global__ void select_back(float* A, float* B, int size, int* indices);
__global__ void set_select(float* A, float* B, int size, int* indices);
__global__ void set_select_back(float* A, float* B, int size, int* indices);
__global__ void concat(float *dest, float *src, unsigned int src_size, unsigned int src_stride, unsigned int dest_stride, bool derivative);

// GPU: Transformations
__global__ void shift(float* A, float* B, int batch, int depth, int irows, int icols, int* shift, int mode, float constant);
__global__ void rotate(float* A, float* B, int batch, int depth, int irows, int icols, float angle_rad, int* center, int mode, float constant);
__global__ void scale(float* A, float* B, int batch, int depth, int irows, int icols, int orows, int ocols, int* new_shape, int mode, float constant);
__global__ void flip(float* A, float* B, int batch, int depth, int irows, int icols, int axis);
__global__ void crop(float* A, float* B, int batch, int depth, int irows, int icols, int orows, int ocols, int* coords_from, int* coords_to, int* offsets, float constant, bool inverse);
__global__ void crop_scale(float* A, float* B, int batch, int depth, int irows, int icols, int orows, int ocols, int* coords_from, int* coords_to, int mode, float constant);

// GPU: Data augmentation
__global__ void shift_random(float* A, float* B, int batch, int depth, int irows, int icols, float* factor_x, float* factor_y, int mode, float constant, float* rnd);
__global__ void rotate_random(float* A, float* B, int batch, int depth, int irows, int icols, float* factor, int* offset_center, int mode, float constant, float* rnd);
__global__ void scale_random(float* A, float* B, int batch, int depth, int irows, int icols, int orows, int ocols, float* factor, int mode, float constant, float* rnd);
__global__ void flip_random(float* A, float* B, int batch, int depth, int irows, int icols, int axis, float* rnd);
__global__ void crop_random(float* A, float* B, int batch, int depth, int irows, int icols, int orows, int ocols, float* rnd);
__global__ void crop_scale_random(float* A, float* B, int batch, int depth, int irows, int icols, int orows, int ocols, float* factor, int mode, float constant, float* rnd);
__global__ void cutout_random(float* A, float* B, int batch, int depth, int irows, int icols, int orows, int ocols, float* factor_x, float* factor_y, float constant, float* rnd);

// GPU: Generator
__global__ void init(unsigned int seed, curandState_t* states);
__global__ void random_uniform(curandState_t* states, float* numbers);

// GPU: Math (in-place)
__global__ void abs_(float* a, long int size);
__global__ void acos_(float* a, long int size);
__global__ void add_(float* a, long int size, float v);
__global__ void asin_(float* a, long int size);
__global__ void atan_(float* a, long int size);
__global__ void ceil_(float* a, long int size);
__global__ void clamp_(float* a, long int size, float min, float max);
__global__ void cos_(float* a, long int size);
__global__ void cosh_(float* a, long int size);
__global__ void exp_(float* a, long int size);
__global__ void floor_(float* a, long int size);
__global__ void log_(float* a, long int size);
__global__ void log2_(float* a, long int size);
__global__ void log10_(float* a, long int size);
__global__ void logn_(float* a, long int size, float n);
__global__ void mod_(float* a, long int size, float v);
__global__ void inv_(float* a, float v, long int size);
__global__ void mult_(float* a, long int size, float v);
__global__ void normalize_(float* a, long int size, float min_ori, float max_ori, float min, float max);
__global__ void pow_(float* a, long int size, float exp);
__global__ void powb_(float* a, long int size, float base);
__global__ void reciprocal_(float* a, long int size);
__global__ void remainder_(float* a, long int size, float v);
__global__ void round_(float* a, long int size);
__global__ void rsqrt_(float* a, long int size);
__global__ void sigmoid_(float* a, long int size);
__global__ void sign_(float* a, long int size);
__global__ void sin_(float* a, long int size);
__global__ void sinh_(float* a, long int size);
__global__ void sqr_(float* a, long int size);
__global__ void sqrt_(float* a, long int size);
__global__ void tan_(float* a, long int size);
__global__ void tanh_(float* a, long int size);
__global__ void trunc_(float* a, long int size);

// GPU: Math (static)
__global__ void addc(float scA,float* a,float scB,float *b, float *c,long int incC, long int size);
__global__ void el_mult(float* a,float *b, float *c, long int incC, long int size);
__global__ void el_div(float* a, float *b, float *c, long int incC, long int size);
__global__ void sum_mat_row(float* a, float* b, float* c, long int cols, long int rows);
__global__ void sum_mat_col(float* a, float* b, float* c, long int cols, long int rows);

// GPU: Should be reductions

// GPU: Reduction
__global__ void reduce_sum2D(float *a,float *b,long int r,long int c,long int axis);

__global__ void reduce_mean(float *A,float *B,int *map,int size);
__global__ void reduce_op_sum(float *A,float *B,int *map,int size);
__global__ void reduce_op_diff(float *A,float *B,int *map,int size);
__global__ void reduce_op_mult(float *A,float *B,int *map,int size);
__global__ void reduce_op_div(float *A,float *B,int *map,int size);

__global__ void reduction_kernel(float *I,float *O,float *S,int m, int keepdims,int d,int *ind,int rs);
__global__ void reduction_back_kernel(float *I,float *O,float *S,int m, int keepdims,int d,int *ind,int rs);

__global__ void reduction_permute(float *I,float *O,int *ind,int size);
__global__ void reduction_kernel_keep(float *r, float *I, int *ind, int size, int rsize);
__global__ void reduction_kernel_keep_inc(float *r, float *I, int *ind, int size, int rsize);

__global__ void reduction_kernel_sum(float *I,float *O,int m, int d,int *ind,int rs);


// GPU: Truth value testing
__global__ void glogical_all(float *A, int size, bool &result);
__global__ void glogical_any(float *A, int size, bool &result);

// GPU: Logic functions: Comparisons
__global__ void gpu_isfinite(float *A, float *B, int size);
__global__ void gpu_isinf(float *A, float *B, int size);
__global__ void gpu_isnan(float *A, float *B, int size);
__global__ void gpu_isneginf(float *A, float *B, int size);
__global__ void gpu_isposinf(float *A, float *B, int size);

// GPU: Logic functions: Comparisons
__global__ void glogical_and(float *A, float *B, float *C, int size);
__global__ void glogical_or(float *A, float *B, float *C, int size);
__global__ void glogical_not(float *A, float *B, int size);
__global__ void glogical_xor(float *A, float *B, float *C, int size);

// GPU: Logic operations: Comparison ops
__global__ void glogical_allclose(float *A, float *B, float rtol, float atol, bool equal_nan, int size, bool &close);
__global__ void glogical_isclose(float *A, float *B, float *C, float rtol, float atol, bool equal_nan, int size);
__global__ void glogical_greater(float *A, float *B, float *C, int size);
__global__ void glogical_greater_equal(float *A, float *B, float *C, int size);
__global__ void glogical_less(float *A, float *B, float *C, int size);
__global__ void glogical_less_equal(float *A, float *B, float *C, int size);
__global__ void glogical_equal(float *A, float *B, float *C, int size);
__global__ void glogical_not_equal(float *A, float *B, float *C, int size);



#endif
