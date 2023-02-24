#pragma once

namespace PREN
{
    template <class T, class U>
    class Integratable
    {
    public:
        virtual T Integrate(U a, U b) = 0;
    };
}
