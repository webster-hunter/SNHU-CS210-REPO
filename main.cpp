#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Python.h"
#include <Windows.h>
#include <cmath>
using namespace std;


void CallProcedure(string pyFunction) {
	PyObject* pName, * pModule, * pFunc, * pValue;
	const char* f = pyFunction.c_str();

	Py_Initialize();
	pName = PyUnicode_FromString("py_source"); // Create testFile.py as PyObject.
	pModule = PyImport_Import(pName); // Import the created PyObject pName.
	pFunc = PyObject_GetAttrString(pModule, f); // Pass test_func, a function to be executed, to PyObject.
	pValue = PyObject_CallObject(pFunc, NULL); // Execute by passing parameters to pFunc. This is the case when the current parameter is NULL.
	Py_Finalize();
}

int menu() {
	system("cls");

	string input; // user input var
	int inputInt = -1; // used for comparison
	int i;

	// --------------- Menu Output ---------------//
	cout << "---------------------------------------\n"
		<< "               M E N U\n"
		<< "=======================================\n"
		<< "1. List of all items purchased.\n"
		<< "2. Find the quantity sold of a product.\n"
		<< "3. Histogram of all items sold.\n"
		<< "4. Exit\n\n";

	// --------------- Input / Validation ---------------//
	while (true) {
		cout << "Please select an option (1-4): ";
		try {
			cin >> input;

			// check for non-digit input
			for (i = 0; i < input.size(); ++i) {
				if (!isdigit(input.at(i))) {
					inputInt = -1;
					throw runtime_error("Non-Digit Input.");
				}
			}

			// check for valid numeric input
			inputInt = atoi(input.c_str());
			if (inputInt > 4 || inputInt < 1) {
				inputInt = -1;
				throw runtime_error("Input Must Be 1-4.");
			}
			else { // valid input
				system("cls");
				return inputInt;
			}
		}
		catch (runtime_error& exc) {
			cout << "ERROR: " << exc.what() << endl << endl;
		}
	}
}

// PURPOSE: Print text-based histogram
void histogram() {
	// open product frequency file
	ifstream productFrequency;
	productFrequency.open("frequency.dat");

	// verify that the file is open, return if not
	if (!productFrequency.is_open()) {
		cout << "ERROR: frequency.dat was not opened.";
		system("pause");
		return;
	}
	
	string line; // used to store lines from frequency.dat
	string item; // store name of item
	int count; // store item count
	stringstream ss; // store lines as string stream to be read from
	while (getline(productFrequency, line)) {
		ss << line; // line turned into ss
		ss >> item; // get item name
		ss >> count; // get item count

		// format output
		cout << setw(12)<< item << "| " << string(count, '*') << endl;
		ss.clear(); // clear ss
	}
}

// THIS FUNCTION WAS INTENDED TO BE USED TO ALLOW THE USER TO SLECT A FILE
/* 
string getDataFile() {
	string filename;
	bool goodFile = false;
	ifstream file;

	while (!goodFile) {
		cout << "Input Product Data Filename: ";
		cin >> filename;

		file.open(filename);

		if (file.is_open() && filename != "frequency.dat") {
			cout << "File found.\n\n";
			file.close();
			goodFile = true;
			return filename;
		}
		else {
			cout << "File not found.\n\n";
		}
	}
}
*/

int main() {
	int select = -1;
	//string filename = getDataFile();

	CallProcedure("write_frequency");

	// LOOP UNTIL EXIT IS SELECTED
	while (true) {
		select = menu();
		
		// SWITCH STATEMENT USED FOR MENU SELECTIONS
		switch (select) {
		case 1: 
			cout << "1. List of all items purchased.\n";
			CallProcedure("all_items");
			break;
		case 2:
			cout << "2. Find the quantity sold of a product.\n";
			CallProcedure("item_count");
			break;
		case 3:
			cout << "3. Histogram of all items sold.\n\n";
			histogram();
			break;
		case 4:
			return 0;
		default:
			cout << "An unexpected error has occurred.\n";
		}
		system("pause");
	}
}
