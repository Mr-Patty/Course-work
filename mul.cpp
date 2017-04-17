#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "mul_lib.hpp"
#include <iomanip>

using namespace std;
using namespace Mul_lib;

int main() {
    vector<long long> first, second;
    vector<long long> res;
    ifstream ifs{"nums.txt"};
    ofstream ofs{"out.txt"};

    if (!ifs) {
        cerr << "Error: File could not be found\n";
        return 1;
    }
    first = get_number(ifs);
    second = get_number(ifs);

    // print_res(first, std::cout);
    // cout << first.size() << endl;
    // print_res(second, std::cout);

    auto n = max(first.size(), second.size());
    // cout << first.size() << endl;

    extend_vec(first, n);
    extend_vec(second, n);
    // cout << first[] << endl;
    // print_vec(first);
    // print_vec(second);

    clock_t t;
    t = clock();

    res = naive_mul(first, second);
    // print_vec(res);
    finalize(res);
    // print_vec(res);
    t = clock() - t;

    print_res(res, ofs);

    double f = static_cast<float> (t) / CLOCKS_PER_SEC;

    cout << "Naive algorithm took me " << t << " cycles (" <<
    std::fixed << std::setprecision(6) << f << " seconds)\n";
    // printf("%lf", f);
    // print_vec(first);
    // print_vec(second);
    t = clock();
    res = karatsuba_mul(first, second);
    finalize(res);

    t = clock() - t;


    print_res(res, ofs);
    f = static_cast<float> (t) / CLOCKS_PER_SEC;
    cout << "Karatsuba algorithm took me " <<
     t << " cycles (" << std::setprecision(6) << f << " seconds)\n";

    return 0;
}
