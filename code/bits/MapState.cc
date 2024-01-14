#include "MapState.h"

namespace xy {

  namespace {

  constexpr int MapWidth = 250;
  constexpr int MapHeight = 250;

    constexpr int InitialFactor = 50;

    void midpointDisplacementRecursive(std::vector<gf::Vector2i>& points, std::size_t i0, std::size_t i1, int factor, gf::Random& random)
    {
      if (i1 - i0 <= 1) {
        return;
      }

      if (factor == 0) {
        factor = 1;
      }

      std::size_t mid = (i0 + i1) / 2;
      assert(i0 < mid && mid < i1);

      gf::Vector2i midPoint = (points[i0] + points[i1]) / 2;
      midPoint += gf::diry(random.computeUniformInteger(-factor, factor));

      points[mid] = midPoint;
      midpointDisplacementRecursive(points, i0, mid, factor / 2, random);
      midpointDisplacementRecursive(points, mid, i1, factor / 2, random);
    }

    std::vector<gf::Vector2i> midpointDisplacement(gf::Vector2i p0, gf::Vector2i p1, gf::Random& random)
    {
      const std::size_t size = std::abs(p1.x - p0.x + 1);
      std::vector<gf::Vector2i> points(size);
      points.front() = p0;
      points.back() = p1;
      midpointDisplacementRecursive(points, 0, size - 1, InitialFactor, random);
      return points;
    }

  }

  MapState::MapState(gf::Random& random)
  : cells({ MapWidth, MapHeight })
  {
    auto points = midpointDisplacement({ 0, MapHeight / 2 }, { MapWidth - 1, MapHeight / 2 }, random);

    for (auto point : points) {
      while (point.y < MapHeight) {
        cells(point).biome = Biome::Gravel;
        ++point.y;
      }
    }

  }

}
