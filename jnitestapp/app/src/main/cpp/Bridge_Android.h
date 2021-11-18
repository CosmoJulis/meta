//
//  Bridge_Android.h
//
//  Created by li zhenyu on 2019/8/23.
//

#ifndef Bridge_Android_h
#define Bridge_Android_h

#include <jni.h>

extern "C" {
    void _platform_install();
    const char * _getAppName();
    const char * _getVersion();
    const char * _getBundleVersion();
    bool _isDebug();
    const char * _getUDID();
    const char * _getIMSI();
    const char * _getCountryCode();
    const char * _getLocation();
    bool _isVirtual();
    bool _isRoot();
    bool _isVPN();
    bool _isFringeScreen();

    JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_networkStatusDidUpdate(JNIEnv * env, jobject jobj, int status);
    JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_backButtonDidTap(JNIEnv * env, jobject jobj);

    void _vibrate(float duration);
    void _print(const char * content);
    void _goApplicationMarket(const char * appID);
    void _goSetting();
    void _goRate();
    void _copyText(const char * text);
    void _report(const char * event, const char * content);
    void _openUrl(const char * url);
    void _exit();


    JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_loginCallback(JNIEnv * env, jobject jobj, jint with, jboolean succcess, jstring json);

    bool _hasDefaultGoogleAccount();
    JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_gameLoginCallback(JNIEnv * env, jobject jobj, jboolean succcess, jstring json);

    JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_saveGameDataCallback(JNIEnv * env, jobject jobj, jstring data, jboolean succcess, jstring json);

    void _logout();

    JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_purchaseCallback(JNIEnv * env, jobject jobj, jstring sku, jboolean succcess, jstring json);

    JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_shareCallback(JNIEnv * env, jobject jobj, jboolean succcess);
    JNIEXPORT void JNICALL Java_com_unity3d_player_bridge_BridgeJava_adCallback(JNIEnv * env, jobject jobj, jboolean succcess, jint reason, jstring json);


}


#include "YTFun.h"
void _login(YTFUN_NAMESPACE::Bridge::LoginWith with, const YTFUN_NAMESPACE::Bridge::BridgeLoginCallback callback);
void _gameLogin(const YTFUN_NAMESPACE::Bridge::BridgeGameLoginCallback callback);
void _saveGameData(std::string data, const YTFUN_NAMESPACE::Bridge::BridgeSaveGameDataCallback callback);
void _purchase(std::string sku, const YTFUN_NAMESPACE::Bridge::BridgePurchaseCallback callback);
void _shareText(std::string text, std::string link, const YTFUN_NAMESPACE::Bridge::BridgeShareCallback callback);
bool _canShowAd(YTFUN_NAMESPACE::Bridge::AdMode mode);
void _showAd(YTFUN_NAMESPACE::Bridge::AdMode mode, std::string adUnit, const YTFUN_NAMESPACE::Bridge::BridgeAdCallback callback);
void _setAdUserId(std::string uid);
void _hideBanner(std::string adUnit);

#endif
