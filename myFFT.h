// DFT
void myDFT(double* re, double* im, int N, int Fs);

// FFT Cooley-Turkey with array pointer
void myFFT(double* nXr, double* nXi, double real[], double imag[], int N, int h, int sam_gap);
// FFT Cooley-Turkey w/o creating new arrays
void myFFT2(double* nXr, double* nXi, int fst, double real[], double imag[], int N, int h, int sam_gap);