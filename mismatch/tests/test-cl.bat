cl.exe /Wall /EHsc /Ox _makewords.cpp /link /out:_makewords.exe
cl.exe /Wall /EHsc /Ox _lowercase.cpp /link /out:_lowercase.exe
cl.exe /Wall /EHsc /Ox _sort.cpp /link /out:_sort.exe
cl.exe /Wall /EHsc /Ox _unique.cpp /link /out:_unique.exe
cl.exe /Wall /EHsc /Ox _mismatch.cpp /link /out:_mismatch.exe
cl.exe /Wall /EHsc /Ox mismatch_program.cpp /link /out:mismatch_program.exe
mismatch_program .\tests\words.txt .\tests\alice.txt > alice_output_1.txt
_makewords .\tests\alice.txt | _lowercase | _sort | _unique | _mismatch .\tests\words.txt > alice_output_2.txt
mismatch_program alice_output_1.txt alice_output_2.txt
mismatch_program alice_output_2.txt alice_output_1.txt
_makewords alice_output_1.txt | _lowercase | _sort | _unique | _mismatch alice_output_2.txt
_makewords alice_output_2.txt | _lowercase | _sort | _unique | _mismatch alice_output_1.txt