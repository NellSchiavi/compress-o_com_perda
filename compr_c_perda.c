#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Função que quantiza um valor 
int quantize(float value, int levels) {
    int q = (int)(value * (levels - 1) + 0.5f);
    return q;
}

// Função para reconstruir um valor quantizado (descompressão)
float dequantize(int q_value, int levels) {
    return (float)q_value / (levels - 1);
}

int main() {
    // entrada de dados exemplos
    float input_data[] = {0.12f, 0.47f, 0.33f, 0.81f, 0.95f, 0.50f, 0.20f, 0.88f};
    int length = sizeof(input_data) / sizeof(input_data[0]);

    int levels = 8;  // nível de quantização (quanto menor, maior a perda)

    int quantized_data[length];
    float reconstructed_data[length];

    // Bits necessários por valor
    int bits_per_value = (int)ceil(log2(levels));
    int original_bits_per_value = 32;  

    // cabeçario da saida
    printf("Original\tQuantized\tReconstructed\n");
    for (int i = 0; i < length; i++) {
        quantized_data[i] = quantize(input_data[i], levels);
        reconstructed_data[i] = dequantize(quantized_data[i], levels);

        printf("%.4f\t\t%d\t\t%.4f\n", input_data[i], quantized_data[i], reconstructed_data[i]);
    }

    // Estatísticas para compressão
    int original_total_bits = length * original_bits_per_value;
    int compressed_total_bits = length * bits_per_value;

    float compression_ratio = (float)compressed_total_bits / original_total_bits;

    printf("\nOriginal size: %d bits\n", original_total_bits);
    printf("Compressed size: %d bits\n", compressed_total_bits);
    printf("Compression ratio: %.2f%% of original size\n", compression_ratio * 100);

    return 0;
}
