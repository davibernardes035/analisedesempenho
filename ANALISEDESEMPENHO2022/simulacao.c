#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double aleatorio() {

	double u = rand() / ((double) RAND_MAX + 1);
	//limitando entre (0,1]
	u = 1.0 - u;

	return (u);

}

double minimo(double num1, double num2){
    if(num1 < num2)
        return num1;

    return num2;
}

double maximo(double num1, double num2){
    if(num1 > num2)
        return num1;

    return num2;
}

int main(){

    // printf("numero aleatorio: %lF\n", aleatorio());
    double tempo_simulacao;
    double tempo_decorrido = 0.0;

    double intervalo_medio_chegada;
    double tempo_medio_servico;

    double chegada, servico;

    double soma_tempo_servico = 0.0;

    unsigned long int fila = 0;
    unsigned long int max_fila = 0;

    
    srand(time(NULL));

    printf("informe o tempo de simulacao (segundos): ");
    scanf("%lF", &tempo_simulacao);

    printf("informe o intervalo entre chegadas (segundos): ");
    scanf("%lF", &intervalo_medio_chegada);
    
    printf("informe o tempo medio de servico (segundos): ");
    scanf("%lF", &tempo_medio_servico);

    double l = 1.0/intervalo_medio_chegada;

    // gerando o tempo de chegada da primeira requisicao
    chegada = (-1.0 / l) * log(aleatorio());

    while(tempo_decorrido <= tempo_simulacao){
        
        tempo_decorrido = !fila ? chegada : minimo(chegada, servico);

        // chegada

        if(tempo_decorrido == chegada){

            // printf("Chegada em: %lF\n", tempo_decorrido);
            if(!fila){

                servico = tempo_decorrido + (-1.0 / (1.0/tempo_medio_servico)) * log(aleatorio());
                soma_tempo_servico += servico - tempo_decorrido;

            }
            fila++;
            max_fila = fila > max_fila? fila : max_fila;
            chegada = tempo_decorrido + (-1.0 / (1.0/intervalo_medio_chegada)) * log(aleatorio());

        }else{ // saida
            


            fila--;

            if(fila){

                servico = tempo_decorrido + (-1.0 / (1.0/tempo_medio_servico)) * log(aleatorio());
                soma_tempo_servico += servico - tempo_decorrido;

            }

            // printf("Saida em: %lF\n", tempo_decorrido);

        }   

    }

    printf("Ocupacao: %lF\n", soma_tempo_servico/maximo(tempo_decorrido, servico));
    printf("Max_Fila: %ld\n", max_fila);
    printf("Fila: %ld\n", fila);



    return 0;

}
