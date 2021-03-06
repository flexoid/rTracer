#ifndef VECTOR3_H
#define VECTOR3_H

#include <math.h>

class Vector3
{
public:
    // Data
    float x, y, z;

    // Ctors
    Vector3( float InX, float InY, float InZ ) : x( InX ), y( InY ), z( InZ )
    {
    }
    Vector3( ) : x(0.0f), y(0.0f), z(0.0f)
    {
    }

    // Operator Overloads
    inline bool operator== (const Vector3& V2) const
    {
        return (x == V2.x && y == V2.y && z == V2.z);
    }

    inline bool operator!= (const Vector3& V2) const
    {
        return !(*this == V2);
    }

    inline Vector3 operator+ (const Vector3& V2) const
    {
        return Vector3( x + V2.x,  y + V2.y,  z + V2.z);
    }

    inline Vector3 operator- (const Vector3& V2) const
    {
        return Vector3( x - V2.x,  y - V2.y,  z - V2.z);
    }

    inline Vector3 operator- ( ) const
    {
        return Vector3(-x, -y, -z);
    }

    inline Vector3 operator/ (float S ) const
    {
        return Vector3 (x / S , y / S, z / S);
    }

    inline Vector3 operator* (const Vector3& V2) const
    {
        return CrossProduct(V2);
    }  

    inline Vector3 operator* (float S) const
    {
        return Vector3 (x * S,  y * S,  z * S);
    }

    inline void operator+= ( const Vector3& V2 )
    {
        x += V2.x;
        y += V2.y;
        z += V2.z;
    }

    inline void operator-= ( const Vector3& V2 )
    {
        x -= V2.x;
        y -= V2.y;
        z -= V2.z;
    }

    inline float operator[] ( int i )
    {
        if ( i == 0 ) return x;
        else if ( i == 1 ) return y;
        else return z;
    }

    // Functions
    inline float DotProduct( const Vector3 &V1 ) const
    {
        return V1.x*x + V1.y*y + V1.z*z;
    }

    Vector3 CrossProduct( const Vector3 &V1 ) const
    {
        return Vector3 (y*V1.z-z*V1.y, z*V1.x-x*V1.z, x* V1.y-y*V1.x);
    }

    // These require math.h for the sqrtf function
    float Length( ) const
    {
        return sqrtf( x*x + y*y + z*z );
    }

    float DistanceFrom( const Vector3 &V1 ) const
    {
        return ( *this - V1 ).Length();
    }

    Vector3 Norm()
    {
        float fMag = ( x*x + y*y + z*z );
        if (fMag == 0) return Vector3(x,y,z);
        float fMult = 1.0f/sqrtf(fMag);
        return Vector3(x*fMult, y*fMult, z*fMult);
    }

    static Vector3 Null()
    {
        return Vector3(0.0f, 0.0f, 0.0f);
    }
};
#endif // VECTOR3_H
