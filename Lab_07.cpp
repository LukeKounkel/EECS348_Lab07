#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
using namespace std;

/*
Name: Luke Kounkel
KUID: 3215488
Description: This lab builds on Lab 5, leveraging additional C++ features, such as classes and function overloading, and operator overloading.
Collaborators: None
*/


class Matrix {
private:
    int size; // Matrix is assumed to be square, so size x size
    vector<vector<int>> data;

public:
    // Constructor to initialize an empty matrix of given size
    Matrix(int n) : size(n), data(n, vector<int>(n, 0)) {}

    // Function to load matrix data from a file
    bool loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) return false;

        file >> size; // Read matrix size
        data.resize(size, vector<int>(size, 0));
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                file >> data[i][j];
            }
        }
        file.close();
        return true;
    }

    // Function to display the matrix
    void display() const {
        for (const auto& row : data) {
            for (int val : row) {
                cout << setw(4) << val;
            }
            cout << endl;
        }
    }

    // Operator overloading for matrix addition
    Matrix operator+(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Operator overloading for matrix multiplication
    Matrix operator*(const Matrix& other) const {
        Matrix result(size);
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                result.data[i][j] = 0;
                for (int k = 0; k < size; ++k) {
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }

    // Function to calculate the sum of the main and secondary diagonal elements
    int diagonalSum() const {
        int mainDiagSum = 0, secDiagSum = 0;
        for (int i = 0; i < size; ++i) {
            mainDiagSum += data[i][i];
            secDiagSum += data[i][size - 1 - i];
        }
        return mainDiagSum + secDiagSum;
    }

    // Function to swap two rows in the matrix
    void swapRows(int row1, int row2) {
        if (row1 >= 0 && row1 < size && row2 >= 0 && row2 < size) {
            swap(data[row1], data[row2]);
        } else {
            cout << "Invalid row indices for swapping!" << endl;
        }
    }
};

int main() {
    Matrix mat(4); // Assuming a default size initially; actual size will be set from the file
    if (!mat.loadFromFile("matrix_input.txt")) {
        cout << "Error loading matrix from file." << endl;
        return 1;
    }

    cout << "Matrix loaded from file:" << endl;
    mat.display();

    // Example of matrix addition
    Matrix mat2 = mat; // Copy of mat for addition demonstration
    Matrix sumMatrix = mat + mat2;
    cout << "\nMatrix after addition:" << endl;
    sumMatrix.display();

    // Example of matrix multiplication
    Matrix productMatrix = mat * mat2;
    cout << "\nMatrix after multiplication:" << endl;
    productMatrix.display();

    // Example of calculating diagonal sums
    int diagSum = mat.diagonalSum();
    cout << "\nSum of main and secondary diagonal elements: " << diagSum << endl;

    // Example of swapping rows
    int row1 = 1, row2 = 3;
    cout << "\nMatrix after swapping rows " << row1 << " and " << row2 << ":" << endl;
    mat.swapRows(row1, row2);
    mat.display();

    return 0;
}
