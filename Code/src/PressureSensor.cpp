#include <PressureSensor.h>

PressureSensor::PressureSensor(int Out_pin, int Sck_pin)
{
    this->Sck_pin = Sck_pin;
    this->Out_pin = Out_pin;
    this->PR = PR;
    this->HX711_inst = new HX711();

    this->HX711_inst->begin(this->Out_pin, this->Sck_pin, 32);
}

void PressureSensor::Calibrate(int times)
{
    this->HX711_inst->tare(times);  

    Serial.println("Tare updated. Press to continue ...");
    while (!Serial.available()) {}  

    long scale = this->HX711_inst->read_average(100);
    this->HX711_inst->set_scale(scale/2);
}

float PressureSensor::Read_Pressure()
{
    this->PR = this->HX711_inst->get_units();
    return this->PR;
}
