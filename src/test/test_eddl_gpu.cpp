// This file is part of EDDLL an European Distributed Deep Learning Library.
// Developed within the DeepHealth project.
// Boosting AI in Europe.
//
// The MIT License (MIT)
//
// Copyright (c) 2019 Roberto Paredes Palacios, <rparedes@dsic.upv.es>

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

//#include "../tensor.h"
#include "../layer.h"
//#include "../tensor_over.h"

//#define tensor_sum tensor::sum

int main(int argc, char **argv)
{
  Tensor *A=new Tensor({7,1},DEV_GPU);
  A->rand();
  A->info();
  A->print();

  Tensor *C=new Tensor({7,5},DEV_GPU);
  C->rand();
  C->info();
  C->print();

  Tensor *C2=new Tensor({2,5,3,7,10,20},DEV_GPU);
  C2->info();
  /////////////////////////////////////////////////


  Input *I=new Input(C,"in1",DEV_GPU);
  I->info();

  Dense *D=new Dense(I,128,"dense1",DEV_GPU);
  Dense *E=new Dense(D,256,DEV_GPU);

  D->info();
  E->info();

  D->forward();
  D->backward();

  //Add *ad=new Add({D,E},"add1");

  //Layer *a=tensor_sum(tensor_sum(D,D),tensor_sum(D,D));





}


















  ///////////