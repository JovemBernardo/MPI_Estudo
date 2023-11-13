void compute(int total_count, int my_count, float my_points[][3]) {
  // total_count é o número total de pontos
  // my_count é o número de pontos para este processo
  // my_points é uma tabela flutuante de formato [my_count][3]

  // 1- Soma de todos os pontos em local_sum
  float local_sum[3] = {0.0f, 0.0f, 0.0f};

  for (int i = 0; i < my_count; ++i) {
        local_sum[0] += my_points[i][0];
        local_sum[1] += my_points[i][1];
        local_sum[2] += my_points[i][2];
    }

  // 2- Reduz a soma de todos os pontos da variável baricentro
  float barycentre[3];
  MPI_Allreduce(local_sum, barycentre, 3, MPI_FLOAT, MPI_SUM, MPI_COMM_WORLD);
  
  // 3- Divida cada componente do baricentro pelo número de pontos
  barycentre[0] /= total_count;
  barycentre[1] /= total_count;
  barycentre[2] /= total_count;

  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  
  //Para cada ponto
  for (int i = 0; i < my_count; ++i) {
    // 4- Compute the distance for every point
    float dx = my_points[i][0] - barycentre[0];
    float dy = my_points[i][1] - barycentre[1];
    float dz = my_points[i][2] - barycentre[2];
    float dist = std::sqrt(dx * dx + dy * dy + dz * dz);

    
    // E imprimindo o resultado
    printf("%d %d\n", rank, dist);
  }
}