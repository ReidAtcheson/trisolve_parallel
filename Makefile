


main : main.o
	$(CXX) $(CXXFLAGS) -o main main.o -lblas -fopenmp

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp


.PHONY : clean


clean :
	rm -rf ./main
	rm -rf ./main.o
