/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/

#include <cmath>
#include <limits>
#include <iostream>
#include <utility>

#include "tensor.h"
#include "../hardware/cpu/cpu_hw.h"

#ifdef cGPU
#include "../hardware/gpu/gpu_tensor.h"
#include "../hardware/gpu/gpu_hw.h"
#include "../hardware/gpu/nn/gpu_nn.h"
#endif


using namespace std;


void Tensor::shift(Tensor *A, Tensor *B, vector<int> shift, string mode, float constant){
    // shift => {y, x}
    // Parameter check
    if(::abs(shift[0]) >= A->shape[2] || ::abs(shift[1]) >= A->shape[3]){
        msg("The shift is greater than the image size", "Tensor::shift");
    }

    // Check dimensions
    if(A->shape!=B->shape){
        msg("Incompatible dimensions", "Tensor::shift");
    } else if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::shift");
    }

    if (A->isCPU()) {
        cpu_shift(A, B, std::move(shift), get_mode(std::move(mode)), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_shift(A, B, std::move(shift), get_mode(std::move(mode)), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}


void Tensor::rotate(Tensor *A, Tensor *B, float angle, vector<int> offset_center, string mode, float constant) {
    // Check dimensions
    if(A->shape!=B->shape){
        msg("Incompatible dimensions", "Tensor::rotate");
    } else if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::rotate");
    }

    if (A->isCPU()) {
        cpu_rotate(A, B, angle, std::move(offset_center), get_mode(std::move(mode)), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_rotate(A, B, angle, std::move(offset_center), get_mode(std::move(mode)), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}

void Tensor::scale(Tensor *A, Tensor *B, vector<int> new_shape, string mode, float constant) {
    // new_shape => {y, x}
    // Parameter check
    if(new_shape[0] <= 0 || new_shape[1] <= 0){
        msg("The new shape must be a greater than zero", "Tensor::scale");
    }

    // Check dimensions
    if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::scale");
    }

    if (A->isCPU()) {
        cpu_scale(A, B, std::move(new_shape), get_mode(std::move(mode)), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_scale(A, B, std::move(new_shape), get_mode(std::move(mode)), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}


void Tensor::flip(Tensor *A, Tensor *B, int axis) {
    // Parameter check
    if(axis != 0 && axis != 1){
        msg("Axis must be either 0 (vertical axis) or 1 (horizontal axis)", "Tensor::flip");
    }

    // Check dimensions
    if(A->shape!=B->shape){
        msg("Incompatible dimensions", "Tensor::flip");
    } else if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::flip");
    }

    if (A->isCPU()) {
        cpu_flip(A, B, axis);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_flip(A, B, axis);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}

void Tensor::crop(Tensor *A, Tensor *B, vector<int> coords_from, vector<int> coords_to, float constant) {
    // coords => {y, x}
    // Parameter check
    if(coords_from[0] < 0.0f || coords_from[0]>= A->shape[2] ||
       coords_from[1] < 0.0f || coords_from[1]>= A->shape[3] ||
       coords_to[0] < 0.0f || coords_to[0]>= A->shape[2] ||
       coords_to[1] < 0.0f || coords_to[1]>= A->shape[3]){
        msg("Crop coordinates must fall within the range of the tensor", "Tensor::crop");
    }

    // Check dimensions
    if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::crop");
    }

    if (A->isCPU()) {
        cpu_crop(A, B, std::move(coords_from), std::move(coords_to), constant, false);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_crop(A, B, std::move(coords_from), std::move(coords_to), constant, false);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}

void Tensor::crop_scale(Tensor *A, Tensor *B, vector<int> coords_from, vector<int> coords_to, string mode, float constant) {
    // coords => {y, x}
    // Parameter check
    if(coords_from[0] < 0.0f || coords_from[0]>= A->shape[2] ||
       coords_from[1] < 0.0f || coords_from[1]>= A->shape[3] ||
       coords_to[0] < 0.0f || coords_to[0]>= A->shape[2] ||
       coords_to[1] < 0.0f || coords_to[1]>= A->shape[3]){
       msg("Crop coordinates must fall within the range of the tensor", "Tensor::crop_scale");
    }

    // Check dimensions
    if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::crop_scale");
    }

    if (A->isCPU()) {
        cpu_crop_scale(A, B, std::move(coords_from), std::move(coords_to), get_mode(std::move(mode)), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_crop_scale(A, B, std::move(coords_from), std::move(coords_to), get_mode(std::move(mode)), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}


void Tensor::cutout(Tensor *A, Tensor *B, vector<int> coords_from, vector<int> coords_to, float constant) {
    // coords => {y, x}
    // Parameter check
    if(coords_from[0] < 0.0f || coords_from[0]>= A->shape[2] ||
       coords_from[1] < 0.0f || coords_from[1]>= A->shape[3] ||
       coords_to[0] < 0.0f || coords_to[0]>= A->shape[2] ||
       coords_to[1] < 0.0f || coords_to[1]>= A->shape[3]){
       msg("Cutout coordinates must fall within the range of the tensor", "Tensor::cutout");
    }

    // Check dimensions
    if(A->shape!=B->shape){
        msg("Incompatible dimensions", "Tensor::cutout");
    } else if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::cutout");
    }

    if (A->isCPU()) {
        cpu_crop(A, B, std::move(coords_from), std::move(coords_to), constant, true);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_crop(A, B, std::move(coords_from), std::move(coords_to), constant, true);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}




void Tensor::shift_random(Tensor *A, Tensor *B, vector<float> factor_x, vector<float> factor_y, string mode, float constant){
    // Parameter check
    if(factor_x[0] < -1.0f || factor_x[0] > 1.0f ||
       factor_x[1] < -1.0f || factor_x[1] > 1.0f ||
       factor_y[0] < -1.0f || factor_y[0] > 1.0f ||
       factor_y[1] < -1.0f || factor_y[1] > 1.0f){
        msg("The shift factors must fall within the range [-1.0, 1.0]", "Tensor::shift_random");
    }

    // Check dimensions
    if(A->shape!=B->shape){
        msg("Incompatible dimensions", "Tensor::shift_random");
    } else if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::shift_random");
    }

    if (A->isCPU()) {
        cpu_shift_random(A, B, std::move(factor_x), std::move(factor_y), get_mode(std::move(mode)), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_shift_random(A, B, std::move(factor_x), std::move(factor_y), get_mode(std::move(mode)), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}



void Tensor::rotate_random(Tensor *A, Tensor *B, vector<float> factor, vector<int> offset_center, string mode, float constant) {
    // Check dimensions
    if(A->shape!=B->shape){
        msg("Incompatible dimensions", "Tensor::rotate_random");
    } else if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::rotate_random");
    }

    if (A->isCPU()) {
        cpu_rotate_random(A, B,  std::move(factor), std::move(offset_center), get_mode(std::move(mode)), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_rotate_random(A, B,  std::move(factor), std::move(offset_center), get_mode(std::move(mode)), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}

void Tensor::scale_random(Tensor *A, Tensor *B, vector<float> factor, string mode, float constant) {
    // Parameter check
    if(factor[0] < 0.0f || factor[1] < 0.0f){
        msg("The scaling factor must be a positive number", "Tensor::scale_random");
    }

    // Check dimensions
    if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::scale_random");
    }

    if (A->isCPU()) {
        cpu_scale_random(A, B, std::move(factor), get_mode(std::move(mode)), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_scale_random(A, B, std::move(factor), get_mode(std::move(mode)), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}


void Tensor::flip_random(Tensor *A, Tensor *B, int axis) {
    // Parameter check
    if(axis != 0 && axis != 1){
        msg("The axis must be either 0 (vertical axis) or 1 (horizontal axis)", "Tensor::flip_random");
    }

    // Check dimensions
    if(A->shape!=B->shape){
        msg("Incompatible dimensions", "Tensor::flip_random");
    } else if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::flip_random");
    }

    if (A->isCPU()) {
        cpu_flip_random(A, B, axis);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_flip_random(A, B, axis);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}

void Tensor::crop_random(Tensor *A, Tensor *B) {
    // Check dimensions
    if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::crop_random");
    }

    if (A->isCPU()) {
        cpu_crop_random(A, B);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_crop_random(A, B);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}

void Tensor::crop_scale_random(Tensor *A, Tensor *B, vector<float> factor, string mode, float constant) {
    // Parameter check
    if(factor[0] < 0.0f || factor[0] > 1.0f ||
       factor[1] < 0.0f || factor[1] > 1.0f){
       msg("The crop factor must fall within the range [0.0, 1.0]", "Tensor::crop_scale_random");
    }

    // Check dimensions
    if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::crop_scale_random");
    }

    if (A->isCPU()) {
        cpu_crop_scale_random(A, B, std::move(factor), get_mode(std::move(mode)), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_crop_scale_random(A, B, std::move(factor), get_mode(std::move(mode)), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}

void Tensor::cutout_random(Tensor *A, Tensor *B, vector<float> factor_x, vector<float> factor_y, float constant) {
    // Parameter check
    if(factor_x[0] < 0.0f || factor_x[0] > 1.0f ||
       factor_x[1] < 0.0f || factor_x[1] > 1.0f ||
       factor_y[0] < 0.0f || factor_y[0] > 1.0f ||
       factor_y[1] < 0.0f || factor_y[1] > 1.0f){
       msg("The cutout factors must fall within the range [0.0, 1.0]", "Tensor::cutout_random");
    }

    // Check dimensions
    if(A->shape!=B->shape){
        msg("Incompatible dimensions", "Tensor::cutout_random");
    } else if (A->ndim != 4 || B->ndim != 4){
        msg("This method requires two 4D tensors", "Tensor::cutout_random");
    }

    if (A->isCPU()) {
        cpu_cutout_random(A, B, std::move(factor_x), std::move(factor_y), constant);
    }
#ifdef cGPU
    else if (A->isGPU())
      {
        gpu_cutout_random(A, B, std::move(factor_x), std::move(factor_y), constant);
      }
#endif
#ifdef cFPGA
    else {

    }
#endif
}
