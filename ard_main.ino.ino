#include <stdint.h>
#include <myFFT.h>
#define mic_adc 1 // Pin # of the ADC
#define N 512    // Sampling point
#define Fs 3000 // Sampling Frequency

// global variables
double sound_wave[N], re[N], im[N], Xr[N], Xi[N];

void setup(){     
  Serial.begin(115200);
  analogReadResolution(10);
  // pinMode(pin_adc, INPUT);
}

// Sampling process
inline void Sampling(double *sw, double *re, double *im){
  double gap_time = (1000000.0 / Fs);
  int start_time = micros();
  for (int i = 0; i < N; i++){
    while (micros() - start_time < gap_time);
    sw[i] = analogRead(mic_adc);
    // sw[i] = sin(2*3.141592654*50*i/Fs);
    start_time = micros();
  }
  for (int i = 0; i < N; i++){
    re[i] = sw[i];
    im[i] = 0;
  }
}

// Post-processing
inline double postProcessing(double Xr[], double Xi[], double preMax){
  double maxk = -1.0;
  double maxvalue = -1;
  for (int i = N/2; i < N; i++){
    double nowFre = abs((i-N)*Fs*1.0/N);
    double temp = sqrt(Xr[i]*Xr[i] + Xi[i]*Xi[i]);
    // Serial.println(temp);
    if (temp > maxvalue){
      maxk = nowFre;
      maxvalue = temp;
    }
  }
  return maxk;
}

void loop(){
  double preMax = -100.0;
  while (1){
    // Sampling
    Sampling(sound_wave, re, im);
    // FFT
    myFFT2(Xr, Xi, 0, re, im, N, 0, 1);
    // Post-processing
    preMax = postProcessing(Xr, Xi, preMax);
    Serial.println(preMax);
  }
}


