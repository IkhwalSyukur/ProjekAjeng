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

// gates gt;
// myflow fl;
FuzzyHandler fuzzify;
// mylimit lm;
// tombol tb;

// float flow;
// int btstate1;
// int btstate2;
// int btstate3;
// int gatestate1;
// int gatestate2;
// int gatestate3;

// void gt_task(void *pvParameters);
// void fl_task(void *pvParameters);
void fuzzify_task(void *pvParameters);
// void tb_task(void *pvParametres);

// Distance ultrasonic;

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
  // gt.begin();
  // fl.begin();
  fuzzify.begin();
  // lm.begin();
  // tb.begin();
  pinMode(32, OUTPUT);

  // xTaskCreatePinnedToCore(gt_task, "Gate Task", 1024, NULL, 1, NULL, 1);
  // xTaskCreatePinnedToCore(fl_task, "Flow Task", 1024, NULL, 10, NULL, 1);
  delay(1000);
  xTaskCreate(fuzzify_task, "Fuzzy Task", 1024 * 4, NULL, 10, NULL);
  // xTaskCreatePinnedToCore(tb_task, "Tombol Task", 1024, NULL, 1, NULL, 1);
}

void loop()
{
  vTaskDelete(NULL);
}

// void gt_task(void *pvParameters)
// {
//   (void)pvParameters;
//   for (;;)
//   {

//     if (hasil == 1)
//     {
//       gt.gateopen(motor1open,motor1close);
//       gt.gateopen(motor2open,motor2close);
//       gt.gateopen(motor3open,motor3close);
//     }
//     else
//     {
//       gt.gateclose(motor1open,motor1close);
//       if (lm.readlimit(switch1) == 1)
//       {
//         gt.gatestop(motor1open,motor1close);
//       }
//       gt.gateclose(motor2open,motor2close);
//       if (lm.readlimit(switch2) == 1)
//       {
//         gt.gatestop(motor2open,motor2close);
//       }
//       gt.gateclose(motor3open,motor3close);
//       if (lm.readlimit(switch3) == 1)
//       {
//         gt.gatestop(motor3open,motor3close);
//       }
//     }
//   }
// }

// void fl_task(void *pvParameters)
// {
//   (void)pvParameters;
//   for (;;)
//   {
//     flow = fl.readflow();
//   }
// }
int hasil;
void fuzzify_task(void *pvParam)
{
  Serial.println("Fuzzify Task Stareted !");
  while (1)
  {
    fuzzify.setinput(1, ultrasonic.distance[0]);
    fuzzify.fuzify();
    hasil = fuzzify.output();
    Serial.printf("output: %d\n", hasil);
    digitalWrite(32, (hasil == 1) ? HIGH : LOW);
    vTaskDelay(500);
  }
}

// void tb_task(void *pvParameters)
// {
//   (void)pvParameters;
//   for (;;)
//   {
//     btstate1 = tb.readtombol1();
//     btstate2 = tb.readtombol2();
//     btstate3 = tb.readTombol3();

//     if (btstate1 == 1 && gatestate1 == 0)
//     {
//       gt.gateclose(motor1open,motor1close);
//       if (lm.readlimit(switch1)==1){
//         gatestate1=1;
//         gt.gatestop(motor1open,motor1close);
//       }
//     }
//     if (btstate1 == 1 && gatestate1 == 1){
//       gt.gateopen(motor1open,motor1close);
//       vTaskDelay(500);
//       gt.gatestop(motor1open,motor1close);
//     }

//     if (btstate2 == 1 && gatestate2 == 0){
//       gt.gateclose(motor2open,motor2close);
//       if (lm.readlimit(switch2)==1){
//           gatestate2=1;
//           gt.gatestop(motor2open,motor2close);
//       }
//     }
//     if (btstate2==1 && gatestate2 == 1){
//         gt.gateopen(motor2open,motor2close);
//         vTaskDelay(500);
//         gt.gatestop(motor2open,motor2close);
//     }

//     if (btstate3 == 1 && gatestate3 == 0){
//       gt.gateclose(motor3open,motor3close);
//       if (lm.readlimit(switch3)==1){
//         gatestate3=1;
//         gt.gatestop(motor3open,motor3close);
//       }
//     }
//     if (btstate3 == 1 && gatestate3 == 1){
//       gt.gateopen(motor3open,motor3close);
//       vTaskDelay(500);
//       gt.gatestop(motor3open,motor3close);
//     }

//   }
// }
