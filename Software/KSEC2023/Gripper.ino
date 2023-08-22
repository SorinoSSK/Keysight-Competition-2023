void GripperControl() 
{
    // int l = map(data.ch[2], 182, 1811, 5, 180);
    // int z = 0;

    // double h = sqrt (l*l + z*z);
    // double phi = atan(z/l) * (180 / 3.1415);
    // double theta = acos((h/2)/120) * (180 / 3.1415);
    // int a1 = phi + theta; // angle for first part of the arm
    // int a2 = 135 + phi - theta; // angle for second part of the arm

    // int a3 = map(data.ch[4], 172, 1811, 0, 180);
    // int a4 = map(data.ch[5], 1811, 172, 0, 90);

    // base.write(a1);
    // arm.write(a2);
    // wrist.write(a3);
    // grip.write(a4);
    // int ARM1 = ;
    BASE_SERVO.write(map(data.ch[3], 172, 983 , 0, 180));
    ARMS_SERVO.write(map(data.ch[2], 368, 1811, 0, 180));
    WRIST_SERVO.write(map(data.ch[4], 172, 1811, 0, 180));
    GRIP_SERVO.write(map(data.ch[5], 172, 1811, 0, 180));
}

void FoldArm() 
{
    BASE_SERVO.write(180);
    ARMS_SERVO.write(5);
    WRIST_SERVO.write(90);
    GRIP_SERVO.write(45);
}

void GripperState()
{
    if (data.ch[6] > 1000)
        FoldArm();
    else 
        GripperControl();
}
