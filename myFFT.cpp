#include <avr/pgmspace.h>
#include "myFFT.h"
#include <Arduino.h>
#define pi 3.141592654
void myDFT(double* re, double* im, int N, int Fs){
    int re2[N], im2[N];
    for (int i = 0; i < N; i++){
        double temp_re = 0, temp_im = 0;
        for (int j = 0; j < N; j++){
            temp_re += re[j]*cos(-2*pi*i*j/N);
            temp_im += re[j]*sin(-2*pi*i*j/N);
        }
        re2[i] = temp_re;
        im2[i] = temp_im;
    }
    for (int i = 0; i < N; i++){
        re[i] = re2[i];
        im[i] = im2[i];
    }
}

void myFFT(double* nXr, double* nXi, double real[], double imag[], int N, int h, int sam_gap){
    /* Variables:
     nXr: real Freq
     nXi: imagined Freq
     r[]: real signal
     i[]: imagined signal
     N: # of samples
     h: signal starting point
     sam_gap: signal sampling gap
    */
    if (N == 1){
        nXr[0] = real[h];
        nXi[0] = imag[h];
        return;
    }else{
        double nXr1[N/2], nXi1[N/2], nXr2[N/2], nXi2[N/2];
        // Interval recursion
        myFFT(nXr1, nXi1, real, imag, N/2, h, sam_gap*2);
        myFFT(nXr2, nXi2, real, imag, N/2, h+sam_gap, sam_gap*2);
        for (int i = 0; i < (N/2); i++){
            // t <- X_k
            double temp_re = nXr1[i];
            double temp_im = nXi1[i];
            double temp_re_iN2 = nXr2[i];
            double temp_im_iN2 = nXi2[i];
            // X_k <- t + exp(-2*pi*i*k/N) X_(k+N/2)
            nXr[i] = temp_re + cos(-2*pi*i/N)*temp_re_iN2 - sin(-2*pi*i/N)*temp_im_iN2;
            nXi[i] = temp_im + cos(-2*pi*i/N)*temp_im_iN2 + sin(-2*pi*i/N)*temp_re_iN2;
            // X_(k+N/2) <- t - exp(-2*pi*i*k/N) X_(k+N/2)
            nXr[i+N/2] = temp_re - (cos(-2*pi*i/N)*temp_re_iN2 - sin(-2*pi*i/N)*temp_im_iN2);
            nXi[i+N/2] = temp_im - (cos(-2*pi*i/N)*temp_im_iN2 + sin(-2*pi*i/N)*temp_re_iN2);
        }
    }
}


void myFFT2(double* nXr, double* nXi, int fst, double real[], double imag[], int N, int h, int sam_gap){
    /* Variables:
       nXr: real Freq
       nXi: imagined Freq
       fst: Freq starting point
       r[]: real signal
       i[]: imagined signal
       N: # of samples
       h: signal starting point
       sam_gap: signal sampling gap
    */
    if (N == 1){
        nXr[fst] = real[h];
        nXi[fst] = imag[h];
        return;
    }else{
        // double nXr1[N/2], nXi1[N/2], nXr2[N/2], nXi2[N/2];
        // Interval recursion
        myFFT2(nXr, nXi, fst, real, imag, N/2, h, sam_gap*2);
        myFFT2(nXr, nXi, fst+N/2, real, imag, N/2, h+sam_gap, sam_gap*2);
        for (int i = 0; i < (N/2); i++){
            // t <- X_k
            double temp_re = nXr[i+fst];
            double temp_im = nXi[i+fst];
            double temp_re_iN2 = nXr[i+fst+N/2];
            double temp_im_iN2 = nXi[i+fst+N/2];
            // Calculation temp
            double temp1 = cos(-2*pi*i/N)*temp_re_iN2 - sin(-2*pi*i/N)*temp_im_iN2;
            double temp2 = cos(-2*pi*i/N)*temp_im_iN2 + sin(-2*pi*i/N)*temp_re_iN2;
            // X_k <- t + exp(-2*pi*i*k/N) X_(k+N/2)
            nXr[i+fst] = temp_re + temp1;
            nXi[i+fst] = temp_im + temp2;
            // X_(k+N/2) <- t - exp(-2*pi*i*k/N) X_(k+N/2)
            nXr[i+fst+N/2] = temp_re - temp1;
            nXi[i+fst+N/2] = temp_im - temp2;
        }
    }
}