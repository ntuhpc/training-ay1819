#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>
#include "omp.h"
#include "time.h"

// Randomly generate two vector of doubles and do inner product
// Compare the time to do it in serial and in parallel

using namespace std;

vector<double> vec_add(vector<double> v1, vector<double> v2);

int main()
{
    random_device rnd_device;
    mt19937 mersenne_engine {rnd_device()};
    
    uniform_real_distribution
    vector<double> v1, v2;
    
    
}

vector<double> vec_add(vector<double> v1, vector<double> v2)
{
    #progma omp parallel for
    
}

