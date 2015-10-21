/* A patient information reccord system designed by yhalcyon */
/* The patient information includes the patient_id, gender, distance
 * to the hospital, and age. More information can be added.
 * The system includes the functions 'add', 'remove','get_distance'
 * and 'get_age'. It also seperetes the infomation of female 
 * patients and male patients, because some dieases are female 
 * specific and some diseases are male specific.
 */

#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

/*The PatientInfo class contains the information of a patient*/
class PatientInfo{ 
public:
  struct patientdata{
    int patientid;
    char gender;
    int age;
    double distance;
  };
  patientdata info;
};

/*
Define two types of multimaps:
the first type uses the patient_id as the key
the second type uses the distance as the key
*/
typedef multimap<int,PatientInfo::patientdata> ID_info;
typedef multimap<double,PatientInfo::patientdata> DIST_info;

/*
The PatientBook class contains the five functions corresponding 
to the 'add', 'modify', 'remove', 'get_distance' and 'get_age'
operations to the data
*/
class PatientBook{ 
  ID_info id_data;    //the map using patient_id as the key
  DIST_info dist_F;   //the map for the 'Female' patients
  DIST_info dist_M;   //the map for the 'Male' patients 
public:
  void add(int patient_id, char gender, double distance, int age);
  void modify(int patient_id, int new_age);
  void remove(int patient_id);
  double get_distance(char gender, int level);
  int get_age(char gender, int level);
};

/* 
the 'add' function:
Add an patient into the record
The information of the order includes:
1. patient_id, 2. gender, 3. distance, 4. age
*/
void PatientBook::add(int patient_id, char gender, double distance, int age){
  PatientInfo tmp;
  tmp.info.patientid = patient_id;
  tmp.info.gender = gender;
  tmp.info.distance = distance;
  tmp.info.age = age;
  id_data.insert(ID_info::value_type(patient_id,tmp.info));
  if(gender == 'F'){
    dist_F.insert(DIST_info::value_type(distance,tmp.info));
  }
  else if(gender == 'M'){
    dist_M.insert(DIST_info::value_type(distance,tmp.info));
  }
  else
    cerr<<"Invalid input!"<<endl;
}

/* 
the 'modify' function:
modify the age of an existing patient corresponding to
the patient_id to the new age
*/
void PatientBook::modify(int patient_id, int new_age){
      double distance;
      ID_info::iterator it;
      it = id_data.find(patient_id);
      (it->second).age = new_age;
      distance = (it->second).distance;

      if((it->second).gender == 'F'){
	pair<DIST_info::iterator, DIST_info::iterator> itrange;
	itrange = dist_F.equal_range(distance);
	for(DIST_info::iterator it2 = itrange.first; it2 != itrange.second; ++it2){
	  if((it2->second).patientid == patient_id) {
	    (it2->second).age = new_age;
	    break;
	  }
	}
      }
      else{
	pair<DIST_info::iterator, DIST_info::iterator> itrange;
	itrange = dist_M.equal_range(distance);
	for(DIST_info::iterator it2 = itrange.first; it2 != itrange.second; ++it2){
	  if((it2->second).patientid == patient_id) {
	    (it2->second).age = new_age;
	    break;
	  }
	}
      }
}

/* 
the 'remove' function:
delete the existing patient information from the 
record of the system according to the patient_id
*/
void PatientBook::remove(int patient_id){
  char gender;
  double distance;
  ID_info::iterator it;
  it = id_data.find(patient_id);
  if(it == id_data.end()){
    cerr << "error" << endl;
    return;
  }
  distance = (it->second).distance;
  gender = (it->second).gender;
  id_data.erase(it);
  if(gender == 'F'){
    pair<DIST_info::iterator, DIST_info::iterator> itrange;
    itrange = dist_F.equal_range(distance);
    for(DIST_info::iterator it2 = itrange.first; it2 != itrange.second; ++it2){
      if((it2->second).patientid == patient_id) {
	dist_F.erase(it2);
	break;
      }
    }
  }
  else{
    pair<DIST_info::iterator, DIST_info::iterator> itrange;
    itrange = dist_M.equal_range(distance);
    for(DIST_info::iterator it2 = itrange.first; it2 != itrange.second; ++it2){
      if((it2->second).patientid == patient_id) {
	dist_M.erase(it2);
	break;
      }
    }
  }
}

/*
Return the distance for the given gender of patient and level in the order book
*/
double PatientBook::get_distance(char gender, int level){
  DIST_info::iterator it1,it2;
  if(gender == 'F'){
    it1=dist_F.begin();
    double min;
    while(level>=1){
      min = it1->first;
      it2 = dist_F.upper_bound(min);
      if(level==1){
	  cout << it1->first << endl;
	  break;
      }
      else{
	it1 = it2;
	--level;
      }
    }
  }
  else{ // gender == 'M'
    it1=dist_M.begin();
    double min;
    while(level>=1){
      min = it1->first;
      it2 = dist_M.upper_bound(min);
      if(level==1){
	cout << it1->first << endl;
	break;
      }
      else{
	it1 = it2;
	--level;
      }
    }
  }
}

/*
Return the average age of all the patients in the level for 
the given gender of the patient reccord.
*/
int PatientBook::get_age(char gender, int level){
  DIST_info::iterator it1,it2;
  if(gender == 'F'){
    it1=dist_F.begin();
    double min;
    while(level>=1){
      min = it1->first;
      it2 = dist_F.lower_bound(min);
      if(level==1){
	int accumulate=0;
	int count = 0;
	for(DIST_info::iterator it=it1; it!= it2;++it){
	  accumulate += (it->second).age;
	  count++;
	}
	cout << accumulate/count << endl;
	break;
      }
      else{
	it1 = it2;
	--level;
      }
    }
  }
  else{ // gender == 'M'
    it1=dist_M.begin();
    double min;
    while(level>=1){
      min = it1->first;
      it2 = dist_M.upper_bound(min);
      if(level==1){
	int accumulate = 0;
	int count = 0;
	for(DIST_info::iterator it=it1; it!= it2;++it){
	  accumulate += (it->second).age;
	  count++;
	}
	cout << accumulate/count << endl;
	break;
      }
      else{
	it1 = it2;
	--level;
      }
    }
  }
}	


int main(){
  ifstream input;
  input.open("input.txt");
  string action;
  PatientBook mp;
  PatientInfo patient;
  while(input >> action){
    if(action == "add"){
      input >> patient.info.patientid >> patient.info.gender >> patient.info.distance >> patient.info.age;
      mp.add(patient.info.patientid,patient.info.gender,patient.info.distance,patient.info.age);	    
    }
    else if(action == "modify"){
      int id;
      int newage;
      input >> id >> newage;
      mp.modify(id,newage);
    }
    else if(action == "get"){
      string p_s; // distance or age;
      input >> p_s;
      if(p_s == "distance"){
	char f_m; // female or male
	int level;
	input >> f_m >> level; 
	mp.get_distance(f_m,level);
      }
      else{ // ps == "age"	  
	char f_m; // female or male
	int level;
	input >> f_m >> level; 
	mp.get_age(f_m,level);
      }
    }
    else if(action == "remove"){
      int id;
      input >> id;
      mp.remove(id);
    }
    else{
      throw "Action is invalide!";
    }
  }
  
  input.close();
  return 0;
}
