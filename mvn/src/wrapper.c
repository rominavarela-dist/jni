#include <jni.h>
#include <stdio.h>
#include "JNIWrapper.h"

JNIEXPORT jint JNICALL Java_com_hp_hpl_jni_JNIWrapper_run
(JNIEnv *env, jobject thisObj) {
  return 1;
}
