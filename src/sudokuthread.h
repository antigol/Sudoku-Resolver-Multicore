#ifndef SUDOKUTHREAD_H
#define SUDOKUTHREAD_H

#include <QThread>
#include "sumolib.h"
#include "biglist.h"

class SudokuThread : public QThread
{
public:
  SudokuThread(QObject* parent, SumoG jeu);
  virtual ~SudokuThread();

  int dejaRun() const;

  const BigList<SumoData> & getSolutions() const {return _list;}
  unsigned long nbrSolutions() const {return _nbr;}

  void stop();

protected:
  virtual void run();

private:
  int bruteforce(const SumoG &jeu/*, int lvl = 0*/);

  BigList<SumoData> _list;
  unsigned long _nbr;
  SumoG _jeu;
  int _stop;
  int _dejaRun;
};

#endif // SUDOKUTHREAD_H
