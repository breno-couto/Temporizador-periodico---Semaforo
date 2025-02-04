#include <stdio.h>
#include "pico/stdlib.h" // Biblioteca padrão para funcionalidades básicas como GPIO, temporização e E/S.
#include "pico/time.h"   // Biblioteca para gerenciamento de tempo, como manipulação de temporizadores e atrasos.

#define LED_PIN_RED 11  // Pino do LED vermelho
#define LED_PIN_YELLOW 12  // Pino do LED amarelo
#define LED_PIN_GREEN 13  // Pino do LED verde

int estado = 0; // Estado do semáforo

void mudar_semaforo() {
    // Desliga todos os LEDs
    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_YELLOW, 0);
    gpio_put(LED_PIN_GREEN, 0);

    // Alterna entre os estados do semáforo
    if (estado == 0) {
        gpio_put(LED_PIN_RED, 1);  // Liga o vermelho
    } else if (estado == 1) {
        gpio_put(LED_PIN_YELLOW, 1);  // Liga o amarelo
    } else if (estado == 2) {
        gpio_put(LED_PIN_GREEN, 1);  // Liga o verde
    }

    estado = (estado + 1) % 3;  // Alterna entre 0, 1 e 2
}

int main() {
    stdio_init_all(); // Inicializa a comunicação serial

    // Inicializar os pinos GPIO
    gpio_init(LED_PIN_RED);
    gpio_set_dair(LED_PIN_RED, GPIO_OUT);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, GPIO_OUT);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);

    // Define um intervalo de tempo em milissegundos
    uint32_t interval = 3000;

    absolute_time_t next_wake_time = delayed_by_us(get_absolute_time(), interval * 1000);

    while (true) {
        if (time_reached(next_wake_time)) {
            printf("Mudando o semáforo\n");
            mudar_semaforo();
            next_wake_time = delayed_by_us(next_wake_time, interval * 1000);
        }
        sleep_ms(1);
    }
}
