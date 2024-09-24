
# 💧 Aqua - Sistema de Monitoramento Inteligente de Aquários 🐠

<div style="text-align: center;">
  <img src="img/Futuristic aquarium (kinguios).webp" alt="Aquarium Banner" width="70%"/>
</div>

O **Aqua** é um projeto open-source de automação e monitoramento de aquários, desenvolvido para manter o ambiente aquático seguro e estável para seus habitantes. Utilizando um microcontrolador **ESP8266** *(NodeMCU)*, sensores de temperatura, display OLED e conectividade Wi-Fi, o sistema permite o controle automatizado do aquecedor e a exibição de dados relevantes, garantindo o conforto dos peixes e o controle em tempo real das condições do aquário.

## 🔎 Visão Geral
Com a evolução das tecnologias de IoT, o Aqua aproveita a flexibilidade do ESP8266 para monitorar e controlar remotamente o aquário, evitando a sobrecarga do aquecedor e garantindo que o ambiente aquático se mantenha dentro dos parâmetros ideais de temperatura. O sistema não apenas desliga automaticamente o aquecedor quando necessário, como também garante que, após qualquer interrupção de energia ou reinício, o sistema retorne a um estado seguro.

## ✨ Funcionalidades Principais

- **Monitoramento da temperatura** em tempo real com o sensor **DS18B20**.
- **Controle automático do aquecedor** usando um relé, desligando-o em caso de falha.
- **Display OLED** exibe a temperatura e o tempo de uso do aquecedor.
- **Conectividade Wi-Fi** para futuras expansões de monitoramento remoto.
- **Atualizações Over-the-Air (OTA)** para atualizações sem necessidade de conexão física.
- **Sistema de arquivos LittleFS** para armazenamento de configurações e dados.

---

## 🔧 Arquitetura do Sistema

### Componentes Utilizados

- **NodeMCU ESP8266**: Microcontrolador principal do sistema.
- **Sensor DS18B20**: Responsável por medir a temperatura da água.
- **Módulo Relé**: Liga e desliga o aquecedor com base na temperatura.
- **Display OLED SSD1306**: Exibe informações como temperatura e tempo de funcionamento.

### Estrutura de Arquivos

**`main.ino`**

 Arquivo principal que organiza o ciclo do sistema, chamando funções que lidam com:

- Leitura do sensor de temperatura.
- Controle do relé.
- Atualização de dados no display.
- Integração com o Wi-Fi e servidor web.

**`display.h/.cpp`**

- Gerencia a exibição de dados no display OLED SSD1306, incluindo a temperatura atual e o tempo de operação do aquecedor quando este estiver ativo.

**`sensor.h /.cpp`**

- Lida com a leitura do sensor DS18B20 de forma eficiente, utilizando a biblioteca DallasTemperature para obter leituras confiáveis.

**`heaterControl.h/.cpp`**

- Controla o aquecedor através de relés, garantindo a segurança e a operação correta com base na leitura do sensor de temperatura.

**`rede.h/.cpp`**

- Configurações e controle da rede Wi-Fi.

---

## 📦 Plataformas e Ferramentas

Este projeto foi desenvolvido com o **[PlatformIO](https://platformio.org/)**, utilizando o microcontrolador **ESP8266 (NodeMCU)** e o sistema de arquivos **[LittleFS](https://arduino-esp8266.readthedocs.io/en/latest/filesystem.html)**.

---

## 📚 Bibliotecas Utilizadas

### Conectividade

- **[ESP8266WiFi](https://github.com/esp8266/Arduino/tree/master/libraries/ESP8266WiFi)**: Gerencia a conectividade Wi-Fi.
- **[WiFiManager](https://github.com/tzapu/WiFiManager)**: Facilita a configuração da rede Wi-Fi.

### Sensores e Controle

- **[DallasTemperature](https://github.com/milesburton/Arduino-Temperature-Control-Library)**: Manipula o sensor de temperatura DS18B20.
- **[Bounce2](https://github.com/thomasfredericks/Bounce2)**: Debounce para botões físicos.
- **[Adafruit GFX](https://github.com/adafruit/Adafruit-GFX-Library)** e **[SSD1306](https://github.com/adafruit/Adafruit_SSD1306)**: Para o controle e exibição no display OLED.

### Sistema e Atualização

- **[ArduinoOTA](https://github.com/esp8266/Arduino/tree/master/libraries/ArduinoOTA)**: Permite atualizações de firmware via OTA.
- **[LittleFS](https://github.com/earlephilhower/LittleFS)**: Sistema de arquivos usado para armazenar dados e configurações.

---

## 🚀 Como Instalar e Configurar

1. **Clone o projeto:**
   ```bash
   git clone https://github.com/Nerd-Programador/Aqua.git
   ```

2. **Instale as bibliotecas necessárias:**
   ```bash
   pio lib install
   ```

3. **Carregue o código no ESP8266:**
   ```bash
   pio run --target upload
   ```

4. **Configure as credenciais Wi-Fi (se necessário):**
   ```cpp
   #define SSID "Nome_Rede"
   #define PASSWORD "Senha_Rede"
   ```

---

## 📊 Esquema de Conexão do Hardware

### Aqui está o esquema básico de conexão dos componentes:

- DS18B20 conectado ao GPIO D5 do ESP8266.
- Relé conectado ao GPIO D1 para controle do aquecedor.
- Display OLED SSD1306 conectado via I2C (SDA -> D2, SCL -> D1).

---

## 👨‍💻 Como Usar

1. Após a instalação e configuração, o ESP8266 se conectará à sua rede Wi-Fi.

2. A temperatura da água será monitorada constantemente, e o aquecedor será ligado/desligado de acordo com os limites definidos no código.

3. Você pode acessar o sistema pelo navegador, utilizando o endereço IP do ESP8266 para visualizar os dados ou realizar ajustes.

4. O display OLED mostrará as leituras da temperatura e a situação do aquecedor.


## ⚠️ Problemas Conhecidos

Este projeto ainda está em desenvolvimento, e as seguintes questões são conhecidas:

- **Aquecedor preso em "ligado" após reinicialização**: Quando o sistema é reiniciado, o relé do aquecedor pode ficar preso na posição 'On', sendo necessário desligar manualmente em alguns casos.
- **Oscilações de cor nos LEDs**: Algumas oscilações aleatórias ocorrem durante a execução de efeitos de iluminação com os LEDs, possivelmente devido à interferência ou fonte de alimentação.
- **Falha na comunicação do sistema com o site**: Algumas funcionalidades disponíveis no site <u>*Aquario.local*</u> não estão enviando ou recebendo dados corretamente, o que impede o controle remoto em tempo real.

---

## 🚀 Implementações Futuras

Estamos planejando as seguintes melhorias e novas funcionalidades para corrigir os problemas atuais e expandir as capacidades do sistema:

- **Reconexão Wi-Fi automática e mais confiável**: Desenvolver um sistema robusto para reconexão automática após queda de energia ou perda de sinal.
- **Correção do site *Aquario.local***: Implementar uma solução para garantir que todas as funcionalidades do site comuniquem-se corretamente com o sistema, facilitando o monitoramento e controle remoto.
- **Estabilização das cores dos LEDs**: Trabalhar na melhoria do controle de cores para evitar oscilações e garantir transições suaves nos efeitos de iluminação.
- **Monitoramento via aplicativo móvel**: Desenvolver uma aplicação mobile que permita controlar o aquecedor, monitorar a temperatura e receber notificações diretamente no celular.
- **Suporte a mais sensores**: Adicionar compatibilidade para sensores de pH, TDS, e outros parâmetros da água do aquário para monitoramento mais abrangente.
<span style="color: cyan;">
   - Modelo: PH-4502C
   - Modelo: DFRobot-SEN0244
</span>

---

## 🔧 Funcionalidades em Desenvolvimento

Estamos atualmente trabalhando nas seguintes funcionalidades para melhorar o projeto:

- **Melhoria no comportamento do relé do aquecedor**: Implementar um sistema de fail-safe para garantir que o aquecedor desligue corretamente após reinicializações inesperadas.
- **Correção do problema de oscilação nos LEDs**: Investigar e corrigir as oscilações aleatórias, possivelmente otimizando a alimentação e o código de controle de efeitos.
- **Otimização da comunicação do site**: Trabalhar na sincronização correta entre o site e o sistema para garantir a troca confiável de dados em tempo real.
- **Sistema de configuração Wi-Fi via portal**: Melhorar a interface de configuração via WiFiManager para tornar o processo de conectar o dispositivo à rede mais ágil e confiável.
- **Persistência de configurações**: Implementar o uso de **LittleFS** para salvar as configurações do usuário (como temperatura alvo e status do sistema), mesmo após reinicializações.

Se você encontrar outros problemas ou tiver sugestões para melhorias, sinta-se à vontade para [abrir um issue](https://github.com/Nerd-Programador/Aqua/issues). Estamos sempre buscando maneiras de tornar o sistema mais confiável e eficiente!

---

## 👥 Contribuições

Contribuições são bem-vindas! Siga os passos abaixo para colaborar:

1. Faça um **fork** do repositório.
2. Crie uma **branch** para suas alterações:
   ```bash
   git checkout -b minha-branch
   ```
3. Envie as alterações:
   ```bash
   git push origin minha-branch
   ```
4. Abra um **Pull Request**.

---

## 📜 Licença

Este projeto está licenciado sob a [Licença MIT](LICENSE), o que significa que você pode utilizá-lo livremente para fins pessoais e comerciais, desde que mantenha a atribuição original.

---

## 🌐 Referências

- [Documentação do ESP8266](https://www.espressif.com/en/products/socs/esp8266)
- [Sensor DS18B20](https://www.maximintegrated.com/en/products/sensors/DS18B20.html)
- [Tutoriais da Adafruit](https://learn.adafruit.com/)
