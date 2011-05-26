#ifndef MATERIAL_H
#define MATERIAL_H

class Material
{
public:
    Material(float lambert, float phong, float reflectionCoeff, float transperancy, float refractionCoeff)
        : lambert(lambert), phong(phong), reflectionCoeff(reflectionCoeff),
            transperancy(transperancy), refractionCoeff(refractionCoeff) {}
    Material() : lambert(0), phong(0), reflectionCoeff(0), transperancy(0), refractionCoeff(0) {}
    float lambert;
    float phong;
    float reflectionCoeff;
    float transperancy;
    float refractionCoeff;
};

#endif // MATERIAL_H
