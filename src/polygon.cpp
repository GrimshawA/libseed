#include "polygon.hpp"

#include "clipper/clipper.hpp"

namespace pcg
{
    polygon::polygon()
    {

    }

    polygon::polygon(const std::vector<Vector2>& pts)
    {
        _points = pts;
    }

    std::vector<edge> polygon::edges()
    {
        if (_points.size() < 2)
            return {};

        std::vector<edge> e;

        for (int i = 1; i < _points.size(); ++i)
        {
            Vector2 p1 = _points[i-1];
            Vector2 p2 = _points[i];
            e.push_back(edge {p1, p2});
        }

        // close
        e.push_back(edge {_points[_points.size() - 1], _points[0]});

        return e;
    }

    std::vector<Vector2> polygon::points() const
    {
        return _points;
    }

    void polygon::clip(const std::vector<polygon>& clipGroup)
    {
        using namespace ClipperLib;

        auto clipperPoly = [&](const polygon& poly)
        {
            ClipperLib::Path p;
            for (auto& polyP : poly.points())
            {
                p.push_back(IntPoint(polyP.x, polyP.y));
            }
            return p;
        };

        Paths subj(1), clip(clipGroup.size()), solution;

        //define outer blue 'subject' polygon
        subj[0] = clipperPoly(*this);

        for (int i = 0; i < clipGroup.size(); ++i)
        {
            clip[i] = clipperPoly(clipGroup[i]);
        }

        Clipper c;
        c.AddPaths(subj, ptSubject, true);
        c.AddPaths(clip, ptClip, true);
        c.Execute(ctDifference, solution, pftNonZero, pftNonZero);

        std::vector<Vector2> myPoints;

        for (auto& p : solution[0])
        {
            myPoints.push_back(Vector2 {p.X, p.Y});
        }

        _points = myPoints;
    }

    void polygon::inset(int width)
    {
        using namespace ClipperLib;

        auto clipperPoly = [&](const polygon& poly)
        {
            ClipperLib::Path p;
            for (auto& polyP : poly.points())
            {
                p.push_back(IntPoint(polyP.x, polyP.y));
            }
            return p;
        };

        Path subj;
        Paths solution;
        subj = clipperPoly(*this);

        ClipperOffset co;
        co.AddPath(subj, jtRound, etClosedPolygon);
        co.Execute(solution, width);

        std::vector<Vector2> myPoints;

        for (auto& p : solution[0])
        {
            myPoints.push_back(Vector2 {p.X, p.Y});
        }

        _points = myPoints;
    }

    polygon polygon::from_rectangle(const rectangle& rect)
    {
        Vector2 topLeft = rect.getTopLeft();
        Vector2 topRight = rect.getTopRight();
        Vector2 bottomLeft = rect.getBottomLeft();
        Vector2 bottomRight = rect.getBottomRight();

        return polygon {{topLeft, topRight, bottomRight, bottomLeft}};
    }

    std::vector<polygon> polygon::from_rectangles(const std::vector<rectangle>& rects)
    {
        std::vector<polygon> polygons {rects.size()};

        for (int i = 0; i < polygons.size(); ++i)
        {
            polygons[i] = polygon::from_rectangle(rects[i]);
        }

        return polygons;
    }

    std::vector<polygon> polygon::clip_group(const std::vector<polygon>& polys)
    {
        using namespace ClipperLib;

        std::vector<polygon> out {polys.size()};

        auto clipperPoly = [&](const polygon& poly)
        {
            ClipperLib::Path p;
            for (auto& polyP : poly.points())
            {
                p.push_back(IntPoint(polyP.x, polyP.y));
            }
            return p;
        };

        auto clipped_polygon = [&](int index)
        {
            //from clipper.hpp ...
            //typedef signed long long cInt;
            //struct IntPoint {cInt X; cInt Y;};
            //typedef std::vector<IntPoint> Path;
            //typedef std::vector<Path> Paths;

            Paths subj(1), clip(polys.size() - 1), solution;

            //define outer blue 'subject' polygon
            subj[0] = clipperPoly(polys[index]);

            for (int i = 0, j = 0; i < polys.size(); ++i)
            {
                if (i != index)
                {
                    clip[j++] = clipperPoly(polys[i]);
                }
            }

            Clipper c;
            c.AddPaths(subj, ptSubject, true);
            c.AddPaths(clip, ptClip, true);
            c.Execute(ctDifference, solution, pftNonZero, pftNonZero);

            std::vector<Vector2> myPoints;

            for (auto& p : solution[0])
            {
                myPoints.push_back(Vector2 {p.X, p.Y});
            }

            return polygon {myPoints};
        };

        for (int i = 0; i < polys.size(); ++i)
        {
            out[i] = clipped_polygon(i);
        }

        return out;
    }
}
