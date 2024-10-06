# PAA-word-sort

Sorting Wordlist with Insertion Sort and Merge Sort

This project provides a C program that reads a wordlist from a text file, sorts it using **Insertion Sort** and **Merge Sort**, and displays the number of steps each algorithm took. It processes words separated by newlines.

**Note**: The code is written in Brazilian Portuguese.

## Features
- Sorts words using **Insertion Sort** and **Merge Sort**
- Outputs the number of steps taken by each sorting algorithm

## Requirements
- A text file (`in`) containing words, each separated by a newline.

The code was tested using a shuffled version of the MIT `wordlist.txt` file, it was **NOT** tested with other files.

## Installation

1. Place your wordlist in a text file and rename it to `in`.
2. Compile the `main.c` file using a C compiler:

```bash
   gcc main.c -o sortwordlist
```

3. Run the program:

``` bash
./sortwordlist
```

## Usage

The program expects a file named in.txt in the working directory. The reason for this is that this repository is based on a school assignment where it was a requirement to name the input file `in`.

Upon execution, the program will generate two output files:
- `out1`: Contains the sorted contents of the `in` file using **Insertion Sort**.
- `out2`: Contains the sorted contents of the `in` file using **Merge Sort**.

## License

No license has been added yet.
