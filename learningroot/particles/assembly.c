#include "threedgeometry.cpp"
#include <string>
#include <cmath>

Threedpolygon* MakeBrick(double xwidth = 1, double ylength = 1, double zheight = 1, double xpos = 0, double ypos = 0, double zpos = 0)
{
    Point p1( xwidth/2, 0, 0);
    Point p2( 0, ylength/2, 0);
    Point p3( 0, 0, zheight/2);
    Point p4(-xwidth/2, 0, 0);
    Point p5( 0,-ylength/2, 0);
    Point p6( 0, 0,-zheight/2);

    Vector n1(-1, 0, 0);
    Vector n2( 0,-1, 0);
    Vector n3( 0, 0,-1);
    Vector n4( 1, 0, 0);
    Vector n5( 0, 1, 0);
    Vector n6( 0, 0, 1);
    p1 = p1 + xpos*n4;
    p2 = p2 + ypos*n5;
    p3 = p3 + zpos*n6;
    p4 = p4 + xpos*n4;
    p5 = p5 + ypos*n5;
    p6 = p6 + zpos*n6;
    std::vector<Point> p = {p1, p2, p3, p4, p5, p6};
    std::vector<Vector> n = {n1, n2, n3, n4, n5, n6};
    auto brik = new Threedpolygon(p, n);
    return(brik);
};

Threedpolygon* EdgeScintillator()
{
    Point p1(0,0,-2.5);
    Point p2(0,0,2.5);
    Point p3(3.15, 0, 0);
    Point p4(-3.15, 0, -2.5);
    Point p5(0, 3.105, 0);
    Point p6(0, -3.105, 0);

    Vector n1(0,0,1);
    Vector n2(0,0,-1);
    Vector n3(-1, 0, 0);
    Vector n4(1, 0, 0);
    RotateVector(&n4, 0, -M_PI/14, 0);
    Vector n5(0, -1, 0);
    Vector n6(0, 1, 0);

    std::vector<Point> p = {p1, p2, p3, p4, p5, p6};
    std::vector<Vector> n = {n1, n2, n3, n4, n5, n6};
    auto scintillator = new Threedpolygon(p, n);
    return(scintillator);
};


void assembly(std::string filename = "./test.sim.root")
{
    auto mycanvas = new TCanvas();

    const char* str = filename.c_str();
    std::vector<Threedpolygon*> detector;
    TFile *file = TFile::Open(str);
    TTree *alignment = file->Get<TTree>("alignment/tiles");

    double x, y, z, vx, vy, vz;
    alignment->SetBranchAddress("posx", &x);
    alignment->SetBranchAddress("posy", &y);
    alignment->SetBranchAddress("posz", &z);
    alignment->SetBranchAddress("dirx", &vx);
    alignment->SetBranchAddress("diry", &vy);
    alignment->SetBranchAddress("dirz", &vz);

    for (int i = 0; i < alignment->GetEntries(); ++i)
    {
        alignment->GetEntry(i);
        detector.push_back(MakeBrick(6.3, 6.21, 5, 0,0,0));
        detector[i]->Rotate(0, std::atan2(sqrt(vx*vx+vy*vy), vz), std::atan2(vy, vx));
        detector[i]->Move(x, y, z);
        detector[i]->DrawWires();
    };
    auto rulers = new TAxis3D();
    rulers->SetAxisColor(kRed, "X");
    rulers->SetAxisColor(kGreen, "Y");
    rulers->SetAxisColor(kBlue, "Z");
    rulers->Draw();

    TPolyMarker3D *scaler = new TPolyMarker3D(6);


    scaler->SetPoint(0,  -500,  0,  0);  // X mim
    scaler->SetPoint(1,  500,  0,  0);  // X max
    scaler->SetPoint(2,  0, -500,  0);  // Y min
    scaler->SetPoint(3,  0,  500,  0);  // Y max
    scaler->SetPoint(4,  0,  0, -500);  // Z min
    scaler->SetPoint(5,  0,  0,  500);  // Z max

    scaler->SetMarkerColor(0); // invisible
    scaler->Draw();

}
