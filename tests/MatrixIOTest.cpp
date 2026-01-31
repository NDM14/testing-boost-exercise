#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#include <Eigen/Dense>
#include <fstream>
#include <string>

#include "matrixIO.hpp"

BOOST_AUTO_TEST_SUITE(MatrixIOTests)

BOOST_AUTO_TEST_CASE(OpenDataParsesCSVCorrectly)
{
  const std::string testFile = "test_opendata.csv";
  const int         size     = 2;

  std::ofstream ofs(testFile);
  BOOST_REQUIRE(ofs.is_open());
  ofs << "1.5,2.5\n";
  ofs << "3.5,4.5\n";
  ofs.close();

  Eigen::MatrixXd result = matrixIO::openData(testFile, size);

  BOOST_REQUIRE_EQUAL(result.rows(), size);
  BOOST_REQUIRE_EQUAL(result.cols(), size);
  BOOST_CHECK_CLOSE(result(0, 0), 1.5, 1e-9);
  BOOST_CHECK_CLOSE(result(0, 1), 2.5, 1e-9);
  BOOST_CHECK_CLOSE(result(1, 0), 3.5, 1e-9);
  BOOST_CHECK_CLOSE(result(1, 1), 4.5, 1e-9);

  std::remove(testFile.c_str());
}

BOOST_AUTO_TEST_SUITE_END()