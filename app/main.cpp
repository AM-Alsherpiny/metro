//-@am97elsh-//
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <fstream>
#include <string.h>

using namespace std;
///^_^__    -> AM_ELSHERPINY     __^_^///
///^_^__    -> Ebrahim_Mobark    __^_^///
///^_^__    -> Eslam_Omar        __^_^///

//--> proto_types <--//
//void refreach_all(string );
bool ensure(string value, bool searchOrUpdate);
int get_line(int num);
void display_all();
void get_way();
string get_file_name(int num);


//*end of proto_types*//

//--> calss station <--//
class station {
	private:
		int id;				//making id for any station consist of 3 digits
		string name;		//and for any changement consist of 5 digits
		string places[5];
	public:
	//--> constarctor <--//
		station(){
			id = 0;
			name  = "staion";
			places[0] = "null";
		}
	//*end of constractors*//

		
	//--> seters <--//
		void set_id(int x) {
			id = x;
		}
		void set_name(string a) {
			name = a;
		}
		void set_places(string b) {
			int count = 0;
			places[count++] = b;			
		}
	//*end of seters*//
		
	//--> geters <--//
		int get_id() {
			return id;	
		}
		
		string get_name() {
			return name;	
		}
		
		string get_places() {
			int count = 4;
			return places[count--];	
		}
	//*end of geters*//
	
	//--> display_line <--//	
	/// to display all data in a line 
		void display_line(string line_name) {
			ifstream objFile(line_name.c_str());
			
			while(objFile >> name >> id >> places[0] >> places[1] >> places[2]  >> places[3] >> places[4]) {
				cout << id << "     station name: " << name 
						   << "\n                  places: ";
				//-to avoid printing null place -//
				for(int i = 0; i < 5; i++) {
					if(places[i] == "null")		break;
					else {
						if(i != 0)
							cout << ", ";
						cout << places[i];
					} 	
				}
				cout << "\n";
			}
			objFile.close();
		}//*end of display_line function*//
		
		
	
	//--> search <--//	
	/// to search about station or place and get the full data of it
		void search() {
			string value;
			cout << "please enter station or place to search: ";
			cin >> value;
			int x = isExist(value);//to cheak if valid name or not in all files
			//cout << "that is the value of x = " << x << "\n"; 
			while(!x) {
				cout << "invalid station or place please retry :";
				cin >> value;
				x = isExist(value);
			}
			//-get the file name and open it then search in it-//
			string file_name = get_file_name(x);
			ifstream objFile(file_name.c_str());
			
			while(objFile >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4]) {	
				if(value == name || value == places[0] || value == places[1]
					|| value == places[2] || value == places[3] || value == places[4]) {
							
					cout << "station name: " << name << "\n		places: ";
					//-to avoid printing null places -//
					for(int i = 0; i < 5; i++) {
						if(places[i] == "null")		break;
						else {
							if(i != 0)
								cout << ", ";
							cout << places[i] ;
						} 	
					}
					cout << "\n";
				} 			
			}
			objFile.close();
		}//*end of search function*//		
		
	//--> add_places <--//	
	/// to add new places in station instead of null
		void add_places() {
			ifstream all("all_lines.txt");
			ofstream new_file("new.txt");
			
			string sta_name, new_place;
			
			cout << "please enter the name of the station to add place: ";
			cin >> sta_name;
			int x = isStation(sta_name);//to cheak if valid name or not
			while(!x) {
				cout << "invalid name please retry :";
				cin >> sta_name;
				x = isStation(sta_name);
			}
			
			//-to get the file name-//
			string file_name = get_file_name(x);
			ifstream s_file(file_name.c_str());
			
			// to write from the old to the new file
			while(s_file >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4]) {				
				if(sta_name == name) {
					new_file << name << "      " << id << "      ";					
					for(int i = 0; i < 5; i++) {
						if(places[i] == "null") {
							//-get the new place and write it-//
							cout << "please enter the name of the new place: ";
							cin >> new_place;
							new_file << new_place << "	";
							
							//-to set the other value with null-//
							for(int j = (i+1); j < 5; j++) {
								places[j] = "null";
								new_file << places[j] << "      ";
							}
							break; //to add one place	
						} else {
							if(i == 4) {
								cout << "\nSorry man,it's completly full.\n";
								cout << name << "	places: " << places[0] << ", " << places[1] 
									 << ",   " << places[2] << ",   " << places[3] << ", " << places[4] << "\n";
							} else {
								new_file << places[i] << "      ";								
							}							
						}
					}					
				} else {					
					new_file << name << "      " << id << "      " << places[0] << "      " << places[1] 
					<< "      " << places[2] << "      " << places[3] << "      " << places[4] << "\n";
				}
			}
			s_file.close();
			new_file.close();
			remove(file_name.c_str());
			rename("new.txt", file_name.c_str());
			refreach_all(file_name);					
		}//*end of add_places function*//
		
	//--> isExist <--//	
	/// to ensure if the entered value is a name of place or station
		int isExist(string value) {
			ifstream all("all_lines.txt");			
			while(all >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4])
				if(value == name || value == places[0] || value == places[1]
				|| value == places[2] || value == places[3] || value == places[4])
					return id;				
			return 0;			
		}//*end of isExist Function*//
		
	//--> isStation <--//	
	/// to ensure if the entered value is a name of station
		int isStation(string value) {
			ifstream sta_file("all_lines.txt");
			
			while(sta_file >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4])
				if(value == name )
					return id;
			return 0;
		}//*end of isStaion Function*//
		
	//--> get_id <--//	
	///return the id of a specific name
		int get_id(string value, string file) {
			ifstream line(file.c_str());
			
			while(line >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4])
				if(value == name || value == places[0] || value == places[1]
					|| value == places[2] || value == places[3] || value == places[4]) 
					return id;
			return 0;
		}//* end of get_id *//
		
	//--> get_name <--//	
	///return the name of a specific id
		string get_name(int wanted_id, string file_name) {
			ifstream wanted_file(file_name.c_str());
			string result;
			bool flag = false;

			while(wanted_file >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4]) {
				if(id == wanted_id) {
					flag = true;
					result = name;	
				}
			}
			if(!flag) {
				ifstream tahoila("tahoila.txt");
				int t_id;
				string t_name;
				
				while(tahoila >> t_id >> t_name)
					if(t_id == wanted_id)
						result = t_name;				
			}
			return result;				
		}//* end of get_name *//
		
	//--> print_atSameLine <--//
	/// take the currant and destination id and print between theme
		void print_atSameLine(int cur, int dest, string file_name) {
			ifstream line(file_name.c_str());
			
			//-if currant less than destination-//
			if(cur < dest) {
				//-to print the places between theme-//	
				int cont = 1;
				while(line >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4]) {
					if(id >= cur) {
						if(cont == 1)
							cout << "\nYour first station is : 01- "<< name << "\nThen:\n";
						else {
							cout << "     " ;
							if(cont < 10)
								cout << "0";
							cout << cont << "- " << name << "\n"; 
						}
						cont++;
					}
					if(id == dest) break;
				}
				cout << "\n";
			} else {
				string sta_name;
				int back_cont = 1;
				for(int i = cur; i >= dest; i--) {
					sta_name = get_name(i, file_name);
					if(back_cont == 1){
						cout << "\nYour first station is : 01- "<< sta_name << "\nThen:\n";	
					} else {
						cout << "     " ;
						if(back_cont < 10)
							cout << "0";
						cout << back_cont << "- " << sta_name << "\n"; 
					}
					if(i > 1000)	i /= 10; // to handel if there tahoila 
					back_cont++;
				}
				
			}
						
		}//* end of print_atSameLine *//	
		
		//--> refreach_all<--//
		///to rewrite the all_lines.txt file
		void refreach_all(string file_name) {
			ifstream all("all_lines.txt");
			ifstream updated(file_name.c_str());
			ofstream new_file("temp.txt");
			//station s1;
			
			int chk;
			if(file_name == "elmarg_line.txt")	chk = 1;
			else if(file_name == "shobra_line.txt")	chk = 2;
			else chk = 3;
			
			bool f = false;

			
			while(all >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4]) {
				if(get_line(id) == chk && f == false) {
					f = true;
					while(updated >> name >> id >> places[0] >> places[1] >> places[2] >> places[3] >> places[4]) {
						new_file << name << "      " << id << "      " << places[0] << "      " << places[1] 
							 << "      " << places[2] << "      " << places[3] << "      " << places[4] << "\n";
					}
				} else {
					new_file << name << "      " << id << "      " << places[0] << "      " << places[1] 
							 << "      " << places[2] << "      " << places[3] << "      " << places[4] << "\n";
				}
			}
			all.close();
			updated.close();
			new_file.close();
			
			remove("all_lines.txt");
			rename("temp.txt", "all_lines.txt");

		}
		
		
};  //-the end of the station class-//
//////////////////////////////////////////////



//--> main <--//
int main() {
	station objStation;
	cout<<"      ---___---___---___---___---___---___---___---___--"<<endl;
    cout<<"     |                                                  |"<<endl;
    cout<<"     |  HELLO           IS     	        PROGRAME        |"<<endl;
    cout<<"     |          THAT          A METRO    	        |"<<endl;
    cout<<"     |                                                  |"<<endl;
    cout<<"     |___---___---___---___---___---___---___---___---__|"<<endl<<endl<<endl;
    
    
	int choice;
    while(choice) {
		cout << "\n\nplease take your choice: \n";
		cout << "                        to display all press:           1\n";
		cout << "                        to search press:                2\n";
		cout << "                        to add a new place press:       3\n";
		cout << "                        to get your way press:          4\n";
		cout << "                        to exit press:                  0\n";
		cin >> choice;
		switch(choice) {
			case 1:
				display_all();
			break;
				
			case 2:
				objStation.search();
			break;
				
			case 3:
				objStation.add_places();	
			break;
			
			case 4:
				get_way();
			break;
			
			case 0:
				return 0;
			
			
			default: cout << "please enter a right choice: "; 
		}
		
	}
		
	return 0;
}

//--> get_way <--//	
///to let you know your destination
void get_way() {
	station station_1;
	string currant, destination;
	int isValid_1, isValid_2;
	
	cout << "please enter your currant place: ";		cin >> currant;
	isValid_1 = station_1.isExist(currant);
	while(!isValid_1) {
		cout << "Sorry, invalid name please retray: ";
		cin >> currant;
		isValid_1 = station_1.isExist(currant);
	}
		
	
	cout << "please enter your destination place: ";	cin >> destination;
	isValid_2 = station_1.isExist(destination);
	while(!isValid_2) {
		cout << "Sorry, invalid name please retray: ";
		cin >> destination;
		isValid_2 = station_1.isExist(destination);
	}
	
	//-opening files whiche contain destination and source -//
	string file_1, file_2;
	file_1 = get_file_name(isValid_1);
	file_2 = get_file_name(isValid_2);	
	ifstream cur_file(file_1.c_str());
	ifstream des_file(file_2.c_str());
	
	//-search to get ids-//
	int currant_id = station_1.get_id(currant, file_1);
	int destination_id = station_1.get_id(destination, file_2);
	int fnc = get_line(currant_id);
	int fnd = get_line(destination_id);
	//-print the stations between theme and handel the line name-//			
	if (fnc == fnd) {			
		if(fnc == 1) {
			if(currant_id < destination_id) { //-done-//
				cout << "Take Elmarg Helwan Metro line \n";
				station_1.print_atSameLine(currant_id, destination_id, file_1);
			}					
			else {
				cout << "Take Helwan Elmarg Metro line \n";	
				station_1.print_atSameLine(currant_id, destination_id, file_1);
			}
				
		} else if(fnc == 2) { //-done-//
			if(currant_id < destination_id) {
				cout << "Take Shobra Elmonib Metro line \n";
				station_1.print_atSameLine(currant_id, destination_id, file_1);
			} else {
				cout << "Take Elmonib Shobra Metro line \n";
				station_1.print_atSameLine(currant_id, destination_id, file_1);
			}
			
		} else {		//-done-//
			if(currant_id < destination_id) {						
				cout << "Take Cairo_airport Embaba Metro line \n";
				station_1.print_atSameLine(currant_id, destination_id, file_1);
				
			} else {						
				cout << "Take Embaba Cairo_airport Metro line \n";
				station_1.print_atSameLine(currant_id, destination_id, file_1);
				
			}
		}
	}
}//*end of get_way*//


//--> display_all <--//	
/// to display all data in all lines 
void display_all() {
	station obj_1;
	cout << "The first line is Elmarg Helwan line: \n";
	obj_1.display_line("elmarg_line.txt");
	cout << "==========================================================";

	//-add line 2 here-//
	cout << "\n\n";
	cout << "The second line is shobra elmonib line: \n";
	obj_1.display_line("shobra_line.txt");
	cout << "==========================================================";
	
	cout << "\n\n";
	cout << "The Third line is Cairo_Airport Embaba line: \n";
	obj_1.display_line("airport_line.txt");
	cout << "==========================================================";
}//*end of display_all function*//


/*//--> refreach <--//	
/// to delete the unupdated file and create a new one updated
void refreach(string file_name) {	
	remove(file_name.c_str());		//remove the airport_line file
	
	ofstream a_file(file_name.c_str());
	ifstream t_file("new.txt");
	
	string name;
	int id;
	string p[5];
	
	while(t_file >> name >> id >> p[0] >> p[1] >> p[2] >> p[3] >> p[4]) {				
		a_file << name << " 		     " << id << " 		     " << p[0] << "  		    " << p[1] 
			 << "     		 " << p[2] << "   		   " << p[3] << "   		   " << p[4] << "\n";
	}
	a_file.close();
	t_file.close();
	remove("new.txt");
}*/

//--> get_line <--//
int get_line(int num) {
	while(num >= 10) {
		num  /= 10;
	} 
	return num;
}

string get_file_name(int num) {
	int x = get_line(num);
	 
	if(x == 1)
		return "elmarg_line.txt";
	else if (x == 2)
		return "shobra_line.txt";
	else
		return "airport_line.txt";	 
}













