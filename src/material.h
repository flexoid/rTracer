#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
public:
    Material(float InLambert, float InPhong, float InTransp)
        : lambert(InLambert), phong(InPhong), transperancy(InTransp) {}
    float lambert;
    float phong;
    float transperancy;
};

#endif // MATERIAL_H
