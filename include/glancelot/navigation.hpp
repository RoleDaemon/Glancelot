#pragma once
#include "contracts.hpp"
#include <optional>
#include <system_error>

namespace glancelot {
bool naturalLess(const std::filesystem::path& a, const std::filesystem::path& b);
bool isSupportedImage(const std::filesystem::path& path);
std::vector<std::filesystem::path> imageFiles(const std::filesystem::path& directory);
// Lazy traversal searches directories under root; never follows directory links.
std::optional<std::filesystem::path> adjacentFolderImage(
    const std::filesystem::path& root, const std::filesystem::path& directory, int direction);
class Navigator {
public:
    bool open(const std::filesystem::path& file, std::error_code& error);
    bool setRoot(const std::filesystem::path& root);
    void setBoundary(BoundaryMode mode);
    std::optional<std::filesystem::path> step(int direction);
    std::optional<std::filesystem::path> folder(int direction);
    void refresh();
    const NavigationSnapshot& snapshot() const { return state_; }
private:
    NavigationSnapshot state_;
};
}
