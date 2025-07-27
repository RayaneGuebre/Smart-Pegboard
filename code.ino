#include <AccelStepper.h>
#include <Servo.h>

Servo myServo;




#define x_stepper_pin 1
#define x_stepper_dir_pin 2
#define y_stepper_pin 2
#define y_stepper_dir_pin 2
#define x_limit_pin_start 3
#define y_limit_pin_start 4
#define x_limit_pin_end 3
#define y_limit_pin_end 4
#define servo_pin 5
#define INTERFACE_TYPE 1
#define x_units 5
#define y_units 3



AccelStepper x_stepper(INTERFACE_TYPE, x_stepper_pin, x_stepper_dir_pin);
AccelStepper y_stepper(INTERFACE_TYPE, y_stepper_pin, y_stepper_dir_pin );

long x_len_step = 0;
long y_len_step = 0;
bool setted_up = false;



void pick(int x, int y){
    long  u_dimensions = (y_len_step / y_units) * y 
    long desired_x = (x_len_step * 10 / x_units * 13) * x - ((x_len_step * 10 / x_units * 13) / 2);
    long desired_y = (y_len_step / y_units) * y - (y_len_step / y_units / 2);

    x_stepper.moveTo(desired_x);
    y_stepper.moveTo(desired_y);

    while (x_stepper.distanceToGo() != 0 || y_stepper.distanceToGo() != 0){
        x_stepper.run();
        y_stepper.run();
    };
    y_stepper.moveTo((u_dimensions * 30,085) / 100 );
    x_stepper.moveTo((u_dimensions * 30,61) / 100 );
    while (x_stepper.distanceToGo() != 0 || y_stepper.distanceToGo() != 0){
        x_stepper.run();
        y_stepper.run();
    };
    y_stepper.moveTo(-(u_dimensions * 11,99) / 100 );
     while (y_stepper.distanceToGo() != 0){
        y_stepper.run();
    };
}











void setup() {

pinMode(x_stepper_pin, OUTPUT);
pinMode(y_stepper_pin, OUTPUT);
pinMode(x_stepper_dir_pin, OUTPUT);
pinMode(y_stepper_dir_pin, OUTPUT);


pinMode(x_limit_pin_start, INPUT_PULLUP);
pinMode(y_limit_pin_start, INPUT_PULLUP);
pinMode(x_limit_pin_end, INPUT_PULLUP);
pinMode(y_limit_pin_end, INPUT_PULLUP);

x_stepper.setMaxSpeed(1000);      
x_stepper.setAcceleration(500);

y_stepper.setMaxSpeed(1000);      
y_stepper.setAcceleration(500);

myServo.attach(servo_pin);
    
}


void loop() {
    if(setted_up == false){

    // x axis setup
    x_stepper.moveTo(-100000);
    while (digitalRead(x_limit_pin_start) == HIGH){
        x_stepper.run();
    }

    x_stepper.stop();
    x_stepper.setCurrentPosition(0);

    // y axis setup
    y_stepper.moveTO(-10000);
    while (digitalRead(y_limit_pin_start) == HIGH){
        y_stepper.run();
    }
    y_stepper.stop(); 
    y_stepper.setCurrentPosition(0);


    

     // board Measuring

    x_stepper.moveTo(100000);
    while (digitalRead(x_limit_pin_end) == HIGH){
    x_stepper.run();
    }
    x_len_step = x_stepper.currentPosition();
 
     
    y_stepper.moveTo(100000);
    while (digitalRead(y_limit_pin_end) == HIGH){
    y_stepper.run();
    }
    y_len_step = y_stepper.currentPosition();

    setted_up = true;
    







}
}}
