#include "image_render.hpp"
#include "polygon.hpp"
#include <apex_base/math/Math.h>

#include <iostream>

namespace pcg
{
    image_render::image_render(const std::string& filename,
                               int width,
                               int height,
                               int logicalWidth,
                               int logicalHeight)
        : _filename(filename)
        , _logicalWidth(logicalWidth)
        , _logicalHeight(logicalHeight)
    {
        img.create(width, height, sf::Color::Black);
    }

    void image_render::save()
    {
        if (!img.saveToFile(_filename))
        {
            std::cout << "[PCG] Failed to save image: " << _filename << std::endl;
            return;
        }
        std::cout << "[PCG] Saved image: " << _filename << std::endl;
    }

    void image_render::drawPoint(sf::Color c, Vector2 p)
    {
        int pointWidth = 4;

        int topLeftX = p.x - pointWidth / 2;
        int topLeftY = p.y - pointWidth / 2;

        for (int i = 0; i < pointWidth; ++i)
        {
            for (int j = 0; j < pointWidth; ++j)
            {
                set(topLeftX + i, topLeftY + j, c);
            }
        }
    }

    void image_render::drawLine(sf::Color c, Vector2 start, Vector2 end)
    {
        int lineLength = math::distance(start.x, start.y, end.x, end.y);
        Vector2 lineDir = end - start;

        lineDir.normalize();

        for (int i = 0; i < lineLength; ++i)
        {
            int x = start.x + lineDir.x * i;
            int y = start.y + lineDir.y * i;
            drawPoint(c, Vector2 {x, y});
        }
    }

    void image_render::drawPolygon(sf::Color c, polygon& p)
    {
        for (auto& edge : p.edges())
        {
            //std::cout << "EDGE P1: " << edge.p1.x << ", " << edge.p1.y << std::endl;
            //std::cout << "EDGE P2: " << edge.p2.x << ", " << edge.p2.y << std::endl;
            drawLine(c, edge.p1, edge.p2);
        }
    }

    void image_render::set(int x, int y, sf::Color c)
    {
        float ratioX = float(img.getSize().x) / _logicalWidth;
        float ratioY = float(img.getSize().y) / _logicalHeight;

        int normalizedX = x * ratioX;
        int normalizedY = y * ratioY;

        if (normalizedX < 0 || normalizedY < 0)
            return;

        if (normalizedX >= img.getSize().x || normalizedY >= img.getSize().y)
            return;


        img.setPixel(normalizedX, normalizedY, c);
    }
}
