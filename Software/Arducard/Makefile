PROJECT = arducard

F_CPU = 16000000UL
MCU = atmega328p
DEFINES = 

FILES = main.c screen.c

PROGRAMMER = usbasp
PORT = usb

# Common section

# Directories
BUILD_DIR = build
SRC_DIR = src
LIB_SRC_DIR = lib/src
LIB_INCLUDE_DIR = lib/include

# Programmer settings
BAUDRATE = 115200

# Compilers and other
CC := avr-gcc
CXX := avr-g++
OBJCOPY := avr-objcopy
AVRSIZE := avr-size
AVRDUDE := "avrdude"

# File lists
OBJS := $(FILES:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

# Compiler setings
DEFLIST := $(DEFINES:%=-D%)
INC_FLAG := $(addprefix -I,$(INC_DIRS)) -I$(SRC_DIR) -Ilib
CPPFLAGS := $(INC_FLAG) -MMD -MP -Os -DF_CPU=$(F_CPU) $(DEFLIST) -mmcu=$(MCU) -I$(LIB_INCLUDE_DIR)
LDFLAGS := -mmcu=$(MCU)

#Targets

.PHONY: clean build flash

build: $(BUILD_DIR)/$(PROJECT).hex

flash: $(BUILD_DIR)/$(PROJECT).hex
	$(AVRDUDE) -p$(MCU) -c$(PROGRAMMER) -P$(PORT) -b$(BAUDRATE) -Uflash:w:$(BUILD_DIR)/$(PROJECT).hex:i

$(BUILD_DIR)/$(PROJECT).hex: $(BUILD_DIR)/$(PROJECT).elf
	$(OBJCOPY) -O ihex $(BUILD_DIR)/$(PROJECT).elf $(BUILD_DIR)/$(PROJECT).hex

$(BUILD_DIR)/$(PROJECT).elf: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)
	$(AVRSIZE) -C --mcu=$(MCU) $@

$(BUILD_DIR)/%.c.o: $(SRC_DIR)/%.c
	@if not exist $(BUILD_DIR)\\NUL mkdir $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.c.o: $(LIB_SRC_DIR)/%.c
	@if not exist $(BUILD_DIR)\\NUL mkdir $(BUILD_DIR)
	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: $(SRC_DIR)/%.cpp
	@if not exist $(BUILD_DIR)\\NUL mkdir $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

$(BUILD_DIR)/%.cpp.o: $(LIB_SRC_DIR)/%.cpp
	@if not exist $(BUILD_DIR)\\NUL mkdir $(BUILD_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	del /q $(BUILD_DIR)\*

-include $(DEPS)