#include "main.h"

#include <iostream>
#include <string>

using namespace std;

int main()
{
    cout << "--- STARTING SIMULATOR ---" << endl;
    cout << "\n";
    cout << "Please enter string to transmit: ";
    
    string s;
    getline(cin, s);

    cout << "Input string: " << s << endl;
    cout << "\n--- RUNNING THE SIMULATOR ---\n" << endl;
    /* 
       Core() here 
    */

    cout << "Output string: "; // + output string right her

    cout << "\n--- COMPARE TWO STRINGS ---" << endl;
    // cout << result << endl;
    
    cout << "\nConclusion: " << " ---" << endl; // add conclusion here
    cout << "\n--- FINISHING SIMULATOR ---" << endl;
    // cout << "Hello world" << endl;
	return 0;
}
