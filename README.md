# text-compressor
Text Compression using Huffman Encoding in C++

## How to run

-run.bash must be executed first to compile the compress.cpp and decompres.cpp files alomg with the compression.cpp implementation file of compression.h header file.
-after respective .exe files are generated, execute them in order compression first followed by decompression
NOTE: The executable files may fail to execute in linux terminals or git bash (Reason not found yet). 
      Runs successfuly in command prompt. Since cmd cant execute bash files the bash file must be run in a different terminal or you can compilr the files manually by referring the bash file.



## Code Explanation

### 1. `compression.h`
This header file contains the class definitions and function declarations for the Huffman coding algorithm.

- **Node Class**: Represents a node in the Huffman tree.
  - Stores a character (`ch`), its frequency (`freq`), and pointers to its left and right children.
  
- **compare Class**: A comparator used by the priority queue to sort nodes based on their frequencies for Huffman tree construction.

- **Functions**:
  - `buildHuffmanTree()`: Builds the Huffman tree based on character frequencies.
  - `getCodes()`: Traverses the Huffman tree to generate Huffman codes for each character.
  - `encode()`: Encodes the input text using the Huffman codes.
  - `writeBits()`: Writes the encoded string as bits into a binary file.
  - `saveTree()`: Serializes and saves the Huffman tree structure into a file.
  - `loadTree()`: Loads the serialized Huffman tree from a file.
  - `decode()`: Decodes the compressed file back into the original text.

### 2. `error_handler.h`
This header contains a simple error handling mechanism (presumably a macro) used throughout the code to handle file-related or logical errors, such as failure to open files.

- **ERROR Macro/Function**: Stops the program and prints an error message when an issue occurs (e.g., file not found, failed to read/write).

### 3. `compress.cpp`
This file contains the logic for compressing a given text file using Huffman coding.

- **Steps**:
  1. Reads the input text file.
  2. Generates a Huffman tree based on character frequencies.
  3. Encodes the text into a series of bits based on the Huffman tree.
  4. Writes the encoded bits and the Huffman tree to a binary file (`.bin`).
  5. Deletes the original input text file.

### 4. `decompress.cpp`
This file handles the decompression of a binary file that was previously compressed using Huffman coding.

- **Steps**:
  1. Loads the Huffman tree from the binary file.
  2. Reads the compressed bits and decodes them back into the original text.
  3. Writes the decoded text into a new file with a `.txt` extension.
  4. Deletes the compressed binary file.

## How It Works (Overview)
1. **Compression**:
   - The input text file is read and analyzed for character frequency.
   - A Huffman tree is built, and each character is assigned a unique binary code based on its frequency (more frequent characters get shorter codes).
   - The text is then converted to its binary representation, and both the tree and the encoded data are written to a `.bin` file.

2. **Decompression**:
   - The binary file (`.bin`) is read, and the saved Huffman tree is reconstructed.
   - The binary data is decoded back into the original text using the Huffman tree.
   - The decoded text is written to a new text file.
