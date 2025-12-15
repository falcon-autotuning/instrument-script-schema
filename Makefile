build:
	mkdir -p build && cd build && CC=clang CXX=clang++ cmake -G Ninja -DCMAKE_CXX_FLAGS="-Oz" .. && ninja
test:
	./build/test_validator 
	./build/test_examples
clean:
	rm -rf build
