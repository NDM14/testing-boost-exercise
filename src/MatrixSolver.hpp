#pragma once
#include <Eigen/Dense>

/*
A convenience hull to solve dense matrix system by matrix decompositions.

The decomposition type is specified in the constructor.
Supported options are:
- LU: a classic LU decomposition
- QR: a classic QR decomposition
- LU2: a LU decomposition followed by a single refinement iteration (see
https://en.wikipedia.org/wiki/Iterative_refinement)

Afterwards, use `solve(A, b, x)` to solve the linear system A * x = b for x.

Available matrix decomposition types in Eigen:
https://eigen.tuxfamily.org/dox/group__TutorialLinearAlgebra.html
*/
class MatrixSolver {
public:
  // Available decomposition types
  enum DecompositionType { LU,
                           QR,
                           LU2 };

  // Constructor, takes decomposition type.
  MatrixSolver(DecompositionType decompositionType);

  // solve linear system A * x = b for x.
  void solve(const Eigen::MatrixXd &A, const Eigen::VectorXd &b,
             Eigen::VectorXd &x);

private:
  // Used type to compute decomposition
  DecompositionType _decompositionType;
};
