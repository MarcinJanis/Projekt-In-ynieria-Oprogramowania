#pragma once

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <conio.h>
#include <cstdlib>


using namespace std;



// Global Const





class Interface {
public:



	// communicates
	int container_err = 0; // 0 - ok, 1 - milk , 2 - coffe , 3 - both 
	string actual_state = "";

	// memory:
	int keyReaded = 0;
	int acceptedKeys[5] = {0,1,2,3,4};

	// interface for choosing drink
	int positionPointer = 0;



	int keyReader();

	int  display(int actual_state, string choosen_drink, int timeMarker, int expectedFullTime, string communicat);

	void simulationDisplay(bool grinder, bool loading, bool emptying, bool pressurePump, bool milkPump, bool waterIntak, bool heater, int pressureSens, int waterTempSens, int milkTempSens, int waterVolSense);


};



class dSensor {
public:
	bool sig=false;
};

class aSensor {
public:
	int sig=false;
};

class HardwareEq {
public:
	bool power=false;
};

class Pump {
public:
	bool power=false;
};




class Controller {


public: 

	// parameters of product

	int grindingTime=10;
	int pressureTime=25;
	int	milkTime=10;
	int	cleaningTime=10;

	int waterTempMax_C=88;
	int milkTempMax_C=50;
	int	pressureMax_bar=15;
	int	waterVolume_ml=30;
	int offsetTime = 3;

	// Var used in visu
	string choosen_drink = "";
	string communicat = "";

	// Var of state
	bool milkRequired;
	int actual_state=0;
	int expectedFullTime=0;
	int timeMarker=0;



	Interface screen;

	HardwareEq Grinder, LoadingSys, EmptyingSys , Heater;
	aSensor waterTemp, waterPressure, waterIntake, milkTemp;
	Pump waterPressurePump, milkPump, waterIntakePump;
	dSensor coffeLvlSensor, milkLvlSensor;

	int diagnostics(bool tankLvl); //  1 - if its ok, -1 if its empty tank (or other possibles errors) 

	int getSignal(int sig , int limit); // if sig reach limit returns 1, else 0 
	int getSignal(bool sig); // if returns 1 - High , 0 - Low 

	//int tm(int timeInterval, Interface& screen, int (Interface::* fun)(int, string, int), int actual_state, string choosen_drink, int expectedFullTime);  // returns 1 when timer counts to timeInterval (seconds)

	int tm(int timeInterval);

	void setup(int keyPressed);
	void cleaning();

};



