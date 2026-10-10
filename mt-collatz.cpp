#include <thread>
#include <iostream>
#include <string>
#include <mutex>

using std::cout;
using std::cin;
using std::endl;
using std::string;

bool isEven(long value){
    if(value % 2 == 0){
        return true;
    }
    return false;
}

//If the value is even, we divide by 2
long ifEven(long value){
    return value / 2;
}

//If the value is odd we times it by 3 then add one
long ifOdd(long value){
    return (3 * value) + 1;
}

//Checks between 2 cases to split work amongst threads evenly
void initializeStartingIntArray(int* startingIntArray, long n, int t){

    long numbersPerThread = n / t;

    //Case 1: Clean division
    if(n % t == 0){

        for(int i = 0; i < t; ++i){
            startingIntArray[i] = (numbersPerThread * i) + 1;
        }
    }
    /*
    * Case 2: division ends with a remainder
    * We take the remainder, muliply it by the number of threads
    * And then add that remainder to the last starting int index
    * Ex. 150 / 7 = 21.428....
    * We set all indexs in the array except the last to 21
    * Then for the final we take 0.428... * 7 (number of threads) = 3
    * 21 * 6 = 126, then we add 21 + 3(the remainder we aquired) = 150
    */
    else{
        int remainder = n - (numbersPerThread * t);
        for(int i = 0; i < t; ++i){
            //Setting startingInts for all threads except the last one
            if(i + 1 < t){
                startingIntArray[i] = (numbersPerThread * i) + 1;
            }
            else{
                startingIntArray[i] = (numbersPerThread * i) + remainder;
            }
        }
    }

    cout << "Testing initilization of starting int array:" << endl;
    cout << "Numbers Per Thread: " << numbersPerThread << endl;
    cout << "Remainder: " << n - (numbersPerThread * t) << endl;

    for(int i = 0; i < t; ++i){
        cout << startingIntArray[i] << endl;
    }


}

int main(int argc, char* argv[]){

    /*
    Getting the range and number of threads from the command line arguments
    that are used to run the program
    */

    //Argc will be 3, 2 arguments for range and thread count and the argument ./mt-collatz
   if(argc == 3){

    //Holds the value of n, for which the algorithm goes from 1 to n
    long n = std::stol(argv[1]);

    //Holds the number of threads to perform the collatz algorithm on
    int t = std::stoi(argv[2]);

    //Checks if t is zero to prevent division by zero in initilizeStartingIntArray() method
    if(t == 0){
        cout << "Error: Thread count must be higher than 0." << endl;
        return 1;
    }

    //Value at which algorithm must stop at
    const int STOPPING_VALUE = 1;

    //Array initialized on the heap to save stopping time values
    int* stoppingTimeArray = new int[n];

    //Array that has the starting number for each thread
    //Ex. Thread 1 starts at 0, thread 2 starts at 55
    int* startingIntArray = new int[t];

    cout << "Range is: " << n << endl;
    cout << "# of threads is: " << t << endl;

    cout <<"Testing if stopping time array is initialized to zeros: " << stoppingTimeArray[0] << endl;

    initializeStartingIntArray(startingIntArray,n,t);


   }
   else{
    cout << "Error: Argument count is not 3.\nRange and thread amount must be set." << endl;
   }


}