// Você tem acesso às seguintes variáveis ​​globais
int world_rank, world_size;
MPI_Comm custom_comm1, custom_comm2, custom_comm3, tmp;

// O comunicador tmp é fornecido se você precisar apontar para algum lugar, onde você não precisa
// preocupa-se com o comunicador enviado. Por exemplo, ao usar MPI_UNDEFINED como cor.

// world_rank: rank do processo em MPI_COMM_WORLD
//world_size: tamanho de MPI_COMM_WORLD
// Estas duas variáveis ​​já estão inicializadas quando splitting() é chamado

void splitting() {
    // Define a color variable for MPI_Comm_split
    int color;

   // 1- Primeira divisão aqui
    // Processa 0-3 em custom_comm1 e processa 4-6 em custom_comm2
    if (world_rank >= 0 && world_rank <= 3) {
        color = 1; // Color for custom_comm1
        MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &custom_comm1);
    } else if (world_rank >= 4 && world_rank <= 6) {
        color = 2; // Color for custom_comm2
        MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &custom_comm2);
    } else {
        // Process not part of custom_comm1 or custom_comm2
        MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, world_rank, &tmp);
    }

    // 2- Segunda divisão aqui
    // Processa 0 e 4 em custom_comm3
    if (world_rank == 0 || world_rank == 4) {
        color = 3; // Color for custom_comm3
        MPI_Comm_split(MPI_COMM_WORLD, color, world_rank, &custom_comm3);
    } else {
        // Process not part of custom_comm3
        MPI_Comm_split(MPI_COMM_WORLD, MPI_UNDEFINED, world_rank, &tmp);
    }
}