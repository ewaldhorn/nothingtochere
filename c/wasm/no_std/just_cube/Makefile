# Make file for a C to Wasm project

# Version info
VERSION = 1.0.0

# -------------------------------------------------------------------------------------------------
# Compiler and flags
CC = clang
TARGET = wasm32
RELEASE_CFLAGS = -Os
DEBUG_CFLAGS = -g -O0
LDFLAGS = -Wl,--no-entry \
          -Wl,--export=cube \
          -Wl,--export=square \
          -Wl,--export=twice \
          -Wl,--allow-undefined \
          -Wl,--gc-sections

SRC = ./src/math.c ./src/util.c
OUTPUT = ./docs/math.wasm

# -------------------------------------------------------------------------------------------------
# Default to debug build
BUILD_TYPE ?= debug

# -------------------------------------------------------------------------------------------------
# Default target - shows help if no arguments
.PHONY: all build clean help serve debug release

# -------------------------------------------------------------------------------------------------
# Default target (when no target is specified)
all: help

# -------------------------------------------------------------------------------------------------
# Release build target
release:
	$(MAKE) build BUILD_TYPE=release

# -------------------------------------------------------------------------------------------------
# Debug build target
debug:
	$(MAKE) build BUILD_TYPE=debug

# -------------------------------------------------------------------------------------------------
# Build target that uses BUILD_TYPE
build:
	@if [ "$(BUILD_TYPE)" = "debug" ]; then \
		echo "Building debug version..."; \
		$(CC) \
			--target=$(TARGET) \
			-nostdlib \
			$(DEBUG_CFLAGS) \
			$(LDFLAGS) \
			-o $(OUTPUT) $(SRC); \
	elif [ "$(BUILD_TYPE)" = "release" ]; then \
		echo "Building release version..."; \
		$(CC) \
			--target=$(TARGET) \
			-nostdlib \
			$(RELEASE_CFLAGS) \
			$(LDFLAGS) \
			-Wl,--strip-all \
			-o $(OUTPUT) $(SRC); \
	else \
		echo "Error: Unknown BUILD_TYPE '$(BUILD_TYPE)'. Use 'debug' or 'release'."; \
		exit 1; \
	fi

# -------------------------------------------------------------------------------------------------
# Help target
help:
	@echo ""
	@echo "|===========================================================================|"
	@echo "| Project: C to WASM Builder (v$(VERSION))                                       |"
	@echo "| Available targets:                                                        |"
	@echo "|  build     - Build using BUILD_TYPE variable (default: debug)             |"
	@echo "|  release   - Build release version (stripped)                             |"
	@echo "|  debug     - Build debug version (with symbols)                           |"
	@echo "|  clean     - Remove generated files                                       |"
	@echo "|  serve     - Start local HTTP server on port 9000                         |"
	@echo "|  help      - Show this help message                                       |"
	@echo "|---------------------------------------------------------------------------|"
	@echo "| Usage examples:                                                           |"
	@echo "|  make build                   # Build release version                     |"
	@echo "|  make build BUILD_TYPE=debug  # Build debug version                       |"
	@echo "|  make debug                   # Build debug version                       |"
	@echo "|  make release                 # Build release version                     |"
	@echo "|===========================================================================|"
	@echo "  Build configuration:                                                       "
	@echo "   Sources: $(SRC)                                                           "
	@echo "   Output: $(OUTPUT)                                                         "
	@echo "   Target: $(TARGET)                                                         "
	@echo ""

# -------------------------------------------------------------------------------------------------
# Clean target
clean:
	rm -f $(OUTPUT)

# -------------------------------------------------------------------------------------------------
# Check for required tools
check-tools:
	@which $(CC) > /dev/null || (echo "Error: $(CC) not found"; exit 1)
	@which http-server > /dev/null || (echo "Warning: http-server not found. Install with: npm install -g http-server")

# -------------------------------------------------------------------------------------------------
# Serve target - starts local HTTP server
serve: check-tools
	@echo "Starting local HTTP server on port 9000..."
	http-server ./docs/ -p 9000

# -------------------------------------------------------------------------------------------------
# Alias for help
.PHONY: usage
usage: help
