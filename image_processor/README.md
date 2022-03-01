# ImageProcessor
Image processor for .tga files

This project uses C++17 and the C standard library

.tga files can be viewed with GIMP (free), Adobe Photoshop, among others

The main function takes files from a folder "input" and writes to a folder "output"

Each task performs some transformation onto some file(s) from input, writes the transformed version to output, compares the file written to output
and its corresponding file in examples, and prints to the console whether the example file and output file are identical

The folders "input" and "examples" which contain the .tga files are provided
