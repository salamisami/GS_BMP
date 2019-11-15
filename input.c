//
// Created by sami on 11/11/19.
//
#define Err -1
#define ok 0
#include "input.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "BMP_basis_lib.h"
#include <errno.h>
static int height;
static int width;
static BITMAPINFOHEADER infoHeader;
static BITMAPFILEHEADER fileHeader;
typedef RGBTRIPLE (*RGBTRIPLEArrayPointer)[];
int getHeight(){
    return height;
}
int getWidth(){
    return width;
}
BITMAPINFOHEADER getInfoHeader(){
    return infoHeader;
}
// Dynamic memory alloc for RGTRIPLE array
RGBTRIPLEArrayPointer allocRGPTRIPLEArray(dimension dim)
{
    const size_t numBytes = dim.height * dim.width * sizeof(RGBTRIPLE);
    void* p = malloc(numBytes);
    if (p == NULL)
    {
        printf("ERROR: malloc\n");
        exit(-1);
    }
    return p;
}
dimension getDim(const char* filename){
    FILE* fp = fopen(filename,"rb");
    if (fp == NULL){
        printf("File is NULL");
        dimension error;
        error.width = -1;
        error.height = -1;
        return error;
    }
    printf("Read Bitmap Info Header \n");
    size_t elemsRead =  fread((void*)&infoHeader, sizeof(BITMAPINFOHEADER),1,fp);
    width = infoHeader.biWidth;
    height = infoHeader.biHeight;
    dimension dim;
    dim.height = height;
    dim.width = width;
    return dim;
}
int readHeader (){


    const char * filename = "/home/sami/CLionProjects/untitled/test.bmp";
    printf("\nOpen file '%s'\n\n", filename);
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Failed to open file!\n");
        printf("Error %d",errno);
        return -1;
    }

    printf("Read BITMAP FILE HEADER\n");
    size_t elemsRead = fread((void*)&fileHeader, sizeof(BITMAPFILEHEADER), 1, fp);
    printf("elemsRead = '%d'\n\n", elemsRead);

    printf("Read BITMAP INFO HEADER\n");
    size_t elemsRead2 = fread((void*)&infoHeader, sizeof(BITMAPINFOHEADER), 1, fp);
    printf("elemsRead2 = '%d'\n\n", elemsRead2);
    size_t elemsRead3 = fread();
    width = infoHeader.biWidth;
    height = infoHeader.biHeight;
    RGBTRIPLE arr [ width ] [ height ];
    /*for (int i=0;i<width;i++){
        for (int j = 0; j <height ; ++j) {
            arr[i][j]=
        }
    }*/

    printf("Close file\n\n");
    fclose(fp);

    printf("Print BITMAP FILE HEADER\n");
    printBITMAPFILEHEADER(fileHeader);

    printf("Print BITMAP INFO HEADER\n");
    printBITMAPINFOHEADER(infoHeader);

    printf("Call basicChecks\n");
    bool isOkay = basicChecks(fileHeader, infoHeader);
    printf("isOkay = '%d'\n\n", isOkay);

    return 0;
}