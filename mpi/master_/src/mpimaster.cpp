#include <jni.h>
#include <mpi.h>
#include <cstdlib>//legacy stdlib.h and time.h
#include <iostream>
#include <dlfcn.h>
#include <cstring>
#include "MPIController.h"

using namespace std;

static void *mpilibhandle=NULL;
const int FINALIZE= 0;
const int SAY_HELLO= 1;

//mpi
int n_children;
MPI_Comm children;

char processor_name[MPI_MAX_PROCESSOR_NAME];
int name_len;

JNIEXPORT jboolean JNICALL Java_MPIController_loadGlobalLibraries(JNIEnv *env, jclass clazz)
{
    if (NULL == (mpilibhandle = dlopen("libmpi.so" ,RTLD_NOW | RTLD_GLOBAL))) {
        return false;
    }
    return true;
}

/**
* @method init
**/
JNIEXPORT void JNICALL Java_MPIController_init(JNIEnv *env, jobject thisObj) {
  std::cout << "Initializing Master..." << endl;
  MPI_Init(NULL,NULL);
  MPI_Get_processor_name(processor_name, &name_len);

  //add hosts and spawn
  std::cout << "Initializing Children..." << endl;
  MPI_Info info;
  MPI_Info_create(&info);
  MPI_Info_set(info,"hostfile","./host_file");
  MPI_Comm_spawn("../slave_/slave", MPI_ARGV_NULL, 4,
      info, 0, MPI_COMM_WORLD,
      &children, MPI_ERRCODES_IGNORE);

  MPI_Recv(&n_children, 1, MPI_INT, 0, 0, children, MPI_STATUS_IGNORE);
  std::cout << "Got " << n_children << " slaves" << endl;

  std::cout << "Ready" << endl;
  return;
}

/**
* @method sayHello
**/
JNIEXPORT void JNICALL Java_MPIController_sayHello(JNIEnv *env, jobject thisObj) {
  for(int i=0;i<n_children;i++)
    MPI_Send(&SAY_HELLO, 1, MPI_INT, i, 0, children);
}

/**
* @method finish
**/
JNIEXPORT void JNICALL Java_MPIController_finish(JNIEnv *env, jobject thisObj) {
   for(int i=0;i<n_children;i++)
     MPI_Send(&FINALIZE, 1, MPI_INT, i, 0, children);

   MPI_Comm_free(&children);
   MPI_Finalize();
   std::cout << "MPI Finalized" << endl;
   return;
}
