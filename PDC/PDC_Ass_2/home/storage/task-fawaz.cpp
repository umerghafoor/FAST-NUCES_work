#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <dirent.h>
#include <sys/stat.h>

using namespace std;

struct Sequence {
    string data;
    int length;
};

// Read sequences from a single .vie file
void read_vie_file(const string& filename, vector<Sequence>& sequences) {
    ifstream file(filename);
    if (!file) {
        cerr << "Error opening file: " << filename << endl;
        return;
    }

    string line, seq;
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!seq.empty()) {
                sequences.push_back({seq, static_cast<int>(seq.length())});
                seq.clear();
            }
        } else {
            seq += line;
        }
    }
    if (!seq.empty()) sequences.push_back({seq, static_cast<int>(seq.length())});
}

// Read all .vie files in a directory
vector<Sequence> read_sequences(const string& dirname) {
    vector<Sequence> sequences;
    DIR* dir = opendir(dirname.c_str());
    if (!dir) {
        cerr << "Error opening directory: " << dirname << endl;
        return sequences;
    }

    struct dirent* entry;
    while ((entry = readdir(dir)) != nullptr) {
        string filename = entry->d_name;
        if (filename.find(".vie") != string::npos) {
            string path = dirname + "/" + filename;
            struct stat file_stat;
            if (stat(path.c_str(), &file_stat) == 0 && S_ISREG(file_stat.st_mode)) {
                read_vie_file(path, sequences);
            }
        }
    }
    closedir(dir);
    return sequences;
}

// Needleman-Wunsch pairwise alignment
float needleman_wunsch(const Sequence& a, const Sequence& b, float match=1, float mismatch=-1, float gap=-2) {
    int m = a.length, n = b.length;
    vector<vector<float>> dp(m+1, vector<float>(n+1, 0));
    for (int i = 0; i <= m; i++) dp[i][0] = i * gap;
    for (int j = 0; j <= n; j++) dp[0][j] = j * gap;
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            float score = (a.data[i-1] == b.data[j-1]) ? match : mismatch;
            dp[i][j] = max({dp[i-1][j-1] + score, dp[i-1][j] + gap, dp[i][j-1] + gap});
        }
    }
    return dp[m][n];
}

// Compute distance matrix
vector<vector<float>> compute_distance_matrix(const vector<Sequence>& sequences) {
    int n = sequences.size();
    vector<vector<float>> dist(n, vector<float>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            float score = needleman_wunsch(sequences[i], sequences[j]);
            dist[i][j] = 1.0 / (1.0 + abs(score));
            dist[j][i] = dist[i][j];
        }
    }
    return dist;
}

int main() {
    string dirname = "BB11001-package.vie";
    auto sequences = read_sequences(dirname);
    if (sequences.empty()) {
        cerr << "No sequences found or error reading files." << endl;
        return EXIT_FAILURE;
    }

    auto dist = compute_distance_matrix(sequences);
    for (const auto& row : dist) {
        for (float val : row) cout << val << " ";
        cout << endl;
    }
    return 0;
}