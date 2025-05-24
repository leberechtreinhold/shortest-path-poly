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

Path RouteCalculator::CalculateRoute(const Route &route) {
    Path path;
    path.points.push_back(route.start);
    if (route.required_segments.empty()) {
        spdlog::warn("This route didn't have any required segments, setting "
                     "start to end straight.");
        path.points.push_back(route.end);
        spdlog::debug("Calculated path: {}", path);
        return path;
    }

    spdlog::debug("Calculated path: {}", path);
    return path;
}
} // namespace lr::shortest_path