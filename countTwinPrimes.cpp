// Author: Alan Halpin
// Title: Twin Prime Counter
// Date: 26/02/2021
/*
This is a parallel program for counting twin primes less than n. A twin prime is 
a pair of prime numbers with a gap of two between them.

E.G.
(3,5),(5,7),(11,13),(17,19),(29,31) .... 

*/

#include <chrono> // for clock
#include <iostream> // for input
#include <omp.h> // for parallel 
#include <set> // for set DS

using namespace std;

static const int numOfThreads = 8;

bool checkPrime(int number) 
{
        if(number <= 1) // 1 is not prime and primes cannot be negative
        {
            return false;
        }
        for (int i = 2; i < number; i++)
        {
            if(number % i == 0) // If there is no remainder the number is not prime
            {
                return false;
            }
        }
        return true; // Number is prime!
}

int twinPrimePrinter(int range, int threadCount) 
{
    int count = 0;
    set<int> twins;
#pragma omp parallel for num_threads(threadCount)
        for (int i = 2; i < range; i++)
        {
            if(checkPrime(i) == true) 
            {   
                if(checkPrime(i+2) == true)
                {
                    #pragma omp atomic
                    count+=2;
                    twins.insert(i);
                    twins.insert(i+2);
                    //std::cout << "(" << i << "," << (i+2) << ")";
                }
            }
        }

    cout << "Twin Primes; \n";
    for(auto it = twins.begin(); it != twins.end(); it++)
    {
        cout <<  (*it) << " , ";
    }
    return count;
}

int main() 
{
    int input;
    int threadCount;
    std::cout << "Welcome to the twin prime counter!" << "\n";
    std::cout <<"Enter search range: ";
    std::cin >> input;
    std::cout << "Enter number of threads: ";
    std::cin >> threadCount;
    auto start = chrono::steady_clock::now();// Start Clock
    int count = twinPrimePrinter(input, threadCount);
    auto end = chrono::steady_clock::now();// End Clock
    std::cout << "\nTime Taken: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << "ms";
    std::cout << "\nTotal Number of Primes : " << count << "\n";
    return 0;
}