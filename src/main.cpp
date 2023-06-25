#include <Compress.hpp>
#include <Decompress.hpp>

#include <iostream>

// int main()
// {
//     std::string originalFolderPath = "/home/mateusz/Dokumenty/Cpp_projects/BackToTheFuture/BackToTheFuture/example";
//     std::string compressedArchivePath = "/home/mateusz/Dokumenty/Cpp_projects/BackToTheFuture/BackToTheFuture/example.zip";
//     std::string extractedFolderPath = "/home/mateusz/Dokumenty/Cpp_projects/BackToTheFuture/BackToTheFuture/decompress";

//     char option = 0;

//     std::cout << "Choose option [p]ack / [u]npack" << std::endl;
//     std::cin >> option;

//     if (option == 'p')
//     {
//         std::string archivePath;
//         std::string inputPath;
//         std::cout << "Name of file/folder to be packed:";
//         std::cin >> inputPath;
//         std::cout << "Archive name:";
//         std::cin >> archivePath;
//         archive_utils::compress(inputPath, archivePath, [](std::string_view message)
//                                 { std::cout << message << std::endl; });
//     }
//     else if (option == 'u')
//     {
//         std::string archivePath;
//         std::string outputPath;
//         std::cout << "Unpack path:";
//         std::cin >> outputPath;
//         std::cout << "Archive path:";
//         std::cin >> archivePath;
//         archive_utils::compress(outputPath, archivePath, [](std::string_view message)
//                                 { std::cout << message << std::endl; });
//         archive_utils::decompress(outputPath, archivePath, [](std::string_view message)
//                                   { std::cout << message << std::endl; });
//     }
// }

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
