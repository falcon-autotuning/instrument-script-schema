build:
	mkdir -p build && cd build && CC=clang CXX=clang++ cmake -G Ninja -DCMAKE_CXX_FLAGS="-Oz" .. && ninja
test:
	PATH=./build:$$PATH ./build/test_validator 
clean:
	rm -rf build
