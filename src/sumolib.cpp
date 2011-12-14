#include "sumolib.h"
#include "sudokutables.h"

// SumoC
SudokuCase::SudokuCase()
{
    _digits = TOUS;
    _length = 9;
}

int SudokuCase::removeDigit(int f)
{
    if (_digits & f) {
        _digits &= ~f;
        _length--;
        return 1;
    }
    return 0;
}

void SudokuCase::setValue(int f)
{
    _digits = f;
    _length = 1;
}

SudokuCase& SudokuCase::operator= (const SudokuCase& c)
{
    _digits = c._digits;
    _length = c._length;
    return *this;
}

// SumoG
SudokuGame::SudokuGame(const SudokuGame& g)
{
    for (int i(0); i<81; ++i) _cases[i] = g[i];
}

SudokuGame& SudokuGame::operator= (const SudokuGame& g)
{
    for (int i(0); i<81; ++i) _cases[i] = g[i];
    return *this;
}

int SudokuGame::verification() const
{
    // Test si une case n'accepete aucun chiffre possible
    for(int i=0; i<81; ++i)
        if(_cases[i].digitAmount() == 0)
            return 0;

    // Vérification validité de la grille
    // Regarde si un element est à double dans sa ligne, colonne, carré
    for (int i=0; i<3; ++i) {
        for (int j=0; j<9; ++j) {
            for (int k=0; k<9; ++k) {
                if (_cases[grille[i][j][k]].digitAmount() == 1) {
                    const int numero = _cases[grille[i][j][k]].mask();
                    for(int l=0; l<9; l++)
                        if(l != k && _cases[grille[i][j][l]].mask() == numero)
                            return 0;
                }
            }
        }
    }

    return 1;
}

int SudokuGame::rechercheSolutionsTriviales()
{
    int ok(0);

    // il prend un case fixée et enleve les chiffres dans sa ligne, colonne, carré.
    for (int i=0; i<3; ++i) {
        for (int j=0; j<9; ++j) {
            for (int k=0; k<9; ++k) {
                if (_cases[grille[i][j][k]].digitAmount() == 1) {
                    const int numero = _cases[grille[i][j][k]].mask();
                    for (int l=0; l<9; l++)
                        if (l != k)
                            if (_cases[grille[i][j][l]].removeDigit(numero))
                                ok = 1;
                }
            }
        }
    }

    for (int chiffre=UN; chiffre<TOUS; chiffre<<=1) {
        for (int i=0; i<3; ++i) {
            for (int j=0; j<9; ++j) {
                int nbr_vus = 0;
                int kk(0);
                for (int k=0; k<9; ++k)
                    if(_cases[grille[i][j][k]].mask() & chiffre) { nbr_vus++; kk = k; }
                if(nbr_vus == 1) // Si le chiffre apparait qu'une fois dans la ligne, colonne ou le carr alors
                {
                    if(_cases[grille[i][j][kk]].mask() != chiffre) {
                        ok = 1;
                        _cases[grille[i][j][kk]].setValue(chiffre); // il est attribu a la seul case qui peu le prendre
                    }
                }
            }
        }
    }

    return ok;
}

// SumoData
SudokuData::SudokuData()
{
    for(int i(0); i<41; ++i) data[i] = 0;
}

SudokuData::SudokuData(const SudokuGame& g)
{
    setFromSudokuGame(g);
}

void SudokuData::setFromSudokuGame(const SudokuGame& g)
{
    for(int i(0); i<81; ++i)
    {
        if(g[i].digitAmount() == 1)
        {
            int x = 0;
            while(g[i].mask() ^ (1<<x++)) ;
            setData(x, i);
        } else {
            setData(0, i);
        }
    }
}

void SudokuData::setData(char x, int i)
{
    int p = i/2;
    if(i%2) {
        data[p] &= 0x0F;
        data[p] |= (x<<4);
    } else {
        data[p] &= 0xF0;
        data[p] |= x;
    }
}

char SudokuData::operator[] (int i) const
{
    int p = i/2;
    if(i%2) {
        return (data[p]>>4);
    } else {
        return data[p] & 0x0F;
    }
}

SudokuGame SudokuData::toSudokuGame()
{
    SudokuGame g;
    for(int i(0); i<81; ++i)
    {
        char x = this->operator [](i);
        if(x)
        {
            g[i].setValue(1<<(x-1));
        }
    }
    return g;
}
