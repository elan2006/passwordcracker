# Password/Hash Cracker
This is a Bcrypt hash cracker that can be used to crack passwords. It scans the wordlist concurrently and matches it with the given hash string. It uses 4 threads by default but it can use any number of threads you want by changing the `THREAD_COUNT` macro definition in the source file. Bcrypt is the most used hashing algorithm used for storing passwords so I decided to implement a bcrypt hash cracker but it can be swapped out with any hashing algorithm with few modifications to the code.

## Dependency
This program uses (libbcrypt)[https://github.com/trusch/libbcrypt] which needs to be installed for this to compile. You can visit their github repo for installation instructions.

## Compilation
Make sure you have C++ 17.
```
make
```

## Usage
```
usage: ./passwordcracker <hash> <wordlist>
```
Note: wrap the hash around single quotes or it will not work since the hashes have special characters that your shell might recognize.

## Example
The program creates a log file when it exits. It will either show the matched word for the given hash or it will show that it did not match any words from the wordlist.
```
./passwordcracker '$2a$15$9643u9dzSB9miuEBzu0Ko.EgANDVaoK/rZl3Xte.wXA/tZb9yLwVy' rockyou-200.txt 
hash: $2a$15$9643u9dzSB9miuEBzu0Ko.EgANDVaoK/rZl3Xte.wXA/tZb9yLwVy
Batch size: 50
102 Tried jesus
153 Tried cheese
51 Tried loveyou
0 Tried 123456
1 Tried 12345
52 Tried pretty
103 Tried estrella
154 Tried 159753
.
.
.
iloveu matched!
```
1752864247-result.log file:
```
hash $2a$15$9643u9dzSB9miuEBzu0Ko.EgANDVaoK/rZl3Xte.wXA/tZb9yLwVy found in the file rockyou-200.txt
$2a$15$9643u9dzSB9miuEBzu0Ko.EgANDVaoK/rZl3Xte.wXA/tZb9yLwVy - iloveu
```