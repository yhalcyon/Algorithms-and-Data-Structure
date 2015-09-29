/* 
 * C++ program to implement hash tables with singly linked list
 */

#include<iostream>
#include<cstdlib>
#include<string>
#include<cstdio>
using namespace std;

/*
 * Hash node class
 */

class HashNode{

public:
	int key;
	int value;
	HashNode* next;
	
	HashNode(int key, int value){
		this->key = key;
		this->value = value;
		this->next = NULL;
	}
};

/*
 * Hashtable class
 */
class HashTable{
	
	int Table_Size;
	HashNode** htable;

public:
	HashTable(int a){
		Table_Size=a;
		htable = new HashNode*[Table_Size];
		for(int i=0; i<Table_Size; ++i)
			htable[i] = NULL;
	}
	
	~HashTable(){
		for(int i=0; i<Table_Size; ++i){
			HashNode* tmp = htable[i];
			while(tmp){
				HashNode* prev = tmp;
				tmp = tmp->next;
				delete prev;
			}
			delete[] htable;
		}
	}	

	// Hash function, return the key value
	int hashFunc(int key){
		return key%Table_Size;
	}	

	// Insertion
	void Insert(int key, int value){
		int hashKey = hashFunc(key);
		HashNode* prev = NULL;
		HashNode* cur =  htable[hashKey];
		while(cur){
			prev = cur;
			cur = cur->next;
		}
		cur = new HashNode(key, value);
		if(prev == NULL){
			htable[hashKey] = cur;
		}
		else{
			prev->next = cur;
		}
	}

	// Remove
	void Remove(int key){
		int hashKey = hashFunc(key);
		HashNode* cur = htable[hashKey];
		HashNode* prev = NULL;
		if(cur==NULL){
			cerr<<"No element found"<<endl;
			return;
		}
		if(cur->key == key){
			htable[hashKey]->next = cur->next;
			delete cur;
		}			
		else{
			prev = cur;
			cur = cur->next;
			if(cur->key == key){
				prev->next = cur->next;
				delete cur;
			}
		}
	}
	
	// Search element according to a key
	int Search(int key){
		int hashKey = hashFunc(key);
		HashNode* cur = htable[hashKey];
		while(cur){
			if(cur->key == key){
				cout<<cur->value<<endl;
				return cur->value;
			}
			cur = cur->next;
		}
		cout<<"Cannot find the element"<<endl;
		return -1;
	}

};

int main(){
	HashTable hash(65);
	int key, value;
	int operation;
	while(1){
		cout<<"HashTable operations"<<endl;
		cout<<"*********************"<<endl;
		cout<<"1) Insert element into the table"<<endl;
		cout<<"2) Search element in the table"<<endl;
		cout<<"3) Delete element in the table"<<endl;
		cout<<"4) Exit"<<endl;
		cout<<"Enter your operation: "<<endl;
		cin>>operation;
		switch(operation){
			case 1:
				cout<<"Key and element to be inserted: (key value)"<<endl;
				cin>>key>>value;
				hash.Insert(key, value);
				break;
			case 2:
				cout<<"element to be searched: (key)"<<endl;
				cin>>key;
				hash.Search(key);
				break;
			case 3:
				cout<<"Element to be removed: (key)"<<endl;
				cin>>key;
				hash.Remove(key);
				break;
			case 4:
				exit(1);
			default:
				cout<<"Enter the valid operations, please!"<<endl;
		}
	}
	return 0;
}














		

			
			












































