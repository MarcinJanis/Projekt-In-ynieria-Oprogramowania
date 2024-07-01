#include "Classes.h"


using namespace std;



int Controller::getSignal( int sig , int limit) {
	if (sig >= limit) return 1;
	else return 0;

}

int Controller::getSignal(bool sig) {
	if (sig == true) return 1;
	else return 0;

}



int Controller::tm(int timeInterval){

	auto duration = chrono::seconds(timeInterval);  // set time
	auto startTime = chrono::high_resolution_clock::now(); //set initial time

	while (chrono::high_resolution_clock::now() - startTime < duration) {
	
		system("cls"); //cleaning creen
		screen.display(actual_state, choosen_drink,timeMarker, expectedFullTime, communicat);
		screen.simulationDisplay(Grinder.power, LoadingSys.power,EmptyingSys.power,waterPressurePump.power,milkPump.power,waterIntakePump.power,Heater.power,waterTemp.sig,waterPressure.sig,milkTemp.sig,waterIntake.sig);
		timeMarker++; // used in visu
		this_thread::sleep_for(std::chrono::milliseconds(1000)); // frequency of refreashing screen
	}

	return 1;
}


void Controller::setup(int keyPressed) {
	
	expectedFullTime = grindingTime + pressureTime +  offsetTime;
	timeMarker = 0;
	switch (keyPressed) {
	case 0:

		waterVolume_ml = 30;
		milkRequired = false;
		choosen_drink = "Espresso";

		break;
	case 1: 
		waterVolume_ml = 90;
		milkRequired = false;
		choosen_drink = "Americano";
		break;
	case 2:
		waterVolume_ml = 30;
		milkRequired = true;
		choosen_drink = "Cappuciono";
		expectedFullTime = expectedFullTime + milkTime;
		break;
	default:

		break;
	}
}


void Controller::cleaning() {
	waterIntakePump.power = true;
	waterPressurePump.power = true;
	milkPump.power = true;
	actual_state = 5;
	tm((cleaningTime+2));
	waterIntakePump.power = false;
	waterPressurePump.power = false;
	milkPump.power = false;
}


int Controller::diagnostics(bool tankLvl)
{
	if (tankLvl == false) return 1;
	else return -1;
}
