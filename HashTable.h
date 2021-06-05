/*
 * HashTable.h
 *
 *  Created on: Oct 21, 2013
 *      Author: shaowu
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <iostream>
#include <cmath>
#define Size 43
using namespace std;
typedef string Key;
typedef int Item;
struct Unit{
	Key key;
	Item item;
};
class HashTable{
public:
	bool add(Key key, Item item){
		if(isduplicated(key) | isfull()) return false;
		bool flag = true;
		int index = hash(key);
		int ifind =index;
		do{
			if(isempty(ifind)){
				datapool[ifind].item = item;
				datapool[ifind].key = key;
				mask[ifind] = true;
				flag = false;
//				cout << "item = " << datapool[ifind].item << "\tkey = " << datapool[ifind].key << "\t" << index<< "\t: "  << ifind << endl;
			}
			ifind = ++ifind  % Size;
		}while(flag && ifind != index );
		return true;
	}
	Item get(Key key){
		int index = hash(key);
		int ifind =index;
		while( !isempty(ifind) && index >= 0){
			if(datapool[ifind].key.compare(key) == 0){
//				cout << "string compare " << datapool[ifind].key << " \t<-> " << key << " -> \t" << datapool[ifind].key.compare(key) << endl;
				return datapool[ifind].item;
			}
			ifind = ++ifind  % Size;
		}
		cout << "ERROR " << datapool[ifind].key << " \t<-> " << key << " -> \t" << datapool[ifind].key.compare(key) << endl;
		return 0;
	}
	void show(){
		for(int i = 0;i < Size;i++){
			if(!isempty(i)){
				cout <<  "hash :" << hash(datapool[i].key) << "index = " << i << "  -> " << datapool[i].key << " \t"  << datapool[i].item << endl;
			}
		}
}

	int hash(string key){
		int index = 1431655765;
		for(int i = key.length() - 1;i >= 0;i--){
			index ^= key[i] >> i;
		}
		return  (index % divisor);
	}
	bool isempty(int index){
		return !mask[index];
	}
	bool isduplicated(Key data){
		return false;
	}
	bool isfull(){
		return false;
	}
	void reflash(){
         return;
	}
private:
	Unit datapool[Size];
	static const int divisor = Size;
	bool mask[Size];
};


#endif /* HASHTABLE_H_ */
