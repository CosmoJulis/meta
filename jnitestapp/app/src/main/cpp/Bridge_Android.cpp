//
//  Bridge_Android.m
//
//  Created by li zhenyu on 2019/8/23.
//

#import "Bridge_Android.h"
#include "YTFun.h"

#include "jni_helper.hpp"


// @使用JNI的最佳实践 https://www.ibm.com/developerworks/cn/java/j-jni/index.html
JNIEnv * get_JNI_Env() {
    return GetEnv();
}

jclass get_bridge_java_class() {
    JNIEnv * env = get_JNI_Env();
    if (!env) return nullptr;
    jclass jcls = GetClass("com.unity3d.player.bridge.BridgeJava", env);
    if (env->ExceptionCheck()) return nullptr;
    return jcls;
}

jobject get_bridge_java_singleton() {
    static jobject singleton = nullptr;
    if (!singleton) {
        jclass jcls = get_bridge_java_class();
        if (!jcls) return nullptr;
        
        JNIEnv * env = get_JNI_Env();
        jmethodID singletonStaticMethod = env->GetStaticMethodID(jcls, "getInstance", "()Lcom/unity3d/player/bridge/BridgeJava;");
        if (env->ExceptionCheck()) return nullptr;
        
        jobject jobj = env->CallStaticObjectMethod(jcls, singletonStaticMethod);
        if (env->ExceptionCheck()) return nullptr;

        singleton = env->NewGlobalRef(jobj);
        if (env->ExceptionCheck()) return nullptr;
    }
    return singleton;
}


void _platform_install()
{

}

const char * _getAppName()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return nullptr;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "getAppName", "()Ljava/lang/String;");
        if (env->ExceptionCheck()) return nullptr;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring rstring = (jstring)env->CallObjectMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return nullptr;
        const char * str = env->GetStringUTFChars(rstring, nullptr);
        if (env->ExceptionCheck()) return nullptr;
        return str;
    }
    return nullptr;
}

const char * _getVersion()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return nullptr;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "getVersion", "()Ljava/lang/String;");
        if (env->ExceptionCheck()) return nullptr;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring rstring = (jstring)env->CallObjectMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return nullptr;
        const char * str = env->GetStringUTFChars(rstring, nullptr);
        if (env->ExceptionCheck()) return nullptr;
        return str;
    }
    return nullptr;
}

const char * _getBundleVersion()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return nullptr;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "getBundleVersion", "()Ljava/lang/String;");
        if (env->ExceptionCheck()) return nullptr;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring rstring = (jstring)env->CallObjectMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return nullptr;
        const char * str = env->GetStringUTFChars(rstring, nullptr);
        if (env->ExceptionCheck()) return nullptr;
        return str;
    }
    return nullptr;
}

bool _isDebug()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return false;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "isDebug", "()Z");
        if (env->ExceptionCheck()) return false;
        jmethod = tmp;
    }
    if (jmethod) {
        jboolean b = env->CallBooleanMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return false;
        return (bool)b;
    }
    return false;
}

const char * _getUDID()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return nullptr;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "getUDID", "()Ljava/lang/String;");
        if (env->ExceptionCheck()) return nullptr;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring rstring = (jstring)env->CallObjectMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return nullptr;
        const char * str = env->GetStringUTFChars(rstring, nullptr);
        if (env->ExceptionCheck()) return nullptr;
        return str;
    }
    return nullptr;
}

const char * _getIMSI()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return nullptr;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "getIMSI", "()Ljava/lang/String;");
        if (env->ExceptionCheck()) return nullptr;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring rstring = (jstring)env->CallObjectMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return nullptr;
        const char * str = env->GetStringUTFChars(rstring, nullptr);
        if (env->ExceptionCheck()) return nullptr;
        return str;
    }
    return nullptr;
}

const char * _getCountryCode()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return nullptr;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "getCountryCode", "()Ljava/lang/String;");
        if (env->ExceptionCheck()) return nullptr;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring rstring = (jstring)env->CallObjectMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return nullptr;
        const char * str = env->GetStringUTFChars(rstring, nullptr);
        if (env->ExceptionCheck()) return nullptr;
        return str;
    }
    return nullptr;
}


const char * _getLocation()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return nullptr;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "getLocation", "()Ljava/lang/String;");
        if (env->ExceptionCheck()) return nullptr;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring rstring = (jstring)env->CallObjectMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return nullptr;
        const char * str = env->GetStringUTFChars(rstring, nullptr);
        if (env->ExceptionCheck()) return nullptr;
        return str;
    }
    return nullptr;
}

bool _isVirtual()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return false;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "isVirtual", "()Z");
        if (env->ExceptionCheck()) return false;
        jmethod = tmp;
    }
    if (jmethod) {
        jboolean b = env->CallBooleanMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return false;
        return (bool)b;
    }
    return false;
}

bool _isRoot()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();

    if (!env || !jcls || !jobj) return false;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "isRoot", "()Z");
        if (env->ExceptionCheck()) return false;
        jmethod = tmp;
    }
    if (jmethod) {
        jboolean b = env->CallBooleanMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return false;
        return (bool)b;
    }
    return false;
}

bool _isVPN()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return false;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "isVPN", "()Z");
        if (env->ExceptionCheck()) return false;
        jmethod = tmp;
    }
    if (jmethod) {
        jboolean b = env->CallBooleanMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return false;
        return (bool)b;
    }
    return false;
}

bool _isFringeScreen()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return false;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = *env->GetMethodID(jcls, "isFringeScreen", "()Z");
        if (env->ExceptionCheck()) return false;
        jmethod = tmp;
    }
    if (jmethod) {
        jboolean b = env->CallBooleanMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return false;
        return (bool)b;
    }
    return false;
}


JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_networkStatusDidUpdate(JNIEnv * env, jobject jobj, jint status)
{
    int networkStatus = (int)status;
    YTFUN_NAMESPACE::Bridge::getInstance()->networkStatusDidUpdate(YTFUN_NAMESPACE::Bridge::NetworkStatus(networkStatus));
}

JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_backButtonDidTap(JNIEnv * env, jobject jobj)
{
    YTFUN_NAMESPACE::Bridge::getInstance()->backButtonDidTap();
}


void _vibrate(float duration)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "vibrate", "(F)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        jfloat f = duration;
        env->CallVoidMethod(jobj, jmethod, duration);
    }
}

void _print(const char * content)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "android_print", "(Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring string = env->NewStringUTF(content);
        if (env->ExceptionCheck()) return;
        env->CallVoidMethod(jobj, jmethod, string);
    }
}

void _goApplicationMarket(const char * appID)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "goApplicationMarket", "(Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring string = env->NewStringUTF(appID);
        if (env->ExceptionCheck()) return;
        env->CallVoidMethod(jobj, jmethod, string);
    }
}

void _goSetting()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "goSetting", "()V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        env->CallVoidMethod(jobj, jmethod);
    }
}

void _goRate()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "goRate", "()V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        env->CallVoidMethod(jobj, jmethod);
    }
}

void _copyText(const char * text)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "copyText", "(Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring string = env->NewStringUTF(text);
        if (env->ExceptionCheck()) return;
        env->CallVoidMethod(jobj, jmethod, string);
    }
}

void _report(const char * event, const char * content)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "report", "(Ljava/lang/String;Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring arg1 = env->NewStringUTF(event);
        if (env->ExceptionCheck()) return;
        jstring arg2 = env->NewStringUTF(content);
        if (env->ExceptionCheck()) return;
        env->CallVoidMethod(jobj, jmethod, arg1, arg2);
    }
}

void _openUrl(const char * url)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;
    
    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "openUrl", "(Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring string = env->NewStringUTF(url);
        if (env->ExceptionCheck()) return;
        env->CallVoidMethod(jobj, jmethod, string);
    }
}

void _exit()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "exit", "()V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        env->CallVoidMethod(jobj, jmethod);
    }
}




static std::pair<int, YTFUN_NAMESPACE::Bridge::BridgeLoginCallback> * pLoginCallback = nullptr;

void _login(YTFUN_NAMESPACE::Bridge::LoginWith with, const YTFUN_NAMESPACE::Bridge::BridgeLoginCallback callback)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "login", "(I)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }

    if (jmethod) {
        if (pLoginCallback) {
            pLoginCallback->second(false, "cancel");
            delete pLoginCallback;
            pLoginCallback = nullptr;
        }
        pLoginCallback = new std::pair<int, YTFUN_NAMESPACE::Bridge::BridgeLoginCallback> (std::make_pair((int)with, callback));
        env->CallVoidMethod(jobj, jmethod, (jint)with);
    }
}

JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_loginCallback(JNIEnv * env, jobject jobj, jint with, jboolean success, jstring json)
{
    if (pLoginCallback) {
        if (pLoginCallback->first == (int)with) {
            const char * str = env->GetStringUTFChars(json, nullptr);
            if (env->ExceptionCheck()) return;
            std::string jsonString = str;
            pLoginCallback->second((bool)success, jsonString);
            delete pLoginCallback;
            pLoginCallback = nullptr;
        }
    }
}





bool _hasDefaultGoogleAccount()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return false;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "hasDefaultGoogleAccount", "()Z");
        if (env->ExceptionCheck()) return false;
        jmethod = tmp;
    }
    if (jmethod) {
        jboolean b = env->CallBooleanMethod(jobj, jmethod);
        if (env->ExceptionCheck()) return false;
        return (bool)b;
    }
    return false;
}

static YTFUN_NAMESPACE::Bridge::BridgeGameLoginCallback * pGameLoginCallback = nullptr;

void _gameLogin(const YTFUN_NAMESPACE::Bridge::BridgeGameLoginCallback callback)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "gameLogin", "()V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }

    if (jmethod) {
        if (pGameLoginCallback) {
            (*pGameLoginCallback)(false, "cancel");
            delete pGameLoginCallback;
            pGameLoginCallback = nullptr;
        }
        pGameLoginCallback = new YTFUN_NAMESPACE::Bridge::BridgeGameLoginCallback (callback);
        env->CallVoidMethod(jobj, jmethod);
    }
}


JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_gameLoginCallback(JNIEnv * env, jobject jobj, jboolean success, jstring json)
{
    if (pGameLoginCallback) {
        const char * str = env->GetStringUTFChars(json, nullptr);
        if (env->ExceptionCheck()) return;
        std::string jsonString = str;
        (*pGameLoginCallback)((bool)success, jsonString);
        delete pGameLoginCallback;
        pGameLoginCallback = nullptr;
    }
}


static YTFUN_NAMESPACE::Bridge::BridgeSaveGameDataCallback * pSaveGameDataCallback = nullptr;

void _saveGameData(std::string data, const YTFUN_NAMESPACE::Bridge::BridgeSaveGameDataCallback callback)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "saveGameData", "(Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }

    if (jmethod) {
        if (pSaveGameDataCallback) {
            (*pSaveGameDataCallback)(false, "cancel");
            delete pSaveGameDataCallback;
            pSaveGameDataCallback = nullptr;
        }
        pSaveGameDataCallback = new YTFUN_NAMESPACE::Bridge::BridgeSaveGameDataCallback (callback);

        jstring arg1 = env->NewStringUTF(data.c_str());
        if (env->ExceptionCheck()) return;

        env->CallVoidMethod(jobj, jmethod, arg1);
    }
}


JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_saveGameDataCallback(JNIEnv * env, jobject jobj, jboolean success, jstring json)
{
    if (pSaveGameDataCallback) {
        const char * str = env->GetStringUTFChars(json, nullptr);
        if (env->ExceptionCheck()) return;
        std::string jsonString = str;
        (*pSaveGameDataCallback)((bool)success, jsonString);
        delete pSaveGameDataCallback;
        pSaveGameDataCallback = nullptr;
    }
}















void _logout()
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "logout", "()V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        env->CallVoidMethod(jobj, jmethod);
    }
}




static YTFUN_NAMESPACE::Bridge::BridgePurchaseCallback * pPurchaseCallback = nullptr;

void _purchase(std::string sku, const YTFUN_NAMESPACE::Bridge::BridgePurchaseCallback callback)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "purchase", "(Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        if (pPurchaseCallback) {
            (*pPurchaseCallback)(sku.c_str(), false, "cancel");
            delete pPurchaseCallback;
            pPurchaseCallback = nullptr;
        }
        pPurchaseCallback = new YTFUN_NAMESPACE::Bridge::BridgePurchaseCallback (callback);

        jstring arg1 = env->NewStringUTF(sku.c_str());
        if (env->ExceptionCheck()) return;
        env->CallVoidMethod(jobj, jmethod, arg1);
    }
}

JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_purchaseCallback(JNIEnv * env, jobject jobj, jstring sku, jboolean succcess, jstring json)
{
    if (pPurchaseCallback) {
        const char * skucstr = env->GetStringUTFChars(sku, nullptr);
        if (env->ExceptionCheck()) return;
        std::string skuString = skucstr;

        const char * str = env->GetStringUTFChars(json, nullptr);
        if (env->ExceptionCheck()) return;
        std::string jsonString = str;

        (*pPurchaseCallback)(skuString, (int)succcess, jsonString);
        delete pPurchaseCallback;
        pPurchaseCallback = nullptr;
    }
}


static YTFUN_NAMESPACE::Bridge::BridgeShareCallback * pShareCallback = nullptr;

void _shareText(std::string text, std::string link, const YTFUN_NAMESPACE::Bridge::BridgeShareCallback callback)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "shareText", "(Ljava/lang/String;Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        if (pShareCallback) {
            (*pShareCallback)(false);
            delete pShareCallback;
            pShareCallback = nullptr;
        }
        pShareCallback = new YTFUN_NAMESPACE::Bridge::BridgeShareCallback (callback);

        jstring arg1 = env->NewStringUTF(text.c_str());
        if (env->ExceptionCheck()) return;
        jstring arg2 = env->NewStringUTF("");
        if (link.length() > 0) {
            arg2 = env->NewStringUTF(link.c_str());
        }
        env->CallVoidMethod(jobj, jmethod, arg1, arg2);
    }
}

JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_shareCallback(JNIEnv * env, jobject jobj, jboolean succcess)
{
    if (pShareCallback) {
        (*pShareCallback)((int)succcess);
        delete pShareCallback;
        pShareCallback = nullptr;
    }
}

bool _canShowAd(YTFUN_NAMESPACE::Bridge::AdMode mode) {
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return false;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "canShowAd", "(I)Z");
        if (env->ExceptionCheck()) return false;
        jmethod = tmp;
    }
    if (jmethod) {
        jboolean b = env->CallBooleanMethod(jobj, jmethod, jint(mode));
        if (env->ExceptionCheck()) return false;
        return (bool)b;
    }
    return false;
}


static YTFUN_NAMESPACE::Bridge::BridgeAdCallback * pAdCallback = nullptr;

void _showAd(YTFUN_NAMESPACE::Bridge::AdMode mode, std::string adUnit, const YTFUN_NAMESPACE::Bridge::BridgeAdCallback callback)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "showAd", "(ILjava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        if (pAdCallback) {
            (*pAdCallback)(false, YTFUN_NAMESPACE::Bridge::AdReason::failure, "");
            delete pAdCallback;
            pAdCallback = nullptr;
        }
        pAdCallback = new YTFUN_NAMESPACE::Bridge::BridgeAdCallback (callback);

        jstring string = env->NewStringUTF(adUnit.c_str());
        if (env->ExceptionCheck()) return;

        env->CallVoidMethod(jobj, jmethod, jint(mode), string);
    }
}

JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_adCallback(JNIEnv * env, jobject jobj, jboolean succcess, jint reason, jstring json)
{
    if (pAdCallback) {
        const char * str = env->GetStringUTFChars(json, nullptr);
        if (env->ExceptionCheck()) return;
        std::string jsonString = str;
        (*pAdCallback)((bool)succcess, YTFUN_NAMESPACE::Bridge::AdReason(reason), jsonString);
        delete pAdCallback;
        pAdCallback = nullptr;
    }
}

void _setAdUserId(std::string uid)
{
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "setAdUserId", "(Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring string = env->NewStringUTF(uid.c_str());
        if (env->ExceptionCheck()) return;
        env->CallVoidMethod(jobj, jmethod, string);
    }
}


void _hideBanner(std::string adUnit) {
    JNIEnv * env = get_JNI_Env();
    jclass jcls = get_bridge_java_class();
    jobject jobj = get_bridge_java_singleton();
    if (!env || !jcls || !jobj) return;

    static jmethodID jmethod = nullptr;
    if (!jmethod) {
        jmethodID tmp = env->GetMethodID(jcls, "hideBanner", "(Ljava/lang/String;)V");
        if (env->ExceptionCheck()) return;
        jmethod = tmp;
    }
    if (jmethod) {
        jstring string = env->NewStringUTF(adUnit.c_str());
        if (env->ExceptionCheck()) return;
        env->CallVoidMethod(jobj, jmethod, string);
    }
}
