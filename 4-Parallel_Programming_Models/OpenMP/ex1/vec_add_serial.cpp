#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

// Randomly generate two vector of doubles and do summation 

#define VEC_SIZE 30

using namespace std;

void print_vec(vector<int> vec);
vector<int> vec_add(vector<int> v1, vector<int> v2);

int main()
{
    random_device rnd_device;

    // specify the random engine and distribution
    mt19937 mersenne_engine {rnd_device()};
    uniform_int_distribution<int> dist {1, 2018};

    auto gen = [&dist, &mersenne_engine](){
        return dist(mersenne_engine);
    }; 

    // use random int generator to fill two vectors
    vector<int> vec1(VEC_SIZE), vec2(VEC_SIZE);
    generate(begin(vec1), end(vec1), gen);
    generate(begin(vec2), end(vec2), gen);

    print_vec(vec1);
    print_vec(vec2);

    print_vec(vec_add(vec1, vec2));

    return 0;
}

void print_vec(vector<int> vec)
{
    for (auto i : vec) {
        cout << i << " ";
    }
    cout<<"\n";
}

vector<int> vec_add(vector<int> v1, vector<int> v2)
{
    vector<int> result(v1.size());

    for (int i=0; i<v1.size(); ++i)
    {
        result[i]=v1[i]+v2[i];
    }

    return result;
}

