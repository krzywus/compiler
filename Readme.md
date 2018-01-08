### Kompilator prostego języka imperatywnego

Prosty kompilator języka imperatywnego napisny w C++ przy użyciu BISON-a oraz FLEX-a. Gramatyka języka znajduje się w pliku grammar.txt, a kod maszyny rejestrowej odczytujący kod wynikowy kompilatora w pliku interpreter.c .
#### Uruchomienie
Aby skompilować program należy w katalogu głównym wykonać komendę
```sh
$ make
```
Pliki wynikowe zostaną umieszczone w folderze bin/ - plik główny posiada domyślną nazwę a.out. Aby jednocześnie skompilować oraz uruchomić kompilator należy wywołać
```sh
$ make run
```
Domyślnie wyniki są wypisywane na standardowe wyjście.
