//Sample provided by Fabio Galuppo 
//August 2015 
//http://www.simplycpp.com 

//compile: cl.exe /Fo.\bin\obj\ /EHsc /Ox chrono_sample.cpp /link /out:bin\chrono_sample.exe
//run: .\bin\chrono_sample.exe 450

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <numeric>
#include <cstdlib>

using namespace std;
using namespace std::chrono;

int main(int argc, const char* argv[]) 
{
    {
    const auto start = high_resolution_clock::now();
    
    this_thread::sleep_for(seconds(1));
    
    const auto finish = high_resolution_clock::now();

    cout << duration_cast<milliseconds>(finish - start).count() << " ms\n";
    }
    
    {
    vector<int> xs;
    xs.resize(10 * 1024);
    
    long long total = 0;
    int iters = 1;
    if (argc > 1)
        iters = atoi(argv[1]);
          
    const auto start = high_resolution_clock::now();
    
    iota(xs.begin(), xs.end(), 1);
    for (int i = 1; i <= iters; ++i)
        total += accumulate(xs.begin(), xs.end(), 0);
    
    const auto finish = high_resolution_clock::now();
    
    cout << total << "\n";
    cout << duration_cast<microseconds>(finish - start).count() << " us\n";
    }
}
