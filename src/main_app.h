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
// myfuzzy fz;
// mylimit lm;
// tombol tb;

int hasil;
// int distance1;
// int distance2;
// int distance3;
// float flow;
int btstate1;
int btstate2;
int btstate3;
int gatestate1;
int gatestate2;
int gatestate3;

// void jk_task(void *pvParam);
// void gt_task(void *pvParameters);
// void fl_task(void *pvParameters);
// void fz_task(void *pvParameters);
// void tb_task(void *pvParametres);

// Distance ultrasonic;

void setup()
{
  Serial.begin(115200);
  ultrasonic.begin();
  // gt.begin();
  // fl.begin();
  // fz.begin();
  // lm.begin();
  // tb.begin();

  // xTaskCreatePinnedToCore(jk_task, "Readdistance", 1024 * 2, NULL, 10, NULL, 1);
  // xTaskCreatePinnedToCore(gt_task, "Gate Task", 1024, NULL, 1, NULL, 1);
  // xTaskCreatePinnedToCore(fl_task, "Flow Task", 1024, NULL, 10, NULL, 1);
  // xTaskCreatePinnedToCore(fz_task, "Fuzzy Task", 1024, NULL, 10, NULL, 1);
  // xTaskCreatePinnedToCore(tb_task, "Tombol Task", 1024, NULL, 1, NULL, 1);
}

void loop()
{
  // put your main code here, to run repeatedly:
  vTaskDelete(NULL);
}

// void jk_task(void *pvParam)
// {
//   while (1)
//   {
//     ultrasonic.distance[0] = ultrasonic.readSensor(trigPin1, echoPin1);
//     ultrasonic.distance[1] = ultrasonic.readSensor(trigPin2, echoPin2);
//     ultrasonic.distance[2] = ultrasonic.readSensor(trigPin3, echoPin3);

//     Serial.printf("distance 1: %d\n", ultrasonic.distance[0]);
//     Serial.printf("distance 2: %d\n", ultrasonic.distance[1]);
//     Serial.printf("distance 3: %d\n", ultrasonic.distance[2]);
//     vTaskDelay(500);
//   }
// }

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

// void fz_task(void *pvParam)
// {
//   while(1)
//   {
//     fz.setinput(1, distance1);
//     fz.fuzify();
//     hasil = fz.out();
//   }
// }

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