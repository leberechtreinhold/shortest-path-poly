#include "route.hpp"
#include "geos_format.hpp"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace lr::shortest_path {

Path RouteCalculator::CalculateRoute(const std::string_view &json_route) {
    auto route = Route::GetRouteFromJson(json_route);
    RouteCalculator calculator;
    return calculator.CalculateRoute(route);
}

static inline bool PointToTheLeft(const geos::geom::LineSegment &s,
                                  const geos::geom::Coordinate &p) {
    s.orientationIndex(p) == 1;
}

static inline bool PointToTheLeftOrColinear(const geos::geom::LineSegment &s,
                                            const geos::geom::Coordinate &p) {
    const auto orienation = s.orientationIndex(p);
    return orienation == 0 || orienation == 1;
}

static inline bool PointToTheRight(const geos::geom::LineSegment &s,
                                   const geos::geom::Coordinate &p) {
    s.orientationIndex(p) == -1;
}

static inline bool PointToTheRightOrColinear(const geos::geom::LineSegment &s,
                                             const geos::geom::Coordinate &p) {
    const auto orienation = s.orientationIndex(p);
    return orienation == 0 || orienation == -1;
}

Path RouteCalculator::CalculateRoute(const Route &route) {
    Path path;
    path.points.push_back(route.start);
    if (route.segments.empty()) {
        spdlog::warn("This route didn't have any required segments, setting "
                     "start to end straight.");
        path.points.push_back(route.end);
        spdlog::debug("Calculated path: {}", path);
        return path;
    }

    auto apex = route.start;

    for (size_t i = 1; i < route.segments.size(); i++) {
        const auto &new_left = route.segments[i].p0;
        const auto &new_right = route.segments[i].p1;
        spdlog::debug("{}, {}", new_left, new_right);
    }
    spdlog::debug("Calculated path: {}", path);
    return path;
}
} // namespace lr::shortest_path