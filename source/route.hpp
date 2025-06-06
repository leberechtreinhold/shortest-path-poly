#pragma once

#include <geos.h>
#include <nlohmann/json.hpp>
#include <string>
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

namespace utils {
std::string read_file_contents(const std::filesystem::path &path);
void write_file_contents(const std::filesystem::path &path,
                         const std::string_view &content);
} // namespace utils
} // namespace lr::shortest_path
