#include "JNIMath.h"
#include <string.h>

JNIEXPORT jint JNICALL Java_JNIMath_pow2
  (JNIEnv *env, jobject obj, jint num) {
  return num * num;
}

JNIEXPORT jboolean JNICALL Java_JNIMath_isNegative
  (JNIEnv *env, jobject obj, jboolean boolean) {
  return !boolean;
}

JNIEXPORT jstring JNICALL Java_JNIMath_copyString
  (JNIEnv *env, jobject obj, jstring string) {
  const char *str = env->GetStringUTFChars(string, 0);
  char cap[128];
  strcpy(cap, str);
  env->ReleaseStringUTFChars(string, str);
  return env->NewStringUTF(cap);
}

JNIEXPORT jint JNICALL Java_JNIMath_sumAll
  (JNIEnv *env, jobject obj, jintArray array) {
  int i, sum = 0;
  jsize len = env->GetArrayLength(array);
  jint *body = env->GetIntArrayElements(array, 0);
  for (i=0; i<len; i++)
    sum += body[i];

  env->ReleaseIntArrayElements(array, body, 0);
  return sum;
}
