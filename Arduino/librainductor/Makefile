########################################################################

USB_PRODUCT = librainductor
ARDUINO_PATH = /home/valka/.local/arduino-1.5.8
BUILD_DIR = build

CXX_INCLUDE = \
	-I$(ARDUINO_PATH)/hardware/arduino/sam/system/libsam \
	-I$(ARDUINO_PATH)/hardware/arduino/sam/system/CMSIS/CMSIS/Include/ \
	-I$(ARDUINO_PATH)/hardware/arduino/sam/system/CMSIS/Device/ATMEL/ \
	-I$(LIBSAM_PATH) -I$(ARDUINO_PATH)/hardware/arduino/sam/variants/arduino_due_x \
	-I/home/valka/Документы/Arduino/libraries/uShell

CXX_FLAGS = \
	-c -g -O0 -w \
	-fpermissive \
	-ffunction-sections -fdata-sections -nostdlib \
	--param max-inline-insns-single=500 \
	-fno-rtti -fno-exceptions -Dprintf=iprintf \
	-mcpu=cortex-m3 \
	-DF_CPU=84000000L -DARDUINO=158 -DARDUINO_SAM_DUE -DARDUINO_ARCH_SAM -D__SAM3X8E__ \
	-mthumb -DUSB_VID=0x2341 -DUSB_PID=0x003e -DUSBCON -DUSB_MANUFACTURER="Unknown" -DUSB_PRODUCT=\"$(USB_PRODUCT)\"

########################################################################
# uShell library

USHELL_PATH = /home/valka/Документы/Arduino/libraries/uShell
USHELL_SOURCES = uShell.cpp Window_GPIO.cpp Window_Prompt.cpp CyclicStack.cpp gslice.cpp gstring.cpp gslist.cpp garray.cpp gbytes.cpp gcommon.cpp
USHELL_OBJ = ${patsubst %.cpp, $(BUILD_DIR)/uShell/%.o, ${USHELL_SOURCES}}

build/uShell/%.o: $(USHELL_PATH)/%.cpp $(USHELL_PATH)/%.h
	@echo "  G++   $<"
	@arm-none-eabi-g++ $(CXX_FLAGS) -fno-threadsafe-statics $(CXX_INCLUDE) $< -o $@
ushell: $(USHELL_OBJ)

########################################################################

LIBSAM_PATH = $(ARDUINO_PATH)/hardware/arduino/sam/cores/arduino
LIBSAM_SOURCES = Reset.cpp Stream.cpp UARTClass.cpp Print.cpp WMath.cpp wiring_pulse.cpp USARTClass.cpp WString.cpp USB/CDC.cpp USB/USBCore.cpp USB/HID.cpp IPAddress.cpp abi.cpp RingBuffer.cpp new.cpp main.cpp
LIBSAM_OBJ = ${patsubst %.cpp, $(BUILD_DIR)/libsam/%.o, ${LIBSAM_SOURCES}}

build/libsam/%.o: $(LIBSAM_PATH)/%.cpp
	@echo "  GCC   [libsam] $<"
	@arm-none-eabi-gcc $(CXX_FLAGS) -fno-threadsafe-statics $(CXX_INCLUDE) $< -o $@
libsam: $(LIBSAM_OBJ)

########################################################################

CRT_PATH = $(ARDUINO_PATH)/hardware/arduino/sam/cores/arduino
CRT_SOURCES = itoa.c avr/dtostrf.c cortex_handlers.c wiring_digital.c wiring_analog.c WInterrupts.c wiring.c iar_calls_sam3.c syscalls_sam3.c hooks.c wiring_shift.c
CRT_OBJ = ${patsubst %.c, $(BUILD_DIR)/crt/%.o, ${CRT_SOURCES}}

build/crt/%.o: $(CRT_PATH)/%.c
	@echo "  G++   [crt] $<"
	@arm-none-eabi-gcc $(CXX_FLAGS) $(CXX_INCLUDE) $< -o $@
crt: $(CRT_OBJ)

########################################################################

LIBRAINDUCTOR_PATH = /home/valka/Документы/Arduino/librainductor
LIBRAINDUCTOR_SOURCES = librainductor.cpp
LIBRAINDUCTOR_OBJ = ${patsubst %.cpp, $(BUILD_DIR)/%.o, ${LIBRAINDUCTOR_SOURCES}}

build/%.o: $(LIBRAINDUCTOR_PATH)/%.cpp
	@echo "  G++   $<"
	@arm-none-eabi-g++ $(CXX_FLAGS) -fno-threadsafe-statics $(CXX_INCLUDE) $< -o $@
librainductor_x: $(LIBRAINDUCTOR_OBJ)

########################################################################

$(BUILD_DIR)/core.a: $(LIBSAM_OBJ) $(CRT_OBJ)
	@echo "  AR    $(LIBSAM_OBJ) $(CRT_OBJ)"
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/itoa.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/avr/dtostrf.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/cortex_handlers.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/wiring_digital.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/wiring_analog.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/WInterrupts.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/wiring.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/iar_calls_sam3.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/syscalls_sam3.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/hooks.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/crt/wiring_shift.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/Reset.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/Stream.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/UARTClass.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/Print.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/WMath.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/wiring_pulse.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/USARTClass.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/WString.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/USB/CDC.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/USB/USBCore.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/USB/HID.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/IPAddress.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/abi.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/RingBuffer.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/new.o 
	@arm-none-eabi-ar rcs $(BUILD_DIR)/core.a $(BUILD_DIR)/libsam/main.o

########################################################################

variant:
	@echo "  G++   [variant] variant.cpp"
	@arm-none-eabi-g++ $(CXX_FLAGS) -fno-threadsafe-statics $(CXX_INCLUDE) $(ARDUINO_PATH)/hardware/arduino/sam/variants/arduino_due_x/variant.cpp -o $(BUILD_DIR)/variant.o


########################################################################

$(BUILD_DIR)/librainductor.elf: librainductor_x variant $(BUILD_DIR)/core.a
	@echo "  GCC   librainductor.elf"
	@arm-none-eabi-gcc -O0 -Wl,--gc-sections -mcpu=cortex-m3 \
		-T$(ARDUINO_PATH)/hardware/arduino/sam/variants/arduino_due_x/linker_scripts/gcc/flash.ld \
		-Wl,-Map,$(BUILD_DIR)/librainductor.map \
		-o $(BUILD_DIR)/librainductor.elf \
		-L$(BUILD_DIR) -mthumb \
		-Wl,--cref -Wl,--check-sections -Wl,--gc-sections -Wl,--entry=Reset_Handler \
		-Wl,--unresolved-symbols=report-all -Wl,--warn-common -Wl,--warn-section-align \
		-Wl,--warn-unresolved-symbols -Wl,--start-group $(BUILD_DIR)/crt/syscalls_sam3.o \
		$(BUILD_DIR)/uShell/gslice.o \
		$(BUILD_DIR)/uShell/gslist.o \
		$(BUILD_DIR)/uShell/gstring.o \
		$(BUILD_DIR)/uShell/garray.o \
		$(BUILD_DIR)/uShell/gbytes.o \
		$(BUILD_DIR)/uShell/gcommon.o \
		$(BUILD_DIR)/uShell/uShell.o \
		$(BUILD_DIR)/uShell/Window_GPIO.o \
		$(BUILD_DIR)/uShell/Window_Prompt.o \
		$(BUILD_DIR)/uShell/CyclicStack.o \
		$(BUILD_DIR)/librainductor.o \
		$(BUILD_DIR)/variant.o \
		$(ARDUINO_PATH)/hardware/arduino/sam/variants/arduino_due_x/libsam_sam3x8e_gcc_rel.a \
		$(BUILD_DIR)/core.a -Wl,--end-group -lm -gcc 

$(BUILD_DIR)/librainductor.bin: $(BUILD_DIR)/librainductor.elf
	arm-none-eabi-objcopy -O binary $(BUILD_DIR)/librainductor.elf $(BUILD_DIR)/librainductor.bin 

########################################################################

flash:
	stty --file /dev/ttyACM0 1200
	bossac --info --port=ttyACM0 --force_usb_port false --erase --write --boot=1 $(BUILD_DIR)/librainductor.bin --reset

terminal:
	screen /dev/ttyACM0 115200

########################################################################

clean:
	rm -v $(BUILD_DIR)/*.o
	rm -v $(BUILD_DIR)/crt/*.o
	rm -v $(BUILD_DIR)/crt/avr/*.o
	rm -v $(BUILD_DIR)/libsam/*.o
	rm -v $(BUILD_DIR)/libsam/USB/*.o
	rm -v $(BUILD_DIR)/uShell/*.o
	rm -v $(BUILD_DIR)/core.a
	rm -v $(BUILD_DIR)/librainductor.map
	rm -v $(BUILD_DIR)/librainductor.elf
	rm -v $(BUILD_DIR)/librainductor.bin

########################################################################

.PHONY: all

all: ushell libsam crt $(BUILD_DIR)/librainductor.bin

########################################################################
