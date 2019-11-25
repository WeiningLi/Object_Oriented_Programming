#include "mastermind.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char** argv) {
  if (argc!=4) {
    cout << "Incorrect usage, should be: " << endl;
    cout << argv[0] << " seed codeLength guessLimit" << endl;
    return 1;
  }
  if (argc==4) {
    Mastermind mm {atoi(argv[1]),atoi(argv[2]),atoi(argv[3])};
    mm.playGame(); 
  }
  return 0;
}
