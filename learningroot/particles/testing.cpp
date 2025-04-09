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

/*
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

*/

#include <vector>
#include <cmath>
#include <iostream>

const double THRESHOLD = 0.00001;
class Cartesian;
class Point;
class Vector;

class Cartesian
{
    private:
        double m_x;
        double m_y;
        double m_z;
    public: 
        Cartesian(double, double, double);
        double X() const {return m_x;};
        double Y() const {return m_y;};
        double Z() const {return m_z;};
        void SetX(double x){m_x = x;};
        void SetY(double y){m_y = y;};
        void SetZ(double z){m_z = z;};

        
};
Cartesian::Cartesian(double x = 0.0, double y = 0.0, double z = 0.0): m_x(x), m_y(y), m_z(z){};

class Point : public Cartesian
{
    public:
        Point operator+(const Vector&);
        Vector operator-(const Point&);
        void Draw() const;

};


class Vector : public Cartesian
{
    public:
        Vector Cross(const Vector&);
        double Dot(const Vector&);
        Vector operator+(const Vector&);
        Vector operator-(const Vector&);
        Vector& operator*=(const double&);


};

Vector& Vector::operator*=(const double& scalar)
{
    this->SetX(this->X()*scalar);
    this->SetY(this->Y()*scalar);
    this->SetZ(this->Z()*scalar);
    return(*this);
};

Vector operator*(const double& scalar, const Vector& vector)
{
    Vector result = vector;
    result *= scalar;
    return(result);
};
Vector operator*(const Vector& vector, const double& scalar)
{
    Vector result = vector;
    result *= scalar;
    return(result);
};

int main()
{
    Vector vector;
    vector.SetX(11.0);
    vector.SetY(12.0);
    vector.SetZ(13.0);

    std::cout << vector.X() << vector.Y() << vector.Z() << std::endl;
    vector*= 10.0;
    std::cout << vector.X() << vector.Y() << vector.Z() << std::endl;
    return 0;
};