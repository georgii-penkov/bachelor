#include <vector>
/*
ROOT::Math::XYZPoint a(1,1,1);
ROOT::Math::XYZPoint b(0,1,1);
ROOT::Math::XYZPoint c(1,0,1);

auto line = new TPolyLine3D;
line->SetNextPoint(a.X(), a.Y(), a.Z());
line->SetNextPoint(b.X(), b.Y(), b.Z());
line->SetNextPoint(c.X(), c.Y(), c.Z());
line->Draw();


std::vector<ROOT::Math::XYZPoint> vec{a, b, c};
*/

/*
std::vector<double> vec{1,2,3,4,5,6,7,8,9};
std::vector<double> weights(size(vec), 1);
auto hist = new TH1S("hist", "hist", 10, 0, 10);
hist->FillN(9,vec.data(), weights.data());
hist->Draw();
*/

#include<iostream>
class X
{
    double& reference;
    public:
    X(double& ref );
};
X::X (double& ref) : x(ref)
{

}

int main ()
{
    double y;
    X x(y);
    return 0;
}