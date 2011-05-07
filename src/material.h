#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
public:
    Material(float InLambert, float InPhong, float InTransp, float InRefractionCoeff)
        : lambert(InLambert), phong(InPhong), transperancy(InTransp), refractionCoeff(InRefractionCoeff) {}
    Material() : lambert(0), phong(0), transperancy(0), refractionCoeff(0) {}
    float lambert;
    float phong;
    float transperancy;
    float refractionCoeff;
};

#endif // MATERIAL_H
