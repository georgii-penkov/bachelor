// class point
// class line = also via ROOT? TPolyLine3D
// class face = TGeoPolygon
// class convex_3_d_polygon = define by set of points+normalvectors
//#include <cstring>
#include <iostream>
#include <vector>
#include <string>
class point
{
    public:
        float x;
        float y;
        float z;
        char * name;
        point(float x, float y, float z, std::string name_str = " ")
        {
            this->x = x;
            this->y = y;
            this->z = z;
            auto namer = new char[name_str.length()+1];
            std::strcpy(namer, name_str.c_str());
            this->name = namer;
        };

        void print()
        {
            std::cout << "Point " << name << " (" << x << "; " << y << "; " << z << ")" << std::endl;
        };

        void plot()
        {
            auto p = new TPolyMarker3D(0, 1);
            p->SetMarkerSize(1);
            p->SetMarkerColor(2);
            p->SetMarkerStyle(2);
            //p->SetName(name);
            p->SetPoint(0, x, y, z);
            p->Draw();
            auto t = new TAnnotation(x+0.1, y+0.1, z+0.1, name);
            t->SetTextFont(42);
            t->SetTextColor(kBlue);
            t->Draw();

        };
        

    
};

class line
{
    public:
        point *A;
        point *B;
        TPolyLine3D *l = new TPolyLine3D(2);
        line(point * A, point * B)
        {
            this->A = A;
            this->B = B;
            l->SetPoint(0, A->x, A->y, A->z);
            l->SetPoint(1, B->x, B->y, B->z);
        };
        void plot()
        {
            A->plot();
            B->plot();
            l->Draw();
        }
};

class face
{

};

class convex_3d_polygon
{

};

void threedpolygon()
{
    point A(1, 2.0, 3, "A");
    point B(4, 5, 6, "B");
    line AB(&A, &B);
    AB.plot();
}

int main()
{
    point A(1, 2.0, 3, "P");
    A.print();
};