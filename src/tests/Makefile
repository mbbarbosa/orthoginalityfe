all: test_ssfe_ggm test_ssfe_sm

test_ssfe_ggm: test_ssfe_ggm.cpp ../ssfe/ssfe_ggm.tcc ../include/bgroup.hpp ../bgroup/bgroup.tcc ../include/ssfe_ggm.hpp 
	g++ -I ../ -std=c++11 -I ../include -I ../../libff test_ssfe_ggm.cpp -Wfatal-errors -Wall -lntl -lgmp ../../libff/build/libff/libff.a -lstdc++ ../../libff/build/depends/libzm.a -lgmpxx -lpthread -lprocps -o test_ssfe_ggm

test_ssfe_sm: test_ssfe_sm.cpp ../ssfe/ssfe_sm.tcc ../include/bgroup.hpp ../bgroup/bgroup.tcc ../include/ssfe_sm.hpp 
	g++ -I ../ -std=c++11 -I ../include -I ../../libff test_ssfe_sm.cpp -Wfatal-errors -Wall -lntl -lgmp ../../libff/build/libff/libff.a -lstdc++ ../../libff/build/depends/libzm.a -lgmpxx -lpthread -lprocps -o test_ssfe_sm

clean:
	rm -rf test_ssfe_ggm test_ssfe_sm
