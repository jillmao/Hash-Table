//hash table
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class HashTable
{
	public:
		void insertKeyLinear(int key);
		void insertKeyQuadratic(int key);
		void insertKeyDouble(int key);
		//void insertKeySeparate(int key);
		void print();
	private:
		int array[10] = {0};
		vector<int> fails; //to catch what hasn't been inserted into the table
} ;

//Insert key into hash table using linear probing. 
//If key % 10 isn't available, go to next spot in array
void HashTable::insertKeyLinear(int key)
{
	int index = key % 10;
	if (array[index] == 0)
		{
		array[index] = key;
		}
	else{
		index += 1;
		//If key can't be inserted and a wrap around has occurred, exit loop
		while (index != (key % 10)){
			index = index % 10;
			if (array[index] == 0)
				{array[index] = key;
				//exit function if key has been inserted
				return;
				}
			index += 1;
					}
	fails.push_back(key); //catch any key that has not been inserted
		}
}
//insert key into hash table using linear probing. 
//If key % 10 isn't available, try multiplier * multiplier spaces away
//Increment multiplier for every collision
void HashTable::insertKeyQuadratic(int key)
{
	int multiplier = 0;
	int index = key % 10;
	if (array[index] == 0)
		{
		array[index] = key;
		}
	else{
		while (multiplier != 10){
			//increment multiplier for every collision
			//if multiplier hits 10 (size of array), then we know key can't be inserted
			multiplier += 1;
			index = ((multiplier * multiplier) + key) % 10;
			if (array[index] == 0)
				{array[index] = key;
				return;
				}
					}
	fails.push_back(key);
		}
}

//Insert key into hash table using double hashing. 
//If key % 10 isn't available, try every 7 - (key % 7) spaces away until insertion or full wrap around
void HashTable::insertKeyDouble(int key)
{	
	int h2 = 7 - (key % 7);
	int index = key % 10;
	if (array[index] == 0)
		{
		array[index] = key;
		}
	else{
		index = (index + h2) % 10;
		while (index != (key % 10)){
			if (array[index] == 0)
				{array[index] = key;
				return;
				}
			index = (index + h2) % 10;
					}
	fails.push_back(key);
		}
}

//void HashTable::insertKeySeparate(int key)
//{
//	int index = key % 10;
//}

//print the fails and then the hash table
void HashTable::print()
{
for (int i = 0; i < fails.size(); i++)
	{ 
	//print fails first
	cout<<"  " <<fails.at(i)<< " could not be inserted in the table"<<endl<<endl;
	}
	
//iterate through every value of the table
for (int i = 0; i < 10; i++)
	{int value = array[i];
	cout<<"   "<< i << " ";
	 if (value != 0){
	cout<<"  " <<value <<endl;
			}
	 else {
		cout << endl;
		}
	}
}

//main opens keys.txt, reads keys, and inserts them into hash table
int main ()
{
	HashTable linear_table, quadratic_table, double_table, separate_table;

	int key = 0;
	while (key != -1){
		cin>>key;
		if (key != -1){
			linear_table.insertKeyLinear(key);
			quadratic_table.insertKeyQuadratic(key);
			double_table.insertKeyDouble(key);
			//separate_table.insertKeySeparate(key);
				};
		}
	cout<< "Hash Table with Linear Probing";
	cout<< endl<< endl;
	linear_table.print();
	cout<< endl<<endl;
	cout<< "Hash Table with Quadratic Probing";
	cout<< endl<<endl;
	quadratic_table.print();
	cout<< endl<<endl;
	cout<< "Hash Table with Double Hashing";
	cout<< endl<<endl;
	double_table.print();
	//cout<< "Hash Table with Separate Chaining";
	//cout<< endl<<endl;
	//separate_table.print();
  	return 0;
}
