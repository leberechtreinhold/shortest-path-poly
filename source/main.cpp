#include <algorithm>
#include <args.hxx>
#include <cerrno>
#include <filesystem>

#define SPDLOG_FMT_EXTERNAL
#include <spdlog/spdlog.h>
#include <string>

#include "route.hpp"

auto main(int argc, char **argv) -> int {
    args::ArgumentParser parser("Shortest Path Polygon.",
                                "Calculates the shortest path that goes "
                                "through segment (a polygon without holes).");
    args::HelpFlag help(parser, "help", "Display this help menu",
                        {'h', "help"});
    args::Flag verbose(parser, "verbose", "Enables verbose logging",
                       {'v', "verbose"});
    args::ValueFlag<std::string> input_path(parser, "path",
                                            "Path to the route file",
                                            {'i', "input"},
                                            args::Options::Required);
    args::ValueFlag<std::string> output_path(parser, "output_path",
                                             "Path to the output file",
                                             {'o', "output"});

    try {
        parser.ParseCLI(argc, argv);
    } catch (args::Help) {
        std::cout << parser;
        return 0;
    } catch (args::ParseError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    } catch (args::ValidationError e) {
        std::cerr << e.what() << std::endl;
        std::cerr << parser;
        return 1;
    }

    if (!std::filesystem::is_regular_file(*input_path)) {
        std::cerr << "The input " << *input_path
                  << " is not a valid file. Check it exists and that there are "
                     "permissions.";
        std::cerr << parser;
        return 1;
    }

    if (output_path && std::filesystem::exists(*output_path)) {
        std::cerr << "The output " << *output_path
                  << " already exists, and cannot be used as option.";
        std::cerr << parser;
        return 1;
    }

    if (verbose) {
        spdlog::set_level(spdlog::level::debug);
    }

    spdlog::info("Going to calculate route to {}", *input_path);
    auto data = lr::shortest_path::utils::read_file_contents(*input_path);
    spdlog::debug("Processing {} bytes of data", data.size());

    auto json_result = lr::shortest_path::RouteCalculator::CalculateRoute(data);
    spdlog::info("Processed path!");

    if (output_path) {
        lr::shortest_path::utils::write_file_contents(*output_path,
                                                      json_result.dump(4));
        spdlog::info("Result is stored on {}", *output_path);
    }
}
