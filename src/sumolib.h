#ifndef _HSUMOLIB
#define _HSUMOLIB

///////////////////////////////////////
//  ENUM CHIFFRES                    //
///////////////////////////////////////
enum {
    TOUS   = 0x01FF,
    ZERO   = 0x0000,
    UN     = 0x0001,
    DEUX   = 0x0002,
    TROIS  = 0x0004,
    QUATRE = 0x0008,
    CINQ   = 0x0010,
    SIX    = 0x0020,
    SEPT   = 0x0040,
    HUIT   = 0x0080,
    NEUF   = 0x0100
};
///////////////////////////////////////
//  Case du sudoku                   //
///////////////////////////////////////
class SudokuCase {
public:
    SudokuCase();
    int removeDigit(int f);
    void setValue(int f);
    int digitAmount() const { return _length; }
    int mask() const { return _digits; }
    SudokuCase& operator= (const SudokuCase& c);
private:
    int _digits;
    int _length;
};
///////////////////////////////////////
//  Une grille du jeu prette a être calculée //
///////////////////////////////////////
class SudokuGame {
public:
    SudokuGame() {}
    SudokuGame(const SudokuGame& g);
    SudokuCase& operator[] (int i) { return _cases[i]; }
    SudokuCase operator[] (int i) const { return _cases[i]; }
    SudokuGame& operator= (const SudokuGame& g);
    int verification() const;
    int rechercheSolutionsTriviales();
private:
    SudokuCase  _cases[81];
};

///////////////////////////////////////
//  Contient une grille de jeu en un minimum d'espace memoire //
///////////////////////////////////////
class SudokuData {
public:
    SudokuData();
    SudokuData(const SudokuGame& g);
    void setFromSudokuGame(const SudokuGame& g);
    void setData(char x, int i);
    char operator[] (int i) const;
    SudokuGame toSudokuGame();
private:
    unsigned char data[41];
};

#endif
