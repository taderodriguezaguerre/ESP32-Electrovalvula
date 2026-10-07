# Sistema de Riego Automatizado - V1 💧

Este proyecto es la primera versión de un sistema de riego inteligente controlado por WiFi de forma local. Permite accionar una electroválvula profesional de 24V a través de una interfaz web sencilla alojada directamente en el microcontrolador.

🛠️ Arquitectura del Hardware

El sistema utiliza una arquitectura de doble placa para aislar la lógica web de la etapa de potencia y adaptar los voltajes de manera segura:

ESP32 (Cerebro y Servidor): Se conecta a la red WiFi local y aloja la página web. Envía señales lógicas de 3.3V.

Arduino Mega (Intermediario): Recibe la señal del ESP32 y actúa como adaptador de nivel lógico (3.3V a 5V) para accionar el módulo de relé de forma estable.

Módulo Relé 5V (Activo en BAJO): Conmuta la corriente alterna de la etapa de potencia.

Electroválvula Hunter PGV-100 (1" con Solenoide): Controla el flujo de agua. Opera con 24V AC.

Transformador 24V AC: Alimenta el solenoide de la válvula a través del relé.

Nota de plomería: Las conexiones físicas de agua (manguera a acople y acople a válvula) están selladas con Fastix para evitar fugas bajo presión.

✨ Características (V1)

Control Remoto Local: Interfaz web accesible desde cualquier dispositivo conectado a la misma red WiFi.

Servidor Web Embebido: El código HTML, CSS y JS está alojado en la memoria PROGMEM del ESP32.

Acción Manual: Botones de Encendido (ON) y Apagado (OFF) con respuesta visual del estado actual.

🚀 Uso

Cargar el código en el ESP32 ingresando las credenciales de la red WiFi local.

Cargar el código receptor en el Arduino Mega.

Conectar los componentes (GPIO 26 del ESP32 al Pin 2 del Arduino; Pin 3 del Arduino al IN del Relé; masas unificadas).

Abrir el Monitor Serie del ESP32 para obtener la dirección IP local asignada.

Ingresar la IP en un navegador web y controlar el riego.
