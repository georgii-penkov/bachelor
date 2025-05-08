#include "threedgeometry.cpp"

/*
void threedpolygon2()
{

    //Testing finding intersection of planes (=line)
    Point p;
    Point q;
    Vector n;
    Vector m;
    p.SetCoordinates(0,0,0);
    n.SetCoordinates(-1,0,0);
    q.SetCoordinates(1,1,1);
    m.SetCoordinates(-2,-2,1);
    Plane X(p, n);
    Plane Y(q, m);
    Line cross = X.intersection(&Y);
    std::cout << cross.point << std::endl << cross.vector << std::endl;
    
    //Testing finding intersection of lines (=point)
    Point p;
    Point q;
    Vector l;
    Vector m;
    p.SetCoordinates(0,0,0);
    l.SetCoordinates(0,2,0);
    q.SetCoordinates(7,1,0);
    m.SetCoordinates(-2,0,0);
    Line X(p, l);
    Line Y(q, m);
    std::cout << X.Intersection(&Y) << std::endl;
    std::cout << Y.Intersection(&X) << std::endl;
    
    Point p1(0,0,-2);
    Point p2(0,0,2);
    Point p3(2, 0, 0);
    Point p4(-2, 0, 0);
    Point p5(0, 2, 0);
    Point p6(0, -2, 0);
    Point p7(1.5, 1.5, 1.5);
    Point p8(-1.5, 1.5, 1.5);
    Point p9(1.5, -1.5, 1.5);
    Point p10(1.5, 1.5, -1.5);
    Point p11(-1.5, -1.5, 1.5);
    Point p12(1.5, -1.5, -1.5);
    Point p13(-1.5, 1.5, -1.5);
    Point p14(-1.5, -1.5, -1.5);

    Vector n1(0,0,1);
    Vector n2(0,0,-1);
    Vector n3(-1, 0, 0);
    Vector n4(1, 0, 0);
    Vector n5(0, -1, 0);
    Vector n6(0, 1, 0);
    Vector n7(-1, -1, -1);
    Vector n8(1, -1, -1);
    Vector n9(-1, 1, -1);
    Vector n10(-1, -1, 1);
    Vector n11(1, 1, -1);
    Vector n12(-1, 1, 1);
    Vector n13(1, -1, 1);
    Vector n14(1, 1, 1);
    std::vector<Point> p = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14};
    std::vector<Vector> n = {n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14};
    Threedpolygon polygon(p, n);
    polygon.DrawVertices();
    polygon.DrawWires();

    auto rulers = new TAxis3D();
    rulers->SetAxisColor(kRed, "X");
    rulers->SetAxisColor(kGreen, "Y");
    rulers->SetAxisColor(kBlue, "Z");
    rulers->SetAxisRange(-4, 4, rulers->GetOption());

    rulers->Draw();
};
//*/

/*
void threedpolygon2()
{
    Point p(10, 10, 10);
    Vector l(1,2,3);

    Point q(5, 2, 3);
    Vector n(0,0,1);

    Plane plane(q, n);
    Line line(p,l);
    std::cout << plane.Intersection(&line)<< std::endl;
}
//*/


/* //Draw a cube and find intersection with line=pline + t*lline
void threedpolygon2()
{
    Point p1(0,0,-2);
    Point p2(0,0,2);
    Point p3(2, 0, 0);
    Point p4(-2, 0, 0);
    Point p5(0, 2, 0);
    Point p6(0, -2, 0);

    Vector n1(0,0,1);
    Vector n2(0,0,-1);
    Vector n3(-1, 0, 0);
    Vector n4(1, 0, 0);
    Vector n5(0, -1, 0);
    Vector n6(0, 1, 0);


    Point pline(0, 0, 0);
    Vector lline(1,1,1);

    std::vector<Point> p = {p1, p2, p3, p4, p5, p6};
    std::vector<Vector> n = {n1, n2, n3, n4, n5, n6};
    Threedpolygon polygon(p, n);
    Line line(pline, lline);
    polygon.DrawVertices();
    polygon.DrawWires();

    auto rulers = new TAxis3D();
    rulers->SetAxisColor(kRed, "X");
    rulers->SetAxisColor(kGreen, "Y");
    rulers->SetAxisColor(kBlue, "Z");
    rulers->SetAxisRange(-4, 4, rulers->GetOption());

    std::vector<Point> points;
    points = polygon.Intersection(&line);
    for (int i = 0; i < size(points); ++i)
    {
        std::cout << points[i] << std::endl;
    };
    std::cout << std::endl;
    std::vector<Point> points2;
    points2 = polygon.PositiveIntersection(&line);
    for (int i = 0; i < size(points2); ++i)
    {
        std::cout << points2[i] << std::endl;
    };
    std::cout << std::endl;
};
*/


///* //Draw a Cube with corners cut off by planes
void maketiles()
{
    Point p1(0,0,-2);
    Point p2(0,0,2);
    Point p3(2, 0, 0);
    Point p4(-2, 0, 0);
    Point p5(0, 2, 0);
    Point p6(0, -2, 0);
    Point p7(1.5, 1.5, 1.5);
    Point p8(-1.5, 1.5, 1.5);
    Point p9(1.5, -1.5, 1.5);
    Point p10(1.5, 1.5, -1.5);
    Point p11(-1.5, -1.5, 1.5);
    Point p12(1.5, -1.5, -1.5);
    Point p13(-1.5, 1.5, -1.5);
    Point p14(-1.5, -1.5, -1.5);

    Vector n1(0,0,1);
    Vector n2(0,0,-1);
    Vector n3(-1, 0, 0);
    Vector n4(1, 0, 0);
    Vector n5(0, -1, 0);
    Vector n6(0, 1, 0);
    Vector n7(-1, -1, -1);
    Vector n8(1, -1, -1);
    Vector n9(-1, 1, -1);
    Vector n10(-1, -1, 1);
    Vector n11(1, 1, -1);
    Vector n12(-1, 1, 1);
    Vector n13(1, -1, 1);
    Vector n14(1, 1, 1);
    std::vector<Point> p = {p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14};
    std::vector<Vector> n = {n1, n2, n3, n4, n5, n6, n7, n8, n9, n10, n11, n12, n13, n14};
    Threedpolygon polygon(p, n);
    polygon.DrawVertices();
    polygon.DrawWires();

    auto rulers = new TAxis3D();
    rulers->SetAxisColor(kRed, "X");
    rulers->SetAxisColor(kGreen, "Y");
    rulers->SetAxisColor(kBlue, "Z");
    rulers->SetAxisRange(-4, 4, rulers->GetOption());

    rulers->Draw();
};
//*/