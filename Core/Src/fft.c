#include "fft.h"
#include <complex.h>
#include <math.h>
#include "main.h"

#define FFT_MAX_LENGTH  4096

static uint16_t FFT_LENGTH, FFT_BIT_LENGTH;
static complex float W[FFT_MAX_LENGTH] = {0};

void FFT_Init(uint16_t N)
{
    FFT_LENGTH = N;
    FFT_BIT_LENGTH = log2(FFT_LENGTH);

    W[0] = 1;
    for (uint16_t i = 1; i < FFT_LENGTH; i++) {
    	if (i == FFT_LENGTH/2)
    		W[i] = -1;
    	else
    		W[i] = cos((2 * M_PI * i) / FFT_LENGTH) - I*sin((2 * M_PI * i) / FFT_LENGTH);
    }
}

static uint16_t bit_reverse(uint16_t x)
{
    uint16_t bitp = FFT_BIT_LENGTH-1;
    uint16_t xr = 0;

    while (x) {
        xr |= ((x & 0x01) << bitp);
        x /= 2;
        bitp--;
    }

    return xr;
}

static void array_reverse(float array[])
{
    uint16_t j;
    float tmp;

    for (uint16_t i = 0; i < FFT_LENGTH; i++) {
        j = bit_reverse(i);
        if (i < j) {
            tmp = array[i];
            array[i] = array[j];
            array[j] = tmp;
        }
    }
}

void FFT_Compute(float fft_in[], float fft_out[])
{
    complex float fft_data[FFT_LENGTH];
    complex float fft_last_data[FFT_LENGTH];

    array_reverse(fft_in);

    for (uint16_t i = 0; i < FFT_LENGTH/2; i += 2) {
        fft_last_data[i] = fft_in[i+1] + fft_in[i];
        fft_last_data[i+1] = fft_in[i] - fft_in[i+1];

        fft_last_data[i+FFT_LENGTH/2] = fft_in[i+1+FFT_LENGTH/2] + fft_in[i+FFT_LENGTH/2];
        fft_last_data[i+1+FFT_LENGTH/2] = fft_in[i+FFT_LENGTH/2] - fft_in[i+1+FFT_LENGTH/2];
    }

    for (uint16_t i = 0; i < FFT_BIT_LENGTH-2; i++) {
        uint16_t stage_index = (1 << (i+1));
        int16_t index_offset_a, index_offset_b;
        uint16_t W_index = 0;
        uint16_t W_offset = FFT_LENGTH / (stage_index * 2);
        index_offset_a = 0;
        index_offset_b = stage_index;
        uint16_t counter = 0;

        for (uint16_t j = 0; j < FFT_LENGTH/2; j++) {
            fft_data[j] = fft_last_data[j + index_offset_a] + (W[W_index] * fft_last_data[j + index_offset_b]);
            fft_data[j + FFT_LENGTH/2] = fft_last_data[j + index_offset_a + FFT_LENGTH/2] + (W[W_index] * fft_last_data[j + index_offset_b + FFT_LENGTH/2]);

            counter++;
            if (counter == stage_index) {
                counter = 0;
                index_offset_a = (index_offset_a == 0 ? -stage_index : 0);
                index_offset_b = (index_offset_b == stage_index ? 0 : stage_index);
            }

            W_index = (W_index + W_offset) % FFT_LENGTH;
        }
        for (uint16_t j = 0; j < FFT_LENGTH; j++) fft_last_data[j] = fft_data[j];

    }


    for (uint16_t i = 0; i < FFT_LENGTH/2; i++) {
        fft_data[i] = fft_last_data[i] + (W[i] * fft_last_data[i + FFT_LENGTH/2]);
        fft_data[i + FFT_LENGTH/2] = fft_last_data[i] + (W[i + FFT_LENGTH/2] * fft_last_data[i + FFT_LENGTH/2]);
    }

    uint16_t i, j;
    for (i = 0, j = 0; i < FFT_LENGTH; i++, j += 2) {
        fft_out[j] = creal(fft_data[i]);
        fft_out[j + 1] = cimag(fft_data[i]);
    }
}

void FFT_Magnitude(float fft_in[], float fft_out[])
{
    uint16_t i, j;
    for (i = 0, j = 0; i < FFT_LENGTH; i++, j += 2)
        fft_out[i] = sqrt(fft_in[j]*fft_in[j] + fft_in[j+1]*fft_in[j+1]);
}

void FFT_MagnitudeDB(float fft_in[], float fft_out[])
{
	uint16_t i, j;
	for (i = 0, j = 0; i < FFT_LENGTH; i++, j += 2)
		fft_out[i] = 20 * log10(sqrt(fft_in[j]*fft_in[j] + fft_in[j+1]*fft_in[j+1]));
}

void array_scale(float array[], uint16_t N, float scale_factor)
{
	for (uint16_t i = 0; i < N; i++)
		array[i] *= scale_factor;
}
