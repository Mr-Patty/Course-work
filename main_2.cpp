#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <vector>
#include <mpi.h>
 
using namespace std;
 
int main(int argc, char **argv)
{
    double starttime, endtime, restime, maxtime, timemax, temp, *c;
    int proc_rank, proc_amount, rowsA, colsA, size, buf;
 
    if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
        cout << "Problems with MPI" << endl;
 
    MPI_Comm_size(MPI_COMM_WORLD, &proc_amount);
    MPI_Comm_rank(MPI_COMM_WORLD, &proc_rank);
 
    FILE *fileA = fopen(argv[1], "rb");
    FILE *fileB = fopen(argv[2], "rb");
 
    buf = fread(&rowsA, sizeof(int), 1, fileA);
    buf = fread(&colsA, sizeof(int), 1, fileA);
    vector<vector<double> > matrixA(rowsA, vector<double>(colsA));
    for (int i = 0; i < rowsA; i++)
        for (int j = 0; j < colsA; j++)
            buf = fread(&temp, sizeof(double), 1, fileA), matrixA[i][j] = temp;
    fclose(fileA);
 
    buf = fread(&size, sizeof(int), 1, fileB);
    vector<double> vectorB(size);
    for (int i = 0; i < size; i++)
        buf = fread(&temp, sizeof(double), 1, fileB), vectorB[i] = temp;
    fclose(fileB);
 
    vector<double> vectorC(rowsA, 0);
    c = new double[rowsA];
    memset(c, 0, rowsA * sizeof(double));
 
    if (colsA != size)
    {
        cout << "Incorrect sizes!" << endl;
        return 1;
    }
 
    starttime = MPI_Wtime();
 
    if (rowsA >= colsA)
    {
        int part = rowsA / proc_amount;
        int start = part * proc_rank;
 
        for (int i = start; i < start + part; i++)
            for (int j = 0; j < colsA; j++)
                vectorC[i] += matrixA[i][j] * vectorB[j];
 
        if (proc_rank == proc_amount - 1)
            for (int i = part * proc_amount; i < rowsA; i++)
                for (int j = 0; j < colsA; j++)
                    vectorC[i] += matrixA[i][j] * vectorB[j];
    }
 
    if (colsA > rowsA)
    {
        int part = colsA / proc_amount;
        int start = part * proc_rank;
 
        for (int i = 0; i < rowsA; i++)
            for (int j = start; j < start + part; j++)
                vectorC[i] += matrixA[i][j] * vectorB[j];
 
        if (proc_rank == proc_amount - 1)
            for (int i = 0; i < rowsA; i++)
                for (int j = part * proc_amount; j < colsA; j++)
                    vectorC[i] += matrixA[i][j] * vectorB[j];
    }
 
    endtime = MPI_Wtime();
    restime = endtime - starttime;
    maxtime = restime;
 
    MPI_Reduce(&maxtime, &timemax, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
    MPI_Reduce(vectorC.data(), c, rowsA, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
 
    if (!proc_rank)
    {
        char buf[100];
        sprintf(buf, "max process time for %d x %d", rowsA, colsA);
        FILE *stat = fopen(buf, "a+");
        fprintf(stat, "%d %lf\n", proc_amount, timemax);
        fclose(stat);
 
        FILE *fileC = fopen(argv[3], "w");
        fprintf(fileC, "%d\n", rowsA);
        for (int i = 0; i < rowsA; i++)
            fprintf(fileC, "%lf ", c[i]);
        fclose(fileC);
    }
 
    MPI_Finalize();
 
    return 0;
}
 
