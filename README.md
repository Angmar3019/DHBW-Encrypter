# Decrypting and Encrpyting via Terminal 

## User Documentation

__1. Download__

  In order to use the DHBW Encrypter you have to download the repository first. Afterwards you have to extract the content.
  
  (Alternatively you can also clone the repository with `git clone https://github.com/CallMeHein/DHBW-INF21-Programmieren_1-Verschluesseler.git`.)
  

__2. Compile and run__

  Navigate to the folder with the previously downloaded files. In this directory you only have to execute the command `make all`. This will compile and start the program.


__3. Using the program__

  The program has the use to encrypt and decrypt texts with different algorithms.
  
  The control is related to `left = A`, `right = D` and `input/enter = S`.

## Developer Documentation

### Menu

* __Design__:

  In order to create a straightforward way of handling the menu generation, several functions have been created. These allow a simple and consistent way of creating the menu. The following elements were divided into individual functions:
  * Header
    *   Displays the name of the program.
  * Tab Section
    *   A section that shows the user which submenu is currently displayed.
  * Menu Line
    * Generates a empty line for the menu.
  * Footer
    * The end of the terminal, which contains information about the control. Optionally, it can be extended to allow further input from the user.

  Some of the functions have parameters. These are used to attach a specific marking to the selected element. For example, in the header it displays the current position where the user currently is.


* __Navigation__:

    Since the language c is limited in its basic function to constantly check for keyboard input, a function had to be implemented that does this. Uing the function [getch()](https://github.com/Angmar3019/getch) it is possible to constantly wait for keystrokes. The program then checks whether the key entered matches the previously defined keystroke. If this is not the case, the program reports this to the user and repeats the process until a valid keystroke is made.

### Input

In the program the user has three options for entering the message to be encrypted or decrypted. Each of these different options aims at the easy and fast input of data.

  * __Manual Input__:
  
      The content is entered directly in the terminal. the entered message is then passed on to the global variable to be processed later.
      
  * __Input via a file in the same directory__:

      The user enters the name of a file that is located in the same directory as the program. The program now opens the file and reads out the individual lines and processes them into a global variable.

  * __Input via a file an a path__:

      The input of a file with path does not differ from the previous one. However, a difference is made between the two methods in order to point out to the user the proper way to enter the file.

### Processing
   * __Controlling Input__:
     
      Before calling an algorithm's main function the input will be analyzed with the __checkInput module__.
     
      This is done by calling checkInput's self-titled function with the user's input and an integer ranging from 0 to 2 (inclusive) to indicate what limitations the input _should_ have
     * 0: checkInput returns true, if the input consists of only the printable ASCII-characters (ASCII codes 32 - 126). This is used for most algorithms
     * 1: checkInput returns true, if the input consists of only letters from the english alphabet or spaces. Converting to morse requires this restricted character set.
     * 2: checkInput returns true, if the input conststs of only valid letters in the (english) morse alphabet and spaces. Converting from morse requires this.
     
     Mode 0 and 1 are done by iterating over every character in the input and checking whether the character is valid. As soon as one character is invalid, the entire input becomes invalid.
     
     Mode 2 is similar. Instead of iterating over every character on it's own, the input is split by spaces, like written morse usually is. We then iterate over the resulting substrings and compare them with a list of valid morse strings. As soon as one substring is not in this list, the entire input is invalid.
     
     If the input is valid, algorithms continue with their main functions and return a pointer to a string that contains the output. Where possible, this points to the same address as the input, only rewriting the contents.
     Otherwise the algorithms return NULL.
   * __Caesar__:
   
      receives: input and key (int)
      
      Each character in the input is converted to it's ASCII-Code, to which the key is added (encoding) or subtracted (decoding). The result is modified to keep it between the printable range of 32 and 126. The character in the input is then replaced by the new character.
   
   * __Morse__:
      
      receives: input
      
      If encoding, the corresponding morse string of each letter in the input is appended to an output string via parallel arrays. Spaces in the input are conserved in the output
      
      If decoding, the input is split into an array of it's morse strings. We then iterate over this array and append the corresponding letter of each element to the output.
      
   * __Trithemius__:
      
      receives: input
      
      Each character in the input is converted to it's ASCII-Code. Then we add (encoding) or subtract (decoding) the _index_ of the character in the string to it's ASCII-Code. The result is modified to keep it between the printable range of 32 and 126. The character in the input is then replaced by the new character.
      
   * __Vigenere__:
      
      receives: input and key (string)
      
      Iterates over each character in the input and converts it to it's ASCII-Code, as well as the character in the key at the same index. If the key is shorter than the input, it's looped until the last character. After adding (encoding) or subtracting (decoding) these two ASCII-Codes, the result is modified to keep it between the printable range of 32 and 126. The chracter in the input is t hen replaced by the new character
      
   * __OneTimePad__:
      
      receives: input and key (string, length = length of input) (optional)
      
      If no key is given, generate a random key. This generated key is given to the user for future use.
      
      Otherwise, the process is the same as within the Vigenere algorithm, since the OneTimePad is a special, usually more secure, case of the Vigenere algorithm

### Checksum
  When encrypting, the user has the option of generating a checksum from the text entered. This checksum can be read in again during decryption to check whether the integrity of the input has been maintained. Here, the checksum is generated using the [SHA256](https://github.com/openssl/openssl/blob/master/include/openssl/sha.h) algorithm. Afterwards, a file is created in the working directory during the encryption process.


### Output
  When outputting, the text is read from the previously generated global variable. When necessary, a key entered by the user is then passed on to the corresponding algorithm.
  The key is also checked for compatibility with the selected algorithm during input. This is done by checking each character individually according to the specifications of the corresponding algorithm.
  
  When outputting the encrypted / decrypted content, the user has the possibility to choose between two output options.
  * output to terminal
  * output to a file
