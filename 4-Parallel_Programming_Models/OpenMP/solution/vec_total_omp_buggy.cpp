#include <iostream>
#include <vector>
#include "omp.h"

// Randomly generate two vector of doubles and calculate the sum 

#define VEC_SIZE 30

using namespace std;

void print_vec(vector<int> vec);
int vec_sum(vector<int> v1, vector<int> v2);

int main()
{
    vector<int> vec1, vec2;
    
    for (int i=0; i< VEC_SIZE; ++i)
    {
        vec1.push_back(2*i);
        vec2.push_back(2*i+1);
    }


    print_vec(vec1);
    print_vec(vec2);

    cout<<"Sum of vector 1 and 2 is :"<<vec_sum(vec1, vec2)<<endl;
    return 0;
}

void print_vec(vector<int> vec)
{
    for (auto i : vec) {
        cout << i << " ";
    }
    cout<<"\n";
}

int vec_sum(vector<int> v1, vector<int> v2)
{
    int result=0;
    
    #pragma omp parallel for default(none) shared(v1, v2, result)
    for (int i=0; i<v1.size(); ++i)
    {
        result+=v1[i]+v2[i];
    }

    return result;
}

