#include <Compress.hpp>
#include <Decompress.hpp>

#include <iostream>

int main()
{
    std::string originalFolderPath = "/home/mateusz/Dokumenty/Cpp_projects/BackToTheFuture/BackToTheFuture/example";
    std::string compressedArchivePath = "/home/mateusz/Dokumenty/Cpp_projects/BackToTheFuture/BackToTheFuture/example.zip";
    std::string extractedFolderPath = "/home/mateusz/Dokumenty/Cpp_projects/BackToTheFuture/BackToTheFuture/decompress";

    char option = 0;

    std::cout << "Choose option [p]ack / [u]npack" << std::endl;
    std::cin >> option;

    if (option == 'p')
    {
        std::string archivePath;
        std::string inputPath;
        std::cout << "Name of file/folder to be packed:";
        std::cin >> inputPath;
        std::cout << "Archive name:";
        std::cin >> archivePath;
        archive_utils::compress(inputPath, archivePath, [](std::string_view message)
                                { std::cout << message << std::endl; });
    }
    else if (option == 'u')
    {
        std::string archivePath;
        std::string outputPath;
        std::cout << "Unpack path:";
        std::cin >> outputPath;
        std::cout << "Archive path:";
        std::cin >> archivePath;
        archive_utils::compress(outputPath, archivePath, [](std::string_view message)
                                { std::cout << message << std::endl; });
        archive_utils::decompress(outputPath, archivePath, [](std::string_view message)
                                  { std::cout << message << std::endl; });
    }
}