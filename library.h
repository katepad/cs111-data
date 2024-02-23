#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Dance {
  int week_num;
  string week;
  string genre;
  string song;
  int scores[4];
};

void collect(ifstream& fin, Dance& d);
void collect_all(Dance d[], int& size);
void display_header();
void display_all(Dance d[], int size);
void sorting_genre(Dance d[], int size);
void sorting_songname(Dance d[], int size);
void sorting_week(Dance d[], int size);
void sort(Dance d[], int size);
void remove(Dance d[], int& size);
void filter_perfectscore(Dance d[], int size);
void filter_totalscore(Dance d[], int size);
void filter(Dance d[], int size);
int total_score_analysis(Dance d[], int answer);
double avg_score_analysis(Dance d[], int answer1, int answer2);
void analysis_display(Dance d[]);