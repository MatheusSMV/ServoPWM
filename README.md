# Controle de Servo Motor com PWM e Interrupções

Este projeto tem como objetivo controlar o movimento de um servo motor utilizando a placa Raspberry Pi Pico. O servo motor é movido de maneira suave entre os ângulos de 0° e 180°, após as posições iniciais (180°, 90° e 0°), com um ciclo de trabalho (Duty Cycle) ajustado a cada 10ms, utilizando interrupções para garantir precisão no controle.

## Funcionamento

O código configura a GPIO 22 da Raspberry Pi Pico para gerar um sinal PWM que controla o servo motor. A cada 10ms, o ciclo de trabalho do PWM é ajustado de forma incremental, permitindo que o servo se mova suavemente entre 0° e 180°. Quando o servo atinge a posição de 180°, ele começa a se mover de volta para 0°.

### Passos principais do funcionamento:

1. **Configuração do PWM**:
   - A frequência do PWM é configurada para 50Hz, com um intervalo de 20ms (periodo de 20ms).
   - O ciclo de trabalho (Duty Cycle) é controlado por um pulso de 400µs a 2500µs, representando as posições de 0° a 180° do servo.

2. **Incremento e Decremento do Pulso**:
   - A cada 10ms, o valor do pulso é ajustado de forma incremental (+5µs), o que faz o servo mover-se gradualmente.
   - Quando o pulso atinge o valor máximo (2500µs), ele começa a ser decrementado, movendo o servo de volta para a posição inicial (0°).

3. **Interrupções**:
   - O movimento é controlado por interrupções, o que permite um controle preciso e regular do servo sem consumir recursos excessivos da CPU.

## Arquivos

- Código principal que configura o PWM e a interrupção para controlar o servo motor.

## Requisitos

- Wokwi.

## Como Usar

1. Conecte o servo motor à GPIO 22 da Raspberry Pi Pico.
2. Compile o código e faça o upload para a Raspberry Pi Pico.
3. O servo motor começará a se mover de forma suave entre 0° e 180°, após as posições iniciais (180°, 90° e 0°).

## Autor

Matheus Santos Souza.

## Código Base

Professor Ricador Menezes Prates [GitHub](https://github.com/rmprates84/pwm_duty_cycle.git)

## Video

[VideoDeApresentacao](https://youtu.be/--G7rcpNSAM)



