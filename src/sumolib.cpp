#include "sumolib.h"
#include "sudokutables.h"

// SumoC
SumoC::SumoC()
{
  _p = TOUS;
  _np = 9;
}

int SumoC::rmv(int f)
{
  if (_p & f) {
    _p &= ~f;
    _np--;
    return 1;
  }
  return 0;
}

void SumoC::set(int f)
{
  _p = f;
  _np = 1;
}

SumoC& SumoC::operator= (const SumoC& c)
{
  _p = c._p;
  _np = c._np;
  return *this;
}

// SumoG
SumoG::SumoG(const SumoG& g)
{
  for (int i(0); i<81; ++i) _gr[i] = g[i];
}

SumoG& SumoG::operator= (const SumoG& g)
{
  for (int i(0); i<81; ++i) _gr[i] = g[i];
  return *this;
}

int SumoG::verification() const
{
  for(int i=0; i<81; ++i)
    if(_gr[i].np() == 0)
      return 0;

  for (int i=0; i<3; ++i) {
    for (int j=0; j<9; ++j) {
      for (int k=0; k<9; ++k) {
        if (_gr[grille[i][j][k]].np() == 1) {
          const int numero = _gr[grille[i][j][k]].list();
          for(int l=0; l<9; l++)
            if(l != k && _gr[grille[i][j][l]].list() == numero)
              return 0;
        }
      }
    }
  }

  return 1;
}

int SumoG::cherche()
{
  int ok(0);

  for(int i=0; i<3; ++i)
  {
    for(int j=0; j<9; ++j)
    {
      for(int k=0; k<9; ++k)
      {
        if(_gr[grille[i][j][k]].np() == 1)
        {
          const int numero = _gr[grille[i][j][k]].list();
          for(int l=0; l<9; l++)
            if(l != k)
              if(_gr[grille[i][j][l]].rmv(numero))
                ok = 1;
        }
      }
    }
  }

  for(int chiffre=UN; chiffre<TOUS; chiffre<<=1)
  {
    for(int i=0; i<3; ++i)
    {
      for(int j=0; j<9; ++j)
      {
        int nbr_vus = 0;
        int kk(0);
        for(int k=0; k<9; ++k)
          if(_gr[grille[i][j][k]].list() & chiffre) { nbr_vus++; kk = k; }
        if(nbr_vus == 1) // Si le chiffre apparait qu'une fois dans la ligne, colonne ou le carr alors
        {
          if(_gr[grille[i][j][kk]].list() != chiffre)
          {
            ok = 1;
            _gr[grille[i][j][kk]].set(chiffre); // il est attribu a la seul case qui peu le prendre
          }
        }
      }
    }
  }

  return ok;
}

// SumoData
SumoData::SumoData()
{
  for(int i(0); i<41; ++i) data[i] = 0;
}

SumoData::SumoData(const SumoG& g)
{
  set(g);
}

void SumoData::set(const SumoG& g)
{
  for(int i(0); i<81; ++i)
  {
    if(g[i].np() == 1)
    {
      int x = 0;
      while(g[i].list() ^ (1<<x++)) ;
      set(x, i);
    } else {
      set(0, i);
    }
  }
}

void SumoData::set(char x, int i)
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

char SumoData::operator[] (int i) const
{
  int p = i/2;
  if(i%2) {
    return (data[p]>>4);
  } else {
    return data[p] & 0x0F;
  }
}

SumoG SumoData::getG()
{
  SumoG g;
  for(int i(0); i<81; ++i)
  {
    char x = this->operator [](i);
    if(x)
    {
      g[i].set(1<<(x-1));
    }
  }
  return g;
}
