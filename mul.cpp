#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "mul_lib.hpp"
#include <iomanip>
// #include <stdlib.h>

using namespace std;
using namespace Mul_lib;

int main() {
    vector<long long> first, second;
    vector<long long> res;
    double f;
    ifstream ifs{"nums.txt"};
    ofstream ofs{"out.txt"};

    if (!ifs) {
        cerr << "Error: File could not be found\n";
        return 1;
    }
    first = get_number(ifs);
    second = get_number(ifs);
    // print_vec(first);
    // print_vec(second);
    // print_res(first, std::cout);
    // cout << first.size() << endl;
    // print_res(second, std::cout);

    auto n = max(first.size(), second.size());
    // cout << n << endl;

    extend_vec(first, n);
    extend_vec(second, n);
    // cout << first[] << endl;
    // print_vec(first);
    // cout << endl;
    // print_vec(second);

    clock_t t;
    t = clock();

    res = naive_mul(first, second);
    // print_vec(res);
    finalize(res);
    // print_vec(res);
    t = clock() - t;

    print_res(res, ofs);

    f = static_cast<float> (t) / CLOCKS_PER_SEC;

    cout << "Naive algorithm took me " << t << " cycles (" <<
    std::fixed << std::setprecision(6) << f << " seconds)\n";
    // printf("%lf", f);
    // print_vec(first);
    // cout << endl;
    // print_vec(second);
    // cout << endl;
    t = clock();
    res = karatsuba_mul(first, second);
    finalize(res);

    t = clock() - t;
    // print_vec(res);
    //
    // // print_vec(res);
    print_res(res, ofs);
    f = static_cast<float> (t) / CLOCKS_PER_SEC;
    cout << "Karatsuba algorithm took me " <<
     t << " cycles (" << std::setprecision(6) << f << " seconds)\n";

    long long int m = 100;
    int k = 10000;
    clock_t Tn = 0, Tk = 0;
    vector<long long> A, B;
    A.reserve(k);
    B.reserve(k);
    srand (time(NULL));
    // cout << rand()%2 << endl;
    for (long long int i = 0; i < m; i++) {
        A = random_vector(k);
        B = random_vector(k);

        auto n = max(A.size(), B.size());

        extend_vec(A, n);
        extend_vec(B, n);

        // t = clock();
        // res = naive_mul(A, B);
        // finalize(res);
        // t = clock() - t;
        // Tn += t;
        //
        // t = clock();
        // res = karatsuba_mul(A, B);
        // finalize(res);
        // t = clock() - t;
        // Tk += t;
        // cout << t << endl;
        // for(int i = 0; i < A.size(); i++)
        //     cout << A[i] << ' ';
        // cout << endl;
        // for(int i = 0; i < B.size(); i++)
        //     cout << B[i] << ' ';
        // cout << endl;
        // print_vec(res2);
    }
    // for(int i = 0; i < A.size(); i++)
    //     cout << A[i] << ' ';
    // cout << endl;
    // for(int i = 0; i < B.size(); i++)
    //     cout << B[i] << ' ';
    // cout << endl;
    // print_vec(res);

    // double Ts = Tn / m;
    // f = static_cast<float> (Ts) / CLOCKS_PER_SEC;
    // // print_vec(A);
    // // print_vec(B);
    // // cout << endl;
    // // print_vec(res);
    // print_res(res, ofs);
    //
    // cout << "Naive algorithm took me " << Ts << " cycles (" <<
    // std::fixed << std::setprecision(6) << f << " seconds)\n";
    //
    // double Tks = Tk / m;
    // f = static_cast<float> (Tks) / CLOCKS_PER_SEC;
    // cout << "Karatsuba algorithm took me " <<
    //  Tks << " cycles (" << std::setprecision(6) << f << " seconds)\n";


    return 0;
}
