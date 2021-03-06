/*
* EDDL Library - European Distributed Deep Learning Library.
* Version: 0.3
* copyright (c) 2019, Universidad Politécnica de Valencia (UPV), PRHLT Research Centre
* Date: October 2019
* Author: PRHLT Research Centre, UPV, (rparedes@prhlt.upv.es), (jon@prhlt.upv.es)
* All rights reserved
*/

#include <iostream>
#include <stdio.h>
#include <string>

#include "tensor/tensor.h"
#include "dev/aux_tests.h"
#include "utils.h"

using namespace std;


int total_ok = 0;
int total_errors = 0;

void pretty_res(string text, bool res, string extra=""){
    cout << "===================" << endl;
    cout << text << ": ";
    if(res){
        total_ok += 1;
        cout << "OK!";
    }else{
        total_errors += 1;
        cout << "FAILED!";
    }
    cout << extra << endl;
    cout << "===================" << endl;
}

void print_cpu_gpu_correctness(string title, Tensor* t_cpu, Tensor* t_gpu, float epsilon=0.01f){
    pretty_res(title + " small (CPU==GPU correctness)", check_tensors(t_cpu, t_gpu, epsilon));
}

void print_results_ref(string title, TestResult res_small_cpu, TestResult res_small_gpu, Tensor* t_sol, float epsilon=0.01f){
    pretty_res(title + " small (CPU correctness)", check_tensors(res_small_cpu.tensor, t_sol, epsilon));
    pretty_res(title + " small (GPU correctness)", check_tensors(res_small_gpu.tensor, t_sol, epsilon));
    print_cpu_gpu_correctness(title, res_small_cpu.tensor, res_small_gpu.tensor, epsilon);
}

void print_results(string title, TestResult res_cpu, TestResult res_gpu){
    // Check correctness with solution
    pretty_res(title + " (CPU==GPU correctness)", check_tensors(res_cpu.tensor, res_gpu.tensor));
    pretty_res(title + " (GPU << CPU: x" + std::to_string(res_cpu.time/res_gpu.time) + ")", res_gpu.time<res_cpu.time,
               "\n\t- CPU time: " + std::to_string(res_cpu.time) +
               "\n\t- GPU time: " + std::to_string(res_gpu.time));
}

int main(int argc, char **argv) {
    TestResult res_small_cpu, res_small_gpu, res_big_cpu, res_big_gpu;
    Tensor *t_input, *t_input_sol, *t_weights, *t_input_big, *t_weights_big, *t_output, *t_aux;
    Tensor *t_input_cpu, *t_input_gpu;
    string act;

//    // *** [MAXPOOL] *****************************************
//    // Data =================================
//    float mpool_input[16] = {12.0, 20.0, 30.0, 0.0,
//                             8.0, 12.0, 2.0, 0.0,
//                             34.0, 70.0, 37.0, 4.0,
//                             112.0, 100.0, 25.0, 12.0};
//    float mpool_sol[4] = {20.0, 30.0,
//                          112.0, 37.0};
//    t_input = new Tensor({1, 1, 4, 4}, mpool_input, DEV_CPU);
//    t_input_sol = new Tensor({1, 1, 2, 2}, mpool_sol, DEV_CPU);
//    t_input_big = Tensor::randn({1, 1, 1000, 1000}, DEV_CPU);
//
//    res_small_cpu = run_mpool(t_input, DEV_CPU, 1);
//    res_small_gpu = run_mpool(t_input, DEV_GPU, 1);
//    res_big_cpu = run_mpool(t_input_big, DEV_CPU, 1);
//    res_big_gpu = run_mpool(t_input_big, DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("MaxPool2D", res_small_cpu, res_small_gpu, t_input_sol);
//    print_results("[Big] MaxPool2D", res_big_cpu, res_big_gpu);
//
//
//    // *** [CONV2D] *****************************************
//    // Data =================================
//    float conv2d_input[25] = {3.0, 3.0, 2.0, 1.0, 0.0,
//                              0.0, 0.0, 1.0, 3.0, 1.0,
//                              3.0, 1.0, 2.0, 2.0, 3.0,
//                              2.0, 0.0, 0.0, 2.0, 2.0,
//                              2.0, 0.0, 0.0, 0.0, 1.0};
//    float conv2d_kernel[9] = {0.0, 1.0, 2.0,
//                              2.0, 2.0, 0.0,
//                              0.0, 1.0, 2.0};
//    float conv2d_sol[9] = {12.0, 12.0, 17.0,
//                           10.0, 17.0, 19.0,
//                           9.0, 6.0, 14.0};
//    t_input = new Tensor({1, 1, 5, 5}, conv2d_input, DEV_CPU);
//    Tensor *t_conv2d_kernel = new Tensor({1, 1, 3, 3}, conv2d_kernel, DEV_CPU);
//    t_input_sol = new Tensor({1, 1, 3, 3}, conv2d_sol, DEV_CPU);
//    t_input_big =  Tensor::randn({1, 128, 100, 100}, DEV_CPU);
//    Tensor *t_conv2d_kernel_big = Tensor::randn({128, 512, 3, 3}, DEV_CPU);
//
//
//    res_small_cpu = run_conv2d(t_input, t_conv2d_kernel, DEV_CPU, 1);
//    res_small_gpu = run_conv2d(t_input, t_conv2d_kernel, DEV_GPU, 1);
//    res_big_cpu = run_conv2d(t_input_big, t_conv2d_kernel_big, DEV_CPU, 1);
//    res_big_gpu = run_conv2d(t_input_big, t_conv2d_kernel_big, DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Conv2D", res_small_cpu, res_small_gpu, t_input_sol);
//    print_results("[Big] Conv2D", res_big_cpu, res_big_gpu);
//
//
//    // *** [Dense] *****************************************
//    // Data =================================
//    int ndim = 3;
//    int ndim_big = 1000*1000;
//    t_input = Tensor::ones({1, 4}, DEV_CPU);
//    t_weights = Tensor::full({4, ndim}, 2.0, DEV_CPU);
//    t_input_sol = Tensor::full({1, 3}, 8.0, DEV_CPU);
//    t_input_big = Tensor::ones({1, 4}, DEV_CPU);
//    t_weights_big = Tensor::full({4, ndim_big}, 2.0, DEV_CPU);
//
//    res_small_cpu = run_dense(t_input, t_weights, DEV_CPU, 1);
//    res_small_gpu = run_dense(t_input, t_weights, DEV_GPU, 1);
//    res_big_cpu = run_dense(t_input_big, t_weights_big, DEV_CPU, 1);
//    res_big_gpu = run_dense(t_input_big, t_weights_big, DEV_GPU, 1);
//
//    // Print results
//    print_results_ref("Dense", res_small_cpu, res_small_gpu, t_input_sol);
//    print_results("[Big] Dense", res_big_cpu, res_big_gpu);
//
//
//    // *** [Sigmoid] *****************************************
//    // Data =================================
//    t_input_big = Tensor::randn({100, 10000}, DEV_CPU);
//    act = "sigmoid";
//
//    res_big_cpu = run_activation(t_input_big, act, DEV_CPU, 1);
//    res_big_gpu = run_activation(t_input_big, act, DEV_GPU, 1);
//
//    // Print results
//    print_results(act, res_big_cpu, res_big_gpu);
//
//    // *** [Relu] *****************************************
//    // Data =================================
//    t_input_big = Tensor::randn({100, 10000}, DEV_CPU);
//    act = "relu";
//
//    res_big_cpu = run_activation(t_input_big, act, DEV_CPU, 1);
//    res_big_gpu = run_activation(t_input_big, act, DEV_GPU, 1);
//
//    // Print results
//    print_results(act, res_big_cpu, res_big_gpu);
//
//
//    // *** [Softmax] *****************************************
//    // Data =================================
//    t_input_big = Tensor::randn({10000, 100}, DEV_CPU);
//    act = "softmax";
//
//    res_big_cpu = run_activation(t_input_big, act, DEV_CPU, 1);
//    res_big_gpu = run_activation(t_input_big, act, DEV_GPU, 1);
//
//    // Print results
//    print_results(act, res_big_cpu, res_big_gpu);
//
//
//    // *** [BathNorm] *****************************************
//    // Data =================================
//    t_input_big = Tensor::randn({1, 3, 1000, 1000}, DEV_CPU);
//
//    res_big_cpu = run_batchnorm(t_input_big, DEV_CPU, 1);
//    res_big_gpu = run_batchnorm(t_input_big, DEV_GPU, 1);
//
//    // Print results
//    print_results("[Big] BatchNorm", res_big_cpu, res_big_gpu);
//
//
//    // *** [UpSampling] *****************************************
//    // Data =================================
//    vector<int> size = {2, 2};
//    t_input_big = Tensor::randn({1000, 1000}, DEV_CPU);
//
//    res_big_cpu = run_upsampling(t_input_big, size, DEV_CPU, 1);
//    res_big_gpu = run_upsampling(t_input_big, size, DEV_GPU, 1);
//
//    // Print results
//    print_results("[Big] UpSampling", res_big_cpu, res_big_gpu);
//
//
//    // *** [CREATE OPERATIONS] *****************************************
//    // *** [CREATE::ZEROS] *********************************************
//    float *data_sol;
//    data_sol = new float[10]{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
//    t_input_sol = new Tensor({10}, data_sol, DEV_CPU);
//
//    res_small_cpu = run_tensor_create("zeros", DEV_CPU, 1);
//    res_small_gpu = run_tensor_create("zeros", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Create::zeros", res_small_cpu, res_small_gpu, t_input_sol);
//
//
//    // *** [CREATE::ONES] *********************************************
//    data_sol = new float[10]{1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0};
//    t_input_sol = new Tensor({10}, data_sol, DEV_CPU);
//
//    res_small_cpu = run_tensor_create("ones", DEV_CPU, 1);
//    res_small_gpu = run_tensor_create("ones", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Create::ones", res_small_cpu, res_small_gpu, t_input_sol);
//
//
//    // *** [CREATE::FULL] *********************************************
//    data_sol = new float[10]{5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0, 5.0};
//    t_input_sol = new Tensor({10}, data_sol, DEV_CPU);
//
//    res_small_cpu = run_tensor_create("full", DEV_CPU, 1);
//    res_small_gpu = run_tensor_create("full", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Create::full", res_small_cpu, res_small_gpu, t_input_sol);
//
//
//    // *** [CREATE::ARANGE] *********************************************
//    data_sol = new float[9]{1., 2., 3., 4., 5., 6., 7., 8. , 9.};
//    t_input_sol = new Tensor({9}, data_sol, DEV_CPU);
//
//    res_small_cpu = run_tensor_create("arange", DEV_CPU, 1);
//    res_small_gpu = run_tensor_create("arange", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Create::arange", res_small_cpu, res_small_gpu, t_input_sol);
//
//
//    // *** [CREATE::RANGE] *********************************************
//    data_sol = new float[10]{1., 2., 3., 4., 5., 6., 7., 8. , 9., 10.};
//    t_input_sol = new Tensor({10}, data_sol, DEV_CPU);
//
//    res_small_cpu = run_tensor_create("range", DEV_CPU, 1);
//    res_small_gpu = run_tensor_create("range", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Create::range", res_small_cpu, res_small_gpu, t_input_sol);
//
//
//    // *** [CREATE::LINSPACE] *********************************************
//    data_sol = new float[5]{3.0, 4.75, 6.5, 8.25, 10.0};
//    t_input_sol = new Tensor({5}, data_sol, DEV_CPU);
//
//    res_small_cpu = run_tensor_create("linspace", DEV_CPU, 1);
//    res_small_gpu = run_tensor_create("linspace", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Create::linspace", res_small_cpu, res_small_gpu, t_input_sol);
//
//
//    // *** [CREATE::LOGSPACE] *********************************************
//    data_sol = new float[5]{1.2589, 2.1135, 3.5481, 5.9566, 10.0000};
//    t_input_sol = new Tensor({5}, data_sol, DEV_CPU);
//
//    res_small_cpu = run_tensor_create("logspace", DEV_CPU, 1);
//    res_small_gpu = run_tensor_create("logspace", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Create::logspace", res_small_cpu, res_small_gpu, t_input_sol);
//
//
//    // *** [CREATE::EYE] *********************************************
//    data_sol = new float[9]{1., 0., 0.,
//                            0., 1., 0.,
//                            0., 0., 1.};
//    t_input_sol = new Tensor({3, 3}, data_sol, DEV_CPU);
//
//    res_small_cpu = run_tensor_create("eye", DEV_CPU, 1);
//    res_small_gpu = run_tensor_create("eye", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results_ref("Create::eye", res_small_cpu, res_small_gpu, t_input_sol);
//
//
//    // *** [CREATE::RANDOM] *********************************************
//    res_big_cpu = run_tensor_create("randn", DEV_CPU, 1);
//    res_big_gpu = run_tensor_create("randn", DEV_GPU, 1);
//
//    // Check correctness with solution
//    print_results("Create::randn", res_big_cpu, res_big_gpu);  // TODO: Ignore correctness
//
//
//    // *** [Math operations] *****************************************
//    vector<string> math_ops = {"abs", "acos", "add", "asin", "atan", "ceil", "clamp", "cos", "cosh", "exp", "inv",
//                               "floor", "log", "log2", "log10", "logn", "mod", "mult", "normalize", "pow", "powb",
//                               "reciprocal", "remainder", "round", "rsqrt", "sigmoid", "sign", "sin", "sinh",
//                               "sqr", "sqrt", "tan", "tanh", "trunc", "max", "min"};
//
//    for (auto op:math_ops){
//            t_input_big = Tensor::randn({1000, 1000}, DEV_CPU);
//            res_big_cpu = run_tensor_op(t_input_big, op, DEV_CPU, 1);
//            res_big_gpu = run_tensor_op(t_input_big, op, DEV_GPU, 1);
//            print_results(op, res_big_cpu, res_big_gpu);
//    }
//

//
//    t_input = Tensor::range(1.0, 9.0f, 1.0f, DEV_CPU);
//    t_input->reshape_({3, 3});
//    vector<int> idxs = t_input->get_indices_rowmajor(5);
//
//    // [Speed tests]
//    int MAX_TRIES = 10;
//    t_input = Tensor::ones({10, 10, 1000,1000}, DEV_CPU);
//    res_small_cpu = run_tensor_op(t_input, "shift", DEV_CPU, MAX_TRIES);
//
////    res_small_cpu.tensor->toCPU();
////    res_small_cpu.tensor->reshape_({50, 50});
////    res_small_cpu.tensor->print();
//
//    cout << "Runs: " << MAX_TRIES << endl;
//    cout << "Total time: " << res_small_cpu.time << " seconds" << endl;
//    cout << "Avg time: " << res_small_cpu.time/MAX_TRIES << " seconds" << endl;

//
////    // *** [Data augmentation] *****************************************
//    vector<string> data_aug = {
//            //"crop", "crop_random"
//            "shift", "rotate", "flip_h", "flip_v", "scale", "crop", "crop_scale", "cutout",
//            "shift_random", "rotate_random", "flip_h_random", "flip_v_random", "scale_random", "crop_random", "crop_scale_random", "cutout_random"
//    };
//    for (auto op:data_aug){
//        t_input = Tensor::range(1.0, 100.0f, 1.0f, DEV_CPU);
//        vector<int> shape({1, 1, 10, 10});
//        t_input->reshape_(shape);
//
//        // Reshapes
//        if(op=="scale") {
//            t_output = new Tensor({1, 1, 10, 10}, t_input->device);
//        }else if(op=="crop" || op=="crop_random") {
//            t_output = new Tensor({1, 1, 3, 3}, t_input->device);
////        }else if(op=="cutout") {
////            t_output = t_input->clone();
//        } else {
//            t_output = new Tensor(t_input->getShape(), t_input->device);
//        }
//
//        // Test for correctness
//        res_small_cpu = run_tensor_da(t_input, t_output, op, DEV_CPU, 1);
//        res_small_gpu = run_tensor_da(t_input, t_output, op, DEV_GPU, 1);
////        res_small_cpu.tensor->print();
//        print_cpu_gpu_correctness(op, res_small_cpu.tensor, res_small_gpu.tensor);
//        //print_results(op, res_small_cpu, res_small_cpu);
//
//        // Prints
//        cout << "===================" << endl;
//        cout << op << endl;
//        cout << "===================" << endl;
//
//        // Print CPU ********
////        t_input->reshape_({t_input->shape[2], t_input->shape[3]});
////        t_input->print();
////        //        res_small_cpu.tensor->print();
////        res_small_cpu.tensor->reshape_({res_small_cpu.tensor->shape[2], res_small_cpu.tensor->shape[3]});
////        res_small_cpu.tensor->print();
//
//        // Print GPU ******
//        t_input->reshape_({t_input->shape[2], t_input->shape[3]});
//        t_input->print();
//        res_small_gpu.tensor->reshape_({res_small_gpu.tensor->shape[2], res_small_gpu.tensor->shape[3]});
//        res_small_gpu.tensor->toCPU();
//        res_small_gpu.tensor->print();
//    }


    // *** [SELECT:forward] *********************************************
    int *oi_addresses;
    vector<string> idxs;
    vector<vector<int>> idxs_range;

    t_input = Tensor::range(1, 100, 1.0f);
    t_input->reshape_({10, 10});

//    t_input->print();
//    t_output->print();
    res_small_cpu = run_tensor_select(t_input, t_output, "select", DEV_CPU, 1);
    res_small_gpu = run_tensor_select(t_input, t_output, "select", DEV_GPU, 1);

    res_small_cpu.tensor->print();
    res_small_gpu.tensor->print();

    print_cpu_gpu_correctness("select", res_small_cpu.tensor, res_small_gpu.tensor);


    // *** [SELECT:backward] *********************************************
    cout << "---------\n" << endl;
    t_aux = Tensor::range(1, t_output->size, 1.0f);
    t_aux->reshape_(t_output->shape);
    t_output = Tensor::zeros(t_input->shape);
    t_input = t_aux;

//    t_input->print();
//    t_output->print();
    res_small_cpu = run_tensor_select(t_input, t_output, "select_back", DEV_CPU, 1);
    res_small_gpu = run_tensor_select(t_input, t_output, "select_back", DEV_GPU, 1);

    res_small_cpu.tensor->print();  // delta_parent
    res_small_gpu.tensor->print();

    print_cpu_gpu_correctness("select_back", res_small_cpu.tensor, res_small_gpu.tensor);

    string fname = "~/Desktop/elephant.jpg";
    t_input = Tensor::load(fname);
    t_output = t_input->select({"0"});

    t_output->save("mynewarray2img.jpg");
    int asd = 33;

//    Tensor* A = Tensor::full({10}, 100.0f);
//    Tensor* B = Tensor::full({10}, -100.0f);
//    Tensor* C = Tensor::interpolate(0.5f, A, 0.5f, B);
//    A->print();
//    B->print();
//    C->print();
//    A->add_(B);
//    A->print();
//
//    // *** [Summary] *****************************************
//    float total_tests = total_ok + total_errors;
//    cout << "" << endl;
//    cout << "*************************************************" << endl;
//    cout << "*** SUMMARY: ************************************" << endl;
//    cout << "*************************************************" << endl;
//    cout << "Total tests: " << total_ok + total_errors << endl;
//    cout << "\t- Total ok: " << total_ok << " (" << (int)((float)total_ok/total_tests*100.0f) << "%)" << endl;
//    cout << "\t- Total errors: " << total_errors << " (" << (int)((float)total_errors/total_tests*100.0f) << "%)" << endl;
//    cout << "" << endl;


//    // *** [Test Raw-Tensor operations] *****************************************
//    // CPU tensor core ops
//    t_input = Tensor::range(1.0f, 27.0f);
//    t_input->reshape_({3, 3, 3});
//
//    pretty_res("[small] get_address_rowmajor", t_input->get_address_rowmajor({1, 1, 2})==14);
//    pretty_res("[small] get_", t_input->get_({1, 1, 2})==15);
//
//    t_input->set_({1, 1, 2}, 0.0f);
//    pretty_res("[small] set_", t_input->get_({1, 1, 2})==0);

}
