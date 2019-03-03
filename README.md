# Helmes anagram challenge

Challenge: https://www.helmes.com/careers/challenge/

Solution written in C. Should be O(n). Reading the dictionary file takes most of the time.

## Usage
```
./bin/anagram [path-to-dictionary] [word(s)]
```

## Build

Run `make`

### Examples
(Using the dictionary from http://www.eki.ee/tarkvara/wordlist/lemmad.zip)

Single-word:
```
> ./bin/anagram lemmad.txt mjaa
5120,ajam,jaam,jama,maja
```

Multi-word:
```
> ./bin/anagram lemmad.txt beta none
5230,nota bene
```

Disclaimer: I haven't written C in a long time.
