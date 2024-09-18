#include <sstream>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

void parsec_roi_begin() 
{
}

void parsec_roi_end() 
{
}

struct Result {
    vector< vector<int> > A;
};

Result read(string filename) {
    vector< vector<int> > A;
    Result ab;
    string line;
    ifstream infile;
    infile.open (filename.c_str());

    int i = 0;
    while (getline(infile, line) && !line.empty()) {
        istringstream iss(line);
        A.resize(A.size() + 1);
        int a, j = 0;
        while (iss >> a) {
            A[i].push_back(a);
            j++;
        }
        i++;
    }
    infile.close();
    ab.A = A;
    return ab;
}

vector<vector<int>> convolve(const vector<vector<int>>& inputMatrix) {
    int n = inputMatrix.size();
    
    // Define a 3x3 Gaussian-like filter
    vector<vector<int>> filter = {
        {1, 2, 1},
        {2, 4, 2},
        {1, 2, 1}
    };
    
    vector<vector<int>> result(n, vector<int>(n, 0)); // Resultant matrix initialized to 0

    // Perform convolution, avoiding the border elements
    for (int i = 1; i < n - 1; ++i) {
        for (int j = 1; j < n - 1; ++j) {
            int sum = 0;
            
            // Apply filter to the 3x3 neighborhood around the current element
            for (int ki = -1; ki <= 1; ++ki) {
                for (int kj = -1; kj <= 1; ++kj) {
                    sum += inputMatrix[i + ki][j + kj] * filter[ki + 1][kj + 1];
                }
            }
            
            result[i][j] = sum;  // Store the convolution result
        }
    }
    
    return result;
}

// Updated to print a 1D vector
void printVector(const vector<int>& vec) {
    for (size_t i = 0; i < vec.size(); i++) {
        cout << vec[i];
        if (i + 1 != vec.size()) {
            cout << "\t";
        }
    }
    cout << endl;
}

int main (int argc, char* argv[]) {
    srand(time(0));
    string filename;
    if (argc < 3) {
        filename = "2000.in";
    } else {
        filename = argv[2];
    }
    Result result = read (filename);
    parsec_roi_begin();
    vector<vector<int>> C = convolve(result.A);  // Corrected to vector<int>
    parsec_roi_end();
    
    // Optionally print the gathered data as a 1D vector
    //printVector(C);
    
    return 0;
}