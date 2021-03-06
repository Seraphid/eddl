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
//
//__device__ float get_pixel(int b,int px,int py,int pz, int ircd, int irc, int irows, int icols, float* I){
//    if (px < 0) return 0.0;
//    else if (py < 0) return 0.0;
//    else if (px >= icols) return 0.0;
//    else if (py >= irows) return 0.0;
//    else {
//        int ptr = (b * ircd) + (pz * irc) + (py * icols) + px;
//        return I[ptr];
//    }
//}
//
//__device__ void add_pixel(int b,int px,int py,int pz, int ircd, int irc, int irows, int icols, float* ID, float val) {
//    if (px < 0) return;
//    else if (py < 0) return;
//    else if (px >= icols) return;
//    else if (py >= irows) return;
//    else {
//        int ptr = (b * ircd) + (pz * irc) + (py * icols) + px;
//        ID[ptr] += val;
//    }
//}


// MaxPool
__global__ void maxpool2d(float* I, int batch,int irows,int icols, int idepth, int kr,int kc, float* O,int orows,int ocols, int odepth, int sr,int sc,int padrt, int padrb,int padcl, int padcr,float* indX, float* indY) {

    long int ops = batch * orows * ocols * odepth;
    long int thread_id_x = blockDim.x * blockIdx.x + threadIdx.x;

    if (thread_id_x < ops) {
        // output pixel at batch=ob, coord=(or,oc) at map=oz
        int orcd=orows*ocols*odepth; // out size of batch
        int orc=orows*ocols;  // out size of slice
        int ob=thread_id_x/orcd; // current batch (ib=ob)
        int bm=thread_id_x%orcd; // index in batch
        int ouz=bm/orc; // out depth (iuz=ouz)
        int our=(bm%orc)/ocols; // out row
        int ouc=(bm%orc)%ocols; // out col

        int inr = our * sr;  // in row
        int inc = ouc * sc;  // in col
        int ircd=irows*icols*idepth; // in size of batch
        int irc=irows*icols;  // in size of batch

        int min_i = -padrt;
        int max_i = irows+padrt-kr;
        int i = min_i + inr;  // row

        int min_j = -padcl;
        int max_j = icols+padcl-kc;
        int j = min_j + inc;  // column

        int b = ob;  // batch
        int k = ouz;  // depth
        int p = thread_id_x;  // index

        // Check bounds
        if (i <= max_i && j <= max_j){

            float max = GPU_MIN_FLOAT;
            //float max = I[i,j];
            for (int ki = 0; ki < kr; ki++)  // kernel_rows
                for (int kj = 0; kj < kc; kj++) {  // kernel_cols

                    // Get pixel
                    int px = j + kj;
                    int py = i + ki;
                    int pz = k;
                    float v = 0.0;

                    if (px < 0) v = 0.0;
                    else if (py < 0) v = 0.0;
                    else if (px >= icols) v = 0.0;
                    else if (py >= irows) v = 0.0;
                    else {
                        int ptr = (b * ircd) + (pz * irc) + (py * icols) + px;
                        v = I[ptr];
                    }

                    if (v > max) {
                        max = v;
                        indX[p] = j + kj;
                        indY[p] = i + ki;
                    }
                }
            O[p] = max;
        }
    }

}

__global__ void maxpool2d_back(float* D, float* ID, int batch, int irows, int icols, int orows, int ocols, int depth, float* indX, float* indY)
{
    int size=orows * ocols * depth;
    int rsize=orows * ocols;

    int isize = irows *icols * depth;
    int irsize = irows *icols;

    long int ops = batch * size;
    long int thread_id_x = blockDim.x * blockIdx.x + threadIdx.x;

    if (thread_id_x < ops) {

        int b=thread_id_x/size; // current batch (ib=ob)
        int bm=thread_id_x%size; // index in batch
        int z=bm/rsize; // out depth (iuz=ouz)

        int p = thread_id_x;  // index

        // Check bounds
        int px=indX[p];
        int py=indY[p];
        int pz=z;

        p=(b*isize)+(pz*irsize)+(py*icols)+px;
        ID[p]+=D[thread_id_x]; // +val
    }
}

//
//// AvgPool
//// TODO: [Temp!] Review not tested
__global__ void avgpool2d(float* I, int batch,int irows,int icols, int idepth, int kr,int kc, float* O,int orows,int ocols, int odepth, int sr,int sc,int padrt, int padrb,int padcl, int padcr,float* indX, float* indY) {
//
//    long int ops = batch * orows * ocols * odepth;
//    long int thread_id_x = blockDim.x * blockIdx.x + threadIdx.x;
//
//    if (thread_id_x < ops) {
//        // output pixel at batch=ob, coord=(or,oc) at map=oz
//        int orcd=orows*ocols*odepth; // out size of batch
//        int orc=orows*ocols;  // out size of slice
//        int ob=thread_id_x/orcd; // current batch (ib=ob)
//        int bm=thread_id_x%orcd; // index in batch
//        int ouz=bm/orc; // out depth (iuz=ouz)
//        int our=(bm%orc)/ocols; // out row
//        int ouc=(bm%orc)%ocols; // out col
//
//        int inr = our * sr;  // in row
//        int inc = ouc * sc;  // in col
//        int ircd=irows*icols*idepth; // in size of batch
//        int irc=irows*icols;  // in size of batch
//
//        int min_i = -padrt;
//        int max_i = irows+padrt-kr;
//        int i = min_i + inr;  // row
//
//        int min_j = -padcl;
//        int max_j = icols+padcl-kc;
//        int j = min_j + inc;  // column
//
//        int b = ob;  // batch
//        int k = ouz;  // depth
//        int p = thread_id_x;  // index
//
//        // Check bounds
//        if (i <= max_i && j <= max_j){
//
//            float sum = 0.0f;
//            //float max = I[i,j];
//            for (int ki = 0; ki < kr; ki++)  // kernel_rows
//                for (int kj = 0; kj < kc; kj++) {  // kernel_cols
//
//                    // Get pixel
//                    int px = j + kj;
//                    int py = i + ki;
//                    int pz = k;
//                    float v = 0.0;
//
//                    if (px < 0) v = 0.0;
//                    else if (py < 0) v = 0.0;
//                    else if (px >= icols) v = 0.0;
//                    else if (py >= irows) v = 0.0;
//                    else {
//                        int ptr = (b * ircd) + (pz * irc) + (py * icols) + px;
//                        v = I[ptr];
//                    }
//
//                    sum+=v;
//                }
//            O[p] = sum;
//        }
//    }
//
}
//
//// TODO: [Temp!] Review not tested
__global__ void avgpool2d_back(float* D, float* ID, int batch, int irows, int icols, int orows, int ocols, int depth, float* indX, float* indY)
{
//    int size=orows * ocols * depth;
//    int rsize=orows * ocols;
//
//    int isize = irows *icols * depth;
//    int irsize = irows *icols;
//
//    long int ops = batch * size;
//    long int thread_id_x = blockDim.x * blockIdx.x + threadIdx.x;
//
//    if (thread_id_x < ops) {
//
//        int b=thread_id_x/size; // current batch (ib=ob)
//        int bm=thread_id_x%size; // index in batch
//        int z=bm/rsize; // out depth (iuz=ouz)
//
//        int p = thread_id_x;  // index
//
//        // Check bounds
//        int px=indX[p];
//        int py=indY[p];
//        int pz=z;
//
//        p=(b*isize)+(pz*irsize)+(py*icols)+px;
//
//
//        // TODO: Implement
//
//
//    }
}