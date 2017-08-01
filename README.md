# RandomWordFileGenerator_C

Populate a file with a specific number of random words.

### Usage:

Compile the source file:

```
gcc RandomWordGenerator.c -lcurl -o randomwords.out
```

Run the built file:

```
./randomwords.out -n 6 -f words.txt
```

### Options

f - specify name of file to write sequence of random words to

n - specify number of words to write

l - specify length for each new random word
