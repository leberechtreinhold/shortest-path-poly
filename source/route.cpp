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
    return s.orientationIndex(p) == 1;
}

static inline bool PointToTheLeftOrColinear(const geos::geom::LineSegment &s,
                                            const geos::geom::Coordinate &p) {
    const auto orientation = s.orientationIndex(p);
    return orientation == 0 || orientation == 1;
}

static inline bool PointToTheRight(const geos::geom::LineSegment &s,
                                   const geos::geom::Coordinate &p) {
    return s.orientationIndex(p) == -1;
}

static inline bool PointToTheRightOrColinear(const geos::geom::LineSegment &s,
                                             const geos::geom::Coordinate &p) {
    const auto orientation = s.orientationIndex(p);
    return orientation == 0 || orientation == -1;
}

// Since funnel requires keeping the segment reference and the coordinate,
// this helper makes easier to have them together without having to put
// left_coord and left_index everywhere.
struct Point {
    geos::geom::Coordinate coord;
    size_t index;
};

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

    auto apex = Point{route.start, 0};
    auto left = Point{route.segments[0].p0, 0};
    auto right = Point{route.segments[0].p1, 0};

    geos::geom::LineSegment left_edge{apex.coord, left.coord};
    geos::geom::LineSegment right_edge{apex.coord, right.coord};

    for (size_t i = 1; i < route.segments.size(); i++) {
        const auto &new_left = route.segments[i].p0;
        const auto &new_right = route.segments[i].p1;

        if (PointToTheLeftOrColinear(left_edge, new_left)) {
            if (PointToTheLeft(right_edge, new_left) || apex.coord == left.coord) {
                spdlog::debug("{} is to the left of both the funnels, "
                              "continuing with next segment",
                              new_left);
                left = Point{new_left, i};
            } else {
                spdlog::debug("{} is to the left of {} but not {}, which means "
                              "its a corner on {}:{}",
                              new_left, left_edge, right_edge, right.index,
                              right.coord);
                path.points.push_back(right.coord);
                apex = left = right;
                left_edge = geos::geom::LineSegment{apex.coord, left.coord};
                right_edge = geos::geom::LineSegment{apex.coord, right.coord};
                i = apex.index;
            }
        }
        if (PointToTheRightOrColinear(right_edge, new_right)) {
            if (PointToTheRight(right_edge, new_left) || apex.coord == right.coord) {
                spdlog::debug("{} is to the right of both the funnels, "
                              "continuing with next segment",
                              new_right);
                left = Point{new_right, i};
            } else {
                spdlog::debug("{} is to the right of {} but not {}, which means "
                              "its a corner on {}:{}",
                              new_right, right_edge, left_edge, left.index,
                              left.coord);
                path.points.push_back(left.coord);
                apex = right = left;
                left_edge = geos::geom::LineSegment{apex.coord, left.coord};
                right_edge = geos::geom::LineSegment{apex.coord, right.coord};
                i = apex.index;
            }
        }
    }
    spdlog::debug("Calculated path: {}", path);
    return path;
}
} // namespace lr::shortest_path