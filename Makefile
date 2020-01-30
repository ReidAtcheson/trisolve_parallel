


main : main.o
	$(CXX) $(CXXFLAGS) -o main main.o  -Wl,--start-group ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_intel_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -liomp5 -lpthread -lm -ldl

main.o : main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp


.PHONY : clean


clean :
	rm -rf ./main
	rm -rf ./main.o
