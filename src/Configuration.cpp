#include "Configuration.hpp"
#include <iostream>
#include "MatrixSolver.hpp"
#include "yaml-cpp/yaml.h"

Configuration::Configuration(const std::string yamlFile)
{
  YAML::Node  config              = YAML::LoadFile(yamlFile);
  std::string decompositionString = config["DecompositionType"].as<std::string>();
  if (decompositionString == "LU") {
    decompositionType = MatrixSolver::LU;
  } else if (decompositionString == "QR") {
    decompositionType = MatrixSolver::QR;
  } else if (decompositionString == "LU2") {
    decompositionType = MatrixSolver::LU2;
  } else {
    throw std::runtime_error(
        "SIDEMADE does not support the decomposition type \"" +
        decompositionString + "\".");
  }

  matrixFileName = config["MatrixFileName"].as<std::string>();
  matrixSize     = config["MatrixSize"].as<int>();

  std::cout << "Used decomposition type: " << decompositionString << std::endl;
  std::cout << "Used matrix file: " << matrixFileName << std::endl;
  std::cout << "Matrix size: " << matrixSize << "\n"
            << std::endl;
}
