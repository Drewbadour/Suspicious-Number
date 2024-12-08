TARGET := suspicious-number

CC := /usr/bin/gcc

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -Werror

DEBUG_CFLAGS += -O0 -g3
DEBUG_CFLAGS += -Wno-error=unused-parameter
DEBUG_CFLAGS += -Wno-error=unused-variable
DEBUG_CFLAGS += -Wno-error=unused-function
DEBUG_CFLAGS += -Wno-error=null-dereference
DEBUG_CFLAGS += -march=native

RELEASE_CFLAGS += -O3
RELEASE_CFLAGS += -DRELEASE=1

TEST_CFLAGS += -DTESTING=1
TEST_CFLAGS += -DDEBUG=1

LIBS := -lm

# NOTE(Drew): TARGET_ARCHES is basically hard-coded to only be able to do two arches
MINIMUM_MACOS_VERSION := apple-macos11


BIN_DIR := bin
SRC_DIR := src
TEST_DIR := src/test
ASSET_DIR := assets
WORKFLOW_DIR := workflow
WORKFLOW_NAME := $(TARGET).alfredworkflow


ZIP_FLAGS += --recurse-paths
ZIP_FLAGS += --junk-paths
ZIP_FLAGS += --quiet


ALFRED_LINK_DIR := "$(HOME)/Library/Application Support/Alfred/Alfred.alfredpreferences/workflows"
NEW_ALFRED_LINK_DIR := "$(ALFRED_LINK_DIR)/user.workflow.$(TARGET)-debug"


COLOR_RESET   := \033[0m
COLOR_INFO    := \033[32m




### BUILD ###
.PHONY: all
all: debug


.PHONY: debug
debug: CFLAGS += $(DEBUG_CFLAGS)
debug: clean default_build


.PHONY: release
release: CFLAGS += $(RELEASE_CFLAGS)
release: clean universal_build


.PHONY: test
test: CFLAGS += $(DEBUG_CFLAGS)
test: CFLAGS += $(TEST_CFLAGS)
test: clean $(BIN_DIR)/test_runner


### CLEAN ###
.PHONY: clean
clean:
	@rm -rf $(WORKFLOW_DIR) $(BIN_DIR)/*

.PHONY: clean_arches
clean_arches:
	@rm -rf $(WORKFLOW_ARCHES_DIRS)


### WORKFLOW ASSEMBLY ###
$(WORKFLOW_DIR):
	@cp -r $(ASSET_DIR) $(WORKFLOW_DIR)


### BINARIES ###
$(BIN_DIR)/test_runner:
	$(CC) -o $@ $(TEST_DIR)/test_main.c $(CFLAGS) $(LIBS)

$(BIN_DIR)/conv_binary:
	$(CC) -o $@ $(SRC_DIR)/conv_binary.c $(CFLAGS) $(LIBS)
$(BIN_DIR)/conv_binary-x86_64:
	$(CC) -o $@ $(SRC_DIR)/conv_binary.c $(CFLAGS) $(LIBS) -target x86_64-$(MINIMUM_MACOS_VERSION)
$(BIN_DIR)/conv_binary-arm64:
	$(CC) -o $@ $(SRC_DIR)/conv_binary.c $(CFLAGS) $(LIBS) -target arm64-$(MINIMUM_MACOS_VERSION)
$(WORKFLOW_DIR)/conv_binary: $(WORKFLOW_DIR) $(BIN_DIR)/conv_binary-x86_64 $(BIN_DIR)/conv_binary-arm64
	lipo -create -output $@ $(BIN_DIR)/conv_binary-x86_64 $(BIN_DIR)/conv_binary-arm64

$(BIN_DIR)/conv_decimal:
	$(CC) -o $@ $(SRC_DIR)/conv_decimal.c $(CFLAGS) $(LIBS)
$(BIN_DIR)/conv_decimal-x86_64:
	$(CC) -o $@ $(SRC_DIR)/conv_decimal.c $(CFLAGS) $(LIBS) -target x86_64-$(MINIMUM_MACOS_VERSION)
$(BIN_DIR)/conv_decimal-arm64:
	$(CC) -o $@ $(SRC_DIR)/conv_decimal.c $(CFLAGS) $(LIBS) -target arm64-$(MINIMUM_MACOS_VERSION)
$(WORKFLOW_DIR)/conv_decimal: $(WORKFLOW_DIR) $(BIN_DIR)/conv_decimal-x86_64 $(BIN_DIR)/conv_decimal-arm64
	lipo -create -output $@ $(BIN_DIR)/conv_decimal-x86_64 $(BIN_DIR)/conv_decimal-arm64

$(BIN_DIR)/conv_hex:
	$(CC) -o $@ $(SRC_DIR)/conv_hex.c $(CFLAGS) $(LIBS)
$(BIN_DIR)/conv_hex-x86_64:
	$(CC) -o $@ $(SRC_DIR)/conv_hex.c $(CFLAGS) $(LIBS) -target x86_64-$(MINIMUM_MACOS_VERSION)
$(BIN_DIR)/conv_hex-arm64:
	$(CC) -o $@ $(SRC_DIR)/conv_hex.c $(CFLAGS) $(LIBS) -target arm64-$(MINIMUM_MACOS_VERSION)
$(WORKFLOW_DIR)/conv_hex: $(WORKFLOW_DIR) $(BIN_DIR)/conv_hex-x86_64 $(BIN_DIR)/conv_hex-arm64
	lipo -create -output $@ $(BIN_DIR)/conv_hex-x86_64 $(BIN_DIR)/conv_hex-arm64

.PHONY: default_build
default_build: $(BIN_DIR)/conv_binary $(BIN_DIR)/conv_decimal $(BIN_DIR)/conv_hex

.PHONY: universal_build
universal_build: $(WORKFLOW_DIR)/conv_binary $(WORKFLOW_DIR)/conv_decimal $(WORKFLOW_DIR)/conv_hex


### PACKAGING ###
$(WORKFLOW_NAME): release
	@zip $(ZIP_FLAGS) "$(WORKFLOW_NAME)" "$(WORKFLOW_DIR)"

.PHONY: package
package: $(WORKFLOW_NAME)
	@echo "Workflow file can be found at $(COLOR_INFO)$(WORKFLOW_NAME)$(COLOR_RESET)"


### LINKING ###
.PHONY: unlink
unlink:
	@echo "Unlinking $(COLOR_INFO)$(NEW_ALFRED_LINK_DIR)$(COLOR_RESET)"
	@rm -rf "$(NEW_ALFRED_LINK_DIR)"


.PHONY: link
link: unlink release
	@echo "Linking to $(COLOR_INFO)$(NEW_ALFRED_LINK_DIR)$(COLOR_RESET)"
	@mkdir -p "$(NEW_ALFRED_LINK_DIR)"
	@ln -s "$(shell pwd)"/"$(WORKFLOW_DIR)"/* "$(NEW_ALFRED_LINK_DIR)/"



### HELP ###
help:
	@echo "usage: make [$(COLOR_INFO)target$(COLOR_RESET)]"
	@echo "\t$(COLOR_INFO)build$(COLOR_RESET) - Compile all binaries in a debug build for the local architecture"
	@echo "\t$(COLOR_INFO)test$(COLOR_RESET) - Compile the unit tests for the local architecture"
	@echo "\t$(COLOR_INFO)release$(COLOR_RESET) - Compile all binaries in a release build for the local architecture"
	@echo "\t$(COLOR_INFO)package$(COLOR_RESET) - Create a universal $(WORKFLOW_NAME) for distribution"
	@echo "\t$(COLOR_INFO)link$(COLOR_RESET) - Link the workflow into the install of Alfred"
	@echo "\t$(COLOR_INFO)unlink$(COLOR_RESET) - Unlink the workflow from Alfred"
	@echo "\t$(COLOR_INFO)clean$(COLOR_RESET) - Delete all of the build products"
	@echo "\t$(COLOR_INFO)help$(COLOR_RESET) - This menu"
