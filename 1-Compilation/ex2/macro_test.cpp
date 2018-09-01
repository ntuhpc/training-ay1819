/*
 * Test different macro usage
 * 
 */

#include <iostream>

int main()
{
    int a, b;
    std::cout<<"Please enter two numbers, seperated by space"<<std::endl;
    std::cin>> a >> b;
    
    #if defined (USE_MULTI)
    std::cout<<"USE_MULTI is defined. a*b="<<a*b<<std::endl;
    return 0;
    #endif 
    
    #if defined (USE_ADD)
    std::cout<<"USE_ADD is defined. a+b="<<a+b<<std::endl;
    return 0;
    #endif 
    
    #if defined (USE_SUBS)
    std::cout<<"USE_SUBS is defined. a-b="<<a-b<<std::endl;
    return 0;
    #endif 
    
    std::cout<<"No macro is defined."<<std::endl;
    return 0;
}

