#include "creator.hpp"
#include "point_distribution.hpp"
#include "image_render.hpp"
#include "rectangle.hpp"
#include "cropper.hpp"
#include "polygon.hpp"

#include <apex_base/math/Math.h>

namespace pcg
{
    creator::creator()
    {

    }

    void creator::createDistricts(const world_parameters& params)
    {
        int numDistricts = math::randomInt(10, 15);

        auto districtSeedPoints = point_distribution::even(numDistricts, 10000, 10000);

        auto districtRects = rectangle::from_points(districtSeedPoints);

        for (auto& district : districtRects)
        {
            district.expand(math::randomInt(2000, 8000), math::randomInt(2000, 8000));
        }

        auto districtPolygons = polygon::from_rectangles(districtRects);

        for (int i = 0; i < districtPolygons.size(); ++i)
        {
            std::vector<polygon> otherPolygons;
            for (int j = 0; j < districtPolygons.size(); ++j)
            {
                if (j != i)
                    otherPolygons.push_back(districtPolygons[j]);
            }

            districtPolygons[i].clip(otherPolygons);
            districtPolygons[i].inset(-10);
        }

        image_render img {"points.png", 1024, 1024, 10000, 10000};

        for (auto& p : districtSeedPoints)
        {
            img.drawPoint(sf::Color::White, p);
        }

        for(auto& poly : districtPolygons)
        {
            sf::Color c = sf::Color::Blue;
            c.r = math::randomInt(0, 255);
            c.g = math::randomInt(0, 255);
            c.b = math::randomInt(0, 255);
            img.drawPolygon(c, poly);
        }

//        polygon p {{ Vector2 {1000, 1000},
//                    Vector2 {5000, 1000},
//                    Vector2 {5000, 5000},
//                    Vector2 {1000, 5000}
//                  }};

//        img.drawPolygon(sf::Color::Green, p);

        img.save();
    }

    class structure
    {
    public:
        enum archtypes
        {
            Apartments,
            House,
            Hospital,
            CityHall,
            Offices,
            PoliceDept,
            Arcade,
            Store,
            Mall,
            Hotel,
            School,
            Prison,
            ParkingLot
        };

        class room
        {
        public:
            polygon _walls;
        };

        class floor
        {
        public:
            std::vector<room> rooms;
        };

        std::vector<floor> _floors;
        polygon            _outerWall;
    };

    void creator::createBuilding()
    {

    }
}
