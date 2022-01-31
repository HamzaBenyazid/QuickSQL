<h1 align="center">QuickSQL compiler</h1>

<h4 align="center">
 "QuickSQL" A simple language for generating SQL scripts using a simplified and intuitive syntax.
<br>
Made during second year of engineering school.
</h4>

<p align="center">
    <img src="https://i.imgur.com/otIz6Hu.png" alt="screenshot">
</p>

## Some Features

* Simple syntax.
* Simple to use.
* Gives you a lot of infos about your errors to help you fix them. 
* Fast compilation.

## Installation

You must have installed **Make** and **GCC** on your computer to compile the program.

To compile and Run:
* **In Linux :**

1. Run command `make` in the folder which contains the `Makefile` to create the binary file.
2. Then, you can run the compiler with the command :`./quicksql inputfile output_file_name`

For example : `./quicksql inputFile.txt output` , this command will generate `output.sql` containing SQL code.

* **In Windows :**
1. Change the first line of the file `makefile` to `OS	:= Windows_NT`
2. Run command `make` in the folder which contains the `makefile` to create the binary file.
3. Then, you can run the compiler with the command :`./quicksql.exe inputfile output_file_name`


For example : `./quicksql.exe inputFile.txt output` , this command will generate `output.sql` containing SQL code.
