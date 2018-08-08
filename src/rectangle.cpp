#include "conjuring/rectangle.hpp"

namespace pcg
{
    rectangle::rectangle()
    {

    }

    rectangle::rectangle(glm::vec2 center, float extents)
    {
        _center = center;
        _width = _height = extents;
    }

    void rectangle::expand(float widthExpansion, float heightExpansion)
    {
        _width += widthExpansion;
        _height += heightExpansion;
    }

    std::vector<rectangle> rectangle::from_points(const std::vector<glm::vec2>& pts)
    {
        std::vector<rectangle> rects {pts.size()};

        for (int i = 0; i < pts.size(); ++i)
        {
            rects[i] = rectangle {pts[i], 1};
        }

        return rects;
    }
}
