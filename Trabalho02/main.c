/* 
 * Título: COMPRESSÃO DE ÁUDIO
 * Nome: Gustavo Siqueira Barbosa
 * NºUSP: 10728122
 * Código do curso: SCC0201
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include "./func.h"

#define READLINE_BUFFER 4096
char *readline(FILE *stream) {
    char *string = 0;
    int pos = 0; 

	do{

        if (pos % READLINE_BUFFER == 0) 
            string = (char *) realloc(string, (pos / READLINE_BUFFER + 1) * READLINE_BUFFER);

        string[pos] = (char) fgetc(stream);
    }while(string[pos++] != '\n' && string[pos-1] != '\r' && !feof(stream));

    string[pos-1] = 0;
    string = (char *) realloc(string, pos);

    return string;
}

int main(int argc, char *argv[]){
    
    char *wav_filename = readline(stdin);

    int n_coef; //número T de coeficientes
    scanf(" %d",&n_coef);

    //Lendo os dados do arquivo wav
    int data_size=0;
    unsigned char *wav_data = read_wav_data(wav_filename, &data_size);

    //aplicando a transformada de Fourier, ordenando e zerando valores
    CoefData *v_coef = DFT(wav_data, data_size);

    mergeSortMagnitude(v_coef, 0, data_size-1);
    for (int i=0; i < n_coef; i++){
        printf("%d\n",(int)v_coef[i].magnitude);
    }

    for (int i=n_coef; i < data_size; i++)
        v_coef[i].coef = 0;

    //reordenando valores pelo index e aplicando a reversa da Fourier
    mergeSortIndex(v_coef, 0, data_size-1);
    unsigned char *audio = DFT_inverse(v_coef, data_size);


    //escrevendo o novo arquivo de áudio
    FILE* fp = fopen(wav_filename, "rb");
    unsigned char buffer[40];
    fread(&buffer, sizeof(unsigned char), 40, fp);
    
    FILE *f_audio = fopen("new_audio.wav", "wb");
    fwrite(&buffer, sizeof(unsigned char), 40, f_audio);

    int i=data_size-1;
    while(i >= 0){
        fwrite(&audio[i--], sizeof(unsigned char), 1, f_audio);
    }


    //liberando memória
    free(wav_filename);
    free(wav_data);
    free(v_coef);
    free(audio);
    fclose(fp);
    fclose(f_audio);

    return 0;
}
