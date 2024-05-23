/*
 * fft.h
 *
 *  Created on: Feb 19, 2024
 *      Author: Admin
 */

#ifndef INC_FFT_H_
#define INC_FFT_H_

#include "main.h"

void FFT_Init(uint16_t N);
void FFT_Compute(float fft_in[], float fft_out[]); // fft_out 2x wiekszy rozmiar
void FFT_Magnitude(float fft_in[], float fft_out[]);
void array_scale(float array[], uint16_t N, float scale_factor);
void FFT_MagnitudeDB(float fft_in[], float fft_out[]);

#endif /* INC_FFT_H_ */
