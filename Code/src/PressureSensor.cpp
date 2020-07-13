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
    this->scale->begin(this->Out_pin, this->Sck_pin, 64);
    this->scale->get_scale();
    this->scale->tare();
    this->scale->set_offset(this->sensorOfset);
    this->scale->set_scale(this->sensorDivider);

    this->PR = this->scale->get_units();

    return this->PR;
}