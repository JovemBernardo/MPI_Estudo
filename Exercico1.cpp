#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {
  // Initialisation
  int MPI_Init(int argc, char **argv);
  // Reading size and rank
  int world_size;
  int world_rank;
  MPI_Comm_size(MPI_COMM_WORLD, &world_size);
  MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

  //Variaveis
  char processor_nome[MPI_MAX_PROCESSOR_NAME];
  int name;
  MPI_Get_processor_name(processor_nome, &name);

  // Printing
  printf("Hello world!! \n Processador: %s. \n Classificação %d de %d Processadores.\n", processor_nome, world_rank, world_size);
  
  // Finalisation
  int MPI_Finalize();

  return 0;
}