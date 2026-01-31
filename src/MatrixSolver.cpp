#include "MatrixSolver.hpp"
#include <Eigen/Dense>
#include <cassert>
#include <iostream>

using namespace Eigen;

MatrixSolver::MatrixSolver(DecompositionType decompositionType)
    : _decompositionType(decompositionType) {}

void MatrixSolver::solve(const Eigen::MatrixXd &A, const Eigen::VectorXd &b,
                         Eigen::VectorXd &x)
{
  if (_decompositionType == LU) {
    PartialPivLU<MatrixXd> LU;
    LU.compute(A);
    x = LU.solve(b);
  } else if (_decompositionType == QR) {
    FullPivHouseholderQR<MatrixXd> QR;
    QR.compute(A);
    x = QR.solve(b);
  } else if (_decompositionType == LU2) {
    PartialPivLU<MatrixXd> LU;
    LU.compute(A);
    x = LU.solve(b);
    VectorXd residual =
        b -
        A * x; // only really effective if we could go to higher precision here
    x = x + LU.solve(residual);
  } else {
    assert(false); // Unsupported decomposition type, should be caught in configuration
                   // already
  }
}
