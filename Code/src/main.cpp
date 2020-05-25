// by Amir Sk , MHG, MHM, ASM
// Apr. 5rd 2020

#include "main.h"

/* ------------- Static Functions ------------*/
// static void motorSpeedCheck(){
// 	if(round(Motor::getInstance()->getEncRPM())>90)
// 	{
// 		Serial.println("check");
// 		onMotorStop();
// 		comeAndGo=0;
// 	}
// }


void setup()
{
	noInterrupts();

	for (size_t i = 8; i <= 30; i++)
		table_RC[i - 8] = i;

	Init_Timer1();
	Init_Timer3();
	Init_Timer4();
	Init_Timer5();

	Serial.begin(115200);

	Global_SysConfig = new SysConfig(2, 20, 0);
	Global_SysConfig->setParams(6e-1, 5e-3, 37);

	PinConfiguration::getInstance()->pinConfiguration();

	coolBuzz = new Buzzer(PinConfiguration::buzzerPin);

	onButton = new Button(PinConfiguration::onButton_pin);
	onButton->setPressCallback(onButton_callback);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin, INPUT, open_uSw_callback, LOW);

	bLED = new LED(PinConfiguration::bLED_pin);
	wLED = new LED(PinConfiguration::wLED_pin);

	respVolume = new Potentiometer(PinConfiguration::Potentiometer_Volume, 7);
	respCycle = new Potentiometer(PinConfiguration::Potentiometer_Cycle, 23);
	IERatio = new Potentiometer(PinConfiguration::Potentiometer_IE, 4);

	PR = new PressureSensor(PinConfiguration::PR_Out, PinConfiguration::PR_Sck);

	respCycle->set_Range(table_RC, sizeof table_RC);
	respVolume->set_Range(table_RV, sizeof table_RV);
	IERatio->set_Range(table_IE, sizeof table_IE);

	motorController = new MotorController();

	//LCD::getInstance()->LCD_Logo();

	interrupts();

	digitalWrite(PinConfiguration::motorDriverOnOff, HIGH);
	Motor::getInstance()->initEnc(PinConfiguration::motorEncoderPin, INPUT, enc_callback, FALLING);
	Timer1Start(round(15625 * Global_SysConfig->timeStep) - 1);

}

void loop()
{
	//LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read(), IERatio->Potentiometer_Read(), PR->Read_Pressure());
	//LCD::getInstance()->LCD_Clear();

	//LCD::getInstance()->LCD_graph();

	//Serial.println(respCycle->Potentiometer_Read());
	//Serial.println(IERatio->Potentiometer_Read());

	onButton->check();
	if (onButton->get_Clicked() == true && onButton->get_On_Off() == BSTATE_ON){
		onButton->set_Clicked(false);
		motorController->startReciporating();
	}
	else if (onButton->get_Clicked() == true && onButton->get_On_Off() == BSTATE_OFF)
	{
		motorController->stopReciporating();
		onButton->set_Clicked(false); 
	}
	
	if(timeStepValid){
		motorController->motorControllerHandler();	
	}
	wdt_reset();
}
