CC=zig cc
FLAGS=-Wall
RUNNER=zig run
MAIN_FILE=main.c
TEST_FILE=test.c
INCLUDE_FILES=app_lib.c matrix.c
LINK_FILES=-lncurses
OUT_FOLDER=bin
OUT_FILE=matrix

.PHONY: default
default:
	@echo
	@echo "Make file to use Zig as a drop-in C compiler."
	@echo
	@echo "Options:"
	@echo "default: Displays make options."
	@echo "run:     Runs the main.c file."
	@echo "build:   Builds the binaries to the bin directory."
	@echo "test:    Runs the project tests."
	@echo "clean:   Cleans up the build output."
	@echo

.PHONY: clean
clean:
	@rm -rf $(OUT_FOLDER)

.PHONY: run
run:
	@$(RUNNER) $(MAIN_FILE) $(INCLUDE_FILES) $(LINK_FILES)

.PHONY: test
test:
	@clear;$(RUNNER) $(TEST_FILE) $(INCLUDE_FILES) $(LINK_FILES);

.PHONY: build
build:
	@mkdir -p $(OUT_FOLDER);$(CC) $(MAIN_FILE) $(INCLUDE_FILES) $(LINK_FILES) -o $(OUT_FOLDER)/$(OUT_FILE) $(FLAGS);
