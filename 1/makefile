# Path to the executable (you may need to change this variable)
EXE=build/src/dhtml
# Path to VCPKG toolchain (you may need to change this variable)
VCPKG="/opt/vcpkg/scripts/buildsystems/vcpkg.cmake"
# Memory checker (you may need to change this variable)
MEMCHECK=valgrind --quiet --leak-check=full --leak-resolution=med  --track-origins=yes --vgdb=no
# Compare tool with flags (you may need to change this variable)
DIFF=diff

.PHONY: build test_client test_server static_analysis clean all test_all compare

all: build test_all

test_client: build
	@echo "======================"
	@echo "TEST CLIENT"
	@echo "======================"
	$(MEMCHECK) $(EXE) --client --address 127.0.0.1 --port 8000 --verbose sample-files/index.html

test_server: build
	@echo "======================"
	@echo "TEST SERVER"
	@echo "======================"
	$(MEMCHECK) $(EXE) --server --address 127.0.0.1 --port 8000 --verbose --max-transfers 1

test_all: build
	@echo "======================"
	@echo "TEST ALL"
	@echo "======================"
	mkdir -p tmp
	timeout 5s bash -c '$(EXE) --server --address 127.0.0.1 --port 8000 --max-transfers 4 > tmp/out-server.txt' 2>&1 &
	@sleep 1s
	$(EXE) --client --address 127.0.0.1 --port 8000 index.html > tmp/out-client-1.txt 2>&1
	$(EXE) --client --address 127.0.0.1 --port 8000 sample-files/index.html > tmp/out-client-2.txt 2>&1
	$(EXE) --client --address 127.0.0.1 --port 8000 sample-files/index2.html > tmp/out-client-3.txt 2>&1
	$(EXE) --client --address 127.0.0.1 --port 8000 sample-files/index3.html > tmp/out-client-4.txt 2>&1
	-$(EXE) --client --address 127.0.0.1 --port 8000 sample-files/index3.html > tmp/out-client-5.txt 2>&1
	@echo ""

compare:
	$(DIFF) sample-files/index.html tmp/out-client-2.txt
	$(DIFF) sample-files/index2.html tmp/out-client-3.txt
	$(DIFF) sample-files/index3.html tmp/out-client-4.txt

build:
	@echo "======================"
	@echo "BUILD"
	@echo "======================"
	mkdir -p build
	cmake -Bbuild ./ -DCMAKE_TOOLCHAIN_FILE=$(VCPKG)
	cmake --build ./build
	@echo ""

static_analysis: 
	@echo "======================"
	@echo "CPPCHECK"
	@echo "======================"
	cppcheck -q --enable=all --suppressions-list=suppressions.cppcheck src
	@echo ""

clean:
	rm -rf ./build