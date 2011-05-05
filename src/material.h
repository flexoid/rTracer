#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
public:
    Material(float InLambert, float InPhong, float InTransp)
        : lambert(InLambert), phong(InPhong), transperancy(InTransp) {}
    Material() : lambert(0), phong(0), transperancy(0) {}
    float lambert;
    float phong;
    float transperancy;
};

#endif // MATERIAL_H
