#include <string>
#include <math.h>
#include "include/png/png.h"
#include "rgbtopng.h"
#include "android/log.h"
const png_uint_32 width = 255;
const png_uint_32 height = 255;
unsigned char pixels[width*height*4];
int getValue(int row,int num){
    return (row *width+num-1)*4;
}
void drawOval(int x,int y,int width,int height){
    int leftTopX=x-width/2;
    int leftTopY=y-height/2;
    int rightTopX=x+width/2;
    int rightTopY=y+height/2;
    int leftButtonX=x-width/2;
    int leftButtonY=y+height/2;
    int rightButtonX=x+width/2;
    int rightButtonY=y+height/2;
    int F1=x-1;
    int F2=x+1;
    int TopX=x;
    int TopY=y-height;

    int a=sqrt(TopY*TopY+F1*F1);
    int c=F1;

    for(float i=x-width/2;i<=x+width/2;i++) {
        float m  =sqrt(1.0*((pow(a, 2) - pow(c, 2))*pow(a,2)-(pow(a, 2) - pow(c, 2))*pow(i,2))/ pow(a,2));
        __android_log_print(ANDROID_LOG_ERROR,"WJS_ERROR","%f",m);
        int ret=getValue(i,m);
        pixels[ret]=255;
        pixels[ret+1]=0;
        pixels[ret+2]=0;
        pixels[ret+3]=255;
    }

}
extern "C" JNIEXPORT jstring

JNICALL Java_com_example_bitmapoper_MainActivity_stringFromJNI(JNIEnv *env, jobject,jstring jpath) {
    char *path=jstringTostring(env,jpath);
    memset(pixels,0, sizeof(pixels));
    drawOval(120,120,240,100);




    writePng(path,pixels,width,height,8);
    char value[2000];
    sprintf(value,"%d",getValue(1,3));
    return env->NewStringUTF(value);
}