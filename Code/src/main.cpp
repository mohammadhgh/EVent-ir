// by Amir Sk , MHG, MHM, ASM
// Apr. 5rd 2020

#include "main.h"

/* ------------- Static Functions ------------*/
// static void resetParams()
// {
// 	Motor::getInstance()->resetEncPeriod();
// 	Motor::getInstance()->resetPC();
// 	pid->resetParams();
// 	degreeTracker->resetPosition();
// }

// static void onMotorStart()
// {
// 	resetParams();
// 	Motor::getInstance()->motorStart();
// 	timeStepValid = 0;
// 	Timer1Start(round(15625 * pid->getTimeStep()) - 1);
// }

// static void onMotorStop()
// {
// 	Motor::getInstance()->motorStop();
// 	resetParams();
// 	Timer1Stop();
// }

// static void motorSpeedCheck(){
// 	if(round(Motor::getInstance()->getEncRPM())>90)
// 	{
// 		Serial.println("check");
// 		onMotorStop();
// 		comeAndGo=0;
// 	}
// }

// void static initial_Check()
// {
// 	if (open_uSwitch->get_Status() == BSTATE_HIGH)
// 	{
// 		Serial.println("Initial Setup");
// 		Motor::getInstance()->setSpeed(Global_SysConfig->motorInitPWM+2);
// 		Motor::getInstance()->setDirection(DIRECTION_OPEN);
// 		Motor::getInstance()->motorStart();
// 		while (open_uSwitch->get_Clicked() == false){
// 			delay(1);
// 			motorSpeedCheck();
// 			//Serial.println(Motor::getInstance()->getEncRPM());
// 		}
// 		open_uSwitch->set_Clicked(false);
// 		Motor::getInstance()->motorStop();
// 		Motor::getInstance()->setSpeed(Global_SysConfig->motorInitPWM);
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

	//mot_Driver = new Motor_Driver(Motor::getInstance());

	onButton = new Button(PinConfiguration::onButton_pin);
	onButton->setPressCallback(onButton_callback);

	open_uSwitch = new Button(PinConfiguration::open_uSw_pin, INPUT, open_uSw_callback, LOW);

	bLED = new LED(PinConfiguration::bLED_pin);
	wLED = new LED(PinConfiguration::wLED_pin);

	respVolume = new Potentiometer(PinConfiguration::Potentiometer_Volume, 7);
	respCycle = new Potentiometer(PinConfiguration::Potentiometer_Cycle, 23);
	IERatio = new Potentiometer(PinConfiguration::Potentiometer_IE, 4);

	respCycle->set_Range(table_RC, sizeof table_RC);
	respVolume->set_Range(table_RV, sizeof table_RV);
	IERatio->set_Range(table_IE, sizeof table_IE);

	// pid = new PID(2.5, 32, 25e-3, 10);
	// pid->setTimeStep(Global_SysConfig->timeStep);
	// pid->setOutputRange(0, 255);

	// degreeTracker = new DegreeTracker((float)33, Global_SysConfig->duration, Global_SysConfig->timeStep);

	interrupts();

	digitalWrite(PinConfiguration::motorDriverOnOff, HIGH);
	// Motor::getInstance()->setSpeed(Global_SysConfig->motorInitPWM);
	Motor::getInstance()->initEnc(PinConfiguration::motorEncoderPin, INPUT, enc_callback, FALLING);
	// initial_Check();
	motorController = new MotorController();
	Timer1Start(round(15625 * 5e-3) - 1);
}

void loop()
{
	if(timeStepValid){
			motorController->motorControllerHandler();
	}


	//mot_Driver->update_resp_rate(Global_SysConfig);
	// //mot_Driver->check();
	// //LCD::getInstance()->LCD_Menu(respVolume->Potentiometer_Read(), respCycle->Potentiometer_Read(), IERatio->Potentiometer_Read());
	// onButton->check();

	// if(motorStopped==0)
	// 	motorSpeedCheck();

	// if (onButton->get_Clicked() == true && onButton->get_On_Off() == BSTATE_ON)
	// {
	// 	Serial.println("start");
	// 	Motor::getInstance()->setDirection(DIRECTION_CLOSE);
	// 	comeAndGo=1;
	// 	onMotorStart();
	// 	onButton->set_Clicked(false);
	// }

	// else if (onButton->get_Clicked() == true && onButton->get_On_Off() == BSTATE_OFF)
	// {
	// 	motorMustStop=1;
	// 	onButton->set_Clicked(false);
	// }
	// if(k==2){
	// 	k=0;
	// 	if(motorMustStop==1){
	// 		onMotorStop();
	// 		motorMustStop=0;
	// 		for (int i = 0; i < myCounter; i++)
	// 		{
	// 			Serial.print(i);
	// 			Serial.print("\t");
	// 			Serial.print(calcedLeftTime[i],3);
	// 			Serial.print("\t");
	// 			Serial.print(calcedLeftDegree[i],3);
	// 			Serial.print("\t");
	// 			Serial.print(MotorPwm[i]);
	// 			Serial.print("\t");
	// 			Serial.println(MotorSpeedActual[i]);
	// 		}
	// 		Serial.println(on_uSwithHitPC);

	// 		j=0;
	// 		myCounter=0;
	// 		comeAndGo=0;
	// 		Motor::getInstance()->setSpeed(Global_SysConfig->motorInitPWM);
	// 	}
	// }

	// /*if (open_uSwitch->get_Clicked() == true)
	// {
	// 	//TCNT5 = 0;
	// 	//Motor::getInstance()->changeDirection();
	// 	//bLED->switch_led();
	// 	//pid->resetParams();
	// 	open_uSwitch->set_Clicked(false);
	// }*/

	// if (Motor::getInstance()->getStatus() == MOTOR_IS_ON)
	// {
	// 	if (timeStepValid)
	// 	{
	// 		timeStepValid = 0;
	// 		degreeTracker->updateTime();
	// 		degreeTracker->updatePosition(Motor::getInstance()->getPC());
	// 		motorSpeed = pid->Calc(degreeTracker->updateDesiredRPM(), Motor::getInstance()->getEncRPM());
	// 		Motor::getInstance()->setSpeed(motorSpeed);

	// 		calcedLeftTime[myCounter]    = degreeTracker->getLeftTime();
	// 		calcedLeftDegree[myCounter]  = degreeTracker->getLeftDeltaDegree();
	// 		MotorPwm[myCounter] 		 = motorSpeed;
	// 		MotorSpeedActual[myCounter]  = round(Motor::getInstance()->getEncRPM());

	// 		if(myCounter<399)
	// 			myCounter++;

	// 		if (degreeTracker->getLeftTime()<0.035){
	// 			motorStopped = 1;
	// 			//f[0]=Motor::getInstance()->getPC();
	// 			//t[0]=degreeTracker->getLeftTime();
	// 			Motor::getInstance()->motorStop();
	// 			j++;
	// 		}
	// 	}
	// }
	// else if (j==1){
	// 	if (timeStepValid)
	// 	{
	// 		timeStepValid = 0;

	// 		degreeTracker->updateTime();
	// 		degreeTracker->updatePosition(Motor::getInstance()->getPC());
	// 		degreeTracker->updateDesiredRPM();

	// 		calcedLeftTime[myCounter]    = degreeTracker->getLeftTime();
	// 		calcedLeftDegree[myCounter]  = degreeTracker->getLeftDeltaDegree();
	// 		MotorPwm[myCounter] 		 = motorSpeed;
	// 		MotorSpeedActual[myCounter]  = round(Motor::getInstance()->getEncRPM());

	// 		if(myCounter<399)
	// 			myCounter++;
	// 	}
	// }

	// if(degreeTracker->getLeftTime()<0){
	// 	k++;
	// 	//j++;
	// 	///if(j==2)
	// 	j=0;
	// 	motorStopped=0;
	// 	int currentPC=Motor::getInstance()->getPC();
	// 	Timer5Stop();
	// 	onMotorStop();
	// 	changeDir=not(changeDir);
	// 	if(changeDir){
	// 		Motor::getInstance()->setDirection(DIRECTION_OPEN);
	// 		degreeTracker->updateDesiredDelatTime(2*Global_SysConfig->duration);
	// 		degreeTracker->updateDesiredDeltaDegree(33);
	// 		//degreeTracker->resetPosition();
	// 	}
	// 	else{
	// 		Motor::getInstance()->setDirection(DIRECTION_CLOSE);
	// 		if (open_uSwitch->get_Clicked() == true){
	// 			degreeTracker->updateDesiredDeltaDegree(33+(currentPC-on_uSwithHitPC)*(float)360/(float)MOTOR_PULSE_PER_TURN);
	// 			degreeTracker->resetPosition();
	// 			open_uSwitch->set_Clicked(false);
	// 			Serial.println(on_uSwithHitPC);
	// 			Serial.println(currentPC);
	// 			Serial.println(degreeTracker->getLeftDeltaDegree());
	// 		}
	// 		else
	// 		{
	// 			degreeTracker->updateDesiredDeltaDegree(33);
	// 			//degreeTracker->resetPosition();
	// 		}

	// 		degreeTracker->updateDesiredDelatTime(Global_SysConfig->duration);
	// 	}
	// 	Motor::getInstance()->setSpeed(Global_SysConfig->motorInitPWM);

	// 	delay(45);
	// 	onMotorStart();

	// }

	wdt_reset();
}
