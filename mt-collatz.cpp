#include <thread>
#include <iostream>
#include <string>
#include <mutex>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//Value at which algorithm must stop at
const int STOPPING_VALUE = 1;
int currentValueCounter = 1;
int* stoppingTimeArray;

void initTest(long n, int t){
    cout << "Range: " << n << endl;
    cout << "Thread Count: " << t << endl;

}

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

//Starting int is inclusive, finishing int is exclusive
void startThreadLoop(){

        int counter = 0;
        int newInt = currentValueCounter;
        int index = newInt - 1;
        ++currentValueCounter;

        while(newInt != STOPPING_VALUE){
            if(isEven(newInt)){
                newInt = ifEven(newInt);
            }
            else{
                newInt = ifOdd(newInt);
            }

            ++counter;
        }
        stoppingTimeArray[index] = counter;
}

void printStoppingTimeHistogram(int* array, int numberOfValues){
    for(int k = 0; k <= 1000; ++k){
        int counter = 0;

        for(int i = 0; i < numberOfValues; ++i){
            if(array[i] == k){
                ++counter;
            }
        }

        cout << k << "," << counter << endl;
    }
}

void printStoppingTime(int* array, int numberOfValues){
    for(int i = 0; i < numberOfValues; ++i){
        cout << i + 1 << ": " << array[i] << endl;
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
    const long n = std::stol(argv[1]);

    //Holds the number of threads to perform the collatz algorithm on
    const int t = std::stoi(argv[2]);

    //Checks if t is zero to prevent division by zero in initilizeStartingIntArray() method
    if(t == 0){
        cout << "Error: Thread count must be higher than 0." << endl;
        return 1;
    }

    //Array initialized on the heap to save stopping time values
    stoppingTimeArray = new int[n];

    initTest(n,t);
    
    while(currentValueCounter != n + 1){
        startThreadLoop();
    }

    // printStoppingTimeHistogram(stoppingTimeArray,n);
    printStoppingTime(stoppingTimeArray,n);

   }
   else{
    cout << "Error: Argument count is not 3.\nRange and thread amount must be set." << endl;
   }


}