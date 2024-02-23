#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "library.h"
using namespace std;

//collects all data
void collect(ifstream& fin, Dance& d) {
    fin >> d.week_num;
    fin.ignore();
    getline(fin, d.week, ',');
    getline(fin, d.genre, ',');
    getline(fin, d.song);
  
    for(int j = 0; j < 4; j++){
      fin >> d.scores[j];
      fin.ignore();
    }
}//End of collecting fucntion.


void collect_all(Dance d[], int& size) {
  ifstream input_file;
  string file_name;
  string url;
  do {
    cout << "What file would you like to open?\t";
    getline(cin, file_name);
    input_file.open(file_name);
    if (input_file.is_open() == false) {
      cout << file_name << " does not exist. Try again.\n";
    }
  } while(input_file.is_open() == false);

  cout << endl;

  //Takes out url.
  getline(input_file, url);

  //Collects data.
  while(!input_file.eof()){
    collect(input_file, d[size]);
    size++;
  }
}


//Displays header
void display_header(){
  const string header[4] = {"WEEK", "GENRE", "SONG", "SCORES"};
  
  for(int i = 0; i < 4; i++) {
    cout << left << setw(20) << header[i];
  }
  cout << endl;
} //End of displaying header function


//displays data.
void display_all(Dance d[], int size) {
  display_header();
  for(int i = 0; i < size; i++){
    cout << setw(2) << d[i].week_num << ": ";
    cout << setw(16) << d[i].week;
    cout << setw(20) << d[i].genre;
    cout << setw(20) << d[i].song;
    for(int j = 0; j < 4; j++) {
      cout << setw(5) << d[i].scores[j];
    }
    cout << endl;
  }
} //End of displaying function


//sorts by genre
void sorting_genre(Dance d[], int size){
  for(int j = 0; j < size - 1; j++){
    for (int i = size-1; i > 0; i--){
      if (d[i].genre < d[i-1].genre) {
        swap(d[i-1],d[i]);
      }
    }
  }
} //End of sorting genre fucntion.

//sorts by song name
void sorting_songname(Dance d[], int size){
  for(int j = 0; j < size - 1; j++){
    for (int i = size-1; i > 0; i--){
      if (d[i].song < d[i-1].song) {
        swap(d[i-1],d[i]);
      }
    }
  }
} //End of sorting song name fucntion.

//sorts by week
void sorting_week(Dance d[], int size){
  for(int j = 0; j < size - 1; j++){
    for (int i = size-1; i > 0; i--){
      if (d[i].week_num < d[i-1].week_num) {
        swap(d[i-1],d[i]);
      }
    }
  }
} //End of sorting week fucntion.


void sort(Dance d[], int size){
  int sort_option = 0;
  do {
    cout << "How would you like to sort? Enter a number 1-3.\n1: By Genre\n2: By Song\n3: By Week (Chronological)\n";
    cin >> sort_option;
    cin.ignore();
    cout << endl;
    switch (sort_option){
      case 1:
          //Sorting by genre
          sorting_genre(d, size);
          display_all(d, size);
          cout << endl;
        break;
      case 2:
          //Sorting by song
          sorting_songname(d, size);
          display_all(d, size);
          cout << endl;
        break;
      case 3:
          //Sorting by week
          sorting_week(d, size);
          display_all(d, size);
          cout << endl;
        break;
    }
  } while (sort_option < 1 || sort_option > 3);
}


//removing function
void remove(Dance d[], int& size){
  int to_remove;
  int pos = 0;
  bool is_found = false;

  do{
    cout << "Enter the week # (1-10) you would like to remove.\t";
    cin >> to_remove;
  } while(to_remove < 1 || to_remove > 10);
  
  for (int i = 0; i < size && is_found == false; i++){
    if (to_remove == d[i].week_num) {
      pos = i;
      is_found = true;
    } else {
      is_found = false;
    }
  }

  if (is_found == true){
    for (int i = pos; i < size - 1; i++){
      d[i] = d[i+1];
    }
    size--;
  } else {
    cout << "\nThat data has already been removed.\n";
  }
} //End of removing fucntion.


//Filtering by perfect score
void filter_perfectscore(Dance d[], int size){
  display_header();
  for (int i = 0; i < size; i++){
    if (d[i].scores[0] + d[i].scores[1] + d[i].scores[2] + d[i].scores[3] == 40) {
      cout << setw(2) << d[i].week_num << ": ";
      cout << setw(16) << d[i].week;
      cout << setw(20) << d[i].genre;
      cout << setw(20) << d[i].song;
      for(int n = 0; n < 4; n++) {
        cout << setw(5) << d[i].scores[n];
      }
      cout << endl;
    }
  }
  cout << endl;
} //End of filtering perfect scores.


//Filtering by total score
void filter_totalscore(Dance d[], int size){
  int score_range;
  do {
    cout << "Enter a number 29-40.\t";
    cin >> score_range;
  } while(score_range < 29 || score_range > 40);
  cout << "\nHere are the dances that got a total score of " << score_range << " and higher:\n";
  cout << endl;
  display_header();
  for (int i = 0; i < size; i++){
    if (d[i].scores[0] + d[i].scores[1] + d[i].scores[2] + d[i].scores[3] >= score_range) {
      cout << setw(2) << d[i].week_num << ": ";
      cout << setw(16) << d[i].week;
      cout << setw(20) << d[i].genre;
      cout << setw(20) << d[i].song;
      for(int n = 0; n < 4; n++) {
        cout << setw(5) << d[i].scores[n];
      }
      cout << endl;
    }
  }
  cout << endl;
} //End of filtering total scores.

//Whole filter function with navigation
void filter(Dance d[], int size){
  int filter_option = 0;
  do {
  cout << "How would you like to filter? Enter a number 1-2.\n1: By perfect scores\n2: By target score gap\n";
  cin >> filter_option;
  cin.ignore();
  cout << endl;
    switch (filter_option){
      case 1:
        //Filter by Perfect Score
        filter_perfectscore(d, size);
        break;
      case 2:
        //Filter by target score gap
        filter_totalscore(d, size);
      break;
    }
  } while (filter_option < 1 || filter_option > 2);
} //End of whole filter function

//Analysis 1
int total_score_analysis(Dance d[], int answer){
  int value = 0;
    for(int i = 0; i < 4; i++) {
      value += d[answer-1].scores[i];
    }
  return value;
}


//Analysis 2
double avg_score_analysis(Dance d[], int answer1, int answer2){
  double value = 0;
    for(int i = 0; i < 4; i++) {
      value += d[answer1-1].scores[i];
    }
    for(int i = 0; i < 4; i++) {
      value += d[answer2-1].scores[i];
    }
  value = double(value) / 2;
  return value;
}

void analysis_display(Dance d[]){
  int analysis_option = 0;
  int analysis1_answer;
  int analysis2_answer1;
  int analysis2_answer2;
  int analysis2_total;
    do {
    cout << "What would you like to analyze?\n1: Total score from one week.\n2: Average performance score from 2 different weeks.\n";
    cin >> analysis_option;
    cin.ignore();
    cout << endl;
    switch (analysis_option) {
      case 1: 
        do {
          cout << "Enter a number of the week 1-10:\t";
          cin >> analysis1_answer;
        } while(analysis1_answer < 1 || analysis1_answer > 10);
        cout << "The total score of week #" << analysis1_answer << " is " << total_score_analysis(d, analysis1_answer) << ".\n\n";
        break;
      case 2:
        do {
          cout << "Enter a number of the first week that you would like to compare a\nperformance average with:\t";
          cin >> analysis2_answer1;
        } while(analysis2_answer1 < 1 || analysis2_answer1 > 10);
        analysis2_total += analysis2_answer1;
  
        do {
          cout << "Enter another number of the second week that you would like to compare a\nperformance average with:\t";
          cin >> analysis2_answer2;
          if (analysis2_answer2 == analysis2_answer1){
            cout << "You already entered that week.\n";
          }
        } while((analysis2_answer2 < 1 || analysis2_answer2 > 10) || analysis2_answer2 == analysis2_answer1);
        analysis2_total += analysis2_answer2;
  
      cout << fixed << showpoint << setprecision(1);
      cout << "The average performance score between week #" << analysis2_answer1 << " and week #" << analysis2_answer2 << " is " << avg_score_analysis(d, analysis2_answer1, analysis2_answer2) << ".\n\n";
        break;
    }
  } while (analysis_option < 1 || analysis_option > 2);
}