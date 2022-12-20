#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
Ticker servo_feedback_ticker;

PwmIn servo0_f(D9), servo1_f(D10);
PwmOut servo0_c(D11), servo1_c(D12);
BBCar car(servo0_c, servo0_f, servo1_c, servo1_f, servo_ticker, servo_feedback_ticker);

Thread t;
EventQueue queue(32 * EVENTS_EVENT_SIZE);

BusInOut qti_pin(D4,D5,D6,D7);

void print(){
    int a, b;
    float d=0.0;
   //a=car.servo0.targetAngle;
    b=car.servo0.angle;
//    d = (a - b) * 6.5 * 3.14 / 360;
    printf ("%d", a);
    printf ("%f", d);
}

int main() {
    int a, b=0;
    float d=0.0;
    printf("123\n");
    t.start(callback(&queue, &EventQueue::dispatch_forever));

   parallax_qti qti1(qti_pin);
   int pattern, count=0;
    
   car.goStraight(50);
   while(count<4) {
      pattern = (int)qti1;
      // printf("%d\n",pattern);

      switch (pattern) {
         case 0b1000: car.turn(50, 0.1); break;
         case 0b1100: car.turn(50, 0.5); break;
         case 0b0100: car.turn(50, 0.7); break;
         case 0b0110: car.goStraight(50); break;
         case 0b0010: car.turn(50, -0.7); break;
         case 0b0011: car.turn(50, -0.5); break;
         case 0b0001: car.turn(50, -0.1); break;
         case 0b1111: 
            car.stop();
            wait_us(1000000);
            car.goStraight(35);
            wait_us(500000);
            count++;
         break;
         default: car.goStraight(50);
      }
      ThisThread::sleep_for(10ms);
   }
   car.stop();
    //queue.call(print);
    printf("12\n");
    a=car.servo0.targetAngle;
    b=car.servo0.angle;
    printf ("%d\n", a);
    printf ("%d\n", b);
    //printf ("%f\n", d);

}