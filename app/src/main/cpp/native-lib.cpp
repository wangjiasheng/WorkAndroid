#include <string>
#include <math.h>
#include "include/png/png.h"
#include "rgbtopng.h"
#include "android/log.h"
const png_uint_32 width = 1000;
const png_uint_32 height = 1000;
unsigned char pixels[width*height*4];
int getValue(int row,int num){
    return (row *width+num-1)*4;
}
void drawOval(int x,int y,int width,int height){
    float leftTopX=x-width/2;
    float leftTopY=y-height/2;
    float rightTopX=x+width/2;
    float rightTopY=y-height/2;
    float leftButtonX=x-width/2;
    float leftButtonY=y+height/2;
    float rightButtonX=x+width/2;
    float rightButtonY=y+height/2;

    float F1=(rightTopX-leftTopX)/2;      //椭圆长半轴
    float Y1=(rightButtonY-rightTopY)/2;  //椭圆短半轴


    for(int i=0;i< sizeof(pixels);i++) {
        float srtd = sqrt((1 - ((i - x) * (i - x)) / (F1 * F1)) * (Y1 * Y1)) + y;
        int gg = round(srtd);
        int hh = round(-srtd);
        if (getValue(i, gg) < sizeof(pixels)) {
            pixels[getValue(i, gg)] = 255;
            pixels[getValue(i, gg) + 1] = 0;
            pixels[getValue(i, gg) + 2] = 0;
            pixels[getValue(i, gg) + 3] = 255;

         }
        /*if (getValue(i, hh) < sizeof(pixels)) {
            pixels[getValue(i, hh)] = 255;
            pixels[getValue(i, hh) + 1] = 0;
            pixels[getValue(i, hh) + 2] = 0;
            pixels[getValue(i, hh) + 3] = 255;

        }*/
    }

}
extern "C" JNIEXPORT jstring

JNICALL Java_com_example_bitmapoper_MainActivity_stringFromJNI(JNIEnv *env, jobject,jstring jpath) {
    char *path=jstringTostring(env,jpath);
    memset(pixels,100, sizeof(pixels));
    drawOval(500,500,1000,500);

    writePng(path,pixels,width,height,8);
    char value[2000];
    sprintf(value,"%d",getValue(1,3));
    return env->NewStringUTF("dddd");
}