/************************************************
 * Michael samatas
 * two .cpp File
 ************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <cmath>
#include <fstream>
#include <iomanip>
#include "two.h"
#include "table.h"

// making the original table size 10 and a veruble size 10
Two::Two() : hashMap(10), size(10), head(NULL), tail(NULL) {}


Two::~Two(){
	for (Node* current = head; current != nullptr;) {
		Node* Next = current->Next;
		delete current;
		current = Next;
	}

}

//compairs the argument to the data that is already in the hash table
bool Two::Entry::operator == (const vector<string>& vec) const {
	return (vec[0] == "*" || vec[0] == replan_id) && (vec[1] == "*" || vec[1] == geo_name) && (vec[2] == "*" || vec[2] == geo_stusab) && (vec[3] == "*" || vec[3] == geo_sumlev) && (vec[4] == "*" || vec[4] == geo_state) && (vec[5] == "*" || vec[5] == geo_county) && (vec[6] == "*" || vec[6] == geo_geoid) && (vec[7] == "*" || vec[7] == population);
}

// comparing data for the update function
bool Two::Entry::operator == (Entry const &obj) const {
	if(replan_id == obj.replan_id && geo_name == obj.geo_name && geo_stusab == obj.geo_stusab && geo_sumlev == obj.geo_sumlev && geo_state == obj.geo_state && geo_county == obj.geo_county && geo_geoid == obj.geo_geoid && population == obj.population){
		return 1;
	}
	else{
		return 0;
	}
}

// hashing functuon 
int Two::hashf(string key){
	int pos = atoi(key.c_str());
	pos = pos * pos;
	string spos = to_string(pos);
	string mpos = spos.substr(spos.size()/2, 2);
	int passer = (atoi(mpos.c_str()));
	passer = passer % size;
	//cout << passer << " " << endl;
	return passer;
}

// transfers data from the argument to the hashing table
void Two::Entry::GetEntry(vector<string> args){
	replan_id = args[0];
	geo_name = args[1];
	geo_stusab = args[2];
	geo_sumlev = args[3];
	geo_state = args[4];
	geo_county = args[5];
	geo_geoid = args[6];
	population = args[7];
	isEmpty = false;
}

//printing function
void Two::print(int pos){
	cout << hashMap[pos].replan_id << ", " << hashMap[pos].geo_name << ", " << hashMap[pos].geo_stusab << ", " << hashMap[pos].geo_sumlev << ", " << hashMap[pos].geo_state << ", " << hashMap[pos].geo_county << ", " << hashMap[pos].geo_geoid << ", " << hashMap[pos].population;
}

// printing function
void Two::print(vector<string> args){
	for(int i = 0; i < args.size(); i++){
		if(i < args.size() - 1){
			cout << args[i] << ", ";
		}
		else{
			cout << args[i];
		}
	}
}

vector<Two::Entry> Two::rSelect(vector<string> args) {
	vector<Entry> result;
        int probed = 0;
        int prob = 0;
        bool matched = false;

        if(args[0] == "*"){// if there is not key
                Node *temp = head;
                while(temp != NULL){//search by the link llist
                        if((args[0] == temp->entry->replan_id || args[0] == "*") && (args[1] == temp->entry->geo_name || args[1] == "*") && (args[2] == temp->entry->geo_stusab || args[2] == "*") && (args[3] == temp->entry->geo_sumlev || args[3] == "*") && (args[4] == temp->entry->geo_state || args[4] == "*") && (args[5] == temp->entry->geo_county || args[5] == "*") && (args[6] == temp->entry->geo_geoid || args[6] == "*") && (args[7] == temp->entry->population || args[7] == "*")){

                        cout << "Found (";//cout selected data from the link list
                        cout << temp->entry->replan_id << ", " <<  temp->entry->geo_name << ", " << temp->entry->geo_stusab << ", " <<  temp->entry->geo_sumlev << ", " << temp->entry->geo_state << ", " << temp->entry->geo_county << ", " << temp->entry->geo_geoid << ", " << temp->entry->population;
                        cout << ") in geography" << endl;
                        matched = true;
			result.push_back(*temp->entry);//push the data into a vector fo the bonus

                        }
                        temp=temp->Next;
                }
        }
        else{// if there is a key then we can use the hash function
                int hash = hashf(args[0]);
                int pos = hash;
                while(probed < size){// if there is room in the table
                        if(args[0] == hashMap[pos].replan_id){// see if the keys match
                                cout << "Found (";
                                print(args);
                                cout << ") in geography" << endl;
                                matched = true;
				result.push_back(hashMap[pos]);
                                return result;
                        }
                        probed++;// if not go to the next position
                        pos = (hash + (probed * 2) + ((probed * probed)*3)) % size;//quadratic collision stratigy
                }
        }
                // if the selected data is not found print an error
        if(matched == false){
                        cout << "No entries match query (";
                        cout << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ", " << args[4] << ", " << args[5] << ", " << args[6] << ", " << args[7];
                        cout << ") in geography" << endl;
        }
	return result;
}

void Two::insert(vector<string> args){
	int probed = 0;
	int hash = hashf(args[0]);
	int pos = hash;
	int prob = 0;

	while(probed < size){// loop while there is room in the table
		if(hashMap[pos].isEmpty){// if the space is empty insert in the data in to hash table
			hashMap[pos].GetEntry(args);
			cout << "Inserted (";
			print(pos);
			cout << ") into geography" << endl;

			Node *temp = new Node;//insert data into link list
			temp->entry = &hashMap[pos];
			temp->Next = NULL;
			if(head==NULL && tail == NULL)
			{
				head = temp;
				tail = temp;
			}
			else {
				tail->Next = temp;
				tail = temp;
			}
			return;
		}
		else if (args[0] == hashMap[pos].replan_id){// if the spot is not empty cheach if its already in the table
			cout << "Failed to insert (";
			print(args);
			cout << ") into geography" << endl;
			return;
		}
		//else use quadratic colishion stratigy and then try agian in the ned posotion
		probed++;
		pos = (hash + (probed * 2) + ((probed * probed)*3)) % size;//quadratic collision stratigy
	}
	//if we run out of space in the table we bouble the size of the table
	size = size *2;
	vector<Entry> hashArray(size);
	for(int i = 0; i < size/2; i++){
		if (!hashMap[i].isEmpty) {
			int hold = hashf(hashMap[i].replan_id);
			hashArray[hold].replan_id = hashMap[i].replan_id;
			hashArray[hold].geo_name = hashMap[i].geo_name;
			hashArray[hold].geo_stusab = hashMap[i].geo_stusab;
			hashArray[hold].geo_sumlev = hashMap[i].geo_sumlev;
			hashArray[hold].geo_state = hashMap[i].geo_state;
			hashArray[hold].geo_county = hashMap[i].geo_county;
			hashArray[hold].geo_geoid = hashMap[i].geo_geoid;
			hashArray[hold].population = hashMap[i].population;
			hashArray[hold].isEmpty = false;
		}
	}
	hashMap = hashArray;
	insert(args);
	return;
}

void Two::update(vector<string> args){
	int probed = 0;
	int hash = hashf(args[0]);
	int pos = hash;
	int prob = 0;

	while(probed < size){// while there is room in the table 
		if(args[0] == hashMap[pos].replan_id){// cheack if the key in the argument maces any key in the table
			hashMap[pos].GetEntry(args);// updata the data in the table

			cout << "Updated (";
			print(pos);
			cout << ") in geography" << endl;
			return;
		}
		probed++;//check the next position for the selected data
		pos = (hash + (probed * 2) + ((probed * probed)*3)) % size;
	}
	// if not fount the print an error
	cout << "Failed to update (";
	cout << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ", " << args[4] << ", " << args[5] << ", " << args[6] << ", " << args[7];
	cout << ") in geography" << endl;
}

void Two::select(vector<string> args){
	vector<Entry> temp = rSelect(args);
/*	int probed = 0;
	int prob = 0;
	bool matched = false;

	if(args[0] == "*"){
		Node *temp = head;
		while(temp != NULL){
			if((args[0] == temp->entry->replan_id || args[0] == "*") && (args[1] == temp->entry->geo_name || args[1] == "*") && (args[2] == temp->entry->geo_stusab || args[2] == "*") && (args[3] == temp->entry->geo_sumlev || args[3] == "*") && (args[4] == temp->entry->geo_state || args[4] == "*") && (args[5] == temp->entry->geo_county || args[5] == "*") && (args[6] == temp->entry->geo_geoid || args[6] == "*") && (args[7] == temp->entry->population || args[7] == "*")){

			cout << "Found (";
			cout << temp->entry->replan_id << ", " <<  temp->entry->geo_name << ", " << temp->entry->geo_stusab << ", " <<  temp->entry->geo_sumlev << ", " << temp->entry->geo_state << ", " << temp->entry->geo_county << ", " << temp->entry->geo_geoid << ", " << temp->entry->population;
			cout << ") in geography" << endl;
			matched = true;
			}
			temp=temp->Next;
		}
	}
	else{// if there is a key then we can use the hash function 
		int hash = hashf(args[0]);
		int pos = hash;
		while(probed < size){// if there is room in the table
			if(args[0] == hashMap[pos].replan_id){// see if the keys match
				cout << "Found (";
				print(args);
				cout << ") in geography" << endl;
				matched = true;
				return;
			}
			probed++;// if not go to the next position
			pos = (hash + (probed * 2) + ((probed * probed)*3)) % size;
		}
	}
		// if the selected data is not found print an error
	if(matched == false){
			cout << "No entries match query";
			cout << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ", " << args[4] << ", " << args[5] << ", " << args[6] << ", " << args[7];
			cout << ") in geography" << endl;
	}*/
}

void Two::del(vector<string> args){
	int probed = 0;
	int prob = 0;
	bool matched = false;

	Node *temp = head;
	Node *befor_del;
	befor_del = NULL;

	while(temp != NULL){//
		if((args[0] == temp->entry->replan_id || args[0] == "*") && (args[1] == temp->entry->geo_name || args[1] == "*") && (args[2] == temp->entry->geo_stusab || args[2] == "*") && (args[3] == temp->entry->geo_sumlev || args[3] == "*") && (args[4] == temp->entry->geo_state || args[4] == "*") && (args[5] == temp->entry->geo_county || args[5] == "*") && (args[6] == temp->entry->geo_geoid || args[6] == "*") && (args[7] == temp->entry->population || args[7] == "*")){
			cout << "Deleted (";
			cout << temp->entry->replan_id << ", " <<  temp->entry->geo_name << ", " << temp->entry->geo_stusab << ", " <<  temp->entry->geo_sumlev << ", " << temp->entry->geo_state << ", " << temp->entry->geo_county << ", " << temp->entry->geo_geoid << ", " << temp->entry->population;
			cout << ") in geography" << endl;
			matched = true;
			temp->entry->isEmpty = true;

			if(temp == head && temp == tail){
				temp->entry->isEmpty = true;
				delete temp;
				head = NULL;
				tail = NULL;
				break;
			}
			else if(temp == head){
				temp->entry->isEmpty = true;
				befor_del = temp;
                                temp = temp->Next;
                                delete befor_del;
                                head = temp;
			}
			else if(temp == tail){
				temp->entry->isEmpty = true;
				tail = befor_del;
				befor_del->Next = NULL;
				delete temp;
				break;
			}
			else{
				temp->entry->isEmpty = true;
				befor_del->Next = temp->Next;
				delete temp;
				temp = befor_del->Next;
			}
		}
		else{
			befor_del = temp;
			temp=temp->Next;
		}	
	}
	if(matched == false){
        	cout << "Failed to delete (";
                cout << args[0] << ", " << args[1] << ", " << args[2] << ", " << args[3] << ", " << args[4] << ", " << args[5] << ", " << args[6] << ", " << args[7];
                cout << ") in geography" << endl;
        }
}

void Two::display(){
	Node *temp = head;
	Node *hold = NULL;

	if(head == nullptr)
		return;

	cout << "replan_id geo_name                                     geo_stusab geo_sumlev geo_state geo_county geo_geoid    population" << endl;
	for(Node* temp = head; temp != nullptr; temp = temp->Next){// loop throught the table
		//if(hashMap[i].empty()){//if there is data in the position of the vector
			cout << left << setw(10) << temp->entry->replan_id;//print out the data
			cout << left << setw(45) << temp->entry->geo_name;
			cout << left << setw(11) << temp->entry->geo_stusab;
			cout << left << setw(11) << temp->entry->geo_sumlev;
			cout << left << setw(10) << temp->entry->geo_state;
			cout << left << setw(11) << temp->entry->geo_county;
			cout << left << setw(13) << temp->entry->geo_geoid;
			cout << left << setw(1) << temp->entry->population << endl;
	}
} 


void Two::write(){ 
	ofstream output ("out_geog.csv");//open the outupt file
	if(output.is_open()){
		Node *temp = head;
		Node *hold = NULL;

		output << "replan_id" << endl;
		output << "replan_id,geo_name,geo_stusab,geo_sumlev,geo_state,geo_county,geo_geoid,population" << endl;
		if(head == nullptr)
                	return;
		
		for(Node* temp = head; temp != nullptr; temp = temp->Next){// loop throught the table
			//if(hashMap[i].empty()){//if there is data in the position of the vector
				output << temp->entry->replan_id << "," << temp->entry->geo_name << "," << temp->entry->geo_stusab << "," << temp->entry->geo_sumlev << "," << temp->entry->geo_state << "," << temp->entry->geo_county << "," << temp->entry->geo_geoid << "," << temp->entry->population << endl;
		}
	}
	else{
		cout << "Unable to open output file" << endl;
	}
	output.close();
}

void Two::bonus(vector<string> args, vector<string> cols){
	vector<Entry> temp = rSelect(args);
	string scheme[] = { "replan_id", "geo_name", "geo_stusab", "geo_sumlev", "geo_state", "geo_county", "geo_geoid", "population" };

	for (int j = 0; j < 8; j++)
		for (int k = 0; k < cols.size(); k++)
			if (scheme[j] == cols[k])
				cout << setw(45) << scheme[j];
	cout << endl;
	for (int i = 0; i < temp.size(); i++) {
		for (int j = 0; j < 8; j++)
			for (int k = 0; k < cols.size(); k++)
				if (scheme[j] == cols[k]) switch (j) {
					case 0: cout << setw(10) << temp[i].replan_id; break;
					case 1: cout << setw(45) << temp[i].geo_name; break;
					case 2: cout << setw(11) << temp[i].geo_stusab; break;
					case 3: cout << setw(11) << temp[i].geo_sumlev; break;
					case 4: cout << setw(10) << temp[i].geo_state; break;
					case 5: cout << setw(11) << temp[i].geo_county; break;
					case 6: cout << setw(13) << temp[i].geo_geoid; break;
					case 7: cout << setw(1) << temp[i].population; break;

				}
		cout << endl;
	}
	cout << endl;

}
