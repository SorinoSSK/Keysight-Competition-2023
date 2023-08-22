void MovementControl() 
{
    int YValue = map(data.ch[0], 179, 1811, -127, 127);
    int XValue = map(data.ch[1], 176, 1811, -127, 127);

    DiffSteer.computeMotors(XValue, YValue);

    int spdL = map(DiffSteer.computedLeftMotor(), -127, 127, -255, 255);
    int spdR = map(DiffSteer.computedRightMotor(), -127, 127, -255, 255);
    // Serial.print(spdL);
    // Serial.print("\t");
    // Serial.println(spdR);
    if (spdL > MovementDeadZone) 
    {
        digitalWrite(IN1,HIGH);
        digitalWrite(IN2,LOW);
        motorL= abs(spdL);
    }
    else if (spdL < -MovementDeadZone) 
    {
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,HIGH);
        motorL = abs(spdL);
    }
    else 
    {
        digitalWrite(IN1,LOW);
        digitalWrite(IN2,LOW);
        motorL = 0;
    }

    if (spdR > MovementDeadZone) 
    {
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,HIGH);
        motorR = abs(spdR);
    }
    else if (spdR < -MovementDeadZone) 
    {
        digitalWrite(IN3,HIGH);
        digitalWrite(IN4,LOW);
        motorR = abs(spdR);
    }
    else 
    {
        digitalWrite(IN3,LOW);
        digitalWrite(IN4,LOW);
        motorR = 0;
    }

    analogWrite(ENA, motorL);
    analogWrite(ENB, motorR);
}

void StopMovement() 
{
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
}
