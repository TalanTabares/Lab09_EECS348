/*
Author: Talan Tabares
Subject: Lab09
Date: 4/8/2025
Description: Program similar to Lab 08 where an input file reads in a matrix and performs various operations. This program can handle integer and float values.

Inputs:
 - lab09_test_file.txt (Generic name, but the test file is a user specified file)

Outputs:
 - Mat1
 - Mat2
*/



#include <iostream> //Input / Output Library
#include <fstream> // File input library
#include <vector> // Library that allows use of vector properties
#include <iomanip> // Library to help with formatting outputs
#include <type_traits> // Library that is used as a tool to check types in a template

using namespace std; // Ease of use tool to make syntax simpler

template <typename T> // Allows the Matrix class to use integers and floats
class Matrix { // Define Matrix Class
private: // Define private data
    int size; // Initialize the integer size
    vector<vector<T>> data; // Initialize the vector data

public: // Define public data
    Matrix(int n) : size(n), data(n, vector<T>(n)) {} // Constructor to set the NxN matrix

    friend istream& operator>>(istream& in, Matrix<T>& mat) { // Used to read data from input
        for (int i = 0; i < mat.size; ++i) // Rows
            for (int j = 0; j < mat.size; ++j) // Columns
                in >> mat.data[i][j]; // Access elements
        return in; // Return input
    }

    friend ostream& operator<<(ostream& out, const Matrix<T>& mat) { // Organizes Matrix so it can be displated in the correct format
        out << fixed << setprecision(2); // Make output 2 decimals 
        for (int i = 0; i < mat.size; ++i) { // Rows
            for (int j = 0; j < mat.size; ++j) // Columns
                out << setw(8) << static_cast<double>(mat.data[i][j]); // Print formatted values
            out << endl; // New line
        }
        return out; // Return output
    }

    Matrix<T> operator+(const Matrix<T>& other) const { // Operator for addition of matrices
        Matrix<T> result(size); // Create a matrix that is the same size of the NxN
        for (int i = 0; i < size; ++i) // Rows
            for (int j = 0; j < size; ++j) // Columns
                result.data[i][j] = this->data[i][j] + other.data[i][j]; // Add elements together
        return result; // Return the resulting matrix
    }

    
    Matrix<T> operator*(const Matrix<T>& other) const { // Operator for multiplication of matrices
        Matrix<T> result(size); // Create matrix of size NxN
        for (int i = 0; i < size; ++i) // Rows
            for (int j = 0; j < size; ++j) // Columns
                for (int k = 0; k < size; ++k) // Elements for dot product
                    result.data[i][j] += this->data[i][k] * other.data[k][j]; // Multiply and track results
        return result; // Return resulting matrix
    }

   
    void printDiagonalSums() const { // Operator for summing diagonals
        T mainDiag = 0, secDiag = 0; // Initialize variables to track the sum
        for (int i = 0; i < size; ++i) { // Diagonal elements
            mainDiag += data[i][i]; // add and store
            secDiag += data[i][size - 1 - i]; // add and store
        }
        cout << "Main diagonal sum: " << static_cast<double>(mainDiag) << endl; // Print main diagonal sum
        cout << "Secondary diagonal sum: " << static_cast<double>(secDiag) << endl; // Print second diagonal sum
    }

   
    void swapRows(int row1, int row2) { // Operator to swap rows in a matrix
        if (row1 >= 0 && row2 >= 0 && row1 < size && row2 < size) // Check validity of indices
            std::swap(data[row1], data[row2]); // Swap rows
    }


    void swapColumns(int col1, int col2) { // Operator to swap columns in a matrix
        if (col1 >= 0 && col2 >= 0 && col1 < size && col2 < size) // Check validity of indices
            for (int i = 0; i < size; ++i) // loop through each row
                std::swap(data[i][col1], data[i][col2]); // swap elements from the columns
    }

 
    template<typename U> // Template to update an element in one of the matrices
    void updateElement(int row, int col, U value) { // Define function
        if (row >= 0 && col >= 0 && row < size && col < size) // Check validity of indices
            data[row][col] = static_cast<T>(value); // Assign the value with proper type
    }
};


template <typename T> // Template to load matrix and operations
void loadAndOperateMatrix(const string& filename) { // Function to open file and perform operations
    ifstream file(filename); // Open file
    if (!file) { // Check if file is detected
        cerr << "Failed to open file.\n"; // Display error if file could not be opened
        return; // Exit
    }

    int N, type; // Declare size of the matrix
    file >> N >> type; 

    Matrix<T> mat1(N), mat2(N); // Create properly sized matrices
    file >> mat1 >> mat2; // Put elements into matrices

    cout << "Matrix A:\n" << mat1; // Print matrix 1
    cout << "\nMatrix B:\n" << mat2; // Print matrix 2

    cout << "\nMatrix A + B:\n" << (mat1 + mat2); // Print matrix 1 + matrix 2
    cout << "\nMatrix A * B:\n" << (mat1 * mat2); // Print matrix 1 * matrix 2

    cout << "\nDiagonal sums of Matrix A:\n"; // Display message
    mat1.printDiagonalSums(); // Perform diagonal sum operatoin

    mat1.swapRows(0, 1); // Perform swap rows operation
    cout << "\nMatrix A after swapping row 0 and 1:\n" << mat1; // Display resulting matrix

    mat1.swapColumns(0, 1); // Perform swap columns operation
    cout << "\nMatrix A after swapping column 0 and 1:\n" << mat1; // Display resulting matrix

    mat1.updateElement(2, 2, static_cast<T>(999)); // Changes the element [2,2] = 999
    cout << "\nMatrix A after updating (2,2) to 999:\n" << mat1; //  Print result of update element
}

int main() { // Main function where program starts
    string filename; // Initialize filename variable
    cout << "Enter the filename: "; // Display message
    cin >> filename; // Input for filename

    ifstream check(filename); // Open file
    if (!check) { // Check if file is opened
        cerr << "Cannot open file.\n"; // Print error if file not opened
        return 1; // return 1 to indicate that the program did not run correctly
    }

    int N, type; // Initialize 2 variables for input data
    check >> N >> type; // Read values for N and type
    check.close(); // Close file

    if (type == 0) // If 0, integer version
        loadAndOperateMatrix<int>(filename); // create matrices in integer format
    else if (type == 1) // If 1, float version
        loadAndOperateMatrix<double>(filename); // Create matrices in float format
    else // If neither is detected
        cout << "Unknown matrix type flag.\n"; // Print error message

    return 0; // Return 0 if program is ran correctly
}
