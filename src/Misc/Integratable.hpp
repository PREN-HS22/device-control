#pragma once

namespace CleaningDevice
{
    template <typename T, typename U>
    class Integratable
    {
    public:
        virtual T Integrate(U a, U b, U dx) = 0;
    };
}
