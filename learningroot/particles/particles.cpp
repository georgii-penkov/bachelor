// how to do boundary definition and check if particle inside? arbitrary boundary not necessarily convex...
// assume convex shape. input array of planes as array of points and normal vectors. intersections of planes define lines. intersections of lines define vertices. on __init__ calculate all vertices 
// using vertices create instances of ROOT TGeoPolygon 2D polygons as boundaries. for check if point in boundary, see if projection of point on all planes inside polygon. TGeoPolygon has method for last part
#include <vector>
#include <string>
#include "TF1.h"


class particle
{
    public:
    ROOT::Math::XYZPoint *position = new ROOT::Math::XYZPoint();
    ROOT::Math::XYZPoint *old_position = new ROOT::Math::XYZPoint();
    ROOT::Math::XYZVector *velocity = new ROOT::Math::XYZVector();
    TPolyLine3D *arrow = new TPolyLine3D(2);
    TPolyLine3D *path = new TPolyLine3D();
    TPolyMarker3D *marker = new TPolyMarker3D(1);
    double * lifetime = new double;
    bool * alive = new bool;
    particle(double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0)
    {
        position->SetCoordinates(x, y, z);
        old_position->SetCoordinates(x, y, z);
        path->SetNextPoint(x, y, z);
        velocity->SetCoordinates(vx, vy, vz);
        *lifetime = 0;
        *alive = true;
        marker->SetMarkerSize(1);
        marker->SetMarkerColor(2);
        marker->SetMarkerStyle(8);
    };
    void DrawPoint()
    {
        marker->SetPoint(0, position->X(), position->Y(), position->Z());
        marker->Draw();
    };
    void Draw()
    {
        arrow->SetPoint(0, position->X(), position->Y(), position->Z());
        arrow->SetPoint(1, position->X()+velocity->X(), position->Y()+velocity->Y(), position->Z()+velocity->Z());
        arrow->Draw();
    };
    void Reflect(ROOT::Math::XYZVector *normal)
    {
        float scalar = velocity->Dot(*normal);
        if (scalar > 0) {scalar = -1*scalar;};
        *velocity = *velocity - (2*scalar) * *normal;
        //*velocity = *velocity - *normal;
    };

    ROOT::Math::XYZPoint project(float dt)
    {
        ROOT::Math::XYZPoint x;
        x.SetCoordinates(position->X()+dt*velocity->X(), position->Y()+dt*velocity->Y(), position->Z()+dt*velocity->Z());
        return(x);
    };

    void Move(double dt) //fast forward by time dt. Recursive function could have been used for large dt, many reflections, but problem because of use of pointers
    {
        old_position->SetCoordinates(position->X(), position->Y(), position->Z());
        position->SetCoordinates(position->X()+dt*velocity->X(), position->Y()+dt*velocity->Y(), position->Z()+dt*velocity->Z());
        path->SetNextPoint(position->X(), position->Y(), position->Z());

    };

    void Kill()
    {
        velocity->SetCoordinates(0,0,0);
        *alive = false;
        
    }
    
    // variables position, velocity    
    // methods create, destroy, reflect
};

class system
{
    public:
    std::vector<particle*> particles;
    TGeometry tile;
    system()
    {

    };
    void AddParticle(particle* p)
    {
        particles.push_back(p);
    };
    void Run(double time)
    {
        for (int i = 0; i < size(particles); ++i)
        {
            Trace(particles[i], time);
        };
    };

    void Trace(particle *particle, double time)
    {

    };

};

void particles()
{
    /*
    new TGeoManager("world", "A simples geometry.");
    TGeoMaterial *scintillator = new TGeoMaterial("scintillator",0,0,0);
    TGeoMedium *scintillator_medium = new TGeoMedium("scintillator",1,scintillator);
    TGeoVolume *top=gGeoManager->MakeBox("Top",scintillator_medium,10.,10.,10.);

    gGeoManager->SetTopVolume(top);
    gGeoManager->CloseGeometry();
    top->SetFillColor(kMagenta);
    gGeoManager->SetTopVisible();
    top->Draw();
    */


    //detector_material->SetFillColor(2);

    auto geom = new TGeometry("Tile", "Tile");
    geom->cd();
    float scx = 6.3;
    float scy = 6.4;
    float scz = 5;
    float detx = 3;
    float dety = 3;
    float detz = 0.1;
    auto scintillator = new TBRIK("scintillator", "scintillator", "void", scx, scy, scz);
    auto scintillatornode = new TNode("scintillatornode", "scintillatornode", scintillator);
    scintillatornode->SetPosition(0.5*scx, 0.5*scy, 0.5*scz);
    scintillatornode->SetVisibility(1);
    scintillatornode->cd();
    auto detector = new TBRIK("detector", "detector", "void", detx, dety, detz);
    detector->SetFillColor(2);
    detector->SetFillStyle(kFSolid);
    
    auto detectornode = new TNode("detector", "detector", detector);
    detectornode->SetVisibility(1);
    //detectornode->SetPosition(0.5*scintillatorsize-0.5*detectorsize, 0.5*scintillatorsize-0.5*detectorsize, 0.5*scintillatorsize-0.5*detectorsize);
    std::cout << detector->GetFillColor() << std::endl;
    detectornode->SetPosition(0, 0, -detz-scz);

    geom->Draw();
    auto rulers = new TAxis3D();
    rulers->Draw();

    
    ROOT::Math::XYZVector *normal = new ROOT::Math::XYZVector;
    normal->SetCoordinates(-1,0,0);
    particle a(-1,-1,-1,1,1,1);
    //a.Reflect(normal);
    a.Draw();
    a.DrawPoint();
    //a.Move(1);
    //a.DrawPoint();
    //a.Draw();
    //double * arr[20];
    //detectornode->ShootRay(a.position; a.velocity->X(), a.velocity->Y(), a.velocity->Z(), arr, 20, 3);
    //std::cout << arr[1];
}