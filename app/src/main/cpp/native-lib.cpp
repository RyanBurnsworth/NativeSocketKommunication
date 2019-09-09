#include <jni.h>
#include <string>
#include "klient.h"

/**
 *
 * @param env - reference to the JNI environment
 * @param jStr - incoming jstring
 * @return - outputs a proper C++ string
 */
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

/**
 *
 * @param env - reference to the JNI environment
 * @param instance - reference to *this* Java object
 * @param hostname - the IP address of the remote server
 * @param port  - the port to connect to on the remote server
 * @return  - returns a socket to be stored and used or -1 for error
 */
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

/**
 *
 * @param env - reference to the JNI environment
 * @param instance - reference to *this* Java object
 * @param sock - active socket to send data through
 * @param data - data to be sent to the remote server
 */
JNIEXPORT void JNICALL
Java_com_ryanburnsworth_nativesocketkommunication_MainActivity_sendData(
        JNIEnv *env,
        jobject instance,
        jint sock,
        jstring data) {
    klient k;
    string sData = jstring2string(env, data);
    k.sendData((int) sock, sData);
}

/**
 *
 * @param env - reference to the JNI environment
 * @param instance - reference to *this* Java object
 * @param sock - active socket to disconnect
 */
JNIEXPORT void JNICALL
Java_com_ryanburnsworth_nativesocketkommunication_MainActivity_disconnect(
        JNIEnv *env,
        jobject instance,
        jint sock) {
    klient k;
    k.disconnectFromServer((int) sock);
}

/**
 *
 * @param env - reference to the JNI environment
 * @param instance - reference to *this* Java object
 * @param sock - active socket to listen for incoming data from
 * @return - returns incoming data from remote server
*/
JNIEXPORT jstring JNICALL
Java_com_ryanburnsworth_nativesocketkommunication_MainActivity_recvData(
        JNIEnv *env,
        jobject instance,
        jint sock) {
    klient k;
    string data = k.recvData((int) sock);
    return env->NewStringUTF(data.c_str());
}
}