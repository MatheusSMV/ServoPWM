#include <stdio.h> //Biblioteca de entrada e saída padrão em C.
#include "pico/stdlib.h" //Biblioteca padrão para o SDK.
#include "hardware/pwm.h" //Biblioteca que permite o controle do PWM.
#include "hardware/timer.h" //Biblioteca para trabalhar com temporizador e interrupção.

#define servo 22 //Definindo o a gpio do servo motor.

const uint16_t wrap = 40000; //Pelos cálculos o wrap tem que ser de 40000 para garantir a frquência de PWM do 50 Hz. 
//Importante lembrar tentou-se com 4000 e não conseguiu o processo total de movimento do servo motor.
const float divisor_pwm = 62.5; //Com wrap de 40000 e o dividor e frequência de 50 Hz tem-se o dividor de pwm de 62.5 aproximadamente lembrar (40001)

//Constante definidas pela própio documento da atividade Professor Ricardo
const uint16_t pulso_minimo = 500; //500µs o servo estará em 0 graus.
const uint16_t pulso_medio = 1470;  //1.470µs o servo estará em 90 graus.
const uint16_t pulso_maximo = 2400; //2.400µs o servo estará em 180 graus.
//Importante lembrar o servo começa já em 90 graus então estamos falando em termos rotacionais e não posição fixa.
const uint16_t incremento = 5; //O incremento de  ±5µs conforme o aconselhado na atividade.
const uint16_t delay = 10;  //Atraso de 10ms sujerido na atividade
//Lembrando ambas as variáveis são definidas de maneira igual, quem faz o processo de decidir a unidade são as funções que trabalham com elas.

volatile uint16_t pulso_atual = pulso_minimo; //Define o pulso atual como o pulso mínimo.
//Volatile porque é uma variável que se modifica constantemente, importante para não bugar o compilador.
volatile bool incrementando = true; //A variável condicional do if que permitira o incremento para fazer o servo percorrer o caminho desejado.

//Função para configurar o PWM.
void pwm_setup() {
    gpio_set_function(servo, GPIO_FUNC_PWM); //Obtemos o pino.
    uint slice = pwm_gpio_to_slice_num(servo); //Determinamos o canal do PWM.

    pwm_set_clkdiv(slice, divisor_pwm); //Definimos o divisor de clock do PWM, definido acima.
    pwm_set_wrap(slice, wrap); //Definimos o Wrap, isso é o valor máximo do contador do PWM.
    pwm_set_enabled(slice, true); //Ativa o PWM para o nosso slice, no nosso Pino GPIO.
}

//Função para definir o ciclo ativo do PWM -- Período em que o sinal está em nível alto.
void largura_pulso(uint16_t pulso) {
    uint16_t level = (pulso * wrap) / 20000; //Estamos aqui calculando o nível do PWM que será enviado ao pino GPIO.
    pwm_set_gpio_level(servo, level); //A variável pulso será sempre atualizada recendo o pulso atual. //20000µs equivale a 20ms.
}

//Função de interrupção chamada a cada 10ms.
bool timer_callback(struct repeating_timer *t) {
    //Ajusta o pulso do servo com base no incremento.
    largura_pulso(pulso_atual); //Recebe o valor do pulso atual.

    // Atualiza o valor do pulso
    if (incrementando) { //Se incrementando for igual a true.
        pulso_atual += incremento; //incrementando 5µs.
        if (pulso_atual >= pulso_maximo) { //Se o pulso atual for igual ao máximo.
            incrementando = false; //Faço incrementando igual a false.
        }//Logo pode-se prosseguir o loop.
    } else {
        pulso_atual -= incremento; //Estou decrementando 5µs.
        if (pulso_atual <= pulso_minimo) { //Se o pulso atual for igual ao mínimo.
            incrementando = true; //Faço incrementando igual ao true e volto ao loop.
        }
    }

    return true;  //Retorna true para continuar com o temporizador.
}

int main() {
    stdio_init_all(); //Incializando a função padrão de entrada e saída.

    pwm_setup(); //Incializando o nosso PWM.

    largura_pulso(pulso_maximo); //Eu quero que ele vá até a posição de 270 graus ou seja rotacione 180 graus. -- Valores da tarefa.
    sleep_ms(5000); //Espero os 5 segundos como o requisitado.

    largura_pulso(pulso_medio); //Eu quero que ele vá até a posição de 0 graus ou seja rotacione 90 graus para trás. -- Valores da tarefa.
    sleep_ms(5000); //Espero os 5 segundos como o requisitado.

    largura_pulso(pulso_minimo); //Eu quero que ele volte a posição original em 90 graus, logo requesito que ele volte novamente 90 graus. -- Valore da tarefa.
    sleep_ms(5000);//Esperos os 5 segundos como o requisitado.

    //Configura o temporizador para chamar a função timer_callback a cada 10 ms.
    struct repeating_timer timer;
    add_repeating_timer_ms(delay, timer_callback, NULL, &timer); //Chamo a nossa estrutura de interrupção em ms.

    while (true) {

        //Loop livre :).

    }

    return 0;
}
