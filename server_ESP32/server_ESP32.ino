/*
  ModbusTCP for W5x00 Ethernet library
  Basic Server code example

  (c)2020 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266

  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#include <SPI.h>
#include <Ethernet.h>       // Ethernet library v2 is required
#include <ModbusEthernet.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED
};
IPAddress ip(192, 168, 1, 202); // The IP address will be dependent on your local network:
ModbusEthernet mb;              // Declare ModbusTCP instance

int IntegerNumAddr=100, DecimalNumAddr=101, activationAddr=5;

void setup() {
  Serial.begin(115200);     // Open serial communications and wait for port to open
  Ethernet.init(2);        // SS pin
  Ethernet.begin(mac, ip);  // start the Ethernet connection
  while (Ethernet.linkStatus() != LinkON){          //Wait for conection with the net
    delay(500);
    Serial.print(".");
  }
  delay(1000);              // give the Ethernet shield a second to initialize
  mb.server();              // Act as Modbus TCP server
  mb.addReg(HREG(IntegerNumAddr));     // Add Holding register #100
  mb.addReg(HREG(DecimalNumAddr));     // Add Holding register #101
  mb.addCoil(activationAddr);
}

void loop() {
  mb.task();                // Server Modbus TCP queries
  Serial.print("El numero completo es: ");
  Serial.print(mb.Reg(HREG(IntegerNumAddr)));                                       //read the register 100
  Serial.print(".");
  Serial.println(mb.Reg(HREG(DecimalNumAddr)));                                     //read the register 101
  Serial.print("Se activa la señal: ");
  Serial.println(mb.Coil(activationAddr));
  delay(50);
}