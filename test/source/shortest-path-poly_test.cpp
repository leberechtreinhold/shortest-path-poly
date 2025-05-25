#include <catch2/catch_test_macros.hpp>

#include "route.hpp"
#include <geos.h>

using namespace lr::shortest_path;

TEST_CASE("TestEndToEnd", "[route]") {
    REQUIRE(std::filesystem::is_directory("data"));

    std::filesystem::path p("data");
    p /= "basic_route.json";

    std::string data;
    REQUIRE_NOTHROW([&]() {
        data = ::utils::read_file_contents(p);
    }());
    size_t result_size = 0;
    REQUIRE_NOTHROW([&]() {
        auto result = RouteCalculator::CalculateRoute(data);
        result_size = result.dump().size();
    }());
    REQUIRE(result_size > 0);
}

TEST_CASE("TestNoSegments", "[route]") {
    Route route;
    route.start = {0,0};
    route.end = {1,1};
    RouteCalculator calculator;
    auto path = calculator.CalculateRoute(route);
    REQUIRE(path.points.size() == 2);
    REQUIRE(path.points[0] == route.start);
    REQUIRE(path.points[1] == route.end);
}

TEST_CASE("TestSkipSegmentMiddle", "[route]") {
    Route route;
    route.start = {1,1};
    route.end = {1,5};
    route.segments.push_back({{0, 3},{5,3}});

    RouteCalculator calculator;
    auto path = calculator.CalculateRoute(route);
    REQUIRE(path.points.size() == 2);
    REQUIRE(path.points[0] == route.start);
    REQUIRE(path.points[1] == route.end);
}
