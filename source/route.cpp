#include "route.hpp"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace lr::shortest_path {

Route Route::GetRouteFromJson(const std::string_view &json_route) {
    nlohmann::json parsed_json;
    try {
        parsed_json = nlohmann::json::parse(json_route);
    } catch (const nlohmann::json::parse_error &e) {
        spdlog::info("Failed to parse the route. Error: {} at {}", e.what(),
                     e.byte);
        throw;
    }

    Route route{};
    return route;
}

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
        return path;
    }
    return path;
}
} // namespace lr::shortest_path