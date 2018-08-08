#ifndef PCG_CREATOR_HPP_
#define PCG_CREATOR_HPP_

#include <apex_base/Vector.h>
#include <vector>

#include "world_parameters.hpp"

namespace pcg
{
    /*
     *  Closed polygon
     */
    class creator
    {
    public:
        explicit creator();


        void createDistricts(const world_parameters& params);
        void createBuilding();

    private:
    };
}

#endif // PCG_CREATOR_HPP_
