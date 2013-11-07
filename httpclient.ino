#include <Arduino.h>
#include "lwHTTPClientLite.h"
#include "lwHTTPClient.h"
#include "memfree.h"

/*
#include "Ethernet.h"
#include "SPI.h"
*/
#define userkey "Jack"
#define gateway "Zhong"

lwHTTPClientLite clients(userkey,gateway);
const char* sensor="humidity";
int i=-7293;
float f=-98.0301;

void setup()
{
    Serial.begin(9600);
    Serial.println("begin test...");
    bool b=true ;
    clients.append(sensor,b);
    clients.submit();

    int t= micros();
    clients.append(sensor,i);
    //clients.append(sensor,f);
    clients.submit();
    t=micros()-t;

    Serial.print("ms used: ");
    Serial.println(t);

//Serial.print("Username:\t");
//Serial.println(clients.userKey);
}


void upload()
{
    Serial.println("");
    clients.submit();
    Serial.println("====================");
}

void loop()
{
    Serial.println("looping");

    delay(2000);

    bool b=true ;
    clients.append(sensor,b);
    clients.submit();

    i++;
    f++;
    clients.append(sensor,i);
    upload();

    clients.append(sensor,f);
    upload();
//
//    clients.append(sensor,i);
//    clients.append(sensor,f);
//    upload();
//
//    clients.append(sensor,i);
//    clients.append(sensor,f);
//    clients.append(sensor,i);
//    clients.append(sensor,f);
//    upload();
    Serial.println("end loop");
}
