# Included paths
VPATH = src/Algorithms src/Decrypt src/Encrypt src/Librarys src/Menu obj
OUT_DIR = obj

#GCC suffix
CC = gcc
CFLAG = -lssl -lcrypto

#Main programm 
Program = finalprogramm
MAIN_FILE = terminal.c
MAIN_OBJ = $(MAIN_FILE:.c=.o)

#Header files
DEP =	checkInput.h rsa.h caesar.h morse.h oneTimePad.h trithemius.h vigenere.h \
		menu_decrypt.h \
		menu_encrypt.h menu_encrypt_algo.h menu_encrypt_input.h menu_encrypt_options.h menu_encrypt_output.h \
		sha256.h \
		menu_core.h menu_home.h
FILE = $(MAIN_FILE) $(DEP:.h=.c)
OBJ =  $(addprefix $(OUT_DIR)/,$(DEP:.h=.o)) 

#Build and link process
$(Program): $(MAIN_OBJ) $(OBJ)
	$(CC) -o $@ $^ $(CFLAG)

$(OUT_DIR)/%.o: %.c %.h
	$(CC) -c $< -o $@ $(CFLAG)

$(MAIN_OBJ): $(FILE) $(DEP)

#run with "make all"
all: clean $(Program) run
	
#run with "make clean"
clean:
	@rm -f $(OUT_DIR)/*.o $(MAIN_OBJ) $(Program)	

#run with "make run"
run:
	./$(Program)