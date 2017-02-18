
/*
  Herramientas Tecnologicas Profesionales
  www.hetpro-store.com

  Tutorial Original:
  http://tronixstuff.com/2014/01/08/tutorial-arduino-and-sim900-gsm-modules/

  Comandos AT:
  http://probots.co.in/Manuals/SIM900%20GSM%20Modem%20-%20Starter%20Guide.pdf

  Hoja de datos:

  Instrucciones para Arduino: Configura la terminal serial a 19200 baudios para que puedas ver los mensajes.
*/
/* Equipo TeknoChisp. Feb. 2017. David Cabello, Pedro Martínez, Andres Mauriz */

#define Button 12
#include <SoftwareSerial.h>
SoftwareSerial SIM900(7, 8); // Configura el puerto serial para el SIM900
String telefono1="63856***";
String telefono2="670391***";
String telefono3="696357***";
String telefono4="644495***";
String telefono5="60881***";
String telefono6="64404***";
String telefono7="67556***";
String telefono8="64921***";
char incoming_char = 0; //Variable que guarda los caracteres que envia el SIM900
int salir = 0;
int id =0 ;

void sendATCommand(String msg)
{
  Serial.println(msg);
  SIM900.println(msg);
  delay(200);
  espera_mensaje();
  delay(100);
}

void sendATRawCommand(String msg)
{
  Serial.print(msg);
  SIM900.print(msg);
}


void llamar(String Telf)
// Función que permite llamar a un celular local
{
  String msg;
  msg = "ATD "+Telf+";";
  sendATCommand(msg); //Celular
  delay(8000); // wait for 8 seconds...
  sendATCommand("ATH"); // Cuelga el telefono
}

void enter_pin()
{
  sendATCommand("AT");
  sendATCommand("AT+CPIN=?");
  sendATCommand("AT+CPIN=****");  //AT comand to put PIN number
  sendATCommand("AT+CPIN?");
  sendATCommand("AT+GMM");
  sendATCommand("AT+GSN");
  sendATCommand("AT+CREG?");
  sendATCommand("AT+COPS?");
}

void espera_mensaje()
{
  salir = 1;
  while (salir == 1)
  {
    if (SIM900.available() > 0)
    {
      incoming_char = SIM900.read(); //Get the character from the cellular serial port.
      Serial.print(incoming_char); //Print the incoming character to the terminal.
    }
    else {
      salir = 0;
    }
  }
}
void modo_recibe_mensaje()
{
  //Configura el modo texto para enviar o recibir mensajes
  sendATCommand("AT+CMGF=1"); // set SMS mode to text
  sendATCommand("AT+CNMI=2,2,0,0,0");

  // blurt out contents of new SMS upon receipt to the GSM shield's serial out
  delay(1000);
}

void recibe_mensaje()
{
modo_recibe_mensaje();
  for (;;)
  {
    if (SIM900.available() > 0)
    {

      incoming_char = SIM900.read(); //Get the character from the cellular serial port.
      Serial.print(incoming_char); //Print the incoming character to the terminal.
    }
    if (Serial.available() > 0)
    {
      if (Serial.read() == 'A') break;
    }
  }
  Serial.println("OK-2");

  delay(100);
  SIM900.println();
  delay(30000);
  while (1); // Esperate por tiempo indefinido
  
}

void EnviarSMS(String mensaje)
//Funcion para mandar mensaje de texto
{
  String msg = String("AT+CMGS=\"")+mensaje+String("\"");
  sendATCommand("AT+CMGF=1"); // AT command to send SMS message
  sendATCommand("AT+CMGF?"); // AT command to check SMS message mode

  sendATCommand(msg); // recipient's mobile number, in international format
  msg = String("MENSAJE DE ALERTA - Mensaje numero ")+String(id);
  sendATRawCommand(msg); // message to send
  SIM900.println((char)26);  //Equivalent to sending Ctrl+Z, ASCII code 26 //Comando de finalizacion
  delay(5000); // Tiempo para que se envie el mensaje
  espera_mensaje();
  Serial.println("SMS sent successfully");
}

void setup()
{
  Serial.begin(19200); //Configura velocidad serial para el Arduino
  pinMode(Button,INPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  Serial.println("Waiting 20s to start GSM board...");
  SIM900.begin(19200); //Configura velocidad serial para el SIM900
  Serial.println("Setup done!"); //Mensaje OK en el arduino, para saber que todo va bien.
  digitalWrite(11,LOW);
}
void loop(){
  digitalWrite(11,HIGH);
  if(digitalRead(Button)==LOW){
    digitalWrite(11,LOW);
    delay(3000);
    if(digitalRead(Button)==LOW){
      digitalWrite(11,HIGH);
      delay(3000);
      EnviarSMS(telefono1);
      llamar(telefono1);
      EnviarSMS(telefono2);
      llamar(telefono2);
      EnviarSMS(telefono3);
      llamar(telefono3);
      EnviarSMS(telefono4);
      llamar(telefono4);
      EnviarSMS(telefono5);
      llamar(telefono5);
      EnviarSMS(telefono6);
      llamar(telefono6);
      EnviarSMS(telefono7);
      llamar(telefono7);
      EnviarSMS(telefono8);
      llamar(telefono8);
      digitalWrite(11,LOW);
      id++;
  }
 }
 delay(100);
 digitalWrite(11,LOW);
 delay(2000);
}

