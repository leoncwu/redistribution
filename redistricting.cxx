#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <map>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using std :: cout;
using std :: endl;
using std :: cin;
using std :: setw;
using std :: left;
using std :: vector;
using std :: string;
using std :: to_string;
using std :: max_element;
using std :: distance;
using std :: map;
using std :: pair;
using std :: max;
using std :: min;

class Matrix_2D{
private:
  int rows, cols;
  vector<int> elements;
public:
  Matrix_2D(int rows, int cols) : rows(rows), cols(cols) {
    elements = vector<int>(rows*cols,0);
  }
  void set(int row, int col, int value){
    elements.at(row*cols+col) = value;
  }
  int get(int row, int col){
    return elements.at(row*cols+col);
  }
  void print(){
    for(int row = 0; row < rows; row++ ){
      for(int col = 0; col < cols; col++){
        cout << setw(15) << left << get(row, col);
      }
      cout << endl;
    }
  }
};

class Matrix_3D{
private:
  int rows, cols, slcs;
  vector<int> elements;
public:
  Matrix_3D(int rows, int cols, int slcs) : rows(rows), cols(cols), slcs(slcs) {
    elements = vector<int>(rows*cols*slcs,0);
  }
  void set(int row, int col, int slc, int value){
    elements.at(row*cols*slcs+col*slcs+slc) = value;
  }
  int get(int row, int col, int slc){
    return elements.at(row*cols*slcs+col*slcs+slc);
  }
  void print(){
    for(int slc = 0; slc < slcs; slc++){
      cout << setw(15) << left << get(rows-1, cols-1, slc);
    }
    cout << endl;
  }
};

class Voter{
private:
  int ID,party_affiliation;
public:
  Voter(){}
  Voter(int ID, int party_affiliation) : ID(ID),party_affiliation(party_affiliation) {}
  ~Voter(){}
  void set(int ID_in, int party_affiliation_in){
    ID = ID_in;
    party_affiliation = party_affiliation_in;
  }
  int get_affiliation(){
    return party_affiliation;
  }
  void set_affiliation(int aff){
    party_affiliation = aff;
  }
  string print(){
    if(party_affiliation == -1){
      return to_string(ID) +  ":-";
    } else if(party_affiliation == 1) {
      return to_string(ID) +  ":+";
    } else if(party_affiliation == 0) {
      return to_string(ID) +  ":undecided";
    } else {
      return "Illegal affiliation value: " + to_string(party_affiliation) + ". \nError in creating voter " + to_string(ID);
    }
  }
};

class District{
private:
  int major, minor;
  vector<Voter> voter_district;
public:
  District(Voter voter){
    voter_district = vector<Voter>(1,voter);
  }
  District(vector<Voter> voter_district) : voter_district(voter_district){
  }
  int size(){
    return voter_district.size();
  }
  void majority(){
    vector<int> affiliation_record(2,0);
    for(auto e : voter_district){
      if(e.get_affiliation() == -1){
        affiliation_record.at(0)+=1;
      }else if(e.get_affiliation() == 1){
        affiliation_record.at(1)+=1;
      }
    }
    if(affiliation_record.at(0) >affiliation_record.at(1)){
      major = -1;
      minor = 1;
    }else{
      major = 1;
      minor = -1;
    }
  }
  int lean(){
    majority();
    return major;
  }
  void add(Voter new_voter){
    voter_district.push_back(new_voter);
  }
  string print(){
    string info = "[";
    for(auto e : voter_district){
      info += e.print() + ", ";
    }
    info += "]";
    return info;
  }
};

class Districting{
private:
  int major, minor, max_minor_win=0;
  vector<District> all_districts;
public:
  Districting(){}
  Districting(vector<District> all_districts) : all_districts(all_districts) {}
  int size(){
    return all_districts.size();
  }
  int get_max_minor_win(){
    return max_minor_win;
  }
  void set_max_minor_win(int value){
    max_minor_win = value;
  }
  void majority(){
    vector<int> affiliation_record(2,0);
    for(auto e : all_districts){
      if(e.lean() == -1){
        affiliation_record.at(0)+=1;
      }else if(e.lean() == 1){
        affiliation_record.at(1)+=1;
      }
    }
    if(affiliation_record.at(0) >affiliation_record.at(1)){
      major = -1;
      minor = 1;
    }else{
      major = 1;
      minor = -1;
    }
  }
  int lean(){
    majority();
    return major;
  }
  Districting extend_with_new_district(Voter new_voter){
    District new_district(new_voter);
    all_districts.push_back(new_district);
    return all_districts;
  }
  Districting extend_last_district(Voter new_voter){
    int last_location = all_districts.size() - 1;
    all_districts.at(last_location).add(new_voter);
    return all_districts;
  }
  string print(){
    string info = "{";
    for(int indx = 0; indx < all_districts.size(); indx++ ){
      info += to_string(all_districts.at(indx).size()) + all_districts.at(indx).print() + ", ";
    }
    info += "}";
    return info;
  }
};

class Population{
private:
  int major, minor;
  vector<Voter> all_voters;
public:
  Population(){}
  Population(vector<Voter> all_voters) : all_voters(all_voters){}
  Population(string all_affiliation) {
    map<char, int> map_affil;
    map_affil.insert(pair <char, int> ('-', -1));
    map_affil.insert(pair <char, int> ('+', +1));
    all_voters = vector<Voter>(all_affiliation.size());
    for(int id = 0; id < all_affiliation.size(); id++){
      all_voters.at(id).set(id, map_affil.at(all_affiliation.at(id)));
    }
  }
  Population(int population_size,int majority,bool trace){
    all_voters = vector<Voter>(population_size);
    for(int id = 0; id < majority; id++){
      all_voters.at(id).set(id, 1);
    }
    for(int id = majority; id < all_voters.size(); id++){
      all_voters.at(id).set(id, -1);
    }
    if(trace){
      shuffle_all_voters();
    }
  }
  Voter get_voter(int indx){
    return all_voters.at(indx);
  }
  int size(){
    return all_voters.size();
  }
  void shuffle_all_voters(){
    int n = all_voters.size();
    if(n > 1){
      //size_t i;
      srand(time(NULL));
      for(int i = 0; i < n - 1; i++){
        size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
        int t = all_voters.at(j).get_affiliation();
        all_voters.at(j).set_affiliation(all_voters.at(i).get_affiliation());
        all_voters.at(i).set_affiliation(t);
      }
    }
  }
  void majority(){
    vector<int> affiliation_record(2,0);
    for(auto e : all_voters){
      if(e.get_affiliation() == -1){
        affiliation_record.at(0)+=1;
      }else if(e.get_affiliation() == 1){
        affiliation_record.at(1)+=1;
      }
    }
    if(affiliation_record.at(0) > affiliation_record.at(1)){
      major = -1;
      minor = 1;
    }else{
      major = 1;
      minor = -1;
    }
  }
  int lean(){
    majority();
    return major;
  }
  int num_minor_win_in(Population sub_population){
    if(sub_population.lean() == minor){
      return 1;
    }else{
      return 0;
    }
  }
  void add_voter(Voter new_voter){
    all_voters.push_back(new_voter);
  }
  Population sub(int begin_indx, int end_indx){
    Population subset;
    for(int indx = begin_indx; indx <= end_indx; indx++){
      subset.add_voter(all_voters.at(indx));
    }
    return subset;
  }
  Districting minority_rules(int ndistricts){
    Matrix_2D best_minor_win(ndistricts,all_voters.size());
    Matrix_3D partition(ndistricts,all_voters.size(),ndistricts);
    //Matrix_2D partition(ndistricts,all_voters.size());
    majority();
    for (int p = 0; p < all_voters.size(); p++){
      Population sub_population = sub(0,p);
      int num_minor_win = num_minor_win_in(sub_population);
      //cout << "District: " << sub_population.print() << ". minority wins: " << num_minor_win << endl;
      best_minor_win.set(0,p,num_minor_win);
    }
    for(int districting = 1; districting < ndistricts; districting++){
      //cout << "Number of districts: " << districting+1 << endl;
      for(int p = districting; p < all_voters.size(); p++){
        //cout << "Population size: " << p+1 << endl;
        for(int sub_districting = 0; sub_districting < p; sub_districting++){
          Population sub_population = sub(sub_districting+1,p);
          int num_minor_win = num_minor_win_in(sub_population);
          //int max_minor_win;
          if(best_minor_win.get(districting,p) < best_minor_win.get(districting-1,sub_districting)+num_minor_win){
//int max_minor_win = max(best_minor_win.get(districting,p),best_minor_win.get(districting-1,sub_districting)+num_minor_win);
            //max_minor_win = best_minor_win.get(districting-1,sub_districting)+num_minor_win;
            best_minor_win.set(districting,p,best_minor_win.get(districting-1,sub_districting)+num_minor_win);
            partition.set(districting,p,districting,sub_districting+1);
            for(int indx = districting-1; indx >= 0; indx--){
              partition.set(districting,p,indx,partition.get(districting-1,sub_districting,indx));
	    }
	  }//else{
	  //max_minor_win = best_minor_win.get(districting,p);
	  //}
          //cout << "District: " << sub_population.print() << ". minority wins: " << best_minor_win.get(districting,p) << endl;
          //best_minor_win.set(districting,p,max_minor_win);
        }
      }
    }
    //partition.print();
    Districting new_districting;
    new_districting.set_max_minor_win(best_minor_win.get(ndistricts-1,all_voters.size()-1));
    int districting=0;
    for(int p = 0; p < all_voters.size(); p++){
      if(p == partition.get(ndistricts-1,all_voters.size()-1,districting)){
        districting++;
        districting = min(districting, ndistricts-1);
        new_districting.extend_with_new_district(get_voter(p));
      }else{
        new_districting.extend_last_district(get_voter(p));
      }
    }
    return new_districting;
  }
  string print(){
    string info = "[";
    for(auto e : all_voters){
      info += e.print() + ", ";
    }
    info += "]";
    return info;
  }
};

int main(){

  /* Exercise 43.1 */
  cout << "Voter 4 is zero:" << endl;
  Voter nr4(4,0);
  cout << nr4.print() << endl;

  cout << "Voter 5 is positive:" << endl;
  Voter nr5(5,+1);
  cout << nr5.print() << endl;

  cout << "Voter 6 is negative:" << endl;
  Voter nr6(6,-1);
  cout << nr6.print() << endl;

  cout << "Voter 7 is weird:" << endl;
  Voter nr7(7,3);
  cout << nr7.print() << endl;;

  /* Exercise 43.2 */
  cout << "Making district with one B voter" << endl;
  District eight(nr5);
  cout << ".. size: " << eight.size() << endl;
  cout << ".. lean: " << eight.lean() << endl;

  cout << "Making district ABA" << endl;
  District nine( vector<Voter>{ Voter(1,-1),Voter(2,+1),Voter(3,-1) } );
  cout << ".. size: " << nine.size() << endl;
  nine.lean();
  cout << ".. lean: " << nine.lean() << endl;
  cout << "Check all voters in the district: \n" << nine.print() << endl;

  /* Exercies 43.3 */
  string pns( "-++--" );
  Population some(pns);
  cout << "Population from string " << pns << endl;
  cout << ".. size: " << some.size() << endl;
  cout << ".. lean: " << some.lean() << endl;
  cout << "Check all voters in the population: \n" << some.print() << endl;

  Population group=some.sub(1,3);
  cout << "sub population 1--3" << endl;
  cout << ".. size: " << group.size() << endl;
  cout << ".. lean: " << group.lean() << endl;
  cout << "Check all voters in the subset of population: \n" << group.print() << endl;

  /* Exercise 43.4 */
  cout << "Making single voter population B" << endl;
  Population people( vector<Voter>{ Voter(0,+1) } );
  cout << ".. size: " << people.size() << endl;
  cout << ".. lean: " << people.lean() << endl;

  Districting gerry;
  cout << "Start with empty districting:" << endl;
  cout << ".. number of districts: " << gerry.size() << endl;

  /* Exercise 43.5 */
  cout << "Add one D voter:" << endl;
  gerry = gerry.extend_with_new_district( people.get_voter(0) );
  cout << ".. number of districts: " << gerry.size() << endl;
  cout << ".. lean: " << gerry.lean() << endl;
  cout << "add R R:" << endl;
  gerry = gerry.extend_last_district( Voter(1,-1) );
  gerry = gerry.extend_last_district( Voter(2,-1) );
  cout << ".. number of districts: " << gerry.size() << endl; cout << ".. lean: " << gerry.lean() << endl;
  cout << "Add two D districts:" << endl;
  gerry = gerry.extend_with_new_district( Voter(3,+1) );
  gerry = gerry.extend_with_new_district( Voter(4,+1) );
  cout << ".. number of districts: " << gerry.size() << endl;
  cout << ".. lean: " << gerry.lean() << endl;
  cout << "Check all voters in all the districts: \n" << gerry.print() << endl;

  /* Exercise 43.6 */
  Population five("+++--");
  cout << "Redistricting population: " << endl
       << five.print() << endl;
  cout << ".. majority rule: " << five.lean() << endl;
  int ndistricts{3};
  auto gerry1 = five.minority_rules(ndistricts);
  cout << gerry1.print() << endl;
  cout << ".. minority rule: " << gerry1.lean() << endl;
  cout << ".. maximum number of minority districts: " << gerry1.get_max_minor_win() << endl;

  /* Exercise 43.7 */
  //Population test(20,15,false);
  //Population test("++++-+-+--");
  //cout << "Randomly generating population: " << endl;
  //cout << test.print() << endl;
  //ndistricts = 3;
  //auto gerry2 = test.minority_rules(ndistricts);
  //cout << gerry2.print() << endl;
  //cout << ".. minority rule: " << gerry2.lean() << endl;
  bool shuffle_on;
  cout << "Please input 1 for turning on shuffle and 0 for turning of shuffle" << endl;
  cin >> shuffle_on;
  int population_size = 100;
  int max_majority = 0, max_num_districts=0, max_num_minor_districts=0;
  string print_districts;
  for(int majority = population_size/2+1; majority < population_size; majority++){
    cout << "..Analyzing majority: " << majority << endl;
    Population test(population_size,majority,shuffle_on);
    bool minor_win = false;
    Districting gerry_record;
    for(int ndistrict = 1; ndistrict < population_size; ndistrict++){
      auto gerry2 = test.minority_rules(ndistrict);
      if(gerry2.lean() == -1 && gerry_record.get_max_minor_win() < gerry2.get_max_minor_win()){
        minor_win = true;
        gerry_record = gerry2;
      }
    }
    if(minor_win){
      max_majority = majority;
      max_num_districts = gerry_record.size();
      max_num_minor_districts = gerry_record.get_max_minor_win();
      print_districts = gerry_record.print();
    }
    //cout << "..number of districts: " << gerry_record.size() << " minority win: " << gerry_record.get_max_minor_win() << endl;
    //cout << gerry_record.print() << endl;
  }
  cout << print_districts << endl;
  cout << "..maximum number of majority is: " << max_majority << endl;
  cout << "..number of districts: " << max_num_districts << " and minority wins: " << max_num_minor_districts << endl;

  return 0;
}
