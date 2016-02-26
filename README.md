# ardFFT

This is a readable FFT code with simple comments. Everyone with C knowledge should be able to read it and modify it.

The code is run on Arduino Due. 

## Usage
`myFFT(Xr, Xi, re, im, N, 0, 1)`

or 

`myFFT2(Xr, Xi, 0, re, im, N, 0, 1)`

where `Xr` and `Xi` store the real and imagine parts of the frequency, and `re` and `im` are the time signal. Usually `im` are set to be zero. `N` is the number of samples.

More information can be found in the comments.
