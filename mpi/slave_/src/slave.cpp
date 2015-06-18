#include <iostream>
#include <unistd.h>
#include <mpi.h>
#define MASTER 0

using namespace std;

//mpi
int rank;
int n_children;
MPI_Comm parent;
MPI_Comm children;

char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

void slave_work()
{
  std::cout << "[" << rank << "]" << "HELLO FROM SLAVE @ " << processor_name << endl;

  n_children = MPI::COMM_WORLD.Get_size();

  if (rank == MASTER)
    MPI_Send(&n_children, 1, MPI_INT, 0, 0, parent);

  std::cout << "[" << rank << "]" << "BYE BYE FROM SLAVE" << endl;
}

/**
* @method main
**/
int main(int argc, char* argv[])
{
  //init
  MPI_Init(&argc, &argv);
  rank = MPI::COMM_WORLD.Get_rank();
  parent = MPI::COMM_WORLD.Get_parent();
  MPI_Get_processor_name(processor_name, &name_len);

  //work
  slave_work();

  //finialize
  MPI_Finalize();
  return 0;
}
