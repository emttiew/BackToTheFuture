#include <Decompress.hpp>

#include <filesystem>
#include <fstream>
#include <gtest/gtest.h>

namespace fs = std::filesystem;
namespace au = archive_utils;
namespace
{
    class ArchiveUtilsTest : public ::testing::Test
    {
    protected:
        void SetUp() override
        {
            // Create a temporary directory for the tests
            tempDir = fs::temp_directory_path() / "archive_utils_test";
            fs::create_directory(tempDir);
        }

        void TearDown() override
        {
            // Remove the temporary directory and its contents
            fs::remove_all(tempDir);
        }

        fs::path tempDir;
    };

    TEST_F(ArchiveUtilsTest, ecompressSingleFile)
    {
        // Prepare the test data
        std::string testData = "Test data";
        std::string archivePath = (tempDir / "test_archive.zip").string();
        std::string destinationPath = (tempDir / "output").string();

        // Create a zip archive with a single file
        {
            fs::path filePath = tempDir.string() + "/file.txt";
            std::ofstream file(filePath);
            ASSERT_TRUE(file.is_open());
            file << "Test data";
            file.close();
            ZipFile::AddFile(archivePath, filePath);
        }
        // Perform decompression
        au::decompress(destinationPath, archivePath, nullptr);

        // Verify the result
        fs::path decompressedPath = destinationPath + "/file.txt";
        ASSERT_TRUE(fs::exists(decompressedPath));
        ASSERT_TRUE(fs::is_regular_file(decompressedPath));

        std::ifstream decompressedFile(decompressedPath.string(), std::ios::binary);
        ASSERT_TRUE(decompressedFile.is_open());

        std::stringstream buffer;
        buffer << decompressedFile.rdbuf();
        EXPECT_EQ(buffer.str(), testData);
    }

    TEST_F(ArchiveUtilsTest, DISABLED_DDecompressDirectory)
    {
        // Prepare the test data
        std::string testData = "Test data";
        std::string archivePath = (tempDir / "test_archive.zip").string();
        std::string destinationPath = (tempDir / "output").string();

        // Create a zip archive with a directory and a file
        {
            fs::path testDir = "/dir";
            fs::create_directories(testDir);
            ZipArchive::Ptr zipArchive = ZipFile::Open(archivePath);
            ZipArchiveEntry::Ptr entry = zipArchive->CreateEntry(testDir);
            entry->SetAttributes(ZipArchiveEntry::Attributes::Directory);
            ZipFile::SaveAndClose(zipArchive, archivePath);
            fs::path filePath = tempDir.string() + "/dir/file.txt";
            std::ofstream file(filePath);
            ASSERT_TRUE(file.is_open());
            file << "Test data";
            file.close();
            ZipFile::AddFile(archivePath, filePath);
        }

        // Perform decompression
        au::decompress(destinationPath, archivePath, nullptr);

        // Verify the result
        fs::path decompressedPath = destinationPath + "/dir/file.txt";
        ASSERT_TRUE(fs::exists(decompressedPath));
        ASSERT_TRUE(fs::is_regular_file(decompressedPath));

        std::ifstream decompressedFile(decompressedPath.string(), std::ios::binary);
        ASSERT_TRUE(decompressedFile.is_open());

        std::stringstream buffer;
        buffer << decompressedFile.rdbuf();
        EXPECT_EQ(buffer.str(), testData);
    }
}