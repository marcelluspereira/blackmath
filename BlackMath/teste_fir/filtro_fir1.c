//* Teste de filtro FIR
//
*/

filtro_FIR(fract16* entrada, int n_amost){
	
	do {
		//zera sa�da do filtro
	    y=0;

	    //l� dado do arquivo
		sample[0] = entrada;

	    //Convolu��o e acumula��o
	    for (n=0; n<NSAMPLES; n++){
	            y += coeficientes[n]*sample[n];
	            }

	    //desloca amostra
	    for (n=NSAMPLES-1; n>0; n--)
	            {
	            sample[n]=sample[n-1];
	            }

		saida = (short) y;

	    //escreve no arquivo de sa�da
	    fwrite(&saida,sizeof(short),1,out_file);

	 } while (n_amost);
	 
	 return;
}