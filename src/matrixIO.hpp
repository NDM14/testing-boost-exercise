#pragma once
#include <Eigen/Dense>

namespace matrixIO {

// Saves a dense Eigen matrix into a csv file.
void saveData(const std::string &fileName, const Eigen::MatrixXd &matrix);

// Reads a quadratic matrix from a csv file into a dense Eigen matrix
// The csv file should look like (for a matrixSize of 3):
// a,b,c
// d,e,f
// g,h,i
// The implementation is modified from
// https://github.com/AleksandarHaber/Save-and-Load-Eigen-Cpp-Matrices-Arrays-to-and-from-CSV-files
Eigen::MatrixXd openData(const std::string &fileToOpen, const int matrixSize);

} // namespace matrixIO
