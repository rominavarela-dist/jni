#include <jni.h>
#include <mpi.h>
#include <cstdlib>//legacy stdlib.h and time.h
#include <iostream>
#include <dlfcn.h>
#include "MPIController.h"

using namespace std;

static int len = 0;
static char** sargs = 0;
static void *mpilibhandle=NULL;

//mpi
int rank;
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
JNIEXPORT void JNICALL Java_MPIController_init(JNIEnv *env, jclass clazz, jobjectArray argv) {
  std::cout << "Initializing MPI..." << endl;

    len = env->GetArrayLength(argv);
    sargs = (char**)calloc(len+1, sizeof(char*));

    for(int i = 0; i < len; i++)
    {
        jstring jc = (jstring)env->GetObjectArrayElement( argv, i);
        const char *s = env->GetStringUTFChars(jc, 0);
        sargs[i] = (char*)calloc(strlen(s) + 1, sizeof(char));
        strcpy(sargs[i], s);
        env->DeleteLocalRef(jc);
    }

  int rc = MPI_Init(&len, &sargs);

  rank = MPI::COMM_WORLD.Get_rank();
  MPI_Get_processor_name(processor_name, &name_len);

  //add hosts and spawn

  MPI_Info info;
  MPI_Info_create(&info);
  MPI_Info_set(info,"add-hostfile","../slave_/app/host_file");
  MPI_Comm_spawn("../slave_/app/slave", MPI_ARGV_NULL, 4,
      info, 0, MPI_COMM_WORLD,
      &children, MPI_ERRCODES_IGNORE);

  std::cout << "MPI Initialized" << endl;
  MPI_Recv(&n_children, 1, MPI_INT, 0, 0, children, MPI_STATUS_IGNORE);
  std::cout << "[" << rank << "]" << " Got " << n_children << " slaves..." << endl;

  return;
}

/**
* @method sayHello
**/
JNIEXPORT void JNICALL Java_MPIController_sayHello(JNIEnv *env, jobject thisObj) {
  int n= 100;

  for(int i=0;i<n_children;i++)
    MPI_Send(&n, 1, MPI_INT, i, 0, children);
    
  return;
}

/**
* @method finish
**/
JNIEXPORT void JNICALL Java_MPIController_finish(JNIEnv *env, jobject thisObj) {
   std::cout << "MPI Finalized" << endl;
   MPI_Finalize();
   return;
}
