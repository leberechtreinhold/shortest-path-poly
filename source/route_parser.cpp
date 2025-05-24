#include "geos_format.hpp"
#include "route.hpp"
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

namespace lr::shortest_path {

static geos::geom::Coordinate
ParseCoordinate(const nlohmann::json &json_coord) {
    bool valid_json = json_coord.contains("x") && json_coord["x"].is_number() &&
                      json_coord.contains("y") && json_coord["y"].is_number();
    if (!valid_json) {
        spdlog::error("The json doesn't have a correct coordinate formatting. "
                      "JSON: {}",
                      json_coord.dump());
        throw("Incorrect format");
    }
    return geos::geom::Coordinate{json_coord["x"], json_coord["y"]};
}

static geos::geom::LineSegment ParseSegment(const nlohmann::json &json_coord1,
                                            const nlohmann::json &json_coord2) {
    return geos::geom::LineSegment{ParseCoordinate(json_coord1),
                                   ParseCoordinate(json_coord2)};
}

Route Route::GetRouteFromJson(const std::string_view &json_route) {
    nlohmann::json parsed_json;
    try {
        parsed_json = nlohmann::json::parse(json_route);
    } catch (const nlohmann::json::parse_error &e) {
        spdlog::info("Failed to parse the route. Error: {} at {}", e.what(),
                     e.byte);
        throw("Invalid json format");
    }

    bool has_minimum_fields = parsed_json.contains("goals") &&
                              parsed_json["goals"].is_array() &&
                              parsed_json["goals"].size() == 2 &&
                              parsed_json["goals"][0].contains("label") &&
                              parsed_json["goals"][0]["label"] == "FROM" &&
                              parsed_json["goals"][1].contains("label") &&
                              parsed_json["goals"][1]["label"] == "TO" &&
                              parsed_json.contains("segments") &&
                              parsed_json["segments"].is_array() &&
                              parsed_json["segments"].size() % 2 == 0;
    if (!has_minimum_fields) {
        spdlog::
            error("The json doesn't have a correct route formatting. JSON: {}",
                  parsed_json.dump());
        throw("Incorrect format");
    }
    Route route{};
    route.start = ParseCoordinate(parsed_json["goals"][0]);
    route.end = ParseCoordinate(parsed_json["goals"][1]);

    if (parsed_json["segments"].size() == 0) {
        spdlog::warn("No segments defined for this route");
        return route;
    }
    for (size_t i = 0; i < parsed_json["segments"].size(); i += 2) {
        auto new_segment = ParseSegment(parsed_json["segments"][i],
                                        parsed_json["segments"][i + 1]);
        route.segments.push_back(new_segment);
    }
    spdlog::debug("Parsed route: {}", route);
    return route;
}

} // namespace lr::shortest_path