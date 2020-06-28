#include <PressureSensor.h>

PressureSensor::PressureSensor(int Out_pin, int Sck_pin)
{
    this->Sck_pin = Sck_pin;
    this->Out_pin = Out_pin;
    this->PR = PR;
    this->scale = new HX711();
    this->sensorDivider = 59710;
    this->sensorOfset = 1326161;
}

float PressureSensor::Read_Pressure()
{
    long time1 = micros();

    this->scale->begin(this->Out_pin, this->Sck_pin);
    long time2 = micros();

    this->scale->get_scale();
    long time3 = micros();

    this->scale->tare(1);
    long time4 = micros();

    this->scale->set_offset(this->sensorOfset);
    long time5 = micros();

    this->scale->set_scale(this->sensorDivider);
    long time6 = micros();

    this->PR = this->scale->get_units();
    long time7 = micros();

    Serial.println("begin");
    Serial.println(time2 - time1);

    Serial.println("get_scale");
    Serial.println(time3 - time2);

    Serial.println("tare");
    Serial.println(time4 - time3);

    Serial.println("set_offset");
    Serial.println(time5 - time4);

    Serial.println("set_scale");
    Serial.println(time6 - time5);

    Serial.println("get_units");
    Serial.println(time7 - time6);

    return this->PR;
}
