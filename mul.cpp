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

    auto n = max(first.size(), second.size());

    extend_vec(first, n);
    extend_vec(second, n);

    // print_vec(first);


    clock_t t;
    // t = clock();
    //
    // res = naive_mul(first, second);
    //
    // t = clock() - t;
    //
    // print_res(res, ofs);
    //
    // f = static_cast<float> (t) / CLOCKS_PER_SEC;
    //
    // cout << "Naive algorithm took me " << t << " cycles (" <<
    // std::fixed << std::setprecision(6) << f << " seconds)\n";

    // int num = 118;

    // std::ostringstream ost;
    // ost << num;
    // std::cout << ost.str().size() << endl;

    // t = clock();
    // res = karatsuba_mul(first, second);
    // finalize(res);
    //
    // t = clock() - t;
    //
    // print_res(res, ofs);
    //
    // f = static_cast<float> (t) / CLOCKS_PER_SEC;
    // cout << "Karatsuba algorithm took me " <<
    //  t << " cycles (" << std::setprecision(6) << f << " seconds)\n";

    long long int m = 500;
    int k;
    cin >> k;
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

        t = clock();
        res = naive_mul(A, B);
        // finalize(res);
        t = clock() - t;
        Tn += t;
        //
        t = clock();
        res = karatsuba_mul(A, B);
        finalize(res);
        t = clock() - t;
        Tk += t;
        // cout << t << endl;
        // for(int i = 0; i < A.size(); i++)
        //     cout << A[i] << ' ';
        // cout << endl;
        // for(int i = 0; i < B.size(); i++)
        //     cout << B[i] << ' ';
        // cout << endl;
        // print_vec(res2);
    }
    // print_vec(res);

    double Ts = Tn / m;
    f = static_cast<float> (Ts) / CLOCKS_PER_SEC;
    cout << "Naive algorithm took me " << Ts << " cycles (" <<
    std::fixed << std::setprecision(6) << f << " seconds)\n";

    double Tks = Tk / m;
    f = static_cast<float> (Tks) / CLOCKS_PER_SEC;
    cout << "Karatsuba algorithm took me " <<
     Tks << " cycles (" << std::setprecision(6) << f << " seconds)\n";


    return 0;
}
