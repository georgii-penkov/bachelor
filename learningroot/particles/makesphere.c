#include "threedgeometry.cpp"
#include <cmath>

void makesphere()
{
    int n = 15;
    double r = 20;
    Point origin(1,1,1);
    std::vector<Point> points;
    std::vector<Vector> vectors;

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j <= n; ++j)
        {
            if (j==n and i!=0) continue; //prevent weirdness at bottom plane z = -r. FLoating point division for theta j/n, if j==n does not give exactly 1, bc floating point division, lots of planes for different phi with very very slightly tilted to each other, gives lots of unwanted points. Ensure bottom plane only drawn once for phi = 0. Same not necessary for top plane because 0/n actually good 0.
            double phi = 2*M_PI * i/n;
            double theta = M_PI * j/n;
            Point p(r*sin(theta)*cos(phi), r*sin(theta)*sin(phi), r*cos(theta));
            p = p + origin;
            Vector v = origin - p;
            points.push_back(p);
            vectors.push_back(v);
        };
    };

    Threedpolygon polygon(points, vectors);
    polygon.DrawVertices();
    polygon.DrawWires();

    auto rulers = new TAxis3D();
    rulers->SetAxisColor(kRed, "X");
    rulers->SetAxisColor(kGreen, "Y");
    rulers->SetAxisColor(kBlue, "Z");
    rulers->SetAxisRange(-4, 4, rulers->GetOption());

    rulers->Draw();

}
