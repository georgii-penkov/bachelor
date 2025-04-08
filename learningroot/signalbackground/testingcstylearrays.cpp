#include <string>
#include <iostream>

/*
void passandchange(double* params)
{

    std::cout << params[0] << std::endl;
    params[0] = 1.0;
    std::cout << params[0] << std::endl;

};
*/
void defaultvalues(double const* params = nullptr)
{
    if (params == nullptr) {double defaultparams[5]{1,2,3,4,5}; params = defaultparams;};
    std::cout << params[0] << std::endl;
}

/* //for passandchange
int main()
{
    double carr[5]{0.0,0.1,0.2,0.3,0.4};
    std::cout << carr[0] << std::endl;
    std::cout << carr[1] << std::endl;
    passandchange(carr);
    std::cout << carr[0] << std::endl;
    return 0;
}
*/

int main()
{
    double carr[5]{0.0,0.1,0.2,0.3,0.4};
    defaultvalues();
    defaultvalues(carr);
    return 0;
}