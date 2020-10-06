test.out: merge_sort_test.o merge_sort.o
	g++ -o $@ $^

%.o: %.cpp
	g++ -std=c++11 -c $<

runTest: test.out
	./test.out
