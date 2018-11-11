#MAKE FILE
PROJ_NAME   := stm32f0_discoverry
#Dau cham dat trung cho thu muc chua makefile
PRO_DIR     :=.
OUTPUT_PATH := $(PRO_DIR)/output
LINKER_FILE := $(PRO_DIR)/linker/stm32f0.ld

#Cac duong dan tu make file den cac thu muc inc va src
INC_DIR     := $(PRO_DIR)/inc
SRC_DIR     := $(PRO_DIR)/src

#Phan dat cac quy uoc duong dan cua arm-none-eabi de su dung gcc:


COMPILER_DIR := ~/Desktop/gcc-arm-none-eabi-7-2018-q2-update-linux/gcc-arm-none-eabi-7-2018-q2-update
PREFIX_GCC_COMPILER := arm-none-eabi
CC           := $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-gcc
ASM	     := $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-as
LD	     := $(COMPILER_DIR)/bin/$(PREFIX_GCC_COMPILER)-ld

FILE_TO_LINK := $(OUTPUT_PATH)/systick.o $(OUTPUT_PATH)/usart.o $(OUTPUT_PATH)/interrupt.o $(OUTPUT_PATH)/button_polling.o $(OUTPUT_PATH)/gpio.o $(OUTPUT_PATH)/clock.o $(OUTPUT_PATH)/dht11.o $(OUTPUT_PATH)/main.o $(OUTPUT_PATH)/startup_ARMCM0.o

CC_OPT	     := -march=armv6-m -mcpu=cortex-m0 -c -O0 -g -mthumb -I$(INC_DIR)
ASM_OPT	     := -march=armv6-m -mcpu=cortex-m0 -c -mthumb
LD_OPT	     := -T $(LINKER_FILE) -Map $(OUTPUT_PATH)/$(PROJ_NAME).map $(FILE_TO_LINK)


#Tao ra cac rule de quy uoc cho viec make file:
$(OUTPUT_PATH)/dht11.o: $(SRC_DIR)/dht11.c
	@echo "compile $(SRC_DIR)/dht11.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/dht11.c -o $(OUTPUT_PATH)/dht11.o
$(OUTPUT_PATH)/systick.o: $(SRC_DIR)/systick.c
	@echo "compile $(SRC_DIR)/systick.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/systick.c -o $(OUTPUT_PATH)/systick.o
$(OUTPUT_PATH)/usart.o: $(SRC_DIR)/usart.c
	@echo "compile $(SRC_DIR)/usart.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/usart.c -o $(OUTPUT_PATH)/usart.o
$(OUTPUT_PATH)/interrupt.o: $(SRC_DIR)/interrupt.c
	@echo "compile $(SRC_DIR)/interrupt.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/interrupt.c -o $(OUTPUT_PATH)/interrupt.o
$(OUTPUT_PATH)/gpio.o: $(SRC_DIR)/gpio.c
	@echo "compile $(SRC_DIR)/gpio.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/gpio.c -o $(OUTPUT_PATH)/gpio.o
$(OUTPUT_PATH)/clock.o: $(SRC_DIR)/clock.c
	@echo "compile $(SRC_DIR)/clock.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/clock.c -o $(OUTPUT_PATH)/clock.o
$(OUTPUT_PATH)/button_polling.o: $(SRC_DIR)/button_polling.c
	@echo "compile $(SRC_DIR)/button_polling.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/button_polling.c -o $(OUTPUT_PATH)/button_polling.o
$(OUTPUT_PATH)/main.o: $(SRC_DIR)/main.c
	@echo "compile $(SRC_DIR)/main.c file"
	$(CC) $(CC_OPT) $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main.o

$(OUTPUT_PATH)/startup_ARMCM0.o: $(SRC_DIR)/startup_ARMCM0.s
	@echo "compile $(SRC_DIR)/startup_ARMCM0.S file"
	$(ASM) $(ASM_OPT) $(SRC_DIR)/startup_ARMCM0.s -o $(OUTPUT_PATH)/startup_ARMCM0.o

#Su dung linker tat ca cac file .o lai
build: $(FILE_TO_LINK) $(LINKER_FILE)
	@echo "link object files to creat new binary image ($(PROJ_NAME).elf)"
	$(LD) $(LD_OPT) -o $(OUTPUT_PATH)/$(PROJ_NAME).elf

#Phan nay bai 2 de hieu ro tung buoc tao ra file .o
#Phan pre tao file bo tat ca define marco vao main chinh
pre: $(SRC_DIR)/main.c
	@echo "compile $(SRC_DIR)/main.c file"
	$(CC) $(CC_OPT) -E $(SRC_DIR)/main.c -o $(OUTPUT_PATH)/main_pre.c
asm_code:$(OUTPUT_PATH)/main_pre.c
	@echo "compile $(OUTPUT_PATH)/main_pre.c file"
	$(CC) $(CC_OPT) -S $(OUTPUT_PATH)/main_pre.c -o $(OUTPUT_PATH)/main_pre.s
build_asm: $(OUTPUT_PATH)/main_pre.s
	@echo "compile $(OUTPUT_PATH)/main_pre.s file"
	$(ASM) $(ASM_OPT) $(OUTPUT_PATH)/main_pre.s -o $(OUTPUT_PATH)/main_pre.o
#De xoa tat ca cac file co trong output
clean:
	@rm -rf $(OUTPUT_PATH)/*
