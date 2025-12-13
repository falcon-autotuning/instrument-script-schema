

build:
	mkdir build && cd build && cmake .. && make

test:
	./build/test_validator 
	./build/test_examples

clean:
	rm -rf build
