#include "menus_and_library.h"

//-----------------------------------------------------LIBRARY FUNCTIONS---------------------------------------------------------
//Function to print library of components
void printlib(vector<component_ptr> &library){
	if (library.empty()){ cout << endl << "Your library is empty!" << endl; }
	int counter{ 0 };
	cout << endl;
	for (auto it = library.begin(); it < library.end(); it++){
		counter++;
		cout << counter << ". ";
		(*it)->printvalue();
		cout << endl;
	}
}

//Function to print library of circuits
void printlib(vector<circuit_ptr> &library){
	if (library.empty()){ cout << endl << "You have no circuits saved!" << endl; }
	int counter{ 0 };
	cout << endl;
	for (auto it = library.begin(); it < library.end(); it++){
		counter++;
		cout << counter << ". [" << (*it)->getname() << "] :" << endl;
		(*it)->printcircuitvalues();
		(*it)->printcircuitschematic();
		cout << endl;
	}
}

//-----------------------------------------------------MENU FUNCTIONS---------------------------------------------------------
//Explain what the program is about to user
void welcomemessage(){
	cout << "Welcome! This is a program to calculate the impedance of an A.C circuit." << endl
		<< "You will add components to a library and use this library to build circuits." << endl
		<< "You can save created circuits and build a circuit library.\nLet's begin!" << endl;
}

//Main menu for program to give a choice to the user of what to do
void mainmenu(){
	while (true){ //Begin loop
		try{ //Check for valid input
			cout << endl << "\nEnter 'l' to access your library.\nEnter 'b' to build a circuit.\nEnter 'x' to exit the program.\n:";
			cin >> choice;
			if (choice != 'l' && choice != 'x' && choice != 'b'){ cin.clear(); cin.ignore(50, '\n'); throw choiceFlag; } //Throw erros
			if (choice == 'b' && componentlibrary.empty()){ cin.clear(); cin.ignore(50, '\n');  throw emptylibFlag; }
			break; //Exit loop if user enters input correctly
		}
		catch (int errorFlag){ //Catch errors
			if (errorFlag == choiceFlag){ cerr << endl << "Character must be the same as ones mentioned above! Error code " << choiceFlag; }
			if (errorFlag == emptylibFlag){ cerr << endl << "Your library is empty, add components to it! Error code " << emptylibFlag; }
		}
	}
}

//Library menu
void librarymenu(){
	while (true){ //Begin loop
		try{
			cout << "\nEnter 'a' to add a component to library.\nEnter 'p' to print a list of components in the library.\nEnter 'x' to exit the library.\nEnter 'c' to see circuits saved in the library\n:";
			choice = 0; //Reset choice character
			cin >> choice;
			if (choice != 'a' && choice != 'p' &&choice != 'x' &&choice != 'c') { cin.clear(); cin.ignore(50, '\n'); throw choiceFlag; } //Throw errors
		}
		catch (int errorFlag){ //Catch errors
			if (errorFlag == choiceFlag){ cerr << endl << "Character must be the same as ones mentioned above! Error code " << choiceFlag << endl; }
		}

		if (choice == 'x'){ break; } //Exit this while loop
		if (choice == 'p'){ printlib(componentlibrary); } //Print the library of components
		if (choice == 'c'){ printlib(circuitlibrary); } //Print the library of circuits


		if (choice == 'a'){ //Add a componenet
			while (true){ //Begin loop
				try{
					cout << "\nEnter 'r' to add a resistor.\nEnter 'c' to add a capacitor.\nEnter 'i' to add an inductor." <<
						endl << "Enter 'x' to go back to the library\n:";
					choice = 0; //Reset choice character
					cin >> choice;
					if (choice != 'r' && choice != 'c' && choice != 'i' && choice != 'x') { cin.clear(); cin.ignore(50, '\n'); throw choiceFlag; } //Throw errors
				}
				catch (int errorFlag){ //Catch errors
					if (errorFlag == choiceFlag){ cerr << endl << "Character must be the same as ones mentioned above! Error code " << choiceFlag << endl; }
				}

				if (choice == 'x'){ break; } //Exit this while loop
				if (choice == 'r'){
					while (true){ //Begin loop
						try{
							cout << "\nInput the resistance of the resistor in Ohms:";
							inputval = 0;
							cin >> inputval;
							if (cin.fail()){ cin.clear(); cin.ignore(50, '\n'); throw inputfailFlag; } //Throw errors
							break; //Exit loop if no errors flagged
						}
						catch (int errorFlag){
							if (errorFlag == inputfailFlag){ cerr << endl << "Bad input! check that input is a number. Error " << inputfailFlag << endl; }
						}
					}
					component_ptr temp_ptr(new resistor(inputval)); //Create new pointer to a resistor of inputval resistance
					componentlibrary.push_back(move(temp_ptr)); //Move pointer into library
				}
				if (choice == 'c'){
					while (true){ //Begin loop
						try{
							cout << "\nInput the capacitance of the capacitor in Farads:";
							inputval = 0;
							cin >> inputval;
							if (cin.fail()){ cin.clear(); cin.ignore(50, '\n'); throw inputfailFlag; } //Throw errors
							if (inputval <= 0){ cin.clear(); cin.ignore(50, '\n'); throw zeroerrorFlag; }
							break; //Exit loop if no errors flagged
						}
						catch (int errorFlag){
							if (errorFlag == inputfailFlag){ cerr << endl << "Bad input! check that input is a number. Error " << inputfailFlag << endl; }
							if (errorFlag == zeroerrorFlag){ cerr << endl << "Capacitance cannot be less than or equal to zero! Error " << zeroerrorFlag << endl; }
						}
					}
					component_ptr temp_ptr(new capacitor(inputval)); //Create new pointer to a capacitor
					componentlibrary.push_back(move(temp_ptr)); //Move pointer into library
				}
				if (choice == 'i'){
					while (true){ //Begin loop
						try{
							cout << "\nInput the inductance of the inductor in Henries:";
							inputval = 0;
							cin >> inputval;
							if (cin.fail()){ cin.clear(); cin.ignore(50, '\n'); throw inputfailFlag; } //Throw errors
							if (inputval < 0){ cin.clear(); cin.ignore(50, '\n'); throw zeroerrorFlag; }
							break; //Exit loop if no errors flagged
						}
						catch (int errorFlag){
							if (errorFlag == inputfailFlag){ cerr << endl << "Bad input! check that input is a number. Error " << inputfailFlag << endl; }
							if (errorFlag == zeroerrorFlag){ cerr << endl << "Inductance cannot be less than zero! Error " << zeroerrorFlag << endl; }
						}
					}
					component_ptr temp_ptr(new inductor(inputval)); //Create new pointer to a capacitor
					componentlibrary.push_back(move(temp_ptr)); //Move pointer into library
				}
			}
		}

	}
}

//Build circuit menu
void buildcircuitmenu(){
	//User inputs frequency of the circuit
	while (true){
		try{
			cout << endl << "Enter the driving frequency of the circuit in Hertz: ";
			cin >> freq;
			if (cin.fail()){ cin.clear(); cin.ignore(50, '\n'); throw inputfailFlag; } //Throw errors
			if (freq <= 0){ cin.clear(); cin.ignore(50, '\n'); throw zeroerrorFlag; }
			break;
		}
		catch (int errorFlag){ //Catch errors
			if (errorFlag == inputfailFlag){ cerr << endl << "Bad input! check that input is a number. Error " << inputfailFlag; }
			if (errorFlag == zeroerrorFlag){ cerr << endl << "Cannot have a frequency which is less than or equal to zero! Error " << zeroerrorFlag; }
		}
	}

	while (true){
		cout << "\nHere are a list of numbered components in your library:\n";
		printlib(componentlibrary); //Print library

		while (true){
			try{ //Check if input is valid
				cout << "\nEnter the number of the componenet you want to add to the circuit e.g. enter 2 if you want to add the second componenet on the list" <<
					endl << "Enter '0' if you want to stop adding components\n:";
				cin >> componentno; //User inputs components into circuit componenents vector
				if (cin.fail()){ cin.clear(); cin.ignore(50, '\n'); throw inputfailFlag; } //Throw errors
				if (componentno < 0){ cin.clear(); cin.ignore(50, '\n'); throw zeroerrorFlag; }
				if (componentno > static_cast<int>(componentlibrary.size())){ cin.clear(); cin.ignore(50, '\n'); throw outrangeFlag; } //size_t of library.size() does not match type int so must use static_cast 
				break;
			}
			catch (int errorFlag){ //Catch errors
				if (errorFlag == inputfailFlag){ cerr << endl << "Bad input! check that input is a number. Error " << inputfailFlag << endl; }
				if (errorFlag == zeroerrorFlag){ cerr << endl << "Cannot have a component number which is less than zero! Error " << zeroerrorFlag << endl; }
				if (errorFlag == outrangeFlag){ cerr << endl << "The component number must be on the list! Error " << outrangeFlag << endl; }
			}
		}

		if (componentno == 0){ //Ask user if they want to save the circuit
			if (circ.numberofcomponenets() > 0) {
				while (true){
					try{
						cout << "\nDo you want to save this circuit. y/n?";
						choice = 0;
						cin >> choice; //User enters whether component is added in series or parallel
						if (choice != 'y' && choice != 'n') { cin.clear(); cin.ignore(50, '\n'); throw choiceFlag; }
						break;
					}
					catch (int errorFlag){ //Catch errors
						if (errorFlag == choiceFlag){ cerr << endl << "You must enter 'y' or 'n'! Error code " << choiceFlag << endl; }
					}
				}

				if (choice == 'y'){
					string inputname; //Define a string to hold the name of the circuit
					cout << "\nEnter a name for your circuit:";
					cin.ignore();
					getline(cin, inputname);
					circ.setname(inputname); //Set the name of the circuit
					circuit_ptr temp_ptr(new circuit(circ)); //Create new pointer to a capacitor
					circuitlibrary.push_back(move(temp_ptr)); //Move pointer into library
					break;
				}

				if (choice == 'n'){ break; }
			}
		}

		while (true){
			try{ //Check for valid choice
				cout << "\nEnter 's' if you want to add the component in series.\nEnter 'p' if you want to add the component in parallel\n:";
				choice = 0;
				cin >> choice; //User enters whether component is added in series or parallel
				if (choice != 's' && choice != 'p') { cin.clear(); cin.ignore(50, '\n'); throw choiceFlag; }
				if (circ.numberofcomponenets() == 0 && choice == 'p'){ cin.clear(); cin.ignore(50, '\n'); throw noparallelFlag; }
				break;
			}
			catch (int errorFlag){ //Catch errors
				if (errorFlag == choiceFlag){ cerr << endl << "Character must be the same as ones mentioned above! Error code " << choiceFlag << endl; }
				if (errorFlag == noparallelFlag){ cerr << endl << "Cannot add the first component of a circuit in parallel! Error code " << noparallelFlag << endl; }
			}
		}

		componentlibrary[componentno - 1]->setfreq(freq); //Set the frequency of the component
		componentlibrary[componentno - 1]->setconfig(choice); //Set the component to add in series or parallel
		circ.addcomponent(componentlibrary[componentno - 1]); //Add the component to the circuit
		cout << "\nThe circuit has:\n";
		circ.printcircuitvalues(); //Print the circuit impedance
		circ.printcircuitschematic(); //Print a circuit schematic
	}
}
