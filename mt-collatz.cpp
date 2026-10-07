#include <thread>
#include <iostream>
#include <string>
#include <mutex>

using std::cout;
using std::cin;
using std::endl;
using std::string;

int main(int argc, char* argv[]){

    /*
    Getting the range and number of threads from the command line arguments
    that are used to run the program
    */

    //Argc will be 3, 2 arguments for range and thread count and the argument ./mt-collatz
   if(argc == 3){
    long n = std::stol(argv[1]);
    int t = std::stoi(argv[2]);

    cout << "Range is: " << n << endl;
    cout << "# of threads is: " << t << endl;
   }
   else{
    cout << "Error: Argument count is not 3.\nRange and thread amount must be set." << endl;
   }


}