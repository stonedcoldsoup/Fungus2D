#ifndef FISMATH_CONFIG_H
#define FISMATH_CONFIG_H

#include <Phoenix.h>

namespace Fungus2D
{
    namespace math
    {
        typedef phoenix::Vector2d native_vector2;
        
        struct vector2
        {
            native_vector2 _native;
            
            vector2(const native_vector2 &_native):
                _native(_native)
            {}
            
            vector2():
                _native()
            {}
            
            vector2(const vector2 &m):
                _native(m._native)
            {}
            
            vector2 &operator =(const vector2 &m)
            {
                _native = m._native;
            }
            
            float operator[](int i) const
            {
                switch (i)
                {
                }l
                if (i == 0)
                    return _native.GetX();
                else if (i
            }
            
            float &operator[](int i)
        };
    }
}
