#include "sudokuthread.h"

SudokuThread::SudokuThread(QObject* parent, SumoG jeu)
    : QThread(parent), _nbr(0), _jeu(jeu), _stop(0), _dejaRun(0)
{
}

SudokuThread::~SudokuThread()
{
    _list.clear();
}

int SudokuThread::dejaRun() const
{
    return _dejaRun;
}

void SudokuThread::stop()
{
    _stop = 1;
}

void SudokuThread::run()
{
    _dejaRun = 1;
    bruteforce(_jeu);
}

int SudokuThread::bruteforce(const SumoG &jeu/*, int lvl*/)
{
    if(_stop) return 1;

    register int minimum(10);
    register int id(0);
    for(register int i(0); i<81; ++i)
    {
        if(jeu[i].np() != 1 && jeu[i].np() < minimum)
        {
            minimum = jeu[i].np();
            id = i;
        }
    }

    if(minimum == 10)
    {
        _list.append(SumoData(jeu));
        _nbr++;
        return 0;
    }

    SumoG copie(jeu);

    for(register int chiffre=UN; chiffre<TOUS; chiffre<<=1)
    {
        if(copie[id].list() & chiffre)
        {
            copie[id].set(chiffre);

            while(copie.cherche()) ;

            if(copie.verification())
            {
                if(bruteforce(copie/*, lvl+1*/))
                    return 1;
            }
            copie = jeu;
        }
    }
    return 0;
}
