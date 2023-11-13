void probing_process(int &int_sum, float &float_sum) {
  MPI_Status status;
  
  // 1- Sonde a mensagem recebida
  MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);

  // 2- Obtenha a tag e a fonte
  int tag = status.MPI_TAG;
  int source = status.MPI_SOURCE;

  //Imprimindo a mensagem
  printf("Recebi uma mensagem do processo %d com tag %d\n", source, tag);

  // 3- Adiciona em int_sum ou float_sum dependendo da tag da mensagem
  if (tag == 0) {
    int received_int;
    MPI_Recv(&received_int, 1, MPI_INT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    int_sum += received_int;
  } else if (tag == 1) {
    float received_float;
    MPI_Recv(&received_float, 1, MPI_FLOAT, source, tag, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    float_sum += received_float;
  }
}