# RUN INSTRUCTIONS - ENIGMA

## 1. Met CMake (aanbevolen — gebruikt de meegeleverde `CMakeLists.txt`)

---

Maak een build-map en compileer:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

Start het programma (Linux/macOS):

```bash
./enigma
```

Start het programma (Windows, PowerShell/CMD):

```powershell
.\enigma.exe
```

> **Let op:** de meegeleverde `CMakeLists.txt` gebruikt C++20; zorg dat je compiler C++20 ondersteunt.

---

## 2. Directe compilatie zonder CMake

### Linux (g++)

```bash
g++ -std=c++20 -O2 -I. main.cpp encryption/Enigma.cpp -o enigma
./enigma
```

### macOS (clang++)

```bash
clang++ -std=c++20 -O2 -I. main.cpp encryption/Enigma.cpp -o enigma
./enigma
```

### Windows (MinGW-w64, CMD/PowerShell)

```powershell
g++ -std=c++20 -O2 -I. main.cpp encryption/Enigma.cpp -o enigma.exe
.\enigma.exe
```

---

## 3. Als je al een gecompileerde executable hebt

* **Linux/macOS:** voer `./enigma` uit in de map waar de executable staat.
* **Windows:** dubbelklik op `enigma.exe` of voer `enigma.exe` vanuit CMD/PowerShell.

---

## 4. Command-line opties (geen)

De huidige build accepteert geen extra CLI-argumenten; pas `main.cpp` aan voor andere inputs (`ciphertext`, `crib`, `threshold`).
Je moet in de main.cpp commenten of uncommenten om bepaalde stukjes code uit te kunnen voeren. 
Er zijn namelijk 2 delen: de decryptie en de bruteforce. Standaard zal de bruteforce uitgevoerd worden.

---
