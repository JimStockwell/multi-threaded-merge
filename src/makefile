runTest: test.out
	./test.out

test.out: merge_sort_test.o merge_sort.o
	g++ -o $@ $^

%.o: %.cpp
	g++ -std=c++11 -c $<
