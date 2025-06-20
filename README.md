[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-22041afd0340ce965d47ae6ef1cefeee28c7c493a6346c4f15d667ab976d596c.svg)](https://classroom.github.com/a/G8V_0Zaq)

# Tarefa: IoT Security Lab - EmbarcaTech 2025

Autor: **Guilherme Achilles de Oliveira e Aguiar**

Curso: Residência Tecnológica em Sistemas Embarcados

Instituição: EmbarcaTech - HBr

Brasília, 04/06 de 2025

---


## 🎯 Visão Geral

Este projeto demonstra a implementação de um sistema IoT completo usando BitDogLab (Raspberry Pi Pico W), abrangendo desde conectividade básica Wi-Fi até implementação de segurança com criptografia e proteção contra ataques de replay.


## 🚀 Implementação

### Etapa 1: Conectividade Wi-Fi

**Arquivo:** `connections/wifi_control.c`

**Biblioteca:** `pico_cyw43_arch_lwip_threadsafe_background`

**Include principal:** `#include "pico/cyw43_arch.h"`

#### Funcionamento
A função de conexão Wi-Fi é executada no loop principal, recebendo:
- **SSID:** Nome da rede Wi-Fi
- **Senha:** Senha da rede

A implementação gerencia a inicialização do módulo Wi-Fi da Pico W e realiza conexão assíncrona e thread-safe.


<p align = "center">
    <img src="assets/etapa_1.png"
     width="1080px">
</p>


---

### Etapa 2: Setup MQTT Básico

**Arquivo:** `connections/mqtt_comm.c`

**Bibliotecas:** 
- `pico_lwip_mqtt`
- `pico_cyw43_driver`

**Includes principais:**
```c
#include "lwip/apps/mqtt.h"      
#include "lwipopts.h"             
```

#### Configuração
O arquivo `lwipopts.h` foi adaptado dos exemplos da extensão Raspberry Pi Pico e modificado conforme documentação oficial.

---

### Etapa 3: Publicação MQTT sem Segurança

#### Funcionalidades
- Envio de mensagens para o broker MQTT
- Exibição de mensagens nos displays do publisher e subscriber

#### Configuração do Mosquitto
**Arquivo de configuração (.conf):**
- Porta: `1883`
- Configuração: `allow_anonymous true` (descomentada)

**Iniciando o broker:**
```bash
# Execute como administrador
mosquitto -v
```
<p align = "center">
    <img src="assets/etapa_3.png"
     width="1080px">
</p>

<p align = "center">
    <img src= "assets/etapa_3_2.png"
     width="1080px">
</p>

---

### Etapa 4: Autenticação no Mosquitto

#### Criação de Credenciais
```bash
# Criar arquivo de senhas
mosquitto_passwd -c nome_do_arquivo senha_do_arquivo
```

Este comando gera um arquivo contendo o ID do usuário e o hash da senha correspondente.

#### Segurança
- Remoção de acesso anônimo
- Implementação de autenticação baseada em credenciais
- Validação de usuários através de arquivo de senhas

<p align = "center">
    <img src= "assets/etapa_4.png"
   width="1080px">
</p>

<p align = "center">
    <img src= "assets/etapa_4_2.png"
     width="1080px">
</p>

---

### Etapa 5: Criptografia Leve (XOR)

**Arquivo:** `criptografias/`

#### Implementação
- Função de subscribe em `mqtt_comm.c`
- Implementação de criptografia XOR simétrica
- Mesma função para encriptação e decriptação

#### Funcionamento
1. Mensagem é criptografada antes do envio
2. Subscriber recebe e descriptografa a mensagem
3. Resultado exibido no display
4. Tráfego criptografado pode ser analisado via Wireshark

<p align = "center">
    <img src="assets/etapa_5.png"
     width="1080px">
</p>

---

### Etapa 6: Proteção contra Replay Attack

#### Implementação de Timestamp
- Utilização da função `timer_us_32()` para timestamp
- Medição em milissegundos desde inicialização do processador
- Inclusão do timestamp na mensagem criptografada

#### Detecção de Replay
- Processamento de timestamp na função subscribe
- Validação temporal das mensagens
- Exibição de "Replay detectado" em caso de ataque identificado
-  O video da detecção de relays esta disponivel logo abaixo.

<p align = "center">
    <img src= "assets/ETAPA_6.png"
   width="1080px">
</p>


https://github.com/user-attachments/assets/1d9ac055-25f1-45e4-bd8a-39ef659f027b

### Quais técnicas sao escalaveis e podem ser colocadas em um ambiente escolar ?

A criptografia XOR nao é escalavel, pois elas pode ser facilmente quebradas e não suporta autenticação, integridade ou proteção contra ataques sofisticados, tornando-se inviáveis em aplicações reais, mesmo em ambientes escolares, além de não se adaptar bem quando o número de dispositivos cresce. 

As teécnicas escalaveis são:

- HMAC que permite verificar a integridade e autenticidade das mensagens de forma leve;
- Proteção contra replay, feita com timestamps ou contadores, que impede que mensagens antigas sejam reutilizadas por atacantes;
- criptografia AES, que protege os dados transmitidos de forma eficiente e segura.

Todas essas técnicas são escaláveis, pois funcionam bem com poucos ou muitos dispositivos, mantendo a segurança sem exigir grandes recursos.

---

## 📜 Licença
GNU GPL-3.0.
