#include "functions.h"

namespace functions {

double func1(double x, double z) {
    return std::cos(x) * std::sin(z);
}

double func2(double x, double z) {
    return std::exp(std::cos(x) + std::sin(z));
}

double func3(double x, double z) {
    return std::sqrt(std::fabs(x * x - z * z));
}

double func4(double x, double z) {
    return std::cos(x * z);
}

}
