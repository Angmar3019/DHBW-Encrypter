# Decrypting and Encrpyting via Terminal 

## User Documentation

[Anleitung zur Verwendung, Hinweise]

## Developer Documentation

### Input

[]

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
### Output
