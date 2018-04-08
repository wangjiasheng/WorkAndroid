//
// Created by 王家胜 on 2018/4/7.
//
#include "jni.h"
#ifndef BITMAPOPER_RGBTOPNG_H
#define BITMAPOPER_RGBTOPNG_H

#endif //BITMAPOPER_RGBTOPNG_H
char* jstringTostring(JNIEnv* env, jstring jstr);
int writePng(char* png_file_name, unsigned char*  pixels , int width, int height, int bit_depth);