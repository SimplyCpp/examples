g++ -Wall -O2 -std=c++11 -o _makewords.exe _makewords.cpp
g++ -Wall -O2 -std=c++11 -o _lowercase.exe _lowercase.cpp
g++ -Wall -O2 -std=c++11 -o _sort.exe _sort.cpp
g++ -Wall -O2 -std=c++11 -o _unique.exe _unique.cpp
g++ -Wall -O2 -std=c++11 -o _mismatch.exe _mismatch.cpp
g++ -Wall -O2 -std=c++11 -o mismatch_program.exe mismatch_program.cpp
mismatch_program .\tests\words.txt .\tests\alice.txt > alice_output_1.txt
_makewords .\tests\alice.txt | _lowercase | _sort | _unique | _mismatch .\tests\words.txt > alice_output_2.txt
mismatch_program alice_output_1.txt alice_output_2.txt
mismatch_program alice_output_2.txt alice_output_1.txt
_makewords alice_output_1.txt | _lowercase | _sort | _unique | _mismatch alice_output_2.txt
_makewords alice_output_2.txt | _lowercase | _sort | _unique | _mismatch alice_output_1.txt