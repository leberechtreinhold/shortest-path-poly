#pragma once

#include <fmt/core.h>
#include <geos.h>
#include <sstream>
#include "route.hpp"

template<>
struct fmt::formatter<geos::geom::Coordinate> : fmt::formatter<std::string>
{
    auto format(geos::geom::Coordinate t, format_context &ctx) const -> decltype(ctx.out())
    {
        return fmt::format_to(ctx.out(), "({}, {})", t.x, t.y);
    }
};

template<>
struct fmt::formatter<geos::geom::LineSegment> : fmt::formatter<std::string>
{
    auto format(geos::geom::LineSegment t, format_context &ctx) const -> decltype(ctx.out())
    {
        return fmt::format_to(ctx.out(), "[{} - {}]", t.p0, t.p1);
    }
};

template<>
struct fmt::formatter<lr::shortest_path::Path> : fmt::formatter<std::string>
{
    auto format(lr::shortest_path::Path t, format_context &ctx) const -> decltype(ctx.out())
    {
        std::stringstream ss;
        ss << "[";
        for (const auto& p : t.points) {
            ss << fmt::format("{}", p);
        }
        ss << "]";
        return fmt::format_to(ctx.out(), ss.str());
    }
};