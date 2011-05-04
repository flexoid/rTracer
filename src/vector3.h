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
    Vector3( ) : x(0), y(0), z(0)
    {
    }

    // Operator Overloads
    inline bool operator== (const Vector3& V2) const
    {
        return (x == V2.x && y == V2.y && z == V2.z);
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
        float fInv = 1.0f / S;
        return Vector3 (x * fInv , y * fInv, z * fInv);
    }

    inline Vector3 operator/ (const Vector3& V2) const
    {
        return Vector3 (x / V2.x,  y / V2.y,  z / V2.z);
    }

    inline Vector3 operator* (const Vector3& V2) const
    {
        return Vector3 (x * V2.x,  y * V2.y,  z * V2.z);
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
    inline float Dot( const Vector3 &V1 ) const
    {
        return V1.x*x + V1.y*y + V1.z*z;
    }

    inline Vector3 CrossProduct( const Vector3 &V2 ) const
    {
        return Vector3(
                    y * V2.z  -  z * V2.y,
                    z * V2.x  -  x * V2.z,
                    x * V2.y  -  y * V2.x 	);
    }

    // Return vector rotated by the 3x3 portion of matrix m
    Vector3 RotByMatrix( const float m[16] ) const
    {
        return Vector3(
                    x*m[0] + y*m[4] + z*m[8],
                    x*m[1] + y*m[5] + z*m[9],
                    x*m[2] + y*m[6] + z*m[10] );
    }

    // These require math.h for the sqrtf function
    float Magnitude( ) const
    {
        return sqrtf( x*x + y*y + z*z );
    }

    float Distance( const Vector3 &V1 ) const
    {
        return ( *this - V1 ).Magnitude();
    }

    inline void Normalize()
    {
        float fMag = ( x*x + y*y + z*z );
        if (fMag == 0) {return;}

        float fMult = 1.0f/sqrtf(fMag);
        x *= fMult;
        y *= fMult;
        z *= fMult;
        return;
    }

    static Vector3 Null()
    {
        return Vector3(0, 0, 0);
    }
};
#endif // VECTOR3_H
