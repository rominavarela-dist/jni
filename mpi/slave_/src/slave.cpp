#include <iostream>
#include <unistd.h>
#include <mpi.h>
#define MASTER 0

using namespace std;

const int FINALIZE= 0;
const int SAY_HELLO= 1;

//mpi
int rank;
int n_children;
MPI_Comm parent;
MPI_Comm children;

char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

void run()
{
  int command;

  while(true)
  {
    MPI_Recv(&command, 1, MPI_INT, 0, 0, parent, MPI_STATUS_IGNORE);

    switch(command)
    {
      case SAY_HELLO:
        std::cout << "[" << rank << "]" << "HELLO FROM SLAVE @ " << processor_name << endl;
        break;
      case FINALIZE:
        return;
    }
  }
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

  //send something
  n_children = MPI::COMM_WORLD.Get_size();
  if (rank == MASTER)
    MPI_Send(&n_children, 1, MPI_INT, 0, 0, parent);

  //work
  run();

  //finialize
  MPI_Finalize();
  return 0;
}
