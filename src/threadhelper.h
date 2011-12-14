/*
  Liste les threads, recois les signaux, demande des infos pour cr des threads
  Entre autre c'est lui qui regardera le nombre de coeurs prsents sur la machine
*/
#ifndef THREADHELPER_H
#define THREADHELPER_H

#include <QObject>
#include "sudokuthread.h"

class ThreadHelper : public QObject
{
  Q_OBJECT

public:
  ThreadHelper();
  int cpuThreads() const;
  ulong nbrall() const;
  ulong nbrsave() const;
  SudokuData solAt(ulong i) const;
  int nthr() const;
  void reset();
  const QList<SudokuThread*> &tlist() const {return _tlist;}
public slots:
  void start(SudokuGame jeu);
  void stop();
private slots:
  void endThread();
private:
  QList<SudokuGame> decomposer(SudokuGame jeu);
  QList<SudokuGame> decomposerEn(SudokuGame jeu, int min);
signals:
  void finished();
private:
  QList<SudokuThread*> _tlist;
  int _cpu;
  QList<SudokuGame> _jeux;
  int _status;
};

#include <QTextStream>
extern QTextStream cout; // should be in its own file.
#endif // THREADHELPER_H
