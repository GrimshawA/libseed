#ifndef PCG_POLYGON_HPP_
#define PCG_POLYGON_HPP_

#include <apex_base/Vector.h>
#include <vector>
#include "rectangle.hpp"

namespace pcg
{
    struct edge
    {
        Vector2 p1, p2;
    };

    /*
     *  Closed polygon
     */
    class polygon
    {
    public:
        explicit polygon();
        explicit polygon(const std::vector<Vector2>& pts);


        std::vector<edge> edges();
        std::vector<Vector2> points() const;

        void clip(const std::vector<polygon>& clipGroup);
        void inset(int width);

    public:

        static polygon from_rectangle(const rectangle& rect);
        static std::vector<polygon> from_rectangles(const std::vector<rectangle>& rects);

        static std::vector<polygon> clip_group(const std::vector<polygon>& polys);

    private:
        std::vector<Vector2> _points;
    };
}

#endif // PCG_POLYGON_HPP_
