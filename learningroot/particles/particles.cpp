#include <vector>
#include <string>
#include <cstring>
#include <cmath>
#include "threedgeometry.cpp"
#include <tbb/tbb.h>
//requires source /opt/intel/oneapi/tbb/latest/env/vars.sh
#include <chrono>
const double RADIUS = tan(M_PI/2-(M_PI/14)) * 25.6/2 + 2.5;


class Particle
{
    private:
        Point *m_position = new Point;
        Point *m_previous_position = new Point;
        Vector *m_velocity = new Vector;
        bool m_alive;
        double m_created;
        double m_lifetime;
        //TPolyMarker3D m_marker;
        TPolyLine3D *m_vector_marker = new TPolyLine3D(2);
        TPolyLine3D *m_path = new TPolyLine3D;
        TPolyMarker3D *m_marker = new TPolyMarker3D(1);
    public:
        Particle(double x=0, double y=0, double z=0, double vx=0, double vy=0, double vz=0, double created = 0)
        {
            m_position->SetCoordinates(x, y, z);
            m_previous_position->SetCoordinates(x, y, z);
            m_path->SetNextPoint(x, y, z);
            m_velocity->SetCoordinates(vx, vy, vz);
            m_lifetime = 0;
            m_created = created;
            m_alive = true;
            m_marker->SetMarkerSize(1);
            m_marker->SetMarkerColor(2);
            m_marker->SetMarkerStyle(8);
            m_path->SetNextPoint(x, y, z);
            m_vector_marker->SetLineColor(kRed);
        };
        Particle(Point start, Vector velocity, double created = 0)
        {
            m_position->SetCoordinates(start.X(), start.Y(), start.Z());
            m_previous_position->SetCoordinates(start.X(), start.Y(), start.Z());
            m_path->SetNextPoint(start.X(), start.Y(), start.Z());
            m_velocity->SetCoordinates(velocity.X(), velocity.Y(), velocity.Z());
            m_lifetime = 0;
            m_created = created;
            m_alive = true;
            m_marker->SetMarkerSize(1);
            m_marker->SetMarkerColor(kRed);
            m_marker->SetMarkerStyle(8);
            m_vector_marker->SetLineColor(kRed);
        };

        Point Position()
        {
            return(*m_position);
        };

        Point *PositionPointer()
        {
            return(m_position);
        }

        Vector Velocity()
        {
            return(*m_velocity);
        }

        bool IsAlive()
        {
            return(m_alive);
        };

        double Lifetime()
        {
            return(m_lifetime);
        };

        double Created()
        {
            return(m_created);
        };

        void DrawPoint()
        {
            m_marker->SetPoint(0, m_position->X(), m_position->Y(), m_position->Z());
            m_marker->Draw();
        };

        void Kill()
        {
            m_velocity->SetCoordinates(0,0,0);
            m_alive = false;
        };

        void DrawVector()
        {
            DrawPoint();
            m_vector_marker->SetPoint(0, m_position->X(), m_position->Y(), m_position->Z());
            m_vector_marker->SetPoint(1, m_position->X() + m_velocity->Unit().X(), m_position->Y() + m_velocity->Unit().Y(), m_position->Z() + m_velocity->Unit().Z());
            m_vector_marker->Draw();
        };

        void Draw()
        {
            DrawVector();
            DrawPoint();
        };

        void DrawPath()
        {
            m_path->Draw();
        };

        void Reflect(Vector *normal)
        {
            Vector normed_normal = normal->Unit();
            float scalar = m_velocity->Dot(normed_normal);
            if (scalar > 0) {scalar = -1*scalar;};
            *m_velocity = *m_velocity - (2*scalar) * normed_normal;
        };

        Point Project(double time)
        {
            Point x;
            x.SetCoordinates(m_position->X() + time * m_velocity->X(), m_position->Y() + time * m_velocity->Y(), m_position->Z() + time * m_velocity->Z());
            return(x);
        }

        void Move(double dt)
        {
            if (m_alive)
            {
                m_previous_position = m_position;
                //use SetCoordinates method to keep it a positionvector and not convert to displacement vector
                m_position->SetCoordinates(m_position->X() + dt * m_velocity->X(), m_position->Y() + dt * m_velocity->Y(), m_position->Z() + dt * m_velocity->Z());
                m_path->SetNextPoint(m_position->X(), m_position->Y(), m_position->Z());
                m_lifetime += dt;
            };

        };
};

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

Threedpolygon* Backstop()
{
    Point p1(0,0,-2.5);
    MovePoint(&p1, 0, 0, -5.1);
    Point p2(0,0,2.5);
    MovePoint(&p2, 0, 0, -5.1);
    Point p3(3.15+9.60, 0, 0);
    Point p4(-3.15-9.60, 0, -2.5);
    Point p5(0, 160, 0);
    Point p6(0, -160, 0);

    Vector n1(0,0,1);
    Vector n2(0,0,-1);
    Vector n3(-1, 0, 0);
    RotateVector(&n3, 0, +M_PI/14, 0);
    Vector n4(1, 0, 0);
    RotateVector(&n4, 0, -M_PI/14, 0);
    Vector n5(0, -1, 0);
    Vector n6(0, 1, 0);

    std::vector<Point> p = {p1, p2, p3, p4, p5, p6};
    std::vector<Vector> n = {n1, n2, n3, n4, n5, n6};
    auto backstop = new Threedpolygon(p, n);
    return(backstop);
};

class Tile
{
    public:
        Threedpolygon *m_scintillator;
        Threedpolygon *m_sipm;
        std::vector<Particle *> m_particles;
    public:
        Tile(Point position, double theta_x, double theta_y, double theta_z, bool is_edge)
        {
            Threedpolygon *scintillator;
            auto sipm = MakeBrick(3, 3, 0.1, 0, 0, -2.5);
            if (is_edge)
            {
                scintillator = EdgeScintillator();
            }
            else
            {
                scintillator = MakeBrick(6.3, 6.21, 5, 0,0,0);
            };
            sipm->Rotate(theta_x, theta_y, theta_z);
            sipm->Move(position.X(), position.Y(), position.Z());
            scintillator->Rotate(theta_x, theta_y, theta_z);
            scintillator->Move(position.X(), position.Y(), position.Z());
            m_scintillator = scintillator;
            m_sipm = sipm;
        };

        Tile(double x, double y, double z, double theta_x, double theta_y, double theta_z, bool is_edge)
        {
            Threedpolygon *scintillator;
            auto sipm = MakeBrick(3, 3, 0.1, 0, 0, -2.5);
            if (is_edge)
            {
                scintillator = EdgeScintillator();
            }
            else
            {
                scintillator = MakeBrick(6.3, 6.21, 5, 0,0,0);
            };
            sipm->Rotate(theta_x, theta_y, theta_z);
            sipm->Move(x, y, z);
            scintillator->Rotate(theta_x, theta_y, theta_z);
            scintillator->Move(x, y, z);
            m_scintillator = scintillator;
            m_sipm = sipm;
        };

        Threedpolygon *Scintillator()
        {
            return(m_scintillator);
        };
        Threedpolygon *Sipm()
        {
            return(m_sipm);
        };

        void AddParticle(Point position, Vector velocity, double timedelay)
        {
            auto particle = new Particle(position, velocity, timedelay);
            this->m_particles.push_back(particle);
        };
        void AddParticle(double x, double y, double z, double vx, double vy, double vz, double timedelay = 0)
        {
            auto particle = new Particle(x, y, z, vx, vy, vz, timedelay);
            this->m_particles.push_back(particle);
        };


        void DrawParticles()
        {
            for (int i = 0; i < size(m_particles); ++i)
            {
                m_particles[i]->DrawPoint();
            };
        };
        void Draw()
        {
            m_scintillator->DrawWires();
            m_sipm->DrawWires();
            DrawParticles();
        };

        void DrawPaths()
        {
            for (int i = 0; i < size(m_particles); ++i)
            {
                m_particles[i]->DrawPath();
            };
        };

        void PathFind(double time)
        {
            /* //old version
            for (int i = 0; i < size(m_particles); ++i)
            {
                PathFindParticle(m_particles[i], time);
            };
            */

            //added multithreading. works because all photons in the tile are independent (do not interact)
            ///*
            tbb::parallel_for(size_t(0), m_particles.size(), [this, &time](size_t i) {
                this->PathFindParticle(this->m_particles[i], time);
                });
            //*/
        };

        void PathFindParticle(Particle *particle, double time) //cannot do recursive function because of excessive use of pointers
        {
            if (!particle->IsAlive()) {return;};
            Point projection = particle->Project(time);
            while (!m_scintillator->HasInsideStrict(&projection))
            {
                Line line;
                line.point = particle->Position();
                line.vector = particle->Velocity();
                Point bounce_point = m_scintillator->FirstPositiveIntersection(&line);
                double dt = sqrt(((bounce_point - particle->Position()).Mag2())/(particle->Velocity().Mag2()));
                //inaccuracies in calculating dt may cause particle to be outside after moving by dt.
                //to avoid this we use following while loop, which in extreme cases will even back the particle up using negative dt
                //mostly affects small dt, so 2 reflections in a row, or iterations over small times such as by Animate()
                double smallt = 0.00001*dt;
                Point projection2 = particle->Project(dt);
                while (!m_scintillator->HasInsideStrict(&projection2))
                {
                    dt = dt-smallt;
                    projection2 = particle->Project(dt);
                };
                particle->Move(dt);
                ///*
                Point temp_position = particle->Position();
                if (m_sipm->HasInside(&temp_position))
                {
                    particle->Kill();
                    break;
                };
                //*/
                Vector normal = m_scintillator->Normal(&bounce_point);
                particle->Reflect(&normal);
                time = time - dt;
                if (time < 0) return;
                projection = particle->Project(time);
            };
            particle->Move(time);
        };

        void Animate(double time, double frametime)
        {
            int n = 1;
            auto mycanvas = new TCanvas();
            while (n*frametime < time)
            {
                PathFind(frametime);
                Draw();
                string str = std::to_string(n);
                char path[15] = "./frames/frame";
                char png[5] = ".png";
                const char* number(str.c_str());
                std::strcat(path, number);
                std::strcat(path,png);
                mycanvas->SaveAs(path);
                ++n;
            };
            DrawPaths();
        };
        void Rotate(double t_x, double t_y, double t_z)
        {
            m_scintillator->Rotate(t_x, t_y, t_z);
            m_sipm->Rotate(t_x, t_y, t_z);
            for (int i = 0; i < size(m_particles); ++i)
            {
                RotatePoint(m_particles[i]->PositionPointer(), t_x, t_y, t_z);
            };
        };
};

class Ring
{
    private:
    std::vector<Tile*> tiles;
    public:
    Ring(double ypos)
    {
        for (int i = 0; i < 14; ++i)
        {
            tiles.push_back(new Tile(-9.60, ypos, RADIUS, 0,0,0, true));
            tiles.push_back(new Tile(-3.20, ypos, RADIUS, 0,0,0, false));
            tiles.push_back(new Tile( 3.20, ypos, RADIUS, 0,0,0, false));
            tiles.push_back(new Tile( 9.60, ypos, RADIUS, 0,0,M_PI, true));
            tiles[4*i+0]->Rotate(0, -i*M_PI/7, 0);
            tiles[4*i+1]->Rotate(0, -i*M_PI/7, 0);
            tiles[4*i+2]->Rotate(0, -i*M_PI/7, 0);
            tiles[4*i+3]->Rotate(0, -i*M_PI/7, 0);

        }
    };
    void Draw()
    {
        for (int i = 0; i < size(tiles); ++i) {tiles[i]->Draw();};
    };
};

class Detector
{
    private:
    std::vector<Ring *> m_rings;
    std::vector<Threedpolygon *> m_backstop;
    public:
    Detector()
    {
        for (int i = -26; i < 26; ++i)
        {
            m_rings.push_back(new Ring((i+0.5)*6.22));
        };
        for (int i = 0; i < 14; ++i)
        {
            m_backstop.push_back(Backstop());
            m_backstop[i]->Move(0, 0, RADIUS);
            m_backstop[i]->Rotate(0, -i*M_PI/7, 0);
        };
    };
    void Draw()
    {
        for (int i = 0; i < size(m_rings); ++i) {m_rings[i]->Draw();};
        for (int i = 0; i < size(m_backstop); ++i) {m_backstop[i]->DrawWires();};
    };
};



void particles()
{

    auto mycanvas = new TCanvas();
    auto rulers = new TAxis3D();
    rulers->SetAxisColor(kRed, "X");
    rulers->SetAxisColor(kGreen, "Y");
    rulers->SetAxisColor(kBlue, "Z");
    rulers->Draw();

/*
    auto tile = new Tile(0,0,0,0,0,0, true);
    double half_photons = 250000;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0,1.0);
    for (int i = -half_photons; i < half_photons; ++i)
    {
        Point position(1+0.5/(2*half_photons)*i,1+0.5/(2*half_photons)*i,1+0.5/(2*half_photons)*i);
        Vector velocity(distribution(generator), distribution(generator), distribution(generator));
        tile->AddParticle(position, 10*velocity.Unit(), (i+half_photons)/(2*half_photons)*10);
    };

    tile->PathFind(200);
    auto hist = new TH1S("hist", "Time to catch", 1000, 0, 201);
    std::vector<double> times;
    for (int i = 0; i < size(tile->m_particles); ++i) {times.push_back(tile->m_particles[i]->Lifetime() + tile->m_particles[i]->Created());};

    delete tile;

    for (int i = 0; i < size(times); ++i)
    {
        hist->Fill(times[i]);
    };
    hist->Draw();

    auto tile2 = new Tile(0,0,0,0,0,0, false);
    for (int i = -half_photons; i < half_photons+1; ++i)
    {
        Point position(1+0.5/(2*half_photons)*i,1+0.5/(2*half_photons)*i,1+0.5/(2*half_photons)*i);
        Vector velocity(distribution(generator), distribution(generator), distribution(generator));
        tile2->AddParticle(position, 10*velocity.Unit(), (i+half_photons)/(2*half_photons)*10);
    };

    tile2->PathFind(200);
    auto hist1 = new TH1S("hist1", "Time to catch", 1000, 0, 200);
    std::vector<double> times2;
    for (int i = 0; i < size(tile2->m_particles); ++i) {times2.push_back(tile2->m_particles[i]->Lifetime() + tile2->m_particles[i]->Created());};

    delete tile2;

    for (int i = 0; i < size(times2); ++i)
    {
        hist1->Fill(times2[i]);
    };
    hist1->SetColors(kRed);
    hist1->Draw("same");
    mycanvas->SaveAs("./Signal.png");

*/
    ///*
    auto a = MakeBrick(350,350,350, 0,0,0);
    a->DrawWires();
    Detector detector;
    detector.Draw();
    //*/

};

