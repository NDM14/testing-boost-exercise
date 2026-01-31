#pragma once
#include "MatrixSolver.hpp"

/*
A yaml configuration reader.

Data is read from a yaml file in the constructor and accessible then.
*/
struct Configuration {

  // Reads configuration data from a file called yamlFile
  Configuration(const std::string yamlFile);

  // Name of the matrix file
  std::string matrixFileName;

  // Type to decompose matrix
  MatrixSolver::DecompositionType decompositionType;

  // Size of matrix along one dimension, matrix has size _matrixSize x _matrixSize
  int matrixSize;
};
