#pragma once

#include "route.hpp"
#include <fmt/core.h>
#include <geos.h>
#include <sstream>

template <>
struct fmt::formatter<geos::geom::Coordinate> : fmt::formatter<std::string> {
    auto format(geos::geom::Coordinate t,
                format_context &ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "({}, {})", t.x, t.y);
    }
};

template <>
struct fmt::formatter<geos::geom::LineSegment> : fmt::formatter<std::string> {
    auto format(geos::geom::LineSegment t,
                format_context &ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "[{} - {}]", t.p0, t.p1);
    }
};

template <>
struct fmt::formatter<lr::shortest_path::Path> : fmt::formatter<std::string> {
    auto format(lr::shortest_path::Path t,
                format_context &ctx) const -> decltype(ctx.out()) {
        std::stringstream ss;
        ss << "[";
        for (const auto &p : t.points) {
            ss << fmt::format("{}", p);
        }
        ss << "]";
        return fmt::format_to(ctx.out(), ss.str());
    }
};

template <>
struct fmt::formatter<lr::shortest_path::Route> : fmt::formatter<std::string> {
    auto format(lr::shortest_path::Route t,
                format_context &ctx) const -> decltype(ctx.out()) {
        return fmt::format_to(ctx.out(), "{{from {} to {} through {} segments",
                              t.start, t.end, t.segments.size());
    }
};