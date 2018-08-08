#ifndef PCG_RECTANGLE_HPP_
#define PCG_RECTANGLE_HPP_

#include <apex_base/Vector.h>
#include <vector>

namespace pcg
{
    /*
     *  Closed polygon
     */
    class rectangle
    {
    public:
        explicit rectangle();
        explicit rectangle(Vector2 center, float extents);

        void expand(float widthExpansion, float heightExpansion);

    public:

        Vector2 getTopLeft() const
        {
            return Vector2 {_center.x - _width / 2, _center.y - _height / 2};
        }

        Vector2 getTopRight() const
        {
            return Vector2 {_center.x + _width / 2, _center.y - _height / 2};
        }

        Vector2 getBottomLeft() const
        {
            return Vector2 {_center.x - _width / 2, _center.y + _height / 2};
        }

        Vector2 getBottomRight() const
        {
            return Vector2 {_center.x + _width / 2, _center.y + _height / 2};
        }

        static std::vector<rectangle> from_points(const std::vector<Vector2>& pts);

    private:
        Vector2 _center;
        float _width;
        float _height;
    };
}

#endif // PCG_RECTANGLE_HPP_
