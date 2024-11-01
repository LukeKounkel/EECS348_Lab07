#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class Matrix {
public:
    int matrix_size;
    double** matrix_data;

    // Constructor with size parameter
    Matrix(int size = 0) : matrix_size(size) {
        matrix_data = new double*[matrix_size];
        for (int i = 0; i < matrix_size; ++i) {
            matrix_data[i] = new double[matrix_size];
            for (int j = 0; j < matrix_size; ++j) {
                matrix_data[i][j] = 0; // Initialize with zeros
            }
        }
    }

    // Destructor to free memory
    ~Matrix() {
        for (int i = 0; i < matrix_size; ++i) {
            delete[] matrix_data[i];
        }
        delete[] matrix_data;
    }

    // Overloaded addition operator
    Matrix operator+(const Matrix& other) const {
        Matrix result(matrix_size);
        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                result.matrix_data[i][j] = this->matrix_data[i][j] + other.matrix_data[i][j];
            }
        }
        return result;
    }

    // Overloaded multiplication operator
    Matrix operator*(const Matrix& other) const {
        Matrix result(matrix_size);
        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                for (int k = 0; k < matrix_size; ++k) {
                    result.matrix_data[i][j] += this->matrix_data[i][k] * other.matrix_data[k][j];
                }
            }
        }
        return result;
    }
};

void read_matrix_from_file(const string& file_name, Matrix& matrix_1, Matrix& matrix_2) {
    ifstream file(file_name);
    int matrix_size;

    if (file.is_open()) {
        file >> matrix_size;  // Read the first value as the matrix size
        if (matrix_size != matrix_1.matrix_size || matrix_size != matrix_2.matrix_size) {
            cout << "Matrix size mismatch. Expected size: " << matrix_1.matrix_size << ", but found: " << matrix_size << endl;
            return;
        }

        // Read data into matrix_1
        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                file >> matrix_1.matrix_data[i][j];
            }
        }

        // Read data into matrix_2
        for (int i = 0; i < matrix_size; ++i) {
            for (int j = 0; j < matrix_size; ++j) {
                file >> matrix_2.matrix_data[i][j];
            }
        }

        cout << "Matrices loaded from " << file_name << " successfully." << endl;
        file.close();
    } else {
        cout << "Failed to open file " << file_name << endl;
    }
}


void print_matrix(const Matrix& matrix) {
    for (int i = 0; i < matrix.matrix_size; ++i) {
        for (int j = 0; j < matrix.matrix_size; ++j) {
            cout << matrix.matrix_data[i][j] << " ";
        }
        cout << endl;
    }
}

void get_diagonal_sum(const Matrix& matrix) {
    double main_diagonal_sum = 0;
    double secondary_diagonal_sum = 0;

    for (int i = 0; i < matrix.matrix_size; ++i) {
        main_diagonal_sum += matrix.matrix_data[i][i];
        secondary_diagonal_sum += matrix.matrix_data[i][matrix.matrix_size - i - 1];
    }

    cout << "Main Diagonal Sum: " << main_diagonal_sum << endl;
    cout << "Secondary Diagonal Sum: " << secondary_diagonal_sum << endl;
}

void swap_matrix_row(Matrix& matrix, int row1, int row2) {
    // Validate row indices
    if (row1 < 0 || row1 >= matrix.matrix_size || row2 < 0 || row2 >= matrix.matrix_size) {
        cout << "Invalid row indices: " << row1 << " and " << row2 << endl;
        return;
    }

    // Swap rows
    for (int j = 0; j < matrix.matrix_size; ++j) {
        swap(matrix.matrix_data[row1][j], matrix.matrix_data[row2][j]);
    }

    cout << "Rows " << row1 << " and " << row2 << " have been swapped." << endl;
    print_matrix(matrix);  // Display the matrix after swapping rows
}

void print_matrix(const Matrix& matrix_1, const Matrix& matrix_2) {
    cout << "Matrix 1:" << endl;
    print_matrix(matrix_1);
    cout << "Matrix 2:" << endl;
    print_matrix(matrix_2);
}

int main(int argc, char* argv[]) {
    Matrix matrix_1(4), matrix_2(4);
    read_matrix_from_file("matrix_input.txt", matrix_1, matrix_2);

    cout << "Printing matrices:" << endl;
    print_matrix(matrix_1, matrix_2);

    cout << "Adding matrices:" << endl;
    Matrix add_result = matrix_1 + matrix_2;
    print_matrix(add_result);

    cout << "Multiplying matrices:" << endl;
    Matrix multiply_result = matrix_1 * matrix_2;
    print_matrix(multiply_result);

    cout << "get matrix diagonal sum" << endl;
    get_diagonal_sum(matrix_1);

    cout << "swap matrix rows" << endl;
    swap_matrix_row(matrix_1, 0, 1);

    return 0;
}
