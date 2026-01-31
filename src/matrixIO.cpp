#include "matrixIO.hpp"
#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using namespace Eigen;

namespace matrixIO {

void saveData(const string &fileName, const MatrixXd &matrix)
{
  // see https://eigen.tuxfamily.org/dox/structEigen_1_1IOFormat.html
  const static IOFormat CSVFormat(FullPrecision, DontAlignCols, ", ", "\n");

  ofstream file(fileName);
  if (file.is_open()) {
    file << matrix.format(CSVFormat);
    file.close();
  }
}

MatrixXd openData(const string &fileToOpen, const int matrixSize)
{
  ifstream matrixDataFile(fileToOpen);

  // one row of the matrix as a string with comma-separated values
  string matrixRowString;

  // a single matrix entry as a string
  string matrixEntry;

  // matrix entries row by row
  vector<double> matrixEntries;

  int matrixRowNumber = 0;
  int matrixColNumber = 0;

  // read matrixDataFile row by row
  while (getline(matrixDataFile, matrixRowString)) {
    // convert matrixRowString to a stream
    stringstream matrixRowStringStream(matrixRowString);

    // read matrixRowStringStream entry by entry
    while (getline(matrixRowStringStream, matrixEntry, ',')) {
      matrixEntries.push_back(stod(matrixEntry));
      ++matrixColNumber;
    }
    if (matrixColNumber != matrixSize) {
      throw std::runtime_error("The matrix stored in \"" + fileToOpen +
                               "\" has " + std::to_string(matrixColNumber) +
                               " columns, while the specified matrix size is " +
                               std::to_string(matrixSize));
    }
    matrixColNumber = 0;
    ++matrixRowNumber;
  }

  if (matrixRowNumber != matrixSize) {
    throw std::runtime_error("The matrix stored in \"" + fileToOpen +
                             "\" has " + std::to_string(matrixRowNumber) +
                             " rows, while the specified matrix size is " +
                             std::to_string(matrixSize));
  }

  // convert std vector into Eigen matrix and return the matrix
  return Map<Matrix<double, Dynamic, Dynamic, RowMajor>>(
      matrixEntries.data(), matrixRowNumber,
      matrixEntries.size() / matrixRowNumber);
}

} // namespace matrixIO
