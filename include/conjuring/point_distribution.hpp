#ifndef PCG_POINT_DISTRIBUTION_HPP_
#define PCG_POINT_DISTRIBUTION_HPP_

#include <apex_base/Vector.h>
#include <vector>

namespace pcg
{
    /*
     *  Closed polygon
     */
    class point_distribution
    {
    public:
        explicit point_distribution();

    public:

        static std::vector<Vector2> even(int num, int width, int height);

    private:
    };
}

#endif // PCG_POINT_DISTRIBUTION_HPP_
