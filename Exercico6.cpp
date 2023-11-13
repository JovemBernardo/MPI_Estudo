#include <iostream>
#include <cstdlib>
#include <mpi.h>

int main(int argc, char **argv) {
  MPI_Init(&argc, &argv);

  int size, rank;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  constexpr int buffer_count = 5000;
  float buffer[buffer_count];
  memset(buffer, 0, sizeof(buffer));
  
  // Amostragem uniforme, gerando os números e fazendo 1000 repetições
  for (int rep=0; rep < 1000; ++rep) {
    for (int i=0; i < buffer_count; ++i) {
      float val = (float)rand() / RAND_MAX;
      buffer[i] += val;
    }
  }

  //TODO: cria um buffer chamado recepção e chama MPI_Reduce para somar todas as variáveis
  // sobre todos os processos e armazena o resultado no processo 0.
  // No final, você deverá ter variáveis ​​buffer_count.
  float reception[buffer_count];
  MPI_Reduce(buffer, reception, buffer_count, MPI_FLOAT, MPI_SUM, 0, MPI_COMM_WORLD);

  // Agora imprimimos os resultados
  if (rank == 0) {
    for (int i=0; i < buffer_count; ++i)
      printf("%s\n", reception[i]);

  }
  

  MPI_Finalize();
  
  return 0;
}