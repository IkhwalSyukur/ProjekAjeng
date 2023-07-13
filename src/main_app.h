// 1. Wifi
// 2. Ultrasonic
// 3. Flow meter
// 4. Fuzzy
// 5. Gate
// 6. Database (mysql)
// 7. Manual

#include <Arduino.h>
#include "SensorJarak.h"
#include "gate.h"
#include "flow.h"
#include "fuzzi.h"
#include "web.h"

gates gt;
myflow fl;
FuzzyHandler fuzzify;
myweb mw;

float flow;
int kondisi;
int hasil;
int totalflow;
// int gatestate1;
// int gatestate2;
// int gatestate3;

void gt_task(void *pvParameters);
void fl_task(void *pvParameters);
void fuzzify_task(void *pvParameters);
void web_task(void *pvParameters);

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup()
{
  Serial.begin(115200);

  pinMode(datapin, INPUT_PULLUP);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(datapin), pulseCounter, FALLING);

  ultrasonic.begin();
  gt.begin();
  fuzzify.begin();
  mw.begin();
  // lm.begin();
  pinMode(32, OUTPUT);

  xTaskCreatePinnedToCore(gt_task, "Gate Task", 1024, NULL, 5, NULL, 1);
  xTaskCreatePinnedToCore(fl_task, "Flow Task", 1024, NULL, 10, NULL, 1);
  delay(1000);
  xTaskCreatePinnedToCore(fuzzify_task, "Fuzzy Task", 1024 * 2, NULL, 10, NULL, 1);
  xTaskCreatePinnedToCore(web_task, "web Task", 1024*4, NULL, 5, NULL, 1);
}

void loop()
{
  vTaskDelete(NULL);
}

void gt_task(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {
    Serial.print("Kondisi = ");
    Serial.println(kondisi);

    while (kondisi == 0 && hasil >= 60)
    {
      gt.gateopenfull(motor1open,motor1close);
      kondisi=2;
    }

    while (kondisi == 0 && hasil == 50)
    {
      gt.gateopenhalf(motor1open,motor1close);
      kondisi=1;
    }

    while (kondisi == 1 && hasil >= 60)
    {
      gt.gateopenhalf(motor1open,motor1close);
      kondisi=2;
    }

    while (kondisi == 1 && hasil <=30)
    {
      gt.gateclosehalf(motor1open,motor1close);
      kondisi=0;
    }
        
    while (kondisi == 2 && hasil <=30)
    {
      gt.gateclosefull(motor1open,motor1close,limit1);
      kondisi=0;
    }

    while (kondisi == 2 && hasil == 50)
    {
      gt.gateclosehalf(motor1open,motor1close);
      kondisi=1;
    }
    


    vTaskDelay(500);
  }
}

void fl_task(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {
    flow = fl.readflow();
    totalflow = fl.totalflow();
    Serial.print("Flow = ");
    Serial.println(flow);
    vTaskDelay(500);
  }
}
void fuzzify_task(void *pvParam)
{
  Serial.println("Fuzzify Task Started !");
  while (1)
  {
    fuzzify.setinput(1, ultrasonic.distance[2]);
    fuzzify.fuzify();
    hasil = fuzzify.output();
    Serial.printf("output Fuzzy: %d\n", hasil);
    vTaskDelay(500);
  }
}

void web_task(void *pvParam){
  (void)pvParam;
  for (;;){
    mw.send(flow,totalflow,ultrasonic.distance[0],ultrasonic.distance[1],ultrasonic.distance[2],hasil);
  }
}