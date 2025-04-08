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