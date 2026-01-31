#include <Eigen/Dense>
#include <fstream>
#include <iostream>
#include <vector>
#include "Configuration.hpp"
#include "MatrixSolver.hpp"
#include "matrixIO.hpp"

using namespace Eigen;

int main(int argc, char *argv[])
{
  std::cout << "SIDEMADE – Simple Dense Matrix Decomposition\n"
            << std::endl;

  if (argc != 2) {
    std::cerr << "SIDEMADE needs to be called with exactly one argument – the "
              << "configuration file, e.g. 'sidemade config.yml'." << std::endl;
    return -1;
  }

  // read configuration
  Configuration configuration{std::string{argv[1]}};

  // create solver
  MatrixSolver solver{configuration.decompositionType};

  // set a different arbitrary seed for the random generator to avoid a match
  // between random matrices (generated with a seed of 0) and random vectors
  srand(1000);

  // fill matrix and vector structures
  // A is read from file, b is set randomly, x is the solution
  const MatrixXd A = matrixIO::openData(configuration.matrixFileName,
                                        configuration.matrixSize);
  const VectorXd b = VectorXd::Random(configuration.matrixSize);
  VectorXd       x = VectorXd(configuration.matrixSize);

  // solve A * x = b
  std::cout << "Solving ...\n"
            << std::endl;
  solver.solve(A, b, x);

  const double absRes = (A * x - b).norm(); // norm() computes l2 norm
  const double relRes = absRes / x.norm();
  // std::cout << "Solution is:\n" << x << std::endl;
  std::cout << "Absolute l2 residual is: " << absRes << std::endl;
  std::cout << "Relative l2 residual is: " << relRes << std::endl;

  return 0;
}
