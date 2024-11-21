#include "params.h"
#include "neuralNetwork.h"
#include <stdio.h>
#include <Eigen/Dense>
#include <iostream>

using namespace params;
using namespace neuralNetwork;
using namespace std;

int main() {
    
    Eigen::MatrixXd A(2, 2);
    A(0, 0) = 1;
    A(0, 1) = 2;
    A(1, 0) = 3;
    A(1, 1) = 4;

    Eigen::VectorXd v(2);
    v << 1, 2;

    Eigen::VectorXd result = A * v;

    std::cout << "Matrix A:\n" << A << "\n";
    std::cout << "Vector v:\n" << v << "\n";
    std::cout << "Result of A * v:\n" << result << "\n";

    return 0;


    return 0;
}