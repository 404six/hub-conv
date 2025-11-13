/*
 * PROJETO DE EXTENSÃO: HUB DE CONVENIÊNCIA (Controle de Tomada)
 * Aluno: Lucas Morais
 * Disciplina: Programação de Microcontroladores
 * * Este código transforma um ESP32 em um servidor web. 
 * Ao se conectar ao Wi-Fi, ele cria uma página web com botões
 * para ligar e desligar um Módulo Relé conectado ao pino 4.
 */

#include <WiFi.h>
#include <WebServer.h>

// --- Configuração da Rede ---
// Coloque o nome e a senha da sua rede Wi-Fi
const char* ssid = "SEU_SSID";       // <<-- MUDE AQUI
const char* password = "SUA_SENHA";  // <<-- MUDE AQUI
// ----------------------------

// Pino onde o Módulo Relé está conectado
const int relayPin = 4;

// Variável para guardar o estado do relé (LIGADO/DESLIGADO)
bool relayState = false; // Começa desligado

// Cria o objeto do servidor na porta 80 (padrão web)
WebServer server(80);

/*
 * Função handleRoot()
 * Esta é a função chamada quando alguém acessa o IP do ESP32 (ex: 192.168.1.10)
 * Ela vai construir e enviar a página HTML para o navegador.
 */
void handleRoot() {
  String html = "<!DOCTYPE html><html><head><title>Hub de Conveniência</title>";
  
  // Estilo CSS para deixar os botões grandes e bonitos (para celular)
  html += "<meta name='viewport' content='width=device-width, initial-scale=1'>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; background-color: #f0f0f0; }";
  html += "h1 { color: #333; }";
  html += "p { font-size: 1.5rem; }";
  html += "a { text-decoration: none; }";
  html += ".btn { padding: 20px 40px; font-size: 1.2rem; border-radius: 10px; margin: 10px; border: none; cursor: pointer; }";
  html += ".btn-on { background-color: #4CAF50; color: white; }"; // Botão Ligar
  html += ".btn-off { background-color: #f44336; color: white; }"; // Botão Desligar
  html += "</style></head><body>";
  
  // Conteúdo da Página
  html += "<h1>🏠 Hub de Conveniência</h1>";
  html += "<h2>Controle do Ventilador</h2>";
  
  // Mostra o estado atual
  html += "<p>O ventilador está: <strong>";
  if (relayState == true) {
    html += "LIGADO";
  } else {
    html += "DESLIGADO";
  }
  html += "</strong></p>";
  
  // Botões de Ação
  html += "<a href='/ligar'><button class='btn btn-on'>LIGAR</button></a>";
  html += "<a href='/desligar'><button class='btn btn-off'>DESLIGAR</button></a>";
  
  html += "</body></html>";
  
  server.send(200, "text/html", html); // Envia a página pronta para o navegador
}

/*
 * Função handleLigar()
 * Chamada quando o usuário clica no link "/ligar"
 */
void handleLigar() {
  digitalWrite(relayPin, HIGH); // Aciona o relé (pode ser LOW dependendo do seu relé)
  relayState = true;
  server.sendHeader("Location", "/"); // Redireciona de volta para a página principal
  server.send(302, "text/plain", ""); 
}

/*
 * Função handleDesligar()
 * Chamada quando o usuário clica no link "/desligar"
 */
void handleDesligar() {
  digitalWrite(relayPin, LOW); // Desliga o relé (pode ser HIGH dependendo do seu relé)
  relayState = false;
  server.sendHeader("Location", "/"); // Redireciona de volta para a página principal
  server.send(302, "text/plain", "");
}

/*
 * Função handleNotFound()
 * Chamada se o usuário tentar acessar uma página que não existe
 */
void handleNotFound() {
  server.send(404, "text/plain", "404: Pagina Nao Encontrada");
}

/*
 * Configuração Inicial (setup)
 */
void setup() {
  Serial.begin(115200);
  
  // Configura o pino do relé como Saída
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW); // Garante que começa desligado

  // Inicia a conexão Wi-Fi
  Serial.print("Conectando em ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Wi-Fi conectado!");
  Serial.print("Acesse o servidor em: http://");
  Serial.println(WiFi.localIP()); // Mostra o IP do ESP32 no Serial Monitor

  // Configura as "rotas" do servidor web
  server.on("/", handleRoot);          // Página principal
  server.on("/ligar", handleLigar);     // Ação de ligar
  server.on("/desligar", handleDesligar); // Ação de desligar
  server.onNotFound(handleNotFound);  // Página de erro 404

  // Inicia o servidor
  server.begin();
  Serial.println("Servidor HTTP iniciado.");
}

/*
 * Loop Principal
 */
void loop() {
  server.handleClient(); // Fica ouvindo por novas conexões (clicks na página)
}
