#include <vector>
#include <cmath>

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




void RotatePoint(Point* point, double t_x, double t_y, double t_z)
{
    Point old_point = *point;
    //Use Setter method to avoid result turning into a vector because of minus operation (Point - Point = Vector)
    point->SetX(old_point.X()*cos(t_y)*cos(t_z) + old_point.Y()*(sin(t_x)*sin(t_y)*cos(t_z) - cos(t_x)*sin(t_z)) + old_point.Z()*(cos(t_x)*sin(t_y)*cos(t_z) + sin(t_x)*sin(t_z)));
    point->SetY(old_point.X()*cos(t_y)*sin(t_z) + old_point.Y()*(sin(t_x)*sin(t_y)*sin(t_z) + cos(t_x)*cos(t_z)) + old_point.Z()*(cos(t_x)*sin(t_y)*sin(t_z) + sin(t_x)*cos(t_z)));
    point->SetZ(old_point.X()*(-1*sin(t_y)) + old_point.Y()*sin(t_x)*cos(t_y) + old_point.Z()*cos(t_x)*cos(t_y));
};

void RotateVector(Vector *vector, double t_x, double t_y, double t_z)
{
    Vector old_vector = *vector;
    vector->SetX(old_vector.X()*cos(t_y)*cos(t_z) + old_vector.Y()*(sin(t_x)*sin(t_y)*cos(t_z) - cos(t_x)*sin(t_z)) + old_vector.Z()*(cos(t_x)*sin(t_y)*cos(t_z) + sin(t_x)*sin(t_z)));
    vector->SetY(old_vector.X()*cos(t_y)*sin(t_z) + old_vector.Y()*(sin(t_x)*sin(t_y)*sin(t_z) + cos(t_x)*cos(t_z)) + old_vector.Z()*(cos(t_x)*sin(t_y)*sin(t_z) + sin(t_x)*cos(t_z)));
    vector->SetZ(old_vector.X()*(-1*sin(t_y)) + old_vector.Y()*sin(t_x)*cos(t_y) + old_vector.Z()*cos(t_x)*cos(t_y));
};

void MovePoint(Point *point, double x, double y, double z)
{
    point->SetCoordinates(point->X()+x, point->Y()+y, point->Z()+z);
};

class Line
{
    public:
    Point point;
    Vector vector;
    Line()
    {

    };
    Line(Point point, Vector vector)
    {
        this->point = point;
        this->vector = vector.Unit();
    };
    Point Intersection(Line *secondline)
    {
        Point intersection;
        float t = sqrt((this->point-secondline->point).Cross(secondline->vector).Mag2()/this->vector.Cross(secondline->vector).Mag2());
        if (this->vector.Dot(secondline->point - this->point) < 0) {t = -t;};
        intersection = this->point + t*this->vector;
        return(intersection);
    };
    bool IsParallel(Line *secondline)
    {
        if ((this->vector.Unit().Cross(secondline->vector.Unit())).Mag2() < THRESHOLD) {return(true);}
        else {return(false);};
    };

    bool IsWindschief(Line *secondline)
    {
        if (pow((this->point-secondline->point).Unit().Dot(this->vector.Unit().Cross(secondline->vector.Unit())),2) < THRESHOLD) {return(false);}
        else {return(true);};
    };

    bool DontCross(Line *secondline)
    {
        return(IsParallel(secondline) || IsWindschief(secondline));
    };

    void Draw(double length)
    {
        auto line3d = new TPolyLine3D;
        length = length/2;
        line3d->SetNextPoint(this->point.X() + length*this->vector.X(), this->point.Y() + length*this->vector.Y(), this->point.Z() + length*this->vector.Z());
        line3d->SetNextPoint(this->point.X() - length*this->vector.X(), this->point.Y() - length*this->vector.Y(), this->point.Z() - length*this->vector.Z());
        line3d->Draw();
    };

};

class Plane
{
    //a plane is fully defined by a point and a normal vector
    //this point may later be shifted to be in the center of a face
    public:
    Point point;
    Vector normal;
    Plane()
    {

    };
    Plane(Point point, Vector normal)
    {
        this->point = point;
        this->normal = normal.Unit();
    };
    bool IsParallel(Plane *secondplane)
    {
        if (this->normal.Cross(secondplane->normal).Mag2() == 0) {return true;}
        else {return(false);};
    };

    Line Intersection(Plane* secondplane)
    {
        //explanation of geometry in onenote
        Line liner;
        liner.vector = this->normal.Cross(secondplane->normal);
        double t;
        Vector b;
        b = this->normal.Unit()*(secondplane->normal.Dot(this->normal))-secondplane->normal;
        if ( (secondplane->point-this->point).Dot(b)<0 ) {b = -1*b;};
        t = -(this->point-secondplane->point).Dot(secondplane->normal)/(b.Dot(secondplane->normal));
        liner.point = this->point+t*b;
        //line liner(this->point+t*b, this->normal.Cross(secondplane->normal));
        return(liner);
    };

    Point Intersection(Line* line)
    {
        Point x;
        double t =-((line->point - this->point).Dot(this->normal))/(line->vector.Dot(this->normal));
        x = line->point + t * line->vector;
        return(x);
    };


    bool HasInsideStrict(Point *point)
    {
        if ((*point-this->point).Unit().Dot(this->normal.Unit()) > THRESHOLD){return(true);}   
        else {return(false);};
    }

    bool HasInside(Point *point)
    {
        //if projection of connecting line between point in plane and ?point
        //onto normal vector of plane is positive, point is inside the plane
        if ((*point-this->point).Unit().Dot(this->normal.Unit()) >= -THRESHOLD){return(true);}  //BAD THRESHOLD. Other uses of threshold allow threshold e-10, this max e-5
        else {return(false);};
    };

    bool IsOnPlane(Point *point)
    {
        if (pow(((*point-this->point).Unit().Dot(this->normal.Unit())),2) <= THRESHOLD) {return(true);}
        else {return(false);};
    };
    void Move(double x, double y, double z)
    {
        MovePoint(&(this->point), x, y, z);
    };
};

class Face
{
    //each face is defined by a plane, 
    //and boundary line: vertices connected by incrementally increasing angle
    //normal vector of corresponding plane defines the which way from the face is inside the 3d polygon
    public:
    Plane* plane;
    std::vector<Point> vertices;
    Point middle;
    TPolyLine3D lines;
    double reflective;
    Face(Point point, Vector normal, double reflective = 1)
    {
        this->plane = new Plane(point, normal);
        this->reflective = reflective;
    };

    bool IsParallel(Face* secondface)
    {
        return(this->plane->IsParallel(secondface->plane));
    };

    bool HasInside(Point *point)
    {
        return(this->plane->HasInside(point));
    };

    bool HasInsideStrict(Point *point)
    {
        return(this->plane->HasInsideStrict(point));
    };

    double Area(Point *point)    //return sum of areas of triangles between point and sequentially vertices of face
    {
        double area = 0;
        std::vector<Vector> relative_vectors;
        for (int i = 0; i < size(vertices); ++i)
        {
            relative_vectors.push_back(vertices[i] - *point);
        }; 
        relative_vectors.push_back(relative_vectors[0]);
        for (int i = 0; i < size(relative_vectors)-1; ++i)
        {
            area += sqrt((relative_vectors[i].Cross(relative_vectors[i+1]).Mag2()));
        };
        return(area);
    };
    bool IsInFace(Point *point)
    {
        //bool is_on_plane = plane->IsOnPlane(point);
        bool is_on_plane = true;
        bool is_inside_vertices;
        is_inside_vertices = ((Area(point) - Area(&middle)) <= THRESHOLD*size(vertices)*size(vertices));
        return(is_on_plane and is_inside_vertices);
    };

    void DrawPoints()
    {
        auto markers = new TPolyMarker3D;
        for (int i = 0; i < size(vertices); ++i){markers->SetNextPoint(vertices[i].X(), vertices[i].Y(), vertices[i].Z());};
        markers->SetMarkerSize(1);
        markers->SetMarkerColor(2);
        markers->SetMarkerStyle(8);
        markers->Draw();
    };

    void DrawWires()
    {
        this->lines.Draw();
    };
    /*
    void Move(double x, double y, double z)
    {
        plane->Move(double x, double y, double z)
        for (int i = 0; i < size(vertices); ++i)
        {
            vertices[i] = MovePoint(vertices[i], x, y, z);
        };
        middle = MovePoint(middle, x, y, z)
        for (int i = 0; i < size(vertices); ++i)
        {

            lines[i].SetCoordinates(vertices[i].X(), vertices[i].Y(), vertices[i].Z());
        };
        lines[lines.GetN()].SetCoordinates(vertices[0].X(), vertices[0].Y(), vertices[0].Z())
    };
    */

};

class Threedpolygon
{
    public:
        std::vector<Face*> faces;
        Threedpolygon(std::vector<Point> points, std::vector<Vector> normals)
        {
            //create the list of faces and initialize with the points and normals
            for (int i = 0; i < size(points); ++i)
            {
                faces.push_back(new Face(points[i], normals[i]));
            };
            GenerateFaces();
        };
        void GenerateLines(Face* face)
        {
            TPolyLine3D newline;
            for (int i = 0; i < size(face->vertices); ++i)
            {
                newline.SetNextPoint(face->vertices[i].X(), face->vertices[i].Y(), face->vertices[i].Z());
            };
            newline.SetNextPoint(face->vertices[0].X(), face->vertices[0].Y(), face->vertices[0].Z());
            face->lines = newline;
        };

        void GenerateFaces()
        {
            //for each face, find the intersection lines with all the other planes, 
            //create and fill a list called lines with all the intersection lines
            for (int i = 0; i < size(faces); ++i)
            {
                std::vector<Line> lines;
                std::vector<Point> preliminary_vertices;
                for (int j = 0; j < size(faces); ++j)
                {
                    if (i==j){continue;};
                    if (faces[i]->IsParallel(faces[j])) {continue;};
                    lines.push_back(faces[i]->plane->Intersection(faces[j]->plane));
                };

                //intersection of all the lines inside a plane of a face gives us preliminary vertices.
                //lines that dont cross (a. windschief (shouldnt happen as lines per def here are inside same plane), 
                //and b. parallel) are excluded from check
                //these may be false vertices that are excluded by other faces->plane
                for (int j = 0; j < size(lines); ++j)
                {
                    for (int k = j+1; k < size(lines); ++k)
                    {
                        if (j == k) {continue;};
                        if (lines[j].DontCross(&lines[k])) {continue;};
                        preliminary_vertices.push_back(lines[j].Intersection(&lines[k]));
                    };
                };

                /*
                //original idea was iterating over pre_vertices first, 
                //then nested loop over faces, but if pre_vert[j] got erased, 
                //it would try to check it for next face, and segmentation fault
                for (int k = 0; k < size(faces); ++k)   
                {
                    for (int j = size(preliminary_vertices)-1; j >= 0; --j)
                    {
                        if (!faces[k]->HasInside(&preliminary_vertices[j])) {preliminary_vertices.erase(preliminary_vertices.begin()+j);}; 
                    };
                };
                //better solution: use HasInside function and continue
                */
                for (int k = size(preliminary_vertices)-1; k >=0; --k)
                {
                    if (! this->HasInside(&preliminary_vertices[k])) {preliminary_vertices.erase(preliminary_vertices.begin()+k); continue;};
                };
                //sort the vertices by increasing angle to establish lines and write vertices and lines to face 
                SortVertices(faces[i], preliminary_vertices);
                GenerateLines(faces[i]);
            };
        }

        Vector Normal(Point *point)
        {
            Vector normal(0,0,0);
            for (int i = 0; i < size(this->faces); ++i)
            {
                if (faces[i]->IsInFace(point)) {normal += faces[i]->plane->normal;};
            };
            return(normal);
        };

        bool HasInside(Point *point)
        {
            bool is_inside = true;
            for (int i = 0; i < size(this->faces); ++i)
            {
                is_inside = is_inside and this->faces[i]->HasInside(point);
            };
            return(is_inside);
        };

        bool HasInsideStrict(Point *point)
        {
            bool is_inside = true;
            for (int i = 0; i < size(this->faces); ++i)
            {
                is_inside = is_inside and this->faces[i]->HasInsideStrict(point);
            };
            return(is_inside);
        };

        void SortVertices(Face* face, std::vector<Point> preliminary_vertices)
        {
            Point sum;
            for (int i = 0; i < size(preliminary_vertices); ++i)
            {
                sum = sum + preliminary_vertices[i];
            };
            Vector middle;
            middle = sum;
            middle = middle/size(preliminary_vertices);
            face->middle = middle;
            std::vector<Vector> relative_vectors;
            for (int i = 0; i < size(preliminary_vertices); ++i)
            {
                relative_vectors.push_back(preliminary_vertices[i] - face->middle);
            };
            //Set the first vertex
            std::vector<Point> sorted_vertices;
            Point x;
            x.SetCoordinates(preliminary_vertices[0].X(), preliminary_vertices[0].Y(), preliminary_vertices[0].Z());
            sorted_vertices.push_back(x);


            Vector reference;
            reference = relative_vectors[0];
            std::vector<double> angles;
            angles.push_back(-10);
            for (int i = 1; i < size(relative_vectors); ++i)
            {
                double temp_angle;
                temp_angle = (reference.Dot(relative_vectors[i]))/sqrt(reference.Mag2()*relative_vectors[i].Mag2());
                if (reference.Cross(relative_vectors[i]).Dot(face->plane->normal)<0)
                {
                    angles.push_back(-temp_angle - 2);
                }
                else {angles.push_back(temp_angle);};
            };
            for (int i = 1; i < size(angles); ++i)
            {
                int index = 1;
                double largest = -10;
                for (int j = 1; j < size(angles); ++j)
                {
                    if (angles[j] > largest) {index = j; largest = angles[j];};
                };
                angles[index] = -10;
                Point x;
                x.SetCoordinates(preliminary_vertices[index].X(), preliminary_vertices[index].Y(), preliminary_vertices[index].Z());
                sorted_vertices.push_back(x);
            };
            face->vertices = sorted_vertices;
        };

        void DrawVertices()
        {
            for (int i = 0; i < size(faces); ++i) {faces[i]->DrawPoints();};
        };

        void DrawWires()
        {
            for (int i = 0; i < size(faces); ++i) {faces[i]->DrawWires();};
        };

        std::vector<Point> Intersection(Line *line)
        {
            std::vector<Point> points;
            for (int i = 0; i < size(faces); ++i)
            {
                Point point;
                point = faces[i]->plane->Intersection(line);
                if (faces[i]->IsInFace(&point)) {points.push_back(point);};
            };
            return(points);
        };
        std::vector<Point> PositiveIntersection(Line *line)
        {
            std::vector<Point> points;
            points = Intersection(line);
            for (int i = size(points)-1; i >=0 ; --i)
            {
                double t = (points[i] - line->point).Dot(line->vector);
                if (t <= 0) {points.erase(points.begin()+i);};
            };
            return(points);
        };
        Point FirstPositiveIntersection(Line * line)
        {
            std::vector<Point> points = PositiveIntersection(line);
            double smallest = (points[0]-line->point).Mag2();
            int index = 0;
            for (int i = 0; i < size(points); ++i)
            {
                if ((points[i]-line->point).Mag2()< smallest) {index = i; smallest = (points[i]-line->point).Mag2();};
            };

            return(points[index]);
        };
        
        void Move(double x, double y, double z)
        {
            for (int i = 0; i < size(faces); ++i)
            {
                MovePoint(&faces[i]->plane->point, x, y, z);
            };
            GenerateFaces();
        };

        void Rotate(double t_x, double t_y, double t_z)
        {
            for (int i = 0; i < size(faces); ++i)
            {
                RotatePoint(&faces[i]->plane->point, t_x, t_y, t_z);
                RotateVector(&faces[i]->plane->normal, t_x, t_y, t_z);
            };
            GenerateFaces();
        };
        
};

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
void threedgeometry()
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
