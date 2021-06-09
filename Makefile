CXX ?= g++
CXXFLAGS ?= -std=c++20 -O3 -fno-rtti -fno-exceptions -pedantic -Werror -fno-omit-frame-pointer -lbenchmark -lpthread
MAKEFLAGS = -j1

sources = $(wildcard *.cpp)
targets = $(addprefix run-, $(sources:.cpp=))

all: clean ${targets}

build-%:
	$(CXX) $*.cpp -o tst_$* $(CXXFLAGS)

run-%: build-%
	./tst_$*

stat-%: build-%
	perf stat ./tst_$*

record-%: build-%
	perf record -g ./tst_$*

report:
	perf report -G

callgrind-%: build-%
	valgrind --tool=callgrind --callgrind-out-file=callgrind.output ./tst_$*

kcachegrind:
	kcachegrind callgrind.output

clean:
	$(RM) tst_*
	$(RM) *.output
	$(RM) *.data

cpu-on:
	sudo cpupower frequency-set --governor performance

cpu-off:
	sudo cpupower frequency-set --governor powersave
