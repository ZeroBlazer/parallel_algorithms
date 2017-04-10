#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int matrix_multiplication(int argc, char* argv[]);
void Check_for_error(int local_ok, char fname[], char message[]);
void Get_dims(int argc, char* argv[], int* m_p, int* local_m_p, 
      int* n_p, int* local_n_p);
void Allocate_arrays(double** local_A_pp, double** local_x_pp, 
      double** local_y_pp, int local_m, int n, int local_n);
void Read_matrix(char prompt[], double local_A[], int m, int local_m, 
      int n, int local_n);
void Read_vector(char prompt[], double local_vec[], int n, int local_n);
void Generate_matrix(double local_A[], int local_m, int n);
void Generate_vector(double local_x[], int local_n);
void Print_matrix(char title[], double local_A[], int m, int local_m, 
      int n);
void Print_vector(char title[], double local_vec[], int n,
      int local_n);
void Mat_vect_mult(double local_A[], double local_x[], 
      double local_y[], double x[], int m, int local_m, int n, 
      int local_n);
