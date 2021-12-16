#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <stdio.h>


using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

//This function is responsible for finding the frequency of a specific item
void getFreq() {
	string userItem;
	cout << "Please enter the item you wish to search for.\n";
	cin >> userItem;
	//Call python function that does the brainwork
	callIntFunc("findItem", userItem);
	
	
	
}

//This function is responsible for creating the histograph, as well as calling the python script to create the DAT file
void histograph() {
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED);	CallProcedure("createDAT");
	ifstream inFS("frequency.dat");
	string workingStr;
	int workingInt;
	inFS >> workingStr;
	inFS >> workingInt;
	cout << endl;
	//Histograph printing
	while (!inFS.eof()) {
		
		cout << workingStr << " ";
		for (int i = 0; i < workingInt; i++) {
			cout << "*";
		}
		cout << endl;
		inFS >> workingStr;
		inFS >> workingInt;
	}
	inFS.close();
}


void makeSelection(int userInt) {
	//This switch statement makes our selection
	switch (userInt) {
		case 1:
			CallProcedure("allFrequency");
			break;
		case 2:
			getFreq();
			break;
		case 3:
			histograph();
			break;
		case 4:
			cout << "\nGoodbye.\n";
			break;
	}
}


int getInput() {
	int userInt;
	
	while (1) {
		if (cin >> userInt) {
			makeSelection(userInt);
			break;
		}
		else {
			//Verify a valid integer with user
			cout << "Please enter a valid integer" << endl;
			cin.clear();
			cin.ignore();
		}
	}



	return userInt;
}


int main()
{
	//Three Procedures that I was left by Prof
	//CallProcedure("printsomething");
	//cout << callIntFunc("PrintMe", "House") << endl;
	//cout << callIntFunc("SquareValue", 2);

	int userInt = -1;
	while (userInt != 4) {
		CallProcedure("printMenu");
		userInt = getInput();
		cout << "\n";

	}
	return 4;
}