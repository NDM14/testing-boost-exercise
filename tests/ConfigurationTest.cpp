#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
#include "Configuration.hpp"
#include "MatrixSolver.hpp"

BOOST_AUTO_TEST_SUITE(ConfigurationTests)

BOOST_AUTO_TEST_CASE(ReadConfiguration)
{
  const MatrixSolver::DecompositionType expectedDecompositionType{MatrixSolver::QR};
  const std::string                     expectedMatrixFileName{"../data/m3.csv"};
  const int                             expectedMatrixSize{3};

  Configuration configuration{"testconfig.yml"};
  BOOST_TEST(expectedDecompositionType == configuration.decompositionType);
  BOOST_TEST(expectedMatrixFileName == configuration.matrixFileName);
  BOOST_TEST(expectedMatrixSize == configuration.matrixSize);
}

BOOST_AUTO_TEST_SUITE_END()
