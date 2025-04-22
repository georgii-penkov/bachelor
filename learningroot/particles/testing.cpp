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
        Cartesian(const double& x = 0.0, const double& y = 0.0, const double& z = 0.0): m_x(x), m_y(y), m_z(z){};
        double X() const {return m_x;};
        double Y() const {return m_y;};
        double Z() const {return m_z;};
        void SetX(double x){m_x = x;};
        void SetY(double y){m_y = y;};
        void SetZ(double z){m_z = z;};
        void SetCoordinates(const double&, const double&, const double&);
        double Mag2();
        Cartesian& operator=(const Cartesian&);
        Cartesian operator+(const Cartesian&);
};

void Cartesian::SetCoordinates(const double& x, const double& y, const double& z)
{
    m_x = x;
    m_y = y;
    m_z = z;
};

double Cartesian::Mag2()
{
    return(this->X()*this->X() + this->Y()*this->Y() + this->Z()*this->Z());
};

Cartesian& Cartesian::operator=(const Cartesian& second)
{
    this->SetX(second.X());
    this->SetY(second.Y());
    this->SetZ(second.Z());
    return(*this);
};

Cartesian Cartesian::operator+(const Cartesian& second)
{
    Cartesian result;
    result.SetCoordinates(this->X()+second.X(), this->Y()+second.Y(), this->Z()+second.Z());
    return result;
};

class Point : public Cartesian
{
    public:
        Point(const double& x = 0, const double& y = 0, const double& z = 0) : Cartesian(x,y,z) {};
        using Cartesian::operator=;
        using Cartesian::operator+;
        Point operator+(const Vector&);
        Vector operator-(const Point&);
        void Draw() const;

};

class Vector : public Cartesian
{
    public:
        Vector(const double& x = 0, const double& y = 0, const double& z = 0) : Cartesian(x,y,z) {};
        using Cartesian::operator=;
        using Cartesian::operator+;
        Vector operator+(const Vector&);
        Vector operator-(const Vector&);
        Vector& operator+=(const Vector&);
        Vector& operator*=(const double&);
        Vector operator/(const double&);
        Vector Cross(const Vector&);
        double Dot(const Vector&);
        Vector Unit();
};
Vector operator*(const double&, const Vector&);
Vector operator*(const Vector&, const double&);


Point Point::operator+(const Vector& vector)
{
    Point result;
    result.SetX(this->X() + vector.X());
    result.SetY(this->Y() + vector.Y());
    result.SetZ(this->Z() + vector.Z());
    return result;
};

Vector Point::operator-(const Point& point)
{
    Vector result;
    result.SetX(this->X() - point.X());
    result.SetY(this->Y() - point.Y());
    result.SetZ(this->Z() - point.Z());
    return result;
}

Vector Vector::operator+(const Vector& vector)
{
    Vector result;
    result.SetX(this->X()+vector.X());
    result.SetY(this->Y()+vector.Y());
    result.SetZ(this->Z()+vector.Z());
    return result;
};

Vector Vector::operator-(const Vector& vector)
{
    return(*this + (-1.0*vector));
};

Vector& Vector::operator+=(const Vector& vector)
{
    this->SetX(this->X() + vector.X());
    this->SetY(this->Y() + vector.Y());
    this->SetZ(this->Z() + vector.Z());
    return(*this);
}

Vector& Vector::operator*=(const double& scalar)
{
    this->SetX(this->X()*scalar);
    this->SetY(this->Y()*scalar);
    this->SetZ(this->Z()*scalar);
    return(*this);
};

Vector Vector::operator/(const double& scalar)
{
    return((*this)*(1/scalar));
};

Vector Vector::Cross(const Vector& vector)
{
    Vector result;
    result.SetX(this->Y()*vector.Z() - this->Z()*vector.Y());
    result.SetY(this->Z()*vector.X() - this->X()*vector.Z());
    result.SetZ(this->X()*vector.Y() - this->Y()*vector.X());
    return result;
};

double Vector::Dot(const Vector& vector)
{
    return(this->X()*vector.X() + this->Y()*vector.Y()+ this->Z()*vector.Z());
}

Vector Vector::Unit()
{
    return((*this)*(1/sqrt(this->Dot(*this))));
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
    vector = vector.Unit();
    std::cout << vector.X() << vector.Y() << vector.Z() << std::endl;
    Point point;
    point = vector;
    return 0;
};




class Time
{
    private:
        double seconds;
        double minutes;
        double hours;
        double days;
    public:
        void normalise();
};

//Testing rename