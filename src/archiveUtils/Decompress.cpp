#include <Decompress.hpp>

#include "zip_lib/Source/ZipLib/ZipArchive.h"
#include "zip_lib/Source/ZipLib/ZipFile.h"

#include <fstream>

namespace archive_utils
{
    namespace
    {
        void ensureDirectoryExists(fs::path const &dir)
        {
            std::error_code err;
            fs::create_directories(dir, err);
        }
    }

    void decompress(fs::path const &destination, fs::path const &archive, std::function<void(std::string_view)> reporter)
    {
        ensureDirectoryExists(destination);

        auto zipArchive = ZipFile::Open(archive.string());

        for (int i = 0; i < zipArchive->GetEntriesCount(); i++)
        {
            auto entry = zipArchive->GetEntry(i);
            if (entry)
            {
                auto filepath = destination / fs::path{entry->GetFullName()}.relative_path();
                if (reporter)
                    reporter("Creating " + filepath.string());

                if (entry->IsDirectory())
                {
                    ensureDirectoryExists(filepath);
                }
                else
                {
                    ensureDirectoryExists(filepath.parent_path());
                    std::ofstream destFile;
                    destFile.open(filepath.string().c_str(), std::ios::binary | std::ios::trunc);

                    if (!destFile.is_open())
                    {
                        if (reporter)
                            reporter("Failed to create target file.");
                    }

                    auto dataStream = entry->GetDecompressionStream();
                    if (dataStream)
                    {
                        destFile << dataStream->rdbuf();
                    }
                }
            }
        }
    }
}