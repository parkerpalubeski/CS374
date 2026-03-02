#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/wait.h>
#include <ctype.h>
#include "ppm.h"

typedef struct  {
    struct ppm *image;
    int start;
    int height;
    int avgr, avgg, avgb, pixnum;
}slice;

void* thread(void* arg);

int main(int argc, char* argv[])
{
    int num = atoi(argv[1]);
    if(argc != 4 || num == 0)
    {
        fprintf(stderr, "usage: ./grayscaler int filepath filepath\n");
        exit(1);
    }
    //parse thread num
    struct ppm *img = ppm_read(argv[2]);
    pthread_t tids[num];
    slice thr[num];
    //read
    if(img == NULL){
        perror("ppm_read");
        exit(1);
    }
    int thr_height = img->height / num;
    int thr_remainder = img->height % num;
    //generate threads
    for(int i = 0; i < num; i++)
    {
        thr[i].image = img;
        thr[i].start = i * thr_height;
        if(i == num-1){thr[i].height = thr_height + thr_remainder;}
        else{thr[i].height = thr_height;}

        pthread_create(&tids[i], NULL, thread, &thr[i]);
    }
    //join
    for (int i = 0; i < num; i++) {
        pthread_join(tids[i], NULL);
    }
    //get avgs
    int r = 0, g = 0, b = 0, p = 0;
    for (int i = 0; i < num; i++) {
        r += thr[i].avgr;
        g += thr[i].avgg;
        b += thr[i].avgb;
        p += thr[i].pixnum;
        printf("Thread [%d]: %d %d\n", i, thr[i].start, thr[i].height);
    }
    r /= p, g /= p, b /= p;
    printf("Average R: %d\nAverage G: %d\nAverage B: %d\n", r, g, b);

    //write
    if(ppm_write(img, argv[3]) == -1)
    {
        perror("ppm_write");
        exit(1);
    }
    ppm_free(img);

}

void* thread(void* arg) {
    (void)arg;
    slice *thr = arg;
    int finr = 0, fing = 0, finb = 0, p = 0;
    for(int i = thr->start; i < thr->start + thr->height; i ++)//rows
    {
        for(int j = 0; j < thr->image->width; j++)//colums
        {
            int pix = ppm_get_pixel(thr->image, j, i);
            int r = PPM_PIXEL_R(pix);
            int g = PPM_PIXEL_G(pix);
            int b = PPM_PIXEL_B(pix);

            int gray = (299*r + 587*g + 114*b) / 1000;
            ppm_set_pixel(thr->image, j, i, PPM_PIXEL(gray, gray, gray));
            
            finr += r;
            fing += g;
            finb += b;
            p++;
        }
    }

    thr->avgr = finr;
    thr->avgg = fing;
    thr->avgb = finb;
    thr->pixnum = p;


    return NULL;
}