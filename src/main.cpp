#include <Compress.hpp>
#include <Decompress.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        std::cout << "Usage: " << argv[0] << " c|compress|d|decompress <source_path> <archive_path> reporter\n";
        return 1;
    }

    std::string mode = argv[1];
    std::string sourcePath = argv[2];
    std::string archivePath = argv[3];

    std::function<void(std::string_view)> reporter;
    if (argc > 4)
    {
        // Custom reporter provided
        reporter = [](std::string_view message)
        {
            std::cout << message << '\n';
        };
    }

    if (mode == "c" || mode == "compress")
    {
        fs::path source(sourcePath);
        fs::path archive(archivePath);
        archive_utils::compress(source, archive, reporter);
        std::cout << "Compression completed.\n";
    }
    else if (mode == "d" || mode == "decompress")
    {
        fs::path destination(sourcePath);
        fs::path archive(archivePath);
        archive_utils::decompress(destination, archive, reporter);
        std::cout << "Decompression completed.\n";
    }
    else
    {
        std::cout << "Invalid mode. Available modes: compress, decompress\n";
        return 1;
    }

    return 0;
}
