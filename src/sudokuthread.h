#ifndef SUDOKUTHREAD_H
#define SUDOKUTHREAD_H

#include <QThread>
#include "sumolib.h"
#include "biglist.h"

class SudokuThread : public QThread
{
public:
  SudokuThread(QObject* parent, SudokuGame jeu);
  virtual ~SudokuThread();

  int dejaRun() const;

  const BigList<SudokuData> & getSolutions() const {return _list;}
  unsigned long nbrSolutions() const {return _nbr;}

  void stop();

protected:
  virtual void run();

private:
  int bruteforce(const SudokuGame &jeu/*, int lvl = 0*/);

  BigList<SudokuData> _list;
  unsigned long _nbr;
  SudokuGame _jeu;
  int _stop;
  int _dejaRun;
};

#endif // SUDOKUTHREAD_H
