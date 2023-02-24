#pragma once

namespace PREN
{
    template <class T, class U>
    class Derivable
    {
    public:
        virtual T Derive(U x) = 0;
    };
}
