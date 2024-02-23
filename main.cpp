#include <iostream>
#include <fstream>
#include "library.h"
using namespace std;

int main() {
  //Declaring variables
  ifstream input_file;
  string file_name;
  Dance dances[10]; //to an array of struct objects
  string url; //to store url
  int size = 0; //size of struct array
  int option = 0;

  //Collects data.
  collect_all(dances, size);

  //Navigation Options
  do {
    do {
      cout << "How would you like to navigate? Enter a number 1-4.\n1: Display\n2: Sort\n3: Filter\n4: Analyze\n5: Remove\n6: Exit\n";
      cin >> option;
      cin.ignore();
      cout << endl;
      switch (option){
        case 1: //Display_all function
          display_all(dances, size);
          cout << endl;
          break;
        case 2: //Sorting data
          sort(dances, size);
          break;
        case 5: //Removing data
          remove(dances, size);
          cout << endl;
          display_all(dances, size);
          cout << endl;
          break;
        case 3: //Filtering data
          filter(dances, size);
          break;
        case 4: //Analysis of data
          analysis_display(dances);
          break;
        case 6: //Exit
          cout << "Thank you!";
          input_file.close();
          return 0;
      }
    } while(option >= 1 && option <= 6);
  } while(option < 1 || option > 6);
}