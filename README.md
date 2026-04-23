## Unicode Tool (Lab 3)

Analysis for UTF-8 and UTF-16 encodings

## Functionality

Units: counts bytes for UTF-8 and 16-bit units for UTF-16.

Points: counts the actual number of characters (code points), taking into account multibyte sequences and surrogate pairs.

Words: counts words using basic Unicode whitespace delimiters.

Errors: detects and counts invalid byte sequences or broken surrogate pairs.

## Encoding Support (BOM)

Automatic file type detection using Byte Order Mark:

UTF-8: EF BB BF
UTF-16 BE: FE FF
UTF-16 LE: FF FE

## Build and Run

```bash
mkdir build
cd build
cmake ..
cmake --build .
./unicode_tool ../data/test_u16be.txt
```

## Exit Codes

0: successful execution.

1: file path not provided (missing arguments).

3: file access error (does not exist or is locked).

