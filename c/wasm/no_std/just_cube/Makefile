# Compiler and flags
CC = clang
TARGET = wasm32
CFLAGS = -Os
LDFLAGS = -Wl,--no-entry \
          -Wl,--export=cube \
          -Wl,--export=square \
          -Wl,--export=twice \
          -Wl,--allow-undefined \
          -Wl,--strip-all \
          -Wl,--gc-sections

# Source and output
SRC = ./src/math.c ./src/util.c
OUTPUT = ./docs/math.wasm

# Default target - shows help if no arguments
.PHONY: all build clean help serve

# Default target (when no target is specified)
# This approach uses the fact that if no target is specified,
# make will run the first target it encounters
all: help

# Explicit build target
build: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) \
		--target=$(TARGET) \
		-nostdlib \
		$(CFLAGS) \
		$(LDFLAGS) \
		-o $@ $^

# Help target
help:
	@echo ""
	@echo "-------------------------------------------------------------------------------"
	@echo "Available targets:"
	@echo "  build    - Build the WebAssembly module"
	@echo "  clean    - Remove generated files"
	@echo "  serve    - Serves the project"
	@echo "  help     - Show this help message"
	@echo ""
	@echo "Build configuration:"
	@echo "  Sources: $(SRC)"
	@echo "  Output : $(OUTPUT)"
	@echo "  Target : $(TARGET)"
	@echo ""

# Clean target
clean:
	rm -f $(OUTPUT)

serve:
	@echo "Starting local HTTP server on port 9000..."
	http-server ./docs/ -p 9000

# Alias for help
.PHONY: usage
usage: help
