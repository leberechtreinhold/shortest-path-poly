#include "route.hpp"

#include <filesystem>
#include <fstream>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>

namespace lr::shortest_path::utils {
std::string read_file_contents(const std::filesystem::path &path) {
    std::ifstream in(path.string(), std::ios::in | std::ios::binary);
    if (!in) {
        spdlog::error("Failed to open file {}", errno);
        throw(errno);
    }
    std::ostringstream contents;
    contents << in.rdbuf();
    return contents.str();
}

void write_file_contents(const std::filesystem::path &path,
                         const std::string_view &content) {
    std::ofstream out(path.string(), std::ios::out);
    if (!out) {
        spdlog::error("Failed to open file {}", errno);
        throw(errno);
    }
    out << content;
}

} // namespace lr::shortest_path::utils