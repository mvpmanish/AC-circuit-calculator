
#ifndef CIRCUIT_AND_COMPONENTS_H
#define CIRCUIT_AND_COMPONENTS_H

#include<iostream>
#include<vector>
#include<complex>
#include<memory>

using namespace std;

namespace complexnumbers{ //Define a namespace to hold definitions of numbers that are useful for using complex numbers
	const double pi{ 3.14159265359 }; //Define pi
	typedef complex<double> dcomplex; //Define a complex number type
	const dcomplex j(0, 1); //Define j as sqrt(-1)
}

using namespace complexnumbers;


//----------------------------------------------------------CLASSES------------------------------------------------------------

//Abstract base class for a component
class component{
protected:
	double w; //angular frequency of oscillations over component 
	char config; //Character to determine whether component is added in series 's' or parallel 'p' in a circuit
public:
	component(){} //Default constructor
	virtual ~component(){}
	
	void setfreq(double &freq) { w = 2 * pi*freq; }; //Function to set the angular freq
	void setconfig(char &c){config = c; } //Function to set whether component added in series or parallel to a circuit
	double getfreq() const { return w; } //Function to get the angular frequency
	char getconfig(){ return config; }

    //Virtual functions
	virtual dcomplex z() const = 0; //Function to return impedance
	virtual double magz() const = 0; //Function to return the magnitude of the phase difference
	virtual double phasediff() const = 0; //Function to return the phase difference
	virtual void printvalue() const = 0; //Function to print the value of the component e.g. resistance for a resisitor
	virtual void printcomponentschematic() const = 0; //Function to print the schematic of the component to the screen
	virtual unique_ptr<component> clone() const = 0; //Clone function to create a new object and a pointer to the new object
};

typedef unique_ptr<component> component_ptr; //Define a type: unique pointer to a component type

//Class for resistors
class resistor : public component{
private:
	double R; //Resistance
public:
	resistor() : R(0){} //Default constructor
	resistor(double Rin) : R(Rin){} //Parameterised constructor
	~resistor(){} //Destructor
	unique_ptr<component> clone() const{ return component_ptr(new resistor(*this)); } //Clone function to create a new object and a pointer to the new object

	//Access functions
	double resistance() const { return R; } //Function to return resistance
	dcomplex z() const { return R; }
	double magz() const { return R; }
	double phasediff() const { return 0; }
	void printvalue() const { cout << R << " Ohm Resistor"; }
	void printcomponentschematic() const;
	
};

//Class for capacitors
class capacitor : public component{
private:
	double C; //Capacitance
public:
	capacitor(){} //Default constructor, can't have zero capacitance
	capacitor(double Cin) : C(Cin){} //Parameterised constructor
	~capacitor(){} //Destructor
	unique_ptr<component> clone() const{ return component_ptr(new capacitor(*this)); } //Clone function

	//Access functions
	double capacitance() const { return C; } //Function to return capacitance
	dcomplex z() const { return (-j / (w*C)); }
	double magz() const { return abs(z()); }
	double phasediff() const { return arg(z()); }
	void printvalue() const { cout << C << " F Capacictor"; }
	void printcomponentschematic() const;
};

//Class for inductors
class inductor : public component{
private:
	double L; //Inductance
public:
	inductor() : L(0){} //Default constructor
	inductor(double Lin) : L(Lin){} //Parameterised constructor
	~inductor(){} //Destructor
	unique_ptr<component> clone() const{ return component_ptr(new inductor(*this)); } //Clone function


	//Access functions
	double inductance() const { return L; }
	dcomplex z() const { return j*w*L; }
	double magz() const { return abs(z()); }
	double phasediff() const { return arg(z()); }
	void printvalue() const { cout << L << " H Inductor"; }
	void printcomponentschematic() const;
};

//Class for a circuit
class circuit{
private:
	string name;
	dcomplex impedance; //Impedance of circuit
	vector<component_ptr> circuitcomponents; //Vector of component pointers
public:
	circuit() : impedance(0){}; //Default constructor
	circuit(string iname, dcomplex imp) : name(iname), impedance(imp){} //Paramterised constructor
	circuit(circuit &circ); //Copy constructor
	~circuit(){} //Destructor

	//Access function
	dcomplex getimpedance() const { return impedance; }
	double impedancemag() const { return abs(impedance); } //Returns magnitude of impedance of circuit
	double impedancephase() const { return arg(impedance); } //Returns phase difference of impedance of circuit
	int numberofcomponenets() { return circuitcomponents.size(); } //Returns number of components in circuit
	string getname() const { return name;} //Returns the name of the circuit
	void setname(string &iname){ name = iname; } //Sets the name of the circuit
	void clear(); //Clears the circuit
	void addcomponent(component_ptr &comp);//Function to add component to circuit
	void printcircuitvalues() const; //Function to print properties of the circuit
	void printcircuitschematic() const; //Function to print a schmatic of the circuit to the screen
};


#endif
