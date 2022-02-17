# Included paths
VPATH = src src/Algorithms src/Decrypt src/Encrypt src/Librarys src/Menu obj
OUT_DIR = obj

#GCC suffix
CC = gcc
XFLAG = -Isrc/Algorithms -Isrc/Decrypt -Isrc/Encrypt -Isrc/Librarys -Isrc/Menu
CFLAG = -lssl -lcrypto

#Main programm
Program = DHBW_Encrypter_Launcher.exe
MAIN_FILE = DHBW_Encrypter.c
MAIN_OBJ = $(MAIN_FILE:.c=.o)

#Header files
DEP =	checkInput.h caesar.h morse.h oneTimePad.h trithemius.h vigenere.h \
		menu_decrypt.h menu_decrypt_algo.h menu_decrypt_input.h menu_decrypt_options.h menu_decrypt_output.h \
		menu_encrypt.h menu_encrypt_algo.h menu_encrypt_input.h menu_encrypt_options.h menu_encrypt_output.h \
		getch.h navigation.h sha256.h \
		menu_core.h menu_home.h
FILE = $(MAIN_FILE) $(DEP:.h=.c)
OBJ =  $(addprefix $(OUT_DIR)/,$(DEP:.h=.o))

#Build and link process
$(Program): $(MAIN_OBJ) $(OBJ)
	$(CC) -o $@ $^ $(CFLAG)

$(OUT_DIR)/%.o: %.c %.h
	$(CC) $(XFLAG) -c $< -o $@ $(CFLAG)

$(MAIN_OBJ): $(FILE) $(DEP)
	$(CC) $(XFLAG) -c $< -o $@ $(CFLAG)

#run with "make all"
all: clean $(Program) run

#Compile only and dont execute
compile: clean $(Program)

#run with "make clean"
clean:
	@rm -f $(OUT_DIR)/*.o $(MAIN_OBJ) $(Program)

#run with "make run"
run:
	./$(Program)