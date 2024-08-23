CC=zig cc
RUNNER=zig run
LICENSE_FILE=LICENSE.txt
README_FILE=README.md
SRC_FOLDER=src
MAIN_FILE=main.c
TEST_FILE=tests.c
INCLUDE_FILES=lib/my_lib.c lib/my_math.c
OUT_FOLDER=bin
OUT_FILE=output

.PHONY: default
default:
	@echo
	@echo "Make file to use Zig as a drop-in C compiler."
	@echo
	@echo "Options:"
	@echo "default: Displays make options."
	@echo "license: Displays the license file."
	@echo "readme:  Displays the readme file."
	@echo "run:     Runs the main.c file."
	@echo "build:   Builds the binaries to the bin directory."
	@echo "test:    Runs the project tests."
	@echo

.PHONY: license
license:
	cat $(LICENSE_FILE)

.PHONY: readme
readme:
	cat $(README_FILE)

.PHONY: run
run:
	@cd $(SRC_FOLDER);$(RUNNER) $(MAIN_FILE) $(INCLUDE_FILES);cd ..;

.PHONY: test
test:
	@clear;cd $(SRC_FOLDER);$(RUNNER) $(TEST_FILE) $(INCLUDE_FILES);cd ..;

.PHONY: build
build:
	@mkdir -p $(OUT_FOLDER);cd $(SRC_FOLDER);$(CC) $(MAIN_FILE) $(INCLUDE_FILES) -o ../$(OUT_FOLDER)/$(OUT_FILE);cd ..;
