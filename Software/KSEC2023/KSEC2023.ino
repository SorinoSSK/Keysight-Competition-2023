#include "sbus.h"
#include "Servo.h"
#include "DifferentialSteering.h"

/* SBUS objects instantiation for X8R Receiver */
bfs::SbusRx sbus_rx(&Serial3);
bfs::SbusTx sbus_tx(&Serial3);
bfs::SbusData data;

/* L298 Pinout */
int ENA = 5;
int ENB = 6;
int IN1 = 8;
int IN2 = 7;
int IN3 = 12;
int IN4 = 13;

int INVERSE_LEFT_WHEEL  = 1;
int INVERSE_RIGHT_WHEEL = 1;

/* Servo motors object instantiation*/
Servo BASE_SERVO;
Servo ARMS_SERVO;
Servo WRIST_SERVO;
Servo GRIP_SERVO;
Servo TRIG_SERVO;

/* Differential drive setup*/
DifferentialSteering DiffSteer;   // Differential stering object instatiation
int fPivYLimit        = 32;       // Y pivot limit (X Threshold for steering)
int motorL, motorR    = 0;        // Variable declaration
int MovementDeadZone  = 40;

void setup() 
{
    pinMode(ENA, OUTPUT);
    pinMode(ENB, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    BASE_SERVO.attach(11);
    ARMS_SERVO.attach(2);
    WRIST_SERVO.attach(4);
    GRIP_SERVO.attach(3);
  //  servo5.attach(A8);
  //  servo6.attach(A9);

    /* Serial monitor setup */
    Serial.begin(115200);

    /* Start SBUS communication */
    sbus_rx.Begin();
    sbus_tx.Begin();

    /* Start differential drive */
    DiffSteer.begin(fPivYLimit);

    /* Starting Positions */
    StopMovement();                     // Reference from Move.ino
    FoldArm();                          // Reference from Gripper.ino
}

void loop() 
{
    if (sbus_rx.Read()) 
    {
        /* Retrieve the received data */
        data = sbus_rx.data();

        /* Display the received data in Serial monitor */
        for (int8_t i = 0; i < 8; i++) 
        {
            Serial.print(data.ch[i]);
            Serial.print("\t");
        }
        /* Display lost frames and failsafe data */
        Serial.print(data.lost_frame);
        Serial.print("\t");
        Serial.println(data.failsafe);
        
        MovementControl();              // Reference from Move.ino
        GripperState();                 // Reference from Gripper.ino
    }
}
