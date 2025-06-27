#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <mpi.h> 
#include <fftw3.h>
#include <cmath>
#include <map>
#include <chrono>

using namespace std;

struct Sequence {
    string id;
    string seq;
};

// This function will Read a file and store sequences
vector<Sequence> read_file(const string &filename) {
    vector<Sequence> sequences;
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening file: " << filename << endl;
        return sequences;
    }
    string line, current_id, current_seq;
    while (getline(file, line)) {
        if (line.empty()) continue;
        if (line[0] == '>') {
            if (!current_id.empty()) {
                sequences.push_back({current_id, current_seq});
            }
            current_seq.clear();
            current_id = line.substr(1);
        } else {
            current_seq += line;
        }
    }
    if (!current_id.empty()) {
        sequences.push_back({current_id, current_seq});
    }
    file.close();
    return sequences;
}


// Convert Sequences to Numerical Representation
map<char, vector<int>> amino_acid_properties = {
    {'A', {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {'C', {0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {'D', {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {'E', {0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {'F', {0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {'G', {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {'H', {0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0}},
    {'I', {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0}},
    {'K', {0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0}},
    {'L', {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0}},
    {'M', {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0}},
    {'N', {0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0}},
    {'P', {0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0}},
    {'Q', {0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0}},
    {'R', {0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}},
    {'S', {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0}},
    {'T', {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0}},
    {'V', {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0}},
    {'W', {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0}},
    {'Y', {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1}}
};

// Step 1: Convert Sequences to Numerical Representation
// Function to convert a sequence to a numerical representation
// The function will return a vector of doubles representing the sequence
vector<double> encode_sequence(const string &sequence) {
    vector<double> encoded_sequence;

    for (char c : sequence) {
        c = toupper(c);

        if (amino_acid_properties.find(c) != amino_acid_properties.end()) {
            encoded_sequence.insert(
                encoded_sequence.end(),
                amino_acid_properties[c].begin(),
                amino_acid_properties[c].end()
            );
        } else if (c == 'X') {
            encoded_sequence.insert(encoded_sequence.end(), 20, 0);
        } else if (c == 'B') {
            for (size_t i = 0; i < 20; i++) {
                encoded_sequence.push_back((amino_acid_properties['N'][i] + amino_acid_properties['D'][i]) / 2);
            }
        } else {
            cerr << "Unknown amino acid: " << c << endl;
        }
    }

    return encoded_sequence;
}

// Step 2: Apply FFT to Sequences (Parallelizable)
// Function to apply Fast Fourier Transform (FFT) to a sequence
// The function will return the FFT of the sequence
vector<fftw_complex> apply_fft(const vector<double> &sequence) {
    int N = sequence.size();
    vector<fftw_complex> fft_result(N);
    fftw_complex *in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex *out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    fftw_plan plan = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    for (int i = 0; i < N; i++) {
        in[i][0] = sequence[i];
        in[i][1] = 0.0;
    }
    fftw_execute(plan);
    for (int i = 0; i < N; i++) {
        fft_result[i][0] = out[i][0];
        fft_result[i][1] = out[i][1];
    }
    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
    return fft_result;
}

// Step 4: Compute Pairwise Correlations (Parallelizable)
// Function to compute the distance between two sequences using their FFTs
// The distance is computed as 1 - cosine similarity
// The cosine similarity is computed as the dot product of the two FFTs divided by the product of their magnitudes
// The distance is computed as 1 - cosine similarity
double compute_distance(const vector<fftw_complex> &fft1, const vector<fftw_complex> &fft2, int N) {
    double sum_real = 0.0;
    double sum_sq1 = 0.0;
    double sum_sq2 = 0.0;

    for (int i = 0; i < N; i++) {
        sum_real += fft1[i][0] * fft2[i][0] + fft1[i][1] * fft2[i][1];

        sum_sq1 += fft1[i][0] * fft1[i][0] + fft1[i][1] * fft1[i][1];
        sum_sq2 += fft2[i][0] * fft2[i][0] + fft2[i][1] * fft2[i][1];
    }

    double cosine_similarity = sum_real / (sqrt(sum_sq1) * sqrt(sum_sq2));

    return 1.0 - cosine_similarity;
}

int match_score(char a, char b) {
    return (a == b) ? 1 : -1; // Match gives 1, mismatch gives -1
}

int score(int diag, int up, int left, char a, char b, int gap_penalty) {
    int match_mismatch = diag + match_score(a, b); // H(i-1, j-1) + s(i, j)
    int gap_seq1 = up - gap_penalty; // H(i-1, j) - W
    int gap_seq2 = left - gap_penalty; // H(i, j-1) - W

    return max(match_mismatch, max(gap_seq1, gap_seq2));
}

// Needleman-Wunsch algorithm for global sequence alignment
// This function will return the alignment matrix
// The matrix will be used to traceback and get the aligned sequences
// The matrix will be of size (n+1) x (m+1) where n and m are the lengths of the sequences
vector<vector<int>> needleman_wunsch(const string &seq1, const string &seq2, int gap_penalty) {
    int n = seq1.size();
    int m = seq2.size();
    vector<vector<int>> H(n + 1, vector<int>(m + 1, 0));

    for (int i = 1; i <= n; i++) H[i][0] = H[i - 1][0] - gap_penalty;
    for (int j = 1; j <= m; j++) H[0][j] = H[0][j - 1] - gap_penalty;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            H[i][j] = score(H[i-1][j-1], H[i-1][j], H[i][j-1], seq1[i-1], seq2[j-1], gap_penalty);
        }
    }

    return H;
}

// Function to perform traceback to get the aligned sequences
// This Program will start from the bottom right corner of the matrix and move towards the top left corner
// It will follow the path with the highest score
// If there is a tie, it will choose the diagonal move
// If there is a gap, it will add a '-' to the corresponding sequence
pair<string, string> traceback(const vector<vector<int>>& H, const string& seq1, const string& seq2, int gap_penalty) {
    int i = seq1.size();
    int j = seq2.size();
    string aligned_seq1 = "";
    string aligned_seq2 = "";

    while (i > 0 && j > 0) {
        if (H[i][j] == H[i-1][j-1] + match_score(seq1[i-1], seq2[j-1])) {
            aligned_seq1 = seq1[i-1] + aligned_seq1;
            aligned_seq2 = seq2[j-1] + aligned_seq2;
            i--;
            j--;
        } else if (H[i][j] == H[i-1][j] - gap_penalty) {
            aligned_seq1 = seq1[i-1] + aligned_seq1;
            aligned_seq2 = "-" + aligned_seq2;
            i--;
        } else {
            aligned_seq1 = "-" + aligned_seq1;
            aligned_seq2 = seq2[j-1] + aligned_seq2;
            j--;
        }
    }

    while (i > 0) {
        aligned_seq1 = seq1[i-1] + aligned_seq1;
        aligned_seq2 = "-" + aligned_seq2;
        i--;
    }
    while (j > 0) {
        aligned_seq1 = "-" + aligned_seq1;
        aligned_seq2 = seq2[j-1] + aligned_seq2;
        j--;
    }

    return {aligned_seq1, aligned_seq2};
}


int main(int argc, char** argv) {
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (argc < 3) {
        if (rank == 0) {
            cerr << "Usage: " << argv[0] << " <filename>" << " <file unique id>" << endl;
        }
        MPI_Finalize();
        return 1;
    }

    auto start_time = std::chrono::high_resolution_clock::now();


    string filename = argv[1];
    vector<Sequence> sequences;
    if (rank == 0) {
        sequences = read_file(filename);
    }

    int num_sequences = sequences.size();
    MPI_Bcast(&num_sequences, 1, MPI_INT, 0, MPI_COMM_WORLD);
    if (rank != 0) {
        sequences.resize(num_sequences);
    }

    ///////////////////////////////////////////////////////////////////////////////////
    //         Broadcast each sequence's length and data to all processes           //
    ///////////////////////////////////////////////////////////////////////////////////
    for (int i = 0; i < num_sequences; i++) {
        int len = (rank == 0) ? sequences[i].seq.size() : 0;
        MPI_Bcast(&len, 1, MPI_INT, 0, MPI_COMM_WORLD);
        if (rank != 0) {
            sequences[i].seq.resize(len);
        }
        MPI_Bcast(sequences[i].seq.data(), len, MPI_CHAR, 0, MPI_COMM_WORLD);
    }

    ///////////////////////////////////////////////////////////////////////////////////
    /////           Step 2: Apply FFT to Sequences (Parallelizable)                 ///
    ///////////////////////////////////////////////////////////////////////////////////
    vector<vector<fftw_complex>> fft_sequences(num_sequences);
    for (int i = 0; i < num_sequences; i++) {
        vector<double> encoded_seq = encode_sequence(sequences[i].seq);
        fft_sequences[i] = apply_fft(encoded_seq);
    }


    ///////////////////////////////////////////////////////////////////////////////////
    //         Compute Pairwise Correlations (Parallelizable)                        //
    ///////////////////////////////////////////////////////////////////////////////////
    int gap_penalty = 2;
    vector<vector<int>> alignment_scores(num_sequences, vector<int>(num_sequences, 0));
    vector<vector<double>> distance_matrix(num_sequences, vector<double>(num_sequences, 0));
    vector<vector<pair<string, string>>> aligned_sequences_list(num_sequences, vector<pair<string, string>>(num_sequences));

    int rows_per_proc = num_sequences / size;
    int start = rank * rows_per_proc;
    int end = (rank == size - 1) ? num_sequences : start + rows_per_proc;

    for (int i = start; i < end; i++) {
        for (int j = i + 1; j < num_sequences; j++) {
            vector<vector<int>> H = needleman_wunsch(sequences[i].seq, sequences[j].seq, gap_penalty);
            alignment_scores[i][j] = alignment_scores[j][i] = H[sequences[i].seq.size()][sequences[j].seq.size()];

            pair<string, string> aligned_sequences = traceback(H, sequences[i].seq, sequences[j].seq, gap_penalty);
            aligned_sequences_list[i][j] = aligned_sequences_list[j][i] = aligned_sequences;

            distance_matrix[i][j] = distance_matrix[j][i] = compute_distance(fft_sequences[i], fft_sequences[j], sequences[i].seq.size());
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    //                 Gather alignment scores to rank 0                             //
    //           Gather Results and Construct Distance Matrix                        //
    ///////////////////////////////////////////////////////////////////////////////////
    vector<vector<int>> global_scores(num_sequences, vector<int>(num_sequences, 0));
    vector<vector<double>> global_matrix(num_sequences, vector<double>(num_sequences, 0));
    vector<vector<pair<string, string>>> global_aligned_sequences(num_sequences, vector<pair<string, string>>(num_sequences));

    for (int i = 0; i < num_sequences; i++) {
        MPI_Reduce(alignment_scores[i].data(), global_scores[i].data(), num_sequences, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Reduce(distance_matrix[i].data(), global_matrix[i].data(), num_sequences, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    }

    // Gather aligned sequences manually (since MPI does not support complex structures like pairs)
    if (rank == 0) {
        for (int i = 0; i < num_sequences; i++) {
            for (int j = i + 1; j < num_sequences; j++) {
                if (i >= start && i < end) {
                    global_aligned_sequences[i][j] = aligned_sequences_list[i][j];
                    global_aligned_sequences[j][i] = aligned_sequences_list[j][i];
                }
            }
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////
    //           Save alignment scores and distance matrix to files                  //
    //           Save aligned sequences to file (Only on rank 0)                     //
    ///////////////////////////////////////////////////////////////////////////////////
    if (rank == 0) {

        // file names 
        string alignment_file_name = "alignment_scores_" + string(argv[2]) + ".txt";
        string distance_file_name = "distance_matrix_" + string(argv[2]) + ".txt";
        string aligned_sequences_file_name = "aligned_sequences_" + string(argv[2]) + ".txt";


        ofstream alignment_file(alignment_file_name);
        for (const auto &row : global_scores) {
            for (int val : row) {
                alignment_file << val << "\t";
            }
            alignment_file << "\n";
        }
        alignment_file.close();
        cout << "Alignment scores saved to alignment_scores.txt" << endl;

        ofstream distance_file(distance_file_name);
        for (const auto &row : global_matrix) {
            for (double val : row) {
                distance_file << val << "\t";
            }
            distance_file << "\n";
        }
        distance_file.close();
        cout << "Distance matrix saved to distance_matrix.txt" << endl;

        ofstream aligned_sequences_file(aligned_sequences_file_name);
        for (int i = 0; i < num_sequences; i++) {
            for (int j = i + 1; j < num_sequences; j++) {
                aligned_sequences_file << "Alignment between Sequence " << i << " and Sequence " << j << ":\n";
                aligned_sequences_file << global_aligned_sequences[i][j].first << "\n";
                aligned_sequences_file << global_aligned_sequences[i][j].second << "\n\n";
            }
        }
        aligned_sequences_file.close();
        cout << "Aligned sequences saved to aligned_sequences.txt" << endl;
    }

    if (rank == 0) {
        auto end_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end_time - start_time;
        cout << "Execution time: " << duration.count() << " seconds" << endl;
    }

    MPI_Finalize();
    return 0;
}
