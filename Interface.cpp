#include "Classes.h"



using namespace std;





// additional cfunctions used in display()
void moveCursor(int row, int col) {
	cout << "\033[" << row << ";" << col << "H";
}



void setConsoleTextColor(int color) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}




void coffeDraw() {

	int initial_row =9;
	// Glasses drawing 
	for (int k_0 = 0; k_0 < 4; k_0++) {
		for (int k_1 = 0; k_1 < 3; k_1++) {
			moveCursor(initial_row + k_0, 4 + k_1 * 16);
			cout << "|      |";
		}
		cout << endl;
	}
	for (int k_1 = 0; k_1 < 3; k_1++) {
		moveCursor(initial_row + 4, 4 + k_1 * 16);
		cout << "````````";
	}

	// Coffe drawing
	for (int k_0 = 0; k_0 < 4; k_0++) {
		for (int k_1 = 0; k_1 < 3; k_1++) {
			moveCursor( initial_row + k_0, 5 + k_1 * 16);

			if (k_0 < 2) {
				switch (k_1) {
				case 0:
					setConsoleTextColor(0);
					break;
				case 1:
					setConsoleTextColor(0 * 16 + 6);
					break;

				case 2:
					setConsoleTextColor(15);
					break;

				default:
					setConsoleTextColor(15);
					break;
				}
			}
			else setConsoleTextColor(0 * 16 + 6);

			cout << "wwwwww";
		}
		cout << endl;
		setConsoleTextColor(7);
	}

}

int Interface::display(int actual_state, string choosen_drink,int timeMarker, int expectedFullTime, string communicat )
{
	// 
	moveCursor(0, 0);
	// Constant Heading

	cout << "-----------------------------------------------------------------------" << endl;  // line 1 

	cout << "                            Virtual Coffe Machine             " << endl;	// line 2 

	cout << "-----------------------------------------------------------------------" << endl;  // line 3 




    switch ( actual_state  ) {

    case 1:	// Case 1 -> making an order 
        
	cout << "Please, choose drink:          " << endl; // line 4
	//Espresso
	moveCursor(6, 0);
	cout << "1 - Esspresso";
	moveCursor(6, 19);
	cout << "2 - Americano ";
	moveCursor(6, 35);
	cout << "3 - Cappucino ";
	moveCursor(6, 52);
	cout << "Exit";
	moveCursor(6, 62);
	cout << "Cleaning";
	setConsoleTextColor(7);
	//out << "1 -> Espresso	2 -> Americano	3 -> Capuccino" << endl; //line 5
	coffeDraw(); //lines 6 - 9
	cout << endl;

        break;

	case 2: // Case 2 -> prepering Coffe
		cout << "***********************************************************************"<<endl; // line 4
		cout << "     Prepering for you:   " << choosen_drink << endl;
		cout << "***********************************************************************" << endl;
		cout << endl;
		for (int k = 0; k <= timeMarker ; k++) {
			setConsoleTextColor(0x20 | 0x0F);
			cout << " ";
		}
		for (int k = 0; k <= (expectedFullTime - timeMarker); k++) {
			setConsoleTextColor(0x70 | 0x0F);
			cout << " ";
		}
		setConsoleTextColor(0x00 | 0x0F);
		cout << endl;
		cout << "           "  << communicat << endl;


		cout << endl;
		

		break;


	case 3 : // Case 3 -> Coffe is ready 


		cout << endl << endl; // line 4,5
		moveCursor(6, 10);
		cout << communicat;
		cout << endl << endl << endl << endl ;
		// lines 10 and 11 here 
		setConsoleTextColor(8);
		cout << "                     _________" << endl;
		cout << "                     |       |" << endl;
		cout << "                     |       |" << endl;
		cout << "                     |_______|" << endl;
		cout << "                      |_____|" << endl;
		setConsoleTextColor(7);
			if (timeMarker % 2 == 0){
				moveCursor(8,23);
				cout << "(  ) ( ";
				moveCursor(9,23);
				cout << " )(   )";
			}
			else {
				moveCursor(8, 23);
				cout << " )(  ) ";
				moveCursor(9, 23);
				cout << "(  )( ";

			}
		


		break;


	case 4: // Case 4-> Empty tanks
		cout << endl << endl;
		setConsoleTextColor(4);
		cout << "!!!   Empty tank, please refill   !!!";
		setConsoleTextColor(7);
		break;

	case 5: // Case 5 - > Cleaning
		cout << endl << endl;
		
		setConsoleTextColor(4);
		cout << " cleaning procedure, please wait...";
		cout << endl << endl;
		for (int k = 0; k <= timeMarker; k++) {
			setConsoleTextColor(0x20 | 0x0F);
			cout << " ";
		}
		for (int k = 0; k <= (expectedFullTime - timeMarker); k++) {
			setConsoleTextColor(0x70 | 0x0F);
			cout << " ";
		}
		cout << endl;
		setConsoleTextColor(2);
		if (timeMarker >= (expectedFullTime)) cout << " cleaning procedure is done";
		setConsoleTextColor(7);
	
		break;
    default:
        
        break;



	

		return 0;
    }


}


void Interface:: simulationDisplay(bool grinder, bool loading, bool emptying, bool pressurePump, bool milkPump, bool waterIntake, bool heater, int pressureSens, int waterTempSens, int milkTempSens, int waterVolSens) {

	bool WorkinSys[7] = { grinder, loading, emptying, pressurePump, milkPump, waterIntake, heater };

	int Sensor[4] = { waterVolSens,pressureSens,waterTempSens,milkTempSens };

	moveCursor(20, 0); 
	cout << "Monitoring System:";
	moveCursor(21, 0);
	cout << "Working Systems:" << endl;
	cout << "Grinder:" << endl;
	cout << "Loading:" << endl;
	cout << "Emptying:" << endl;
	cout << "Pressure Pump:" << endl;
	cout << "Milk Pump:" << endl;
	cout << "Water Intake:" << endl;
	cout << "Heater:" << endl;
	
	for (int l = 0; l <= 4; l++) {
		moveCursor(21+l, 30);
		

		if (l == 0) cout << "Sensor State:" << endl;
		if (l == 1) cout << "Water intake [ml] :" << endl;
		if (l == 2) cout << "Water temperature [C]:" << endl;
		if (l == 3) cout << "Water pressure [bar] :" << endl;
		if (l == 4) cout << "Milk temp [C] :" << endl;

		
	}
	
	for (int k = 0; k <= 6; k++)
	{
		moveCursor(22 + k, 22);
		if (WorkinSys[k] == false) setConsoleTextColor(4);
		else setConsoleTextColor(2);
		cout << "O";

	}

	setConsoleTextColor(2);
	for (int k = 0; k <= 3; k++)
	{
		moveCursor(22 + k, 58);
		cout << Sensor[k];

	}

	setConsoleTextColor(7);
	moveCursor(11, 1);
}





int Interface::keyReader() {
	//keyReader ver1
	//int key = 0;
	//cout << "	enter your option: " << endl;
	//cin >> key;
	//cout << endl;
	//return key;


	//keyReader ver2 

	int keyReaded = 0;
	int key = 1;


	while (key != 13) {
		key = _getch();
		if (key == 224) {
			//moveCursor(6, 50);	cout << " wykryto strzalke w ";
			key = _getch();
			if (key == 75)
			{
				//cout << " lewo ";
				positionPointer--;
				if (positionPointer < 0)
				{
					positionPointer = 0;
				}
			}
			else if (key == 77)
			{
				//cout << " prawo ";
				positionPointer++;
				if (positionPointer > 4)
				{
					positionPointer = 4;
				}
			}

			moveCursor(6, 0);
			if (positionPointer == 0) setConsoleTextColor(0xF0);
			else setConsoleTextColor(0x07);
			cout << "1 - Esspresso";
			moveCursor(6, 19);
			if (positionPointer == 1) setConsoleTextColor(0xF0);
			else setConsoleTextColor(0x07);
			cout << "2 - Americano ";
			moveCursor(6, 35);
			if (positionPointer == 2) setConsoleTextColor(0xF0);
			else setConsoleTextColor(0x07);
			cout << "3 - Cappucino ";
			moveCursor(6, 52);
			if (positionPointer == 3) setConsoleTextColor(0xF0);
			else setConsoleTextColor(0x07);
			cout << "Exit";
			moveCursor(6, 62);
			if (positionPointer == 4) setConsoleTextColor(0xF0);
			else setConsoleTextColor(0x07);
			cout << "Cleaning";
		
		}



	}
	keyReaded = positionPointer;
	return keyReaded;
}
