#ifndef PCG_WORLD_PARAMS_HPP_
#define PCG_WORLD_PARAMS_HPP_

#include <apex_base/Vector.h>
#include <vector>

namespace pcg
{
    /*
     *  Closed polygon
     */
    class world_parameters
    {
    public:
        explicit world_parameters();

    public:

        enum world_size
        {
            Small,
            Medium,
            Large
        };

        world_size size;

    private:
    };
}

#endif // PCG_WORLD_PARAMS_HPP_
