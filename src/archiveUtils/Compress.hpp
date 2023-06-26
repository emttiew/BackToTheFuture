#pragma once

#include "zipLib/Source/ZipLib/ZipArchive.h"
#include "zipLib/Source/ZipLib/ZipFile.h"

#include <filesystem>
#include <functional>
#include <string_view>

namespace archive_utils
{
    namespace fs = std::filesystem;

    void compress(fs::path const &source, fs::path const &archive, std::function<void(std::string_view)> reporter);
}
