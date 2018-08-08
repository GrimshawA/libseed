#ifndef PCG_RECTANGLE_HPP_
#define PCG_RECTANGLE_HPP_

#include <vector>
#include "conjuring/glm/vec2.hpp"

namespace pcg
{
    /*
     *  Closed polygon
     */
    class rectangle
    {
    public:
        explicit rectangle();
        explicit rectangle(glm::vec2 center, float extents);

        void expand(float widthExpansion, float heightExpansion);

    public:

        glm::vec2 getTopLeft() const
        {
            return glm::vec2 {_center.x - _width / 2, _center.y - _height / 2};
        }

        glm::vec2 getTopRight() const
        {
            return glm::vec2 {_center.x + _width / 2, _center.y - _height / 2};
        }

        glm::vec2 getBottomLeft() const
        {
            return glm::vec2 {_center.x - _width / 2, _center.y + _height / 2};
        }

        glm::vec2 getBottomRight() const
        {
            return glm::vec2 {_center.x + _width / 2, _center.y + _height / 2};
        }

        static std::vector<rectangle> from_points(const std::vector<glm::vec2>& pts);

    private:
        glm::vec2 _center;
        float _width;
        float _height;
    };
}

#endif // PCG_RECTANGLE_HPP_
