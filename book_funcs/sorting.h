#include <stdio.h>
#include <stdlib.h>

void sorting(int argc, char *argv[]);
void Usage(char *prog_name);
void Get_args(int argc, char *argv[], int *n_p, char *g_i_p);
void Generate_list(int a[], int n);
void Print_list(int a[], int n, char *title);
void Read_list(int a[], int n);
void Odd_even_sort(int a[], int n);