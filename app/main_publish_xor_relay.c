#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Para rand()
#include "pico/stdlib.h"
#include "wifi_control.h"
#include "mqtt_comm.h"
#include "write_display.h"
#include "criptografias.h"
#include <time.h>

int main() {

    stdio_init_all();

    init_display();
    clear_display();
    char *text[] = {"Conectando wi-fi"};
    write_string(text, 15, 32, 1);
    show_display();

    // Inicializa gerador de números aleatórios
    srand(time_us_64());

    // Credenciais da rede Wi-Fi
    const char *ssid = "NetCasa";
    const char *password = "982822588";

    // Informações do MQTT
    const char *client_id = "Rasp_1";
    const char *broker_ip = "192.168.1.114";
    const char *client_user = "rasp";
    const char *password2 = "1234";

    // Mensagem temporária
    char mensagem[10];  // Buffer para armazenar número como string

    // Mensagem de inicialização
    for (int i = 0; i < 10; i++) {
        printf("Iniciando o sistema, tentativa %d...\n", i + 1);
        sleep_ms(1000);
    }

    // Conectar no Wi-Fi
    printf("Iniciando conexão Wi-Fi...\n");
    connect_to_wifi(ssid, password);

    clear_display();
    char *text2[] = {"Conectando MQTT"};
    write_string(text2, 10, 32, 1);
    show_display();

    // Conectar no broker MQTT
    printf("Iniciando conexão MQTT...\n");
    mqtt_setup(client_id, broker_ip, client_user, password2);
    //mqtt_setup(client_id, broker_ip, NULL, NULL);
    uint8_t criptografada[16];

    // Loop de publicação
#include <time.h>  // Importante para usar time()

while (true) 
{
    clear_display();
    char *text[] = {"Enviando:"};
    write_string(text, 1, 2, 1);

    float random_message = 26.5f; // Número aleatório de 0 a 50

    char buffer[128];  // Buffer para a mensagem JSON
    
    int timer = time_us_32()/(1e6); // Tempo atual em segundos

    if (timer > 40 && timer <50){
        timer = 20;
    }
    //sprintf(buffer,"%.1f", random_message,timer);
    sprintf(buffer, "{\"valor\":%.1f,\"ts\":%lu}", random_message,timer);

    char *mensagem_dois[] = {buffer};

    //write_string(mensagem_dois,40,32, 2);
    write_string(mensagem_dois,0,32, 1);
    printf("Publicando mensagem: %s\n", buffer);
    show_display();

    // Criptografa
    xor_encrypt_decrypt((uint8_t *)buffer, criptografada, strlen(buffer), 42);

    // Publica no MQTT
    mqtt_comm_publish("escola/sala1/temperatura",(uint8_t *)criptografada, strlen(buffer));

    sleep_ms(1000); // Espera 1 segundo para a próxima publicação
}


    return 0;
}
