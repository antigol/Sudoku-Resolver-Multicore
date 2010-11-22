#ifndef _HSUMOLIB
#define _HSUMOLIB

///////////////////////////////////////
//  ENUM CHIFFRES                    //
///////////////////////////////////////
enum {
  TOUS   = 0x1FF,
  ZERO   = 0x0,
  UN     = 0x1,
  DEUX   = 0x2,
  TROIS  = 0x4,
  QUATRE = 0x8,
  CINQ   = 0x10,
  SIX    = 0x20,
  SEPT   = 0x40,
  HUIT   = 0x80,
  NEUF   = 0x100
};
///////////////////////////////////////
//  SUMO C                           //
///////////////////////////////////////
class SumoC {
public:
  SumoC();
  int rmv(int f);
  void set(int f);
  int np() const { return _np; }
  int list() const { return _p; }
  SumoC& operator= (const SumoC& c);
private:
  int _p;
  int _np;
};
///////////////////////////////////////
//  SUMO G                           //
///////////////////////////////////////
class SumoG {
public:
  SumoG(){}
  SumoG(const SumoG& g);
  SumoC& operator[] (int i) { return _gr[i]; }
  SumoC operator[] (int i) const { return _gr[i]; }
  SumoG& operator= (const SumoG& g);
  int verification() const;
  int cherche();
private:
  SumoC  _gr[81];
};

///////////////////////////////////////
//  SUMO DATA                        //
///////////////////////////////////////
class SumoData {
public:
  SumoData();
  SumoData(const SumoG& g);
  void set(const SumoG& g);
  void set(char x, int i);
  char operator[] (int i) const;
  SumoG getG();
private:
  unsigned char data[41];
};

#endif
