#ifndef MENUS_AND_LIBRARY_H
#define MENUS_AND_LIBRARY_H

#include "circuit_and_components.h"

//-----------------------------------------------------DEFINITIONS------------------------------------------------------------

typedef unique_ptr<circuit> circuit_ptr; //Define a type: unique pointer to a circuit
extern int zeroerrorFlag, inputfailFlag, choiceFlag, emptylibFlag, outrangeFlag, noparallelFlag; //Define error flags
extern vector<component_ptr> componentlibrary; //Create vector of component pointers to store components in library
extern vector<circuit_ptr> circuitlibrary; //Create a vector to store pointers to circuits
extern char choice; //Create choice charcater
extern double inputval, freq; //Define number to input value of components and frequency of circuit
extern int componentno; //Define component number to pick out components to add to the circuit
extern circuit circ; //Define circuit


//-----------------------------------------------------LIBRARY FUNCTIONS---------------------------------------------------------
void printlib(vector<component_ptr> &library);
void printlib(vector<circuit_ptr> &library);


//-----------------------------------------------------MENU FUNCTIONS---------------------------------------------------------
void welcomemessage();
void mainmenu();
void librarymenu();
void buildcircuitmenu();
#endif
