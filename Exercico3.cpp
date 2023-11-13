void play_non_blocking_scenario() {
  MPI_Request request;
  MPI_Status  status;
  int request_finished = 0;

  // Inicializando buffer:
  for (int i=0; i < buffer_count; ++i)
    buffer[i] = (rank == 0 ? i*2 : 0);

  MPI_Barrier(MPI_COMM_WORLD);
  //Iniciando o cronômetro
  double time = -MPI_Wtime(); // Este comando nos ajuda a medir o tempo. Veremos mais sobre isso mais adiante!

  
  ////////// Você não deve modificar nada ANTES deste ponto //////////
  
  if (rank == 0) {
    sleep(3);

    // 1- Inicializa o envio sem bloqueio para o processo 1
    MPI_Isend(buffer, buffer_count, MPI_INT, 1, 0, MPI_COMM_WORLD, &request);

    double time_left = 6000.0;
    while (time_left > 0.0) {
      usleep(1000); // Trabalhamos por 1ms

     // 2- Testa se a requisição foi finalizada (somente se ainda não foi finalizada)
      MPI_Test(&request, &request_finished, &status);
      
      // 1ms restantes para trabalhar
      time_left -= 1000.0;
    }

    // 3- Caso a requisição ainda não esteja completa, aguarde aqui.
    MPI_Wait(&request, &status);

    // Modificando o buffer para o segundo passo
    for (int i=0; i < buffer_count; ++i)
      buffer[i] = -i;

    // 4- Prepare outra requisição para o processo 1 com uma tag diferente
    MPI_Isend(buffer, buffer_count, MPI_INT, 1, 1, MPI_COMM_WORLD, &request);
    
    time_left = 3000.0;
    while (time_left > 0.0) {
      usleep(1000); // Trabalhamos por 1ms

      // 5- Testa se a requisição foi finalizada (somente se ainda não foi finalizada)
      MPI_Test(&request, &request_finished, &status);

      // 1ms restantes para trabalhar
      time_left -= 1000.0;
    }
    // 6- Espere terminar
    MPI_Wait(&request, &status);
    
  } else {
    // Trabalhe por 5 segundos
    sleep(5);

    // 7- Inicializa o recebimento sem bloqueio do processo 0
    MPI_Irecv(buffer, buffer_count, MPI_INT, 0, 0, MPI_COMM_WORLD, &request);

    // 8- Aguarde aqui a conclusão da solicitação
    MPI_Wait(&request, &status);

    print_buffer();
    
    // Trabalhe por 3 segundos
    sleep(3);

    // 9- Inicialize outro recebimento sem bloqueio
    MPI_Irecv(buffer, buffer_count, MPI_INT, 0, 1, MPI_COMM_WORLD, &request);
    
    // 10- Aguarde a conclusão
    MPI_Wait(&request, &status);

    print_buffer();
  }
 ////////// não deve modificar nada APÓS este ponto //////////

  // Parando o cronômetro
  time += MPI_Wtime();

  // Esta linha nos dá o tempo máximo decorrido em cada processo.
  // Veremos a redução mais tarde!
  double final_time;
  MPI_Reduce(&time, &final_time, 1, MPI_DOUBLE, MPI_MAX, 0, MPI_COMM_WORLD);
  
  if (rank == 0)
    printf("Tempo total para cenário sem bloqueio: %fs\n", final_time);
}