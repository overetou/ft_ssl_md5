#Work title
TARGET=ft_ssl

#Directories
OBJ_DIR=obj
SRC_DIR=src
INC_DIRS=includes
LIB_DIRS=

#Compilation related indications
CC=clang
CFLAGS=-Wall -Wextra -Werror
LIBS=

#From there we use the info to compile everything.
SRC_FILE_NAMES = main.c md5.c error.c command_orientation.c md5_execute_loaded.c md5_param_exec.c stdin.c \
function_loading.c hex_disp.c sha256.c sha256_param_exec.c sha256_digest.c md5_final_exec.c md5_digest.c \
sha256_short_funcs.c sha256_init_constants.c
SOURCES=$(addprefix $(SRC_DIR)/, $(SRC_FILE_NAMES))
OBJS:=$(SOURCES:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)
INC_FLAGS=$(addprefix -I,$(INC_DIRS))
LIBIDR_FLAGS=$(addprefix -L,$(LIB_DIRS))
CFLAGS+=$(INC_FLAGS)
LIBS_FLAGS=$(addprefix -l,$(LIBS))
VPATH=$(SRC_DIR)

.phony: $(TARGET) clean re

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LIBIDR_FLAGS) $(LIBS_FLAGS)
	@echo "Compilation succeeded."

fast: $(OBJS)
	$(CC) $(CFLAGS) -O3 $(SOURCES) -o $(TARGET) $(LIBIDR_FLAGS) $(LIBS_FLAGS)
	@echo "Compilation succeeded. Gotta go fast!"

$(OBJS): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(INC_DIRS)/ft_ssl.h |$(OBJ_DIR)
	@$(COMPILE.c) $(OUTPUT_OPTIONS) -o $@ $<

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJS) $(TARGET)

re: clean $(TARGET)
