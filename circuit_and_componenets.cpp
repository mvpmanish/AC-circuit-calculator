#include "circuit_and_components.h"

//------------------------------------------------LONGER FUNCTION DEFINITIONS-------------------------------------------------
//Function to print the schematic of a resistor
void resistor::printcomponentschematic() const{
	if (config == 's'){ //in series
		cout << "|                 |" << endl
			 << "|                 /" << endl
			 << "|                \\" << endl //Double backslash because the first / is ignored
			 << "|                 / R=" << R << endl
			 << "|                \\" << endl
			 << "|                 |" << endl;
	}

	if (config == 'p'){ //in parallel
		cout << "|   R=" << R << "   |" << endl
			 << "|                 |" << endl
			 << "|-----\\/\\/\\-------|" << endl
			 << "|                 |" << endl;
	}
}

//Function to print the schematic of a capacitor
void capacitor::printcomponentschematic() const{
	if (config == 's'){ //in series
		cout << "|                 |" << endl
			 << "|                _|_" << endl
			 << "|                _ _ C=" << C << endl
			 << "|                 |" << endl;
	}

	if (config == 'p'){ //in parallel
		cout << "|   C=" << C << "   |" << endl
			 << "|                 |" << endl
			 << "|------|  |-------|" << endl
			 << "|                 |" << endl;
	}
}

//Function to print the schematic of a inductor
void inductor::printcomponentschematic() const{
	if (config == 's'){ //in series
		cout << "|                 |" << endl
			 << "|                 &" << endl
			 << "|                 &  L=" << L << endl
			 << "|                 &" << endl
			 << "|                 |" << endl;
	}

	if (config == 'p'){ //in parallel
		cout << "|   L=" << L << "   |" << endl
			 << "|                 |" << endl
			 << "|------&&&&-------|" << endl
			 << "|                 |" << endl;
	}
}

//Copy constructor for circuit class (deep copy)
circuit:: circuit(circuit &circ){ 
	name = circ.name; //Copy name
	impedance = circ.impedance; //Copy impedance
	for (auto it = circ.circuitcomponents.begin(); it < circ.circuitcomponents.end(); it++){ //For each element in vector
		circuitcomponents.push_back((*it)->clone()); //Copy a clone of the unique pointer to a component
	}
}

//Function to clear a circuit
void circuit::clear(){ 
	name.clear();
	impedance = 0;
	circuitcomponents.clear();
}

//Function to print a schmatic of the circuit to the screen
void circuit::printcircuitschematic() const{
	cout.precision(2);
	cout.setf(ios::scientific); //Set the output to scientific notation
	
	cout << endl << "+-------{~}-------+" << endl
		 << "|                 |" << endl;
	for (auto it = circuitcomponents.begin(); it < circuitcomponents.end(); it++){ //Print circuit componenets schematics
		(*it)->printcomponentschematic();
	}
	cout << "+-----------------+" << endl;

	cout.precision(6); //Reset the iostream
	cout.unsetf(ios::scientific);
}
//Function to add an impedance and calculate total impedance of circuit z_tot = z1*z2/(z1+z2) for parallel or z_tot=z1+z2 for series
void circuit::addcomponent(component_ptr &comp){
	
	if (comp->getconfig() == 's'){ //If component added in series
		impedance += comp->z();
	}
	if (comp->getconfig() == 'p'){ //If component added in parallel
		dcomplex outputimp;
		outputimp = (impedance*comp->z()) / (impedance + comp->z());
		impedance = outputimp;
	}

	circuitcomponents.push_back(comp->clone()); //Circuit now has a clone of the library component
}

//Function to print the properties of a circuit
void circuit::printcircuitvalues() const{
	cout << "[Impedance magnitude = " << impedancemag() << " Ohms, Phase angle = " << impedancephase()*(180/pi) << " degrees]:" << endl; //Print impedance
	
	for (auto it = circuitcomponents.begin(); it < circuitcomponents.end(); it++){ //Print circuit componenets
		(*it)->printvalue();
		cout << ", |Z| = " << abs((*it)->z()) << " Ohms & arg(Z) = " << arg((*it)->z())*(180 / pi) << " degrees,"; //Print the component's magnitude of impedance and phase shift 

		if ((*it)->getconfig() == 's'){ cout << " in series. " << endl; }
		if ((*it)->getconfig() == 'p'){ cout << " in parallel. " << endl; }

	}
}

