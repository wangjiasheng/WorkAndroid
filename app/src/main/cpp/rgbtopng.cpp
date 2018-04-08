//
// Created by 王家胜 on 2018/4/7.
//
#include <string>
#include <malloc.h>
#include "include/png/png.h"
#include <jni.h>

int writePng(char* png_file_name, unsigned char*  pixels , int width, int height, int bit_depth)
{
    png_structp png_ptr;
    png_infop info_ptr;
    FILE *png_file = fopen(png_file_name, "wb");
    if (!png_file)
    {
        return -1;
    }
    png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(png_ptr == NULL)
    {
        printf("ERROR:png_create_write_struct/n");
        fclose(png_file);
        return 0;
    }
    info_ptr = png_create_info_struct(png_ptr);
    if(info_ptr == NULL)
    {
        printf("ERROR:png_create_info_struct/n");
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return 0;
    }
    png_init_io(png_ptr, png_file);

    //设置PNG文件头
    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth,//颜色深度，也就是每个颜色成分占用位数（8表示8位红8位绿8位蓝，如果有透明通道则还会有8位不透明度）
                 PNG_COLOR_TYPE_RGB_ALPHA,               //颜色类型，PNG_COLOR_TYPE_RGB表示24位真彩深色，PNG_COLOR_TYPE_RGBA表示32位带透明通道真彩色
                 PNG_INTERLACE_NONE,                      //不交错。PNG_INTERLACE_ADAM7表示这个PNG文件是交错格式。交错格式的PNG文件在网络传输的时候能以最快速度显示出图像的大致样子。
                 PNG_COMPRESSION_TYPE_BASE,              //压缩方式
                 PNG_FILTER_TYPE_BASE                     //这个不知道，总之填写PNG_FILTER_TYPE_BASE即可。
    );


    png_colorp palette = (png_colorp)png_malloc(png_ptr, PNG_MAX_PALETTE_LENGTH * sizeof(png_color));
    if (!palette) {
        fclose(png_file);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        return false;
    }
    png_set_PLTE(png_ptr, info_ptr, palette, PNG_MAX_PALETTE_LENGTH);
    png_write_info(png_ptr, info_ptr);
    png_set_packing(png_ptr);
    //这里就是图像数据了
    png_bytepp rows = (png_bytepp)png_malloc(png_ptr, height * sizeof(png_bytep));
    for (int i = 0; i < height; ++i)
    {
        rows[i] = (png_bytep)(pixels + (i) * width * 4);
    }

    png_write_image(png_ptr, rows);
    delete[] rows;
    png_write_end(png_ptr, info_ptr);
    png_free(png_ptr, palette);
    palette=NULL;
    png_destroy_write_struct(&png_ptr, &info_ptr);
    fclose(png_file);
    return 0;
}
char* jstringTostring(JNIEnv* env, jstring jstr)
{
    char* rtn = NULL;
    jclass clsstring = env->FindClass("java/lang/String");
    jstring strencode = env->NewStringUTF("utf-8");
    jmethodID mid = env->GetMethodID(clsstring, "getBytes", "(Ljava/lang/String;)[B");
    jbyteArray barr= (jbyteArray)env->CallObjectMethod(jstr, mid, strencode);
    jsize alen = env->GetArrayLength(barr);
    jbyte* ba = env->GetByteArrayElements(barr, JNI_FALSE);
    if (alen > 0)
    {
        rtn = (char*)malloc(alen + 1);

        memcpy(rtn, ba, alen);
        rtn[alen] = 0;
    }
    env->ReleaseByteArrayElements(barr, ba, 0);
    return rtn;
}