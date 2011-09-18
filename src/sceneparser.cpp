#include "sceneparser.h"

Scene* SceneParser::LoadScene(const char *filename)
{
    FILE *file;
    file = fopen(filename,"r");
    if (file != 0)
    {
        char type[16];
        char str[256];

        fgets_nocomm(str,sizeof(str),file);
        Scene* scene = new Scene(ParseColor(str));

        while(fgets_nocomm(str,sizeof(str),file))
        {
            str[strlen(str)-1] = '\0';
            sscanf(str, "%s", type);
            for (int i = strlen(type) + 1; i < strlen(str) + 1; i++)
                str[i-strlen(type)-1] = str[i];

            if (strcmp(type, "material") == 0)
                ParseMaterial(str);
            else if (strcmp(type, "light") == 0)
                scene->AddLight(ParseLight(str));
            else if (strcmp(type, "camera") == 0)
                scene->AddCamera(ParseCamera(str));
            else if (strcmp(type, "sphere") == 0)
                scene->AddPrimitive(ParseSphere(str));
            else if (strcmp(type, "plane") == 0)
                scene->AddPrimitive(ParsePlane(str));
            else if (strcmp(type, "prism") == 0)
                scene->AddPrimitive(ParsePrism(str));
        }
        fclose(file);
        return scene;
    }
    else
        return 0;
}

Sphere* SceneParser::ParseSphere(const char *str)
{
    float f[4];
    int i[4];
    sscanf(str, "%f %f %f %f %d %d %d %d", &f[0], &f[1], &f[2], &f[3], &i[0], &i[1], &i[2], &i[3]);
    Material* mat = materials.find(i[3])->second;
    if (mat)
        return new Sphere(Vector3(f[0], f[1], f[2]), f[3], ColorRGB(i[0], i[1], i[2]), *mat);
    else
        return 0;
}

Prism* SceneParser::ParsePrism(const char *str)
{
    float f[16];
    int i[4];
    sscanf(str, "%f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %f %d %d %d %d",
           &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7], &f[8], &f[9],
           &f[10], &f[11], &f[12], &f[13], &f[14], &f[15], &i[0], &i[1], &i[2], &i[3]);
    Material* mat = materials.find(i[3])->second;
    if (mat)
        return new Prism(Vector3(f[0], f[1], f[2]), Vector3(f[3], f[4], f[5]), Vector3(f[6], f[7], f[8]),
                         Vector3(f[9], f[10], f[11]), Vector3(f[12], f[13], f[14]), f[15],
                         ColorRGB(i[0], i[1], i[2]), *mat);
    else
        return 0;
}

Plane* SceneParser::ParsePlane(const char *str)
{
    float f[6];
    int i[4];
    sscanf(str, "%f %f %f %f %f %f %d %d %d %d", &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &i[0], &i[1], &i[2], &i[3]);
    Material* mat = materials.find(i[3])->second;
    if (mat)
        return new Plane(Vector3(f[0], f[1], f[2]), Vector3(f[3], f[4], f[5]), ColorRGB(i[0], i[1], i[2]), *mat);
    else
        return 0;
}

Light* SceneParser::ParseLight(const char *str)
{
    float f[4];
    sscanf(str, "%f %f %f %f", &f[0], &f[1], &f[2], &f[3]);
    return new Light(Vector3(f[0], f[1], f[2]), f[3]);
}

Camera* SceneParser::ParseCamera(const char *str)
{
    float f[8];
    sscanf(str, "%f %f %f %f %f %f %f %f",
           &f[0], &f[1], &f[2], &f[3], &f[4], &f[5], &f[6], &f[7]);
    return new Camera(Vector3(f[0], f[1], f[2]), Vector3(f[3], f[4], f[5]), f[6], f[7]);
}

Material* SceneParser::ParseMaterial(const char *str)
{
    int id;
    float f[5];
    sscanf(str, "%d %f %f %f %f %f", &id, &f[0], &f[1], &f[2], &f[3], &f[4]);
    Material* mat = new Material(f[0], f[1], f[2], f[3], f[4]);
    materials[id] = mat;
}

ColorRGB SceneParser::ParseColor(const char *str)
{
    int i[3];
    sscanf(str, "%d %d %d", &i[0], &i[1], &i[2]);
    return ColorRGB(i[0], i[1], i[2]);
}

char* SceneParser::fgets_nocomm(char *s, int size, FILE *stream)
{
    while (1)
    {
        char* res = fgets(s, size, stream);
        if (!res)
            return 0;
        else if (res[0] != ';' && res[0] != '\n' && res[0] != ' ')
            return s;
    }
}
