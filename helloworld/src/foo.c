#include <jni.h>
#include <stdio.h>
#include "JNIFoo.h"

// Implementation of native method sayHello() of HelloJNI class
JNIEXPORT void JNICALL Java_JNIFoo_sayHello(JNIEnv *env, jobject thisObj) {
   printf("Hello World!\n");
   return;
}
