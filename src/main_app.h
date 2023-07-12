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
#include "limit.h"
#include "manual.h"

gates gt;
jarak jk;
myflow fl;
myfuzzy fz;
mylimit lm;
tombol tb;

int hasil;
int Sensor1;
int Sensor2;
int Sensor3;
float flow;
int btstate1;
int btstate2;
int btstate3;
int gatestate1;
int gatestate2;
int gatestate3;

void jk_task(void *pvParameters);
void gt_task(void *pvParameters);
void fl_task(void *pvParameters);
void fz_task(void *pvParameters);
void tb_task(void *pvParametres);

void IRAM_ATTR pulseCounter()
{
  pulseCount++;
}

void setup()
{
  Serial.begin(115200);
  jk.begin();
  gt.begin();
  fz.begin();
  lm.begin();
  tb.begin();

  pinMode(datapin, INPUT_PULLUP);
  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  previousMillis = 0;

  attachInterrupt(digitalPinToInterrupt(datapin), pulseCounter, FALLING);

  xTaskCreatePinnedToCore(jk_task, "ReadSensor", 1024, NULL, 10, NULL, 0);
  // xTaskCreatePinnedToCore(gt_task, "Gate Task", 1024, NULL, 1, NULL, 1);
  xTaskCreatePinnedToCore(fl_task, "Flow Task", 4096, NULL, 10, NULL, 1);
  xTaskCreatePinnedToCore(fz_task, "Fuzzy Task", 1024, NULL, 10, NULL, 1);
  // xTaskCreatePinnedToCore(tb_task, "Tombol Task", 1024, NULL, 1, NULL, 1);
}

void loop()
{
  // put your main code here, to run repeatedly:
  vTaskDelete(NULL);
}

void jk_task(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {
    Sensor1 = jk.ReadSensor(trigPin1, echoPin1);
    Sensor2 = jk.ReadSensor(trigPin2, echoPin2);
    Sensor3 = jk.ReadSensor(trigPin3, echoPin3);
    Serial.print("Sensor 1 = ");
    Serial.println(Sensor1);
    Serial.print("Sensor 2 = ");
    Serial.println(Sensor2);
    Serial.print("Sensor 3 = ");
    Serial.println(Sensor3);
  }
}

void gt_task(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {

    if (hasil == 1)
    {
      gt.gateopen(motor1open, motor1close);
      vTaskDelay(3200);
      gt.gatestop(motor1open,motor1close);
      // gt.gateopen(motor2open, motor2close);
      // gt.gateopen(motor3open, motor3close);
    }
    else
    {
      gt.gateclose(motor1open, motor1close);
      if (lm.readlimit(switch1) == 1)
      {
        gt.gatestop(motor1open, motor1close);
      }
      gt.gateclose(motor2open, motor2close);
      if (lm.readlimit(switch2) == 1)
      {
        gt.gatestop(motor2open, motor2close);
      }
      gt.gateclose(motor3open, motor3close);
      if (lm.readlimit(switch3) == 1)
      {
        gt.gatestop(motor3open, motor3close);
      }
    }
  }
}

void fl_task(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {
    flow = fl.readflow();
    Serial.print("Flow = ");
    Serial.println(flow);
  }
}

void fz_task(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {
    fz.setinput(1, Sensor3);
    fz.fuzify();
    hasil = fz.out();
    Serial.print("Hasil = ");
    Serial.println(hasil);
  }
}

void tb_task(void *pvParameters)
{
  (void)pvParameters;
  for (;;)
  {
    btstate1 = tb.readtombol(tombol1);
    btstate2 = tb.readtombol(tombol2);
    btstate3 = tb.readtombol(tombol3);

    if (btstate1 == 0 && gatestate1 == 0)
    {
      gt.gateclose(motor1open, motor1close);
      if (lm.readlimit(switch1) == 1)
      {
        gatestate1 = 1;
        gt.gatestop(motor1open, motor1close);
      }
    }
    if (btstate1 == 0 && gatestate1 == 1)
    {
      gt.gateopen(motor1open, motor1close);
      vTaskDelay(3200);
      gt.gatestop(motor1open, motor1close);
    }

    if (btstate2 == 0 && gatestate2 == 0)
    {
      gt.gateclose(motor2open, motor2close);
      if (lm.readlimit(switch2) == 1)
      {
        gatestate2 = 1;
        gt.gatestop(motor2open, motor2close);
      }
    }
    if (btstate2 == 0 && gatestate2 == 1)
    {
      gt.gateopen(motor2open, motor2close);
      vTaskDelay(3200);
      gt.gatestop(motor2open, motor2close);
    }

    if (btstate3 == 0 && gatestate3 == 0)
    {
      gt.gateclose(motor3open, motor3close);
      if (lm.readlimit(switch3) == 1)
      {
        gatestate3 = 1;
        gt.gatestop(motor3open, motor3close);
      }
    }
    if (btstate3 == 0 && gatestate3 == 1)
    {
      gt.gateopen(motor3open, motor3close);
      vTaskDelay(3200);
      gt.gatestop(motor3open, motor3close);
    }
  }
}