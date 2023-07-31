OS_NAME = cubebox
VERSION = 0.0.1.0a
STAGE = alpha

TARGET = ix86

# =================================== TOOLS AND FLAGS DEFINITIONS ===================================

CC = i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -I ./src/

CXX = i686-elf-g++
CXXFLAGS = -ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti -I ./src/

AS = i686-elf-as

LD = i686-elf-g++
LDFLAGS = -T linker.ld

# =================================== OUTPUT FILES AND DIRECTORIES ===================================

BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin

# =================================== INPUT FILES ===================================
C_SOURCES = $(find src -type f -name "*.c")
CXX_SOURCES = $(find src -type f -name "*.cpp")
ASM_SOURCES = $(find src -type f -name "*.s")

# =================================== OUTPUT FILES GENERATED ===================================
C_OBJECTS = $(C_SOURCES:%.c=$(OBJ_DIR)/%.o)
CXX_OBJECTS = $(CXX_SOURCES:%.cpp=$(OBJ_DIR)/%.o)
ASM_OBJECTS = $(ASM_SOURCES:%.s=$(OBJ_DIR)/%.o)

# =================================== COMPILER OBJECT OUTPUT FILES ===================================
$(OBJ_DIR)/%.o: src/%.c
	echo "Build $($<) -> $($@)"
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.cpp
	echo "Build $($<) -> $($@)"
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: src/%.s
	echo "Build $($<) -> $($@)"	
	$(AS) $(ASFLAGS) $< -o $@

# =================================== EXECUTABLE GENERATION ===================================
$(BIN_DIR)/$(OS_NAME)-$(VERSION)-$(TARGET)-$(STAGE).bin: $(C_OBJECTS) $(CXX_OBJECTS) $(ASM_OBJECTS)
	$(LD) $(LDFLAGS) $(C_OBJECTS) $(CXX_OBJECTS) $(ASM_OBJECTS) -o $(BIN_DIR)/$(OS_NAME)-$(VERSION)-$(TARGET)-$(STAGE).bin


# =================================== GENERATED FILES REMOVAL ===================================
clean:
	rm -f $(BIN_DIR)/$(OS_NAME).bin $(C_OBJECTS) $(CXX_OBJECTS) $(ASM_OBJECTS)