build: frati planificare numaratoare

run-p1: frati
	./frati

run-p3: planificare
	./planificare

run-p4: numaratoare
	./numaratoare

frati:	frati.cpp
	g++ frati.cpp -o frati

planificare: planificare.cpp
	g++ planificare.cpp -o planificare

numaratoare: numaratoare.cpp
	g++ numaratoare.cpp -o numaratoare

clean:
	rm -f frati planificare numaratoare

