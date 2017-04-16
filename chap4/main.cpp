/*************************
- Implementar el problema Matriz-Vector usando PTthreads.
- Implementar el problema del Calculo de PI
- Realizar pruebas y cambios de la tabla 4.1 del libro (Busy Waiting y Mutex)
- Implementar la lista enlazada multithreading y replicar las tablas 4.3 y 4.4
- Realizar experimentos y replicar los cuadros 4.5
- Implementar el problema presentado en la sección 4.11 del uso de strtok.
 *************************/

#include <stdio.h>
#include "matrix_mult.h"
#include "pi-calc.h"
#include "linked-list.h"
#include "strtok.h"

void Usage(char* prog_name) {
    fprintf(stderr, "Uso: %s <n_threads>\n", prog_name);
    exit(0);
}

int main(int argc, char** argv) {
    if (argc != 2)
        Usage(argv[0]);
    size_t thread_count = atoi(argv[1]);

    matrix_multiplication(thread_count);

    return 0;
}