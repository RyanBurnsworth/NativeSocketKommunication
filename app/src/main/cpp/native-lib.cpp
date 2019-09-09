#include <jni.h>
#include <string>
#include "klient.h"

std::string jstring2string(JNIEnv *env, jstring jStr) {
    if (!jStr)
        return "";

    const jclass stringClass = env->GetObjectClass(jStr);
    const jmethodID getBytes = env->GetMethodID(stringClass, "getBytes", "(Ljava/lang/String;)[B");
    const jbyteArray stringJbytes = (jbyteArray) env->CallObjectMethod(jStr, getBytes,
                                                                       env->NewStringUTF("UTF-8"));

    size_t length = (size_t) env->GetArrayLength(stringJbytes);
    jbyte *pBytes = env->GetByteArrayElements(stringJbytes, NULL);

    std::string ret = std::string((char *) pBytes, length);
    env->ReleaseByteArrayElements(stringJbytes, pBytes, JNI_ABORT);

    env->DeleteLocalRef(stringJbytes);
    env->DeleteLocalRef(stringClass);
    return ret;
}

extern "C" {
JNIEXPORT jint JNICALL
Java_com_ryanburnsworth_nativesocketkommunication_MainActivity_init(
        JNIEnv *env,
        jobject instance,
        jstring hostname,
        jint port) {
    klient k;
    string hname = jstring2string(env, hostname);
    return k.connectToServer(hname, (int) port);
}

JNIEXPORT jint JNICALL
Java_com_ryanburnsworth_nativesocketkommunication_MainActivity_sendData(
        JNIEnv *env,
        jobject instance,
        jint sock,
        jstring data) {
    klient k;
    string sData = jstring2string(env, data);
    k.sendData((int) sock, sData);
    return 1;
}

JNIEXPORT jint JNICALL
Java_com_ryanburnsworth_nativesocketkommunication_MainActivity_disconnect(
        JNIEnv *env,
        jobject instance,
        jint sock) {
    klient k;
    k.disconnectFromServer(sock);
    return 1;
}

JNIEXPORT jstring JNICALL
Java_com_ryanburnsworth_nativesocketkommunication_MainActivity_recvData(
        JNIEnv *env,
        jobject instance,
        jint sock) {
    klient k;
    string data = k.recvData(sock);
    return env->NewStringUTF(data.c_str());
}
}