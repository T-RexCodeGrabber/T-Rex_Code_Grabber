
String comando = "";

long code;
int bits = 28;
int protocol = 6;
int repeatTransmit = 3;

#include <RCSwitch.h>

RCSwitch mySwitch = RCSwitch();

void setup() {
  
  mySwitch.enableTransmit(D2);
  mySwitch.enableReceive(D3);
  mySwitch.setProtocol(protocol);
  mySwitch.setRepeatTransmit(repeatTransmit);

  Serial.begin(9600);
  delay (500);
}

void loop() {

  if (Serial.available()) {
    while (Serial.available()) {
      char caracter = Serial.read();
      comando += caracter;
      delay(10);
    }
    String sCode = comando.substring(0);
    long longCode = sCode.toInt();
    code = longCode;
    if (code > 0) {
      mySwitch.send(code, bits);
      Serial.print("[Enviado] ");
      Serial.print(code);
      Serial.print(" / ");
      Serial.print( bits );
      Serial.print(" bit");
      Serial.print(" / ");
      Serial.println(protocol);
    }
  } comando = "";

  if (mySwitch.available()) {
    long RecCode = mySwitch.getReceivedValue();
    Serial.print("[Recebido] ");
    Serial.print( RecCode );
    Serial.print( " / " );
    Serial.print( mySwitch.getReceivedBitlength() );
    Serial.print(" bit");
    Serial.print(" / ");
    Serial.println( mySwitch.getReceivedProtocol() );

    mySwitch.resetAvailable();
  }
}
