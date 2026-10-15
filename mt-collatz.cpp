//For Threads
#include <thread>
#include <mutex>

//For tracking the duration of the process
#include <time.h>

//Input Output
#include <iostream>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;

//Value at which algorithm must stop at
const int STOPPING_VALUE = 1;
int currentValueCounter = 1;
int* stoppingTimeArray;

long n;
int t;

double computationStartTime;
double computationEndTime;

pthread_mutex_t lock;
bool noLockEnabled;

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

void* threadProcess(void* param){

    int newInt;

    do{
        if(noLockEnabled == false){
            pthread_mutex_lock(&lock);
            newInt = currentValueCounter;
            ++currentValueCounter;
            pthread_mutex_unlock(&lock);
        }
        else{
            newInt = currentValueCounter;
            ++currentValueCounter;
        }


        int counter = 0;

        int index = newInt - 1;

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
    }while(currentValueCounter <= n);
        
    pthread_exit(0);
}

int main(int argc, char* argv[]){

    noLockEnabled = false;

    /*
    Getting the range and number of threads from the command line arguments
    that are used to run the program
    */

    //Argc will be 3, 2 arguments for range and thread count and the argument ./mt-collatz
   if(argc == 3){

    //Holds the value of n, for which the algorithm goes from 1 to n
    n = std::stol(argv[1]);

    //Holds the number of threads to perform the collatz algorithm on
    t = std::stoi(argv[2]);

    //Checks to make sure atleast one thread is being used
    if(t == 0){
        cout << "Error: Thread count must be higher than 0." << endl;
        return 1;
    }

    pthread_mutex_init(&lock,NULL);

    //Array to hold our threads so we can track them then join them later
    pthread_t threadArray[t];

    //Array initialized on the heap to save stopping time values
    stoppingTimeArray = new int[n];
    
    //Creating threads
    for(int i = 0; i < t; ++i){
        //Make it where you can differentiate the different threads 
        //by giving them names other than just thread
        pthread_create(&threadArray[i],NULL,threadProcess, (void*)"thread");
    }

    //Waiting for threads to end before continuing 
    cout << "Waiting for threads" << endl;
    for(int i = 0; i < t; ++i){
        pthread_join(threadArray[i], NULL);
    }

    pthread_mutex_destroy(&lock);

    cout << "Threads done" << endl;

    printStoppingTime(stoppingTimeArray, n);
   }
   else{
    cout << "Error: Argument count is not 3.\nRange and thread amount must be set." << endl;
   }


}