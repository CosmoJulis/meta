//
// Created by Cosmo Julis on 11/19/21.
//

#ifndef JNITESTAPP_ALOG_H
#define JNITESTAPP_ALOG_H

#include<android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "tag", __VA_ARGS__)

#endif //JNITESTAPP_ALOG_H
