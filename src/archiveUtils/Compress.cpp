#include "Compress.hpp"

#include "zip_lib/Source/ZipLib/ZipArchive.h"
#include "zip_lib/Source/ZipLib/ZipFile.h"

namespace archive_utils
{
    void compress(fs::path const &source, fs::path const &archive, std::function<void(std::string_view)> reporter)
    {
        if (fs::is_regular_file(source))
        {
            if (reporter)
                reporter("Packing " + source.string());
            fs::path relativePath = fs::relative(source, source.parent_path());
            ZipFile::AddFile(archive.string(), source.string(), relativePath.string());
        }
        else
        {
            for (auto const &p : fs::recursive_directory_iterator(source))
            {
                if (reporter)
                    reporter("Packing " + p.path().string());

                if (fs::is_directory(p))
                {
                    fs::path relativePath = fs::relative(p, source);
                    auto zipArchive = ZipFile::Open(archive.string());
                    auto entry = zipArchive->CreateEntry(relativePath.string() + "/");
                    entry->SetAttributes(ZipArchiveEntry::Attributes::Directory);
                    ZipFile::SaveAndClose(zipArchive, archive.string());
                }
                else if (fs::is_regular_file(p))
                {
                    fs::path relativePath = fs::relative(p, source);
                    ZipFile::AddFile(archive.string(), p.path().string(), relativePath.string());
                }
            }
        }
    }

}
