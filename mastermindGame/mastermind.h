#ifndef _MASTERMIND_H_
#define _MASTERMIND_H_
#include <random>

struct Mastermind {
    int seed;
    int codeLength;
    int guessLimit;
    char* code;
    // You may add any data members you require
    // as well as any member functions you like.
    // So long as all the methods below are properly
    // implemented.
    Mastermind(int seed, int codeLength, int guessLimit);
    ~Mastermind();
    void playGame();

    // Do not modify this function
    char genCodeChar() {
        static std::default_random_engine gen;
        static std::uniform_int_distribution<int> dist(0,5);
        static bool flag = false;
        if (!flag) {
            gen.seed(seed);
            flag = true;
        }
        char ret = 'A' + dist(gen);
        return ret;
    }
};

#endif
