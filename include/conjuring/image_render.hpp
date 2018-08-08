#ifndef PCG_IMAGE_RENDER_HPP_
#define PCG_IMAGE_RENDER_HPP_

#include <apex_base/Vector.h>
#include <vector>

#include <SFML/Graphics.hpp>

namespace pcg
{
    class polygon;

    /*
     *  Closed polygon
     */
    class image_render
    {
    public:
        explicit image_render(const std::string& filename,
                              int width,
                              int height,
                              int logicalWidth,
                              int logicalHeight);

        void save();

        void drawPoint(sf::Color c, Vector2 p);
        void drawLine(sf::Color c, Vector2 start, Vector2 end);
        void drawPolygon(sf::Color c, polygon& p);

        void set(int x, int y, sf::Color c);

    private:
        sf::Image img;
        std::string _filename;
        int _logicalWidth;
        int _logicalHeight;
    };
}

#endif // PCG_IMAGE_RENDER_HPP_
