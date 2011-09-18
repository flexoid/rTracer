#include "prism.h"
#include "math.h"
#include "../math_c.h"

Prism::Prism(Vector3 point1, Vector3 point2, Vector3 point3, Vector3 point4, Vector3 dir, float heigth, ColorRGB color, Material material)
{
    Vector3 points[8];
    points[0] = point1; points[1] = point2; points[2] = point3; points[3] = point4;
    dir = dir.Norm()*heigth;
    points[4] = point1+dir; points[5] = point2+dir; points[6] = point3+dir; points[7] = point4+dir;

    faces[0].points[0] = points[0]; faces[0].points[1] = points[1]; faces[0].points[2] = points[2]; faces[0].points[3] = points[3];
    faces[0].norm = ((faces[0].points[0]-faces[0].points[3]).CrossProduct(faces[0].points[0]-faces[0].points[1])).Norm();

    faces[1].points[0] = points[0]; faces[1].points[1] = points[1]; faces[1].points[2] = points[5]; faces[1].points[3] = points[4];
    faces[1].norm = ((faces[1].points[0]-faces[1].points[1]).CrossProduct(faces[1].points[0]-faces[1].points[3])).Norm();

    faces[2].points[0] = points[0]; faces[2].points[1] = points[3]; faces[2].points[2] = points[7]; faces[2].points[3] = points[4];
    faces[2].norm = ((faces[2].points[0]-faces[2].points[3]).CrossProduct(faces[2].points[0]-faces[2].points[1])).Norm();

    faces[3].points[0] = points[1]; faces[3].points[1] = points[2]; faces[3].points[2] = points[6]; faces[3].points[3] = points[5];
    faces[3].norm = ((faces[3].points[0]-faces[3].points[1]).CrossProduct(faces[3].points[0]-faces[3].points[3])).Norm();

    faces[4].points[0] = points[2]; faces[4].points[1] = points[3]; faces[4].points[2] = points[7]; faces[4].points[3] = points[6];
    faces[4].norm = ((faces[4].points[0]-faces[4].points[1]).CrossProduct(faces[4].points[0]-faces[4].points[3])).Norm();

    faces[5].points[0] = points[4]; faces[5].points[1] = points[7]; faces[5].points[2] = points[6]; faces[5].points[3] = points[5];
    faces[5].norm = ((faces[5].points[0]-faces[5].points[3]).CrossProduct(faces[5].points[0]-faces[5].points[1])).Norm();

    for(int i=0;i<6;i++)
        faces[i].D = faces[i].norm.DotProduct(faces[i].points[0]);


    this->color = color;
    this->material = material;
}

Vector3 Prism::Norm(Vector3 point)
{
    Vector3 norm = Vector3::Null();
    for(int i=0; i<6; i++)
    {
        if (fabs(faces[i].norm.DotProduct(point)-faces[i].D)<EPS)
        {
            norm = faces[i].norm;
        }
    }
    return norm;
}

Vector3 Prism::Trace(Ray ray)
{
    Vector3 intersecPoint = Vector3::Null();
    for(int i=0; i<6; i++)
    {
        float sn = ray.dir.DotProduct(faces[i].norm);

        if (sn==0)
            continue;

        float dotPointNorm = faces[i].points[0].DotProduct(faces[i].norm);
        float t = (dotPointNorm - ray.from.DotProduct(faces[i].norm)) / sn;

        if (t < EPS)
            continue;

        Vector3 point = ray.from + ray.dir * t;
        if (isInside(point,faces[i]))
            if (intersecPoint==Vector3::Null() || point.DistanceFrom(ray.from) < intersecPoint.DistanceFrom(ray.from))
                intersecPoint = point;
    }
    return intersecPoint;
}

bool Prism::isInside(Vector3 point, Face face)
{
    Vector3 points[4]=face.points;
    if (fabs(face.norm.z)>EPS)
    {
        points[0].z=0; points[1].z=0; points[2].z=0; points[3].z=0; point.z=0;
    }
    else if (fabs(face.norm.x)>EPS)
    {
        points[0].x=points[0].z; points[1].x=points[1].z; points[2].x=points[2].z; points[3].x=points[3].z; point.x=point.z;
        points[0].z=0; points[1].z=0; points[2].z=0; points[3].z=0; point.z=0;
    }
    else
    {
        points[0].y=points[0].z; points[1].y=points[1].z; points[2].y=points[2].z; points[3].y=points[3].z; point.y=point.z;
        points[0].z=0; points[1].z=0; points[2].z=0; points[3].z=0; point.z=0;
    };
    bool ans[4];
    for(int i=0; i<4; i++)
    {
        Vector3 dir=points[(i+1)%4]-points[i];
        ans[i]=(dir.y*point.x-dir.x*point.y-dir.y*points[i].x+dir.x*points[i].y > EPS) ? true : false;
    }
    bool pos=true, neg=false;
    for(int i=0; i<4;i++)
    {
        pos &= ans[i];
        neg |= ans[i];
    }
    if (pos || !neg)
        return true;
    else
        return false;
}

ColorRGB Prism::Color()
{
    return color;
}
