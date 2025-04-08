#include <iostream>
#include <cmath>
#include <random>

/*  //functions were moved to function.cpp for access by multiple macros
double background(const double *x, const double *params)
{
    return(params[3]*x[0]*x[0]+params[4]*x[0]+params[5]);
};

double signal(const double *x, const double *params)
{
    return(params[0]*exp(-0.5*((x[0]-params[1])/params[2])*((x[0]-params[1])/params[2])));
};

double fitfunction(const double *x, const double *params)
{
    return(signal(x, params) + background(x, params));   //really fucking dangerous &params[3], "passing only second part of cstyle array"
};
*/

void generatedata(const double *lowerrange, const double *upperrange, const int *steps, double *params = nullptr, double const randomness = 1)   //generates data y gauss scattered around a gauss signal + parabolic background
                                                                                                                                                //params is array of doubles, [norm, mean, sigma, a, b, c] with background ax^2+bx+c and signal norm*exp(1/2*((x-mean)/sigma)^2
{
    gROOT->ProcessLine(".L functions.cpp");
    double defaultparams[6]{5.0,2.0,0.5,0.05,-1.0,5.0};
    if (params == nullptr) 
    {
        params = &defaultparams[0];
        std::cout << params[0] << std::endl;
    };
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0,randomness);
    TGraphErrors* graph = new TGraphErrors("graph");
    for (int i = 0; i <= *steps; ++i)
    {
        double x = *lowerrange + i*(*upperrange-*lowerrange)/ *steps;
        double y = fitfunction(&x, params);
        double yerror = distribution(generator);
        y = y + yerror;
        yerror = fabs(1.25*yerror);
        std::cout << x << "\t" << y << "\t" << yerror << std::endl;
        graph->AddPointError(x, y, 0, yerror);
        graph->Draw();
    };
    TFile file("./data.root", "RECREATE");
    graph->Write();
    file.Close();
};


int main()
{
    double lowerrange = 0;
    double upperrange = 10;
    int steps = 100;
    generatedata(&lowerrange, &upperrange, &steps);
    return 0;
}