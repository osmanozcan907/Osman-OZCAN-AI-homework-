// dictionary.h
// CS50x — Week 5 — Speller
// Declares the maximum word length and the five functions you must implement.

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word in the dictionary
// (e.g. longest English word is 45 chars — we use 45 + null terminator)
// Bu sabiti dictionary.c içinde dizilerin boyutunu belirlemek için kullanmalısın.
#define LENGTH 45

// Prototypes of functions you must implement in dictionary.c
// Bu fonksiyonların gövdelerini dictionary.c içinde doldurman gerekiyor.

// Bir kelimenin sözlükte olup olmadığını kontrol eder.
bool check(const char *word);

// Kelimeyi bir sayısal indekse (hash table bucket) dönüştürür.
unsigned int hash(const char *word);

// Sözlük dosyasını okur ve Hash Table'ı bellekte oluşturur.
bool load(const char *dictionary);

// Sözlükte kaç kelime olduğunu döndürür.
unsigned int size(void);

// malloc ile ayrılan tüm belleği serbest bırakır.
bool unload(void);

#endif // DICTIONARY_H
