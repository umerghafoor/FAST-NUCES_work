#pragma once
#include <iostream>
#include <fstream>
#include <windows.h>

bool createDirectory(const std::string& path) {
    if (!::CreateDirectoryA(path.c_str(), NULL)) {
        DWORD error = GetLastError();
        if (error != ERROR_ALREADY_EXISTS) {
            std::cerr << "Failed to create directory: " << path << std::endl;
            return false;
        }
    }
    return true;
}

bool copyFile(const std::string& sourcePath, const std::string& destinationPath) {
    // Check if the source file exists
    if (::GetFileAttributesA(sourcePath.c_str()) == INVALID_FILE_ATTRIBUTES) {
        std::cerr << "Source file does not exist." << std::endl;
        return false;
    }

    // Extract the directory path from the destination path
    std::size_t pos = destinationPath.find_last_of("\\/");
    std::string destinationDir = destinationPath.substr(0, pos);

    // Create the destination directory and parent directories if they don't exist
    if (!createDirectory(destinationDir)) {
        return false;
    }

    // Continue with the file copying as before
    std::ifstream sourceFile(sourcePath, std::ios::binary);
    if (!sourceFile.is_open()) {
        std::cerr << "Failed to open source file." << std::endl;
        return false;
    }

    std::ofstream destinationFile(destinationPath, std::ios::binary);
    if (!destinationFile.is_open()) {
        std::cerr << "Failed to open destination file." << std::endl;
        sourceFile.close();
        return false;
    }

    destinationFile << sourceFile.rdbuf();

    sourceFile.close();
    destinationFile.close();

    std::cout << "File copied successfully." << std::endl;
    return true;
}

bool isValidFilePath(const std::string& filePath) 
{
    DWORD fileAttributes = ::GetFileAttributesA(filePath.c_str());

    if (fileAttributes != INVALID_FILE_ATTRIBUTES && !(fileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
        // The path is valid and it points to a file (not a directory)
        return true;
    }
    else {
        std::cerr << "Invalid file path: " << filePath << std::endl;
        return false;
    }
}

bool deleteFile(const std::string& filePath) {
    if (::DeleteFileA(filePath.c_str())) {
        std::cout << "File deleted successfully." << std::endl;
        return true;
    }
    else {
        DWORD error = GetLastError();
        if (error == ERROR_FILE_NOT_FOUND) {
            std::cerr << "File not found: " << filePath << std::endl;
        }
        else {
            std::cerr << "Failed to delete file: " << filePath << std::endl;
        }
        return false;
    }
}