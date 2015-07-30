/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class JNIDataTypes */

#ifndef _Included_JNIMath
#define _Included_JNIMath
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     JNIMath
 * Method:    pow2
 * Signature: (I)I
 */
JNIEXPORT jint JNICALL Java_JNIMath_pow2
  (JNIEnv *, jobject, jint);

/*
 * Class:     JNIMath
 * Method:    isNegative
 * Signature: (Z)Z
 */
JNIEXPORT jboolean JNICALL Java_JNIMath_isNegative
  (JNIEnv *, jobject, jboolean);

/*
 * Class:     JNIMath
 * Method:    copyString
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_JNIMath_copyString
  (JNIEnv *, jobject, jstring);

/*
 * Class:     JNIMath
 * Method:    sumAll
 * Signature: ([I)I
 */
JNIEXPORT jint JNICALL Java_JNIMath_sumAll
  (JNIEnv *, jobject, jintArray);

#ifdef __cplusplus
}
#endif
#endif
