#pragma once
#include <Arduino.h>

#include "WiFi.h"
#include "HTTPClient.h"

const char *ssid = "Variasi Aluminium 1";
const char *password = "hapisahsyukur";

#define ON_Board_LED 2

String postData = "";
String payload = "";

struct myweb
{
    myweb() {}

    void begin()
    {
        Serial.begin(115200);
        pinMode(ON_Board_LED, OUTPUT);
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        Serial.println();
        Serial.println("-------------");
        Serial.print("Connecting");

        int connecting_process_timed_out = 20; //--> 20 = 20 seconds.
        connecting_process_timed_out = connecting_process_timed_out * 2;
        while (WiFi.status() != WL_CONNECTED)
        {
            Serial.print(".");
            digitalWrite(ON_Board_LED, HIGH);
            delay(250);
            digitalWrite(ON_Board_LED, LOW);
            delay(250);

            //........................................ Countdown "connecting_process_timed_out".
            if (connecting_process_timed_out > 0)
                connecting_process_timed_out--;
            if (connecting_process_timed_out == 0)
            {
                vTaskDelay(1000);
                ESP.restart();
            }

            digitalWrite(ON_Board_LED, LOW); //--> Turn off the On Board LED when it is connected to the wifi router.

            //---------------------------------------- If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
            Serial.println();
            Serial.print("Successfully connected to : ");
            Serial.println(ssid);
            // Serial.print("IP address: ");
            // Serial.println(WiFi.localIP());
            Serial.println("-------------");
            //----------------------------------------
        }
    }

    void send(float flow, int totalmili, int sensor1, int sensor2, int sensor3, int pintu)
    {
        if (WiFi.status() == WL_CONNECTED)
        {
            HTTPClient http; //--> Declare object of class HTTPClient.
            int httpCode;    //--> Variables for HTTP return code.

            //    postData = "id=1";
            postData = "&flowRate=" + String(flow);
            postData += "&totalMiliLitres=" + String(totalmili);
            postData += "&Sensor1=" + String(sensor1);
            postData += "&Sensor2=" + String(sensor2);
            postData += "&Sensor3=" + String(sensor3);
            postData += "&pintu=" + String(pintu);
            payload = "";

            digitalWrite(ON_Board_LED, HIGH);
            Serial.println();
            Serial.println("---------------index.php");
            // Example : http.begin("http://192.168.0.0/ESP32_MySQL_Database/Final/updateDHT11data_and_recordtable.php");
            http.begin("http://192.168.43.44/ProjekAjeng/index.php");            //--> Specify request destination
            http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //--> Specify content-type header

            httpCode = http.POST(postData); //--> Send the request
            payload = http.getString();     //--> Get the response payload

            Serial.print("postData : ");
            Serial.println(postData);
            Serial.print("httpCode : ");
            Serial.println(httpCode); //--> Print HTTP return code
            Serial.print("payload  : ");
            Serial.println(payload); //--> Print request response payload

            http.end(); // Close connection
            Serial.println("---------------");
            digitalWrite(ON_Board_LED, LOW);
            //........................................

            vTaskDelay(5000);
        }
    }
};