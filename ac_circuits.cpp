//MANISH PATEL 
//Last date modified: 13/04/2016
//This is a program to compute the impedance of a.c circuits with any number of components connected in series or parallel

#include "menus_and_library.h"

int  zeroerrorFlag{ 1 }, inputfailFlag{ 2 }, choiceFlag{ 3 }, emptylibFlag{ 4 }, outrangeFlag{ 5 }, noparallelFlag{ 6 }; //Define error flags
vector<component_ptr> componentlibrary; //Create vector of component pointers to store components in library
vector<circuit_ptr> circuitlibrary; //Create a vector to store pointers to circuits
char choice{ 0 }; //Create choice charcater
double inputval{ 0 }, freq{ 0 }; //Define number to input value of components and frequency of circuit
int componentno; //Define component number to pick out components to add to the circuit
circuit circ; //Define circuit


//-----------------------------------------------MAIN FUNCTION----------------------------------------------

int main(){

	welcomemessage();

	while (true){ //While loop to run program again at the end (user can break loop)
		
		mainmenu();

		if (choice == 'x'){ exit(1); } //Exit program if user enters 'x' here 
		if (choice == 'l'){ librarymenu(); } //Access library 
		if (choice == 'b'){ //Build a circuit
			circ.clear(); //Reset impedance of circuit
			buildcircuitmenu();
			}
		}
}