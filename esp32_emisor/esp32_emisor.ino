#include <WiFi.h>
#include <WebServer.h>
#include "credenciales.h"
const char* ssid = SECRET_SSID;
const char* password = SECRET_PASS;

WebServer server(80);

// Pines físicos
const int pinSalidaArduino = 26;
const int ledInterno = 2;

// Todo el código HTML, CSS y JS guardado en la memoria del ESP32
const char pagina_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="es">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Control de Riego</title>
    <style>
        body {
            font-family: system-ui, -apple-system, sans-serif;
            display: flex;
            flex-direction: column;
            align-items: center;
            justify-content: center;
            height: 100vh;
            margin: 0;
            background-color: #f4f4f9;
        }
        .container {
            background: white;
            padding: 2rem;
            border-radius: 12px;
            box-shadow: 0 4px 6px rgba(0,0,0,0.1);
            text-align: center;
            width: 80%;
            max-width: 350px;
        }
        h1 { margin-top: 0; color: #333; }
        .estado {
            font-size: 1.2rem;
            margin-bottom: 2rem;
            font-weight: bold;
            color: #666;
        }
        .btn {
            display: block;
            width: 100%;
            padding: 1rem;
            margin: 0.5rem 0;
            font-size: 1.2rem;
            color: white;
            border: none;
            border-radius: 8px;
            cursor: pointer;
            transition: opacity 0.2s;
        }
        .btn:active { opacity: 0.8; }
        .btn-on { background-color: #10b981; }
        .btn-off { background-color: #ef4444; }
    </style>
</head>
<body>
    <div class="container">
        <h1>Sistema de Riego</h1>
        <div class="estado" id="status-text">Estado: Esperando...</div>
        
        <button class="btn btn-on" onclick="enviarComando('on')">Encender Válvula</button>
        <button class="btn btn-off" onclick="enviarComando('off')">Apagar Válvula</button>
    </div>

    <script>
        async function enviarComando(accion) {
            const statusText = document.getElementById('status-text');
            statusText.innerText = "Enviando comando...";
            try {
                // Al estar alojado en el ESP32, usamos rutas relativas
                const response = await fetch(`/api/${accion}`);
                if (!response.ok) throw new Error("Error en el ESP32");
                
                const data = await response.json();
                
                if (data.estado === "ON") {
                    statusText.innerText = "Estado: Válvula ABIERTA 💧";
                    statusText.style.color = "#10b981";
                } else {
                    statusText.innerText = "Estado: Válvula CERRADA 🛑";
                    statusText.style.color = "#ef4444";
                }
            } catch (error) {
                console.error(error);
                statusText.innerText = "Estado: Error de conexión ⚠️";
                statusText.style.color = "#f59e0b";
            }
        }
    </script>
</body>
</html>
)rawliteral";

void setup() {
  Serial.begin(115200);
  
  pinMode(pinSalidaArduino, OUTPUT);
  pinMode(ledInterno, OUTPUT);
  
  // Estado inicial seguro
  digitalWrite(pinSalidaArduino, LOW);
  digitalWrite(ledInterno, LOW);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Conexión exitosa.");
  Serial.print("Ingresá esta IP en tu navegador: ");
  Serial.println(WiFi.localIP());

  // Endpoint que sirve la página web al entrar a la IP
  server.on("/", HTTP_GET, []() {
    server.send(200, "text/html", pagina_html);
  });

  // Endpoints de control
  server.on("/api/on", HTTP_GET, []() {
    digitalWrite(pinSalidaArduino, HIGH);
    digitalWrite(ledInterno, HIGH);
    server.send(200, "application/json", "{\"estado\": \"ON\"}");
    Serial.println("Comando: ON");
  });

  server.on("/api/off", HTTP_GET, []() {
    digitalWrite(pinSalidaArduino, LOW);
    digitalWrite(ledInterno, LOW);
    server.send(200, "application/json", "{\"estado\": \"OFF\"}");
    Serial.println("Comando: OFF");
  });

  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}