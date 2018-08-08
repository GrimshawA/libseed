#include "conjuring/point_distribution.hpp"

#include <random>

namespace pcg
{
    point_distribution::point_distribution()
    {

    }

    std::vector<glm::vec2> point_distribution::even(int num, int width, int height)
    {
        std::default_random_engine generator;
        std::uniform_int_distribution<int> distribution(0,width);
        std::uniform_int_distribution<int> distribution2(0,height);

        std::vector<glm::vec2> pts {num};

        for (auto& p : pts)
        {
            p.x = distribution(generator);
            p.y = distribution2(generator);
        }

        return pts;
    }
}
