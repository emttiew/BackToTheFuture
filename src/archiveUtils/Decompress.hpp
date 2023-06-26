#pragma once

#include "zipLib/Source/ZipLib/ZipArchive.h"
#include "zipLib/Source/ZipLib/ZipFile.h"

#include <filesystem>
#include <functional>
#include <string_view>

namespace fs = std::filesystem;
namespace archive_utils
{
    void decompress(fs::path const &destination, fs::path const &archive, std::function<void(std::string_view)> reporter);
}