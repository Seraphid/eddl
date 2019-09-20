#include <stdio.h>
#include <cmath>
#include <random>

#include "random.h"
#include "utils.h"

#define PI 3.1415926
#define MAX_RTABLE 100000

float *RTable=nullptr;
int posTable=0;

// Default seed
std::random_device rd;  //Will be used to obtain a seed for the random number engine
std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()


float uniform(float min, float max) {
    // rand() may not generate numbers uniformly and is therefore discouraged
    // Talk: https://channel9.msdn.com/Events/GoingNative/2013/rand-Considered-Harmful
    std::uniform_real_distribution<float> distr(min, max);
    return distr(gen);
}

float signed_uniform() {
    return (2.0 * uniform()) - 1.0;
}

float gaussgen() {
    float x, u1, u2;
    int i;
    u1 = uniform();
    u2 = uniform();
    while (u1 == 0.0) u1 = uniform();
    x = std::sqrt(std::log(1 / u1)) * std::cos(2 * PI * u2);
    return x;
}

float slow_randn(float mean, float sd) {
    return (gaussgen() * sd) + mean;
}

void build_randn_table() {
    if (RTable == nullptr) {
        printf("Generating Random Table\n");
        RTable = get_fmem(MAX_RTABLE, "build_randn_table");

        for (int i = 0; i < MAX_RTABLE; i++)
            RTable[i] = gaussgen();
    }
}

float fast_randn(float mean, float sd, int seed) {
    posTable = (posTable + seed) % MAX_RTABLE;
    return (RTable[posTable] * sd) + mean;
}
