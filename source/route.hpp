#pragma once

#include <geos.h>
#include <string>
#include <tl/expected.hpp>
#include <vector>

namespace lr::shortest_path {

struct Route {
    geos::geom::Coordinate start;
    geos::geom::Coordinate end;
    std::vector<geos::geom::LineSegment> required_segments;

    static Route GetRouteFromJson(const std::string_view &json_route);
};

struct Path {
    std::vector<geos::geom::Coordinate> points;
};

class RouteCalculator {
  public:
    static Path CalculateRoute(const std::string_view &json_route);
    Path CalculateRoute(const Route &route);
};
} // namespace lr::shortest_path

