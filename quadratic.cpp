//======================================================
//Author: James Anthony Ortiz
//File: quadratic.cpp
//Assignment: Programming Assignment #2 (Part B)
//Description:
//An open-address hash-map implemented in C++, that accepts randomized keys in
//the closed range [-2^31, 2^31].
//This program detects the amount of collisions based on the 
//.5, .6, .7, .8, .9 load factor values.
//Compile: g++ -std=c++11 quadratic.cpp -o quadratic
//=======================================================

//Libraries used in program:
#include <iostream>
#include <vector>
#include <random>
#include <cstddef>
#include <time.h>
#include <chrono>


using namespace std;

//Global Hash-Table Array for  1,000,000 long-long int values:
long long int arr[1000000]; 

int collisions = 0;


//Function: quadratic_hash
//Description: Attempts to hash value useing linear probing
//Returns: An index for the arr array.
int quadratic_hash(long long int val, int i)
{

  //If the value is positive:
  if(val >= 0)
  {
    int hash;
    int c1 = 1;
    int c2 = 4;
    hash = (val + c1*i + c2*(i*i)) % 1000000;
    return hash;
  }

  //Otherwise: mask bits:
  int hash;
  int c1 = 1;
  int c2 = 4;
  hash = ((val + c1*i + c2*(i*i)) & 0x7FFFFFFFFFFFFFFF) % 1000000;
  return hash;
}//end quadartic_hash()

//Function: insert()
//Description: Inserts a random key into an unoccupied
//space inside of the hashtable, if the currently searched space
//is occupied it will look for an empty one:
//Returns: void
void insert(long long int key, int keys)
{
  int i = 0;
  int hashVal = quadratic_hash(key, i);
  
  //If the spot is not empty:
  //goto the next adjacent location
  //until a vacant area in the Table is found
  while(arr[hashVal] != 0)
  {
    //go to the next value
    i++;
    hashVal = quadratic_hash(key, i); //Wrap-around if necessary
  }

  //Otherwise, insert directly into table:
  arr[hashVal] = key;

}//end function insert()

//Function: insert_with_collision_count()
//Description: This function calculates the number of collisions
//that are taken to insert a value into the hashtable. Essentially,
//it is a version of the function above but without actual insertion
//involved.
//Returns: void
void insert_with_collision_count(long long int key)
{

  int i = 0;
  int hashVal = quadratic_hash(key, i);

  //If the spot is not empty
  //goto the next adjacent location on table,
  //until a vacant area on the table is found:
  while(arr[hashVal] != 0)
  {
    //go down table
    i++;
    hashVal = quadratic_hash(key, i);
    collisions++;
  }//end while

  //no insert here, just counting collisions:
  collisions++;
}//end insert_with_collision_count()


//================================
//MAIN Driver:
//================================

int main()
{
  //Lower-Bound: [-2^31]
  long long lower = -2147483648;
  //Upper-Bound: [2^31]
  long long upper =  2147483648;


  //Zero-out global array:
  for(int i = 0; i < 1000000; i++)
  {
    arr[i] = 0;
  } 


  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::default_random_engine generator(seed);

  std::uniform_int_distribution<long long int> dist(lower, upper);

  
  //Character value used for selection:
  char value;

  //Selection from user:
  cout << "======================================="<< endl;
  cout << "Welcome to the quadratic probing program! " << endl;
  cout << "=======================================" << endl;
  cout << "Please enter a letter that corresponds to a load factor: "  << endl;
  cout << "Enter A for 0.5" << endl;
  cout << "Enter B for 0.6" << endl;
  cout << "Enter C for 0.7" << endl;
  cout << "Enter D for 0.8" << endl;
  cout << "Enter E for 0.9" << endl;
  cout << "Select a value: " ;

  //Recieve char value
  cin >> value;

  float load_factor = 0.0;
  long long int keys = 0;

  switch(toupper(value))
  {
    case 'A':
      {
        keys = 1000000 * 0.5;
        load_factor = 0.5;
        cout << "The load factor you have selected is: " << 0.5 << endl;
        cout << "The number of keys you have selected to use is: " << keys << endl;
        break;
      }

    case 'B':
      {
        keys = 1000000 * 0.6;
        load_factor = 0.6;
        cout << "The load factor you have selected is: " << 0.6 << endl;
        cout << "The number of keys you have selected to use is: " << keys << endl;
        break;
      }

    case 'C':
      {
        keys = 1000000 * 0.7;
        load_factor = 0.7;
        cout << "The load factor you have selected is: " << 0.7 << endl;
        cout << "The number of keys you have selected to use is: " << keys << endl;
        break;
      }
      
    case 'D':
      {
        keys = 1000000 * 0.8;
        load_factor = 0.8;
        cout << "The load factor you have selected is: " << 0.8 << endl;
        cout << "The number of keys you have selected to use is: " << keys << endl;
        break;
      }

    case 'E':
      {
        keys = 1000000 * 0.9;
        load_factor = 0.9;
        cout << "The load factor you have selected is: " << 0.9 << endl;
        cout << "The number of keys you have selected to use is: " << keys << endl;
        break;
      }

    default:
      {
        cout << "Sorry, you have entered the wrong character value. Exiting Program...." << endl;
        break;
      }
      
  }//end switch


  //==================================================================================



  //Insert random values into array arr:

  //For-loop:  
  int counter = 0;
  while(counter < keys)
  {
    //Create a random value as a key:
    long long int rand_value;
    rand_value = dist(generator);
    
    //Attempt to insert value:
    insert(rand_value, keys);
    
    //Increment while-loop counter:
    counter++;
  }//end for-loop:

  //Currently at designated size...:

  //Now, create a for loop with 10,000 random keys, without actual insertion
  //to calculate collisions:

  int new_counter = 0;
  while(new_counter < 10000)
  {
    //Create a random value:
    long long int rand_value;
    rand_value = dist(generator);

    //Count collisions at the load factor: .5
    insert_with_collision_count(rand_value);

    //increment counter for for-loop:
    new_counter++;
  }


  //Calculate average amt. of collisions dividing collisions by 10000:
  double avg_collisions = collisions/10000.0;


  cout << "Calculating results...please wait..." << endl;
  cout << "====================================================" << endl;
  cout << "RESULTS FOR LOAD-FACTOR: " << load_factor <<  endl;

  cout << "The total amount of collisions is: " << collisions << endl; 
  cout << "The total amount of keys were: " << keys << endl;
  cout << "The average amount of collisions with " << keys << " keys were: "  << avg_collisions << endl; 


  int occupied = 0;
  int empty = 0;
  for(int i = 0; i < 1000000; i++)
  {
    if(arr[i] != 0)
    {
      //cout << "[ " << arr[i] << " , "  << "Index: " << i << "]" << endl;
      occupied++;
    }
    else if(arr[i] == 0)
    {
      //cout << "[EMPTY" << ", " <<  " Index:" << i << " ]" <<  endl;
      empty++;
    }
  }


  cout << "Occupied Slots: " << occupied << " Empty Slots: " << empty << endl;
  cout << "====================================================" << endl;


  return 0;
  
}//end MAIN
