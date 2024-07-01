#include "Classes.h"





using namespace std;

// function to symulation of Sensors

int symulate(int value, int valueStep)
{

		this_thread::sleep_for(std::chrono::milliseconds(300));

		 return (value + valueStep);

}







int main() {

	// INITIALIZATION
	Controller coffeMachine;


	// Variabels def

	bool evOrder = false;
	




	coffeMachine.Grinder.power = false;
	coffeMachine.LoadingSys.power = false;
	coffeMachine.EmptyingSys.power = false;
	coffeMachine.waterPressurePump.power = false;
	coffeMachine.milkPump.power = false;
	coffeMachine.waterIntakePump.power = false;
	coffeMachine.Heater.power = false;
	coffeMachine.waterTemp.sig = 21;
	coffeMachine.waterPressure.sig = 0;
	coffeMachine.milkTemp.sig = 8;
	coffeMachine.waterIntake.sig = 0;


	coffeMachine.coffeLvlSensor.sig = false;
	coffeMachine.milkLvlSensor.sig = false;

	
	
	while (1) {
		evOrder = false;
		coffeMachine.screen.keyReaded = 10;
		


		// Step 1 (State 4) Autodiagnostics

		while (coffeMachine.diagnostics(coffeMachine.coffeLvlSensor.sig) != 1) {
			coffeMachine.actual_state = 4; //  State: Empty tanks
			coffeMachine.screen.display(coffeMachine.actual_state, coffeMachine.choosen_drink, coffeMachine.timeMarker, coffeMachine.expectedFullTime, coffeMachine.communicat);
			cout << endl << "Press any key to continue" << endl;  // to simulate refilling 
			_getch();
			coffeMachine.coffeLvlSensor.sig = false;
			coffeMachine.milkLvlSensor.sig = false;

		}

		// Step 2 (State 1) Choose making order

		coffeMachine.actual_state = 1; //  State: Making order

		while (evOrder == false) {
			system("cls");
			coffeMachine.screen.display(coffeMachine.actual_state, coffeMachine.choosen_drink, coffeMachine.timeMarker, coffeMachine.expectedFullTime, coffeMachine.communicat);
			coffeMachine.screen.simulationDisplay(coffeMachine.Grinder.power, coffeMachine.LoadingSys.power, coffeMachine.EmptyingSys.power, coffeMachine.waterPressurePump.power, coffeMachine.milkPump.power, coffeMachine.waterIntakePump.power, coffeMachine.Heater.power, coffeMachine.waterTemp.sig, coffeMachine.waterPressure.sig, coffeMachine.milkTemp.sig, coffeMachine.waterIntake.sig);
			coffeMachine.screen.positionPointer = 1;
			coffeMachine.screen.keyReaded = coffeMachine.screen.keyReader();

			if (coffeMachine.screen.keyReaded == 3) {
				
				exit(0);
			}

			for (int i = 0; i <= 4; i++)
			{

				if (coffeMachine.screen.keyReaded == coffeMachine.screen.acceptedKeys[i])
				{
					if (coffeMachine.screen.keyReaded == 4) {
						coffeMachine.expectedFullTime = coffeMachine.cleaningTime + 3;
						coffeMachine.cleaning();
						coffeMachine.actual_state = 1;
						evOrder = false;
					}
					else {
						coffeMachine.setup(coffeMachine.screen.keyReaded);
						evOrder = true;
					}
					
				}
			}
		}



		

		// Step 3 (State 2) Prepering Coffe
		coffeMachine.actual_state = 2;
			//Grinding
				coffeMachine.Grinder.power = true;
				coffeMachine.communicat = "Gringind coffe ...";
				coffeMachine.tm(coffeMachine.grindingTime);
				coffeMachine.Grinder.power = false;
			//Loading 
				coffeMachine.LoadingSys.power = true;
				coffeMachine.communicat = "Loading Coffe ...";
				coffeMachine.tm(coffeMachine.offsetTime);
				coffeMachine.LoadingSys.power = false;
			//WaterIntake
				coffeMachine.waterIntakePump.power = true;
				coffeMachine.communicat = "Water Intake ...";
				while (coffeMachine.getSignal(coffeMachine.waterIntake.sig, coffeMachine.waterVolume_ml) != 1)
				{

					coffeMachine.waterIntake.sig = symulate(coffeMachine.waterIntake.sig,2);
					coffeMachine.screen.display(coffeMachine.actual_state, coffeMachine.choosen_drink, coffeMachine.timeMarker, coffeMachine.expectedFullTime, coffeMachine.communicat);
					coffeMachine.screen.simulationDisplay(coffeMachine.Grinder.power, coffeMachine.LoadingSys.power, coffeMachine.EmptyingSys.power, coffeMachine.waterPressurePump.power, coffeMachine.milkPump.power, coffeMachine.waterIntakePump.power,  coffeMachine.Heater.power,coffeMachine.waterTemp.sig, coffeMachine.waterPressure.sig, coffeMachine.milkTemp.sig, coffeMachine.waterIntake.sig);

				}

				coffeMachine.waterIntakePump.power = false;

			//Heating
				coffeMachine.Heater.power = true;
				coffeMachine.communicat = "Heating water ...";
				while (coffeMachine.getSignal(coffeMachine.waterTemp.sig, coffeMachine.waterTempMax_C) != 1)
				{

					coffeMachine.waterTemp.sig = symulate(coffeMachine.waterTemp.sig, 5);
					coffeMachine.screen.display(coffeMachine.actual_state, coffeMachine.choosen_drink, coffeMachine.timeMarker, coffeMachine.expectedFullTime, coffeMachine.communicat);
					coffeMachine.screen.simulationDisplay(coffeMachine.Grinder.power, coffeMachine.LoadingSys.power, coffeMachine.EmptyingSys.power, coffeMachine.waterPressurePump.power, coffeMachine.milkPump.power, coffeMachine.waterIntakePump.power, coffeMachine.Heater.power, coffeMachine.waterTemp.sig, coffeMachine.waterPressure.sig, coffeMachine.milkTemp.sig, coffeMachine.waterIntake.sig);

				}

				coffeMachine.Heater.power = false;

			//Pressure

			    coffeMachine.waterPressurePump.power = true;
			    coffeMachine.communicat = "Making Pressure 15 bar ...";
				while (coffeMachine.getSignal(coffeMachine.waterPressure.sig, coffeMachine.pressureMax_bar) != 1)
				{

					coffeMachine.waterPressure.sig = symulate(coffeMachine.waterPressure.sig, 1);
					coffeMachine.screen.display(coffeMachine.actual_state, coffeMachine.choosen_drink, coffeMachine.timeMarker, coffeMachine.expectedFullTime, coffeMachine.communicat);
					coffeMachine.screen.simulationDisplay(coffeMachine.Grinder.power, coffeMachine.LoadingSys.power, coffeMachine.EmptyingSys.power, coffeMachine.waterPressurePump.power, coffeMachine.milkPump.power, coffeMachine.waterIntakePump.power, coffeMachine.Heater.power, coffeMachine.waterTemp.sig, coffeMachine.waterPressure.sig, coffeMachine.milkTemp.sig, coffeMachine.waterIntake.sig);

				}

				
			
			//Coffe
				coffeMachine.communicat = "Your coffie is preparing ...";
				
				coffeMachine.tm(coffeMachine.pressureTime);
				coffeMachine.waterPressurePump.power = false;
			//Milk

				if (coffeMachine.milkRequired == true)
				{
					coffeMachine.milkPump.power = true;
					coffeMachine.communicat = "Adding milk to you coffe...";
					coffeMachine.tm(coffeMachine.milkTime);
					coffeMachine.milkPump.power = false;
				}
			
		//Step 4 (Stae x) Coffe is ready
				coffeMachine.communicat = "Your coffe is ready, enjoy!";
				coffeMachine.actual_state = 3;
				coffeMachine.EmptyingSys.power = true;
				coffeMachine.tm(10);
				coffeMachine.EmptyingSys.power = false;


			// Cleaning variables (symulation )
				
				coffeMachine.waterTemp.sig = 21;
				coffeMachine.waterPressure.sig = 0;
				coffeMachine.waterIntake.sig = 0;
				coffeMachine.milkTemp.sig = 8;
	}

	
}