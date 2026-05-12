# Objektinio programavimo egzamino išankstinė užduotis


## Aprašymas
Programa skaito tekstą iš failo ir atlieka šias užduotis:
- Suskaičiuoja kiek kartų kiekvienas žodis pasikartoja tekste
- Sukuria kryžminių nuorodų lentelę su eilučių numeriais
- Išrenka visus URL adresus iš teksto

## Naudojimas
1. Įklijuokite norimą tekstą į failą `input/sample.txt`
2. Sukompiliuokite programą:
```
make
```
3. Paleiskite programą:
```
./main
```

## Rezultatai
Rezultatai išsaugomi `output/` aplanke:
- `output.txt` — žodžiai kurie pasikartoja daugiau nei vieną kartą ir jų skaičius
- `cross-reference-table.txt` — žodžiai ir eilučių numeriai kuriose jie buvo rasti
- `url-list.txt` — visi rasti URL adresai

## Reikalavimai
- C++23
- g++ kompiliatorius

## Įdiegimo instrukcija
1. Įdiekite Homebrew (Mac paketų tvarkyklė)
Atidarykite terminalą ir įvykdykite:

/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
2. Įdiekite g++ kompiliatorių
brew install gcc
Patikrinkite ar įdiegta:

g++ --version
3. Klonuokite repozitoriją
git clone https://github.com/thrust0/antra-uzduotis-oop.git
cd antra-uzduotis-oop
4. Sukompiliuokite programą
make main
5. Paleiskite programą
./main
Windows vartotojams
Atsisiųskite ir įdiekite MinGW
Pridėkite C:\MinGW\bin į sistemos PATH
Atidarykite Command Prompt ir eikite į projekto aplanką:
