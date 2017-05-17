#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include "Mul_lib/mul_lib.hpp"
#include <iomanip>
#include <mpi.h>
// #include <stdlib.h>

using namespace std;
using namespace Mul_lib;

int main(int argc, char **argv) {
    int proc_rank, proc_amount;

    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
        cout << "Problems with MPI" << endl;

    MPI_Comm_size(MPI_COMM_WORLD, &proc_amount);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);

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
    double my_time;
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

    long long int m = 1000;
    int j = 5000;
    int j_1 = j * 3 / 5;

    ofstream ofs_n_12{"out_n_12.txt"};
    ofstream ofs_k_12{"out_k_12.txt"};
    ofstream ofs_n_34{"out_n_34.txt"};
    ofstream ofs_k_34{"out_k_34.txt"};
    srand (time(NULL));
    if (proc_rank < 2) {
        for (int k = 10; k < j_1; k += 10) {
            clock_t Tn = 0, Tk = 0;
            double Tnn = 0, Tkk = 0;
            vector<long long> A, B;
            A.reserve(k);
            B.reserve(k);
              for (long long int i = 0; i < m; i++) {
                  A = random_vector(k);
                  B = random_vector(k);
                  auto n = max(A.size(), B.size());

                  if (!proc_rank) {
                      t = clock();
                      my_time = MPI_Wtime();
                      res = naive_mul(A, B);
                      finalize(res);
                      t = clock() - t;
                      my_time = MPI_Wtime() - my_time;
                      Tn += t;
                      Tnn += my_time;
                  }
                  // finalize(res);

                  extend_vec(A, n);
                  extend_vec(B, n);

                  //

                  if (proc_rank == 1) {
                      t = clock();
                      my_time = MPI_Wtime();
                      res = karatsuba_mul(A, B);
                      finalize(res);
                      t = clock() - t;
                      my_time = MPI_Wtime() - my_time;
                      Tk += t;
                      Tkk += my_time;
                  }
                  // t = clock() - t;
                  // Tk += t;
              }

              // print_vec(res);
              if (!proc_rank) {
                  double Ts = Tn / m;
                  double Tss = Tnn / m;
                  f = static_cast<float> (Ts) / CLOCKS_PER_SEC;
                  cout << k << ": " << endl;
                  cout << "Naive algorithm took me " << Ts << ' ' << Tss << " cycles (" <<
                  std::fixed << std::setprecision(6) << f << " seconds)\n";
                  ofs_n_12 << '(' << k << ';' << Ts << ")" << endl;
              }

              if (proc_rank == 1) {
                  double Tks = Tk / m;
                  double Tkks = Tkk / m;
                  f = static_cast<float> (Tks) / CLOCKS_PER_SEC;
                  cout << "Karatsuba algorithm took me " <<
                  Tks << ' ' << Tkks << " cycles (" << std::setprecision(6) << f << " seconds)\n";
                  ofs_k_12 << '(' << k << ';' << Tks << ")" << endl;
              }



            // MPI_Reduce(vectorC.data(), c, rowsA, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            // MPI_Reduce(vectorC.data(), c, rowsA, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            //ofs << k << ": " << Ts << ' ' << Tks << endl;


        }
    } else {
        for (int k = j_1; k < j; k += 10) {
            clock_t Tn = 0, Tk = 0;
            double Tnn = 0, Tkk = 0;
            vector<long long> A, B;
            A.reserve(k);
            B.reserve(k);
              for (long long int i = 0; i < m; i++) {
                  A = random_vector(k);
                  B = random_vector(k);
                  auto n = max(A.size(), B.size());

                  if (proc_rank == 2) {
                      t = clock();
                      my_time = MPI_Wtime();
                      res = naive_mul(A, B);
                      finalize(res);
                      t = clock() - t;
                      my_time = MPI_Wtime() - my_time;
                      Tn += t;
                      Tnn += my_time;
                  }
                  // finalize(res);

                  extend_vec(A, n);
                  extend_vec(B, n);

                  //

                  if (proc_rank == 3) {
                      t = clock();
                      my_time = MPI_Wtime();
                      res = karatsuba_mul(A, B);
                      finalize(res);
                      t = clock() - t;
                      my_time = MPI_Wtime() - my_time;
                      Tk += t;
                      Tkk += my_time;
                  }
                  // t = clock() - t;
                  // Tk += t;
              }

              // print_vec(res);
              if (proc_rank == 2) {
                  double Ts = Tn / m;
                  double Tss = Tnn / m;
                  f = static_cast<float> (Ts) / CLOCKS_PER_SEC;
                  cout << k << ": " << endl;
                  cout << "Naive algorithm took me " << Ts << ' ' << Tss << " cycles (" <<
                  std::fixed << std::setprecision(6) << f << " seconds)\n";
                  ofs_n_34 << '(' << k << ';' << Ts << ")" << endl;
              }

              if (proc_rank == 3) {
                  double Tks = Tk / m;
                  double Tkks = Tkk / m;
                  f = static_cast<float> (Tks) / CLOCKS_PER_SEC;
                  cout << "Karatsuba algorithm took me " <<
                  Tks << ' ' << Tkks << " cycles (" << std::setprecision(6) << f << " seconds)\n";
                  ofs_k_34 << '(' << k << ';' << Tks << ")" << endl;
              }



            // MPI_Reduce(vectorC.data(), c, rowsA, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            // MPI_Reduce(vectorC.data(), c, rowsA, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
            //ofs << k << ": " << Ts << ' ' << Tks << endl;


        }
    }


    MPI_Finalize();



    return 0;
}
