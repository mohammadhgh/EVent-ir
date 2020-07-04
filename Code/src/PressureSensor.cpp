#include <PressureSensor.h>

PressureSensor::PressureSensor(int Out_pin, int Sck_pin)
{
    this->Sck_pin = Sck_pin;
    this->Out_pin = Out_pin;
    this->PR = PR;
    this->HX711_inst = new HX711();

    this->HX711_inst->begin(this->Out_pin, this->Sck_pin, 64);
}

void PressureSensor::Calibrate(int times)
{
    this->HX711_inst->tare(times);  

    Serial.println(this->HX711_inst->get_offset());
    Serial.println("Tare updated. Press to continue ...");
    while (!Serial.available()) {}  

    double scale = this->HX711_inst->get_value(times);
    Serial.println(scale);
    this->HX711_inst->set_scale(scale/10);
    Serial.println(this->HX711_inst->get_scale());

    Serial.println("Scale updated. Press to continue ...");
    while (!Serial.available()) {}
}

float PressureSensor::Read_Pressure()
{
    this->PR = this->HX711_inst->get_units(1);
    return this->PR;
}
