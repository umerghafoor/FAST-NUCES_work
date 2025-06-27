#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib>
#include <filesystem>
#include <vector>

//////////////////////////////////////////////////////////////////////////////////
///      this code will open the given folder and read all the .vie files      ///
///      then it will run the msa_serial and msa_parallel on each file         ///
///      and log the execution time of each script in a csv file               ///
///      this code requires the msa_serial and msa_parallel executables  and   ///  
///      data files to be in the same directory                                ///
//////////////////////////////////////////////////////////////////////////////////

namespace fs = std::filesystem;

// Function to get all .vie files in the current directory
std::vector<std::string> getVieFiles(const std::string &directory) {
    std::vector<std::string> vieFiles;

    for (const auto &entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == ".vie") {
            vieFiles.push_back(entry.path().string());
        }
    }

    return vieFiles;
}

// Function to run a command and measure execution time
void runCommand(const std::string &command, const std::string &fileName, std::ofstream &logFile) {
    auto start = std::chrono::high_resolution_clock::now();

    // file uique id
    std::string fileUniqueId = fileName.substr(fileName.find_last_of('/') + 1);
    fileUniqueId = fileUniqueId.substr(0, fileUniqueId.find_last_of('.')); 

    std::cout << "Running command: " << command << " with " << fileName << "...\n";

    std::string fullCommand = command + " " + fileName + " " + fileUniqueId;
    int result = system(fullCommand.c_str());

    if (result != 0) {
        std::cerr << "Error executing command: " << fullCommand << "\n";
        logFile << "Error executing command: " << fullCommand << "\n";
        return;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    logFile << "\"" << command << "\",\"" << fileName << "\",\"" << duration.count() << "\"\n";
    std::cout << "Execution time: " << duration.count() << " seconds\n";
}

int main() {
    std::ofstream logFile("execution_times.csv");

    if (!logFile.is_open()) {
        std::cerr << "Error opening log file\n";
        return 1;
    }

    logFile << "Script Name,File Name,Execution Time (seconds)\n";

    std::vector<std::string> vieFiles = getVieFiles(".");

    if (vieFiles.empty()) {
        std::cerr << "No .vie files found in the current directory.\n";
        logFile << "No .vie files found in the current directory.\n";
        return 1;
    }

    for (const auto &file : vieFiles) {
        runCommand("./msa_serial", file, logFile);


        // modift the number of processors to 8
        runCommand("mpirun -np 8 ./msa_parallel", file, logFile);

        // if you want to specify the machinefile, you can use the following command
        // runCommand("mpirun -np 8 -machinefile machinefile ./msa_parallel", file, logFile);
    }

    std::cout << "Execution completed. Check the execution_times.csv for execution times.\n";

    logFile.close();
    return 0;
}
