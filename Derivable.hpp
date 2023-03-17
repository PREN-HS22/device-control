#pragma once

namespace PREN
{
    template <typename T, typename U>
    class Derivable
    {
    public:
        virtual T Derive(U x) = 0;
    };
}
