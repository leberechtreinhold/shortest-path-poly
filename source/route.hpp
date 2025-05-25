#pragma once

#include <geos.h>
#include <string>
#include <nlohmann/json.hpp>
#include <vector>

namespace lr::shortest_path {

struct Route {
    geos::geom::Coordinate start;
    geos::geom::Coordinate end;
    std::vector<geos::geom::LineSegment> segments;

    static Route GetRouteFromJson(const std::string_view &json_route);
};

struct Path {
    std::vector<geos::geom::Coordinate> points;
};

class RouteCalculator {
  public:
    static nlohmann::json CalculateRoute(const std::string_view &json_route);
    Path CalculateRoute(const Route &route);
    nlohmann::json ResultToJson(const Route &route, const Path &calculated);
};
} // namespace lr::shortest_path
