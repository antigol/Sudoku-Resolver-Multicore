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
  SumoData solAt(ulong i) const;
  int nthr() const;
  void reset();
  const QList<SudokuThread*> &tlist() const {return _tlist;}
public slots:
  void start(SumoG jeu);
  void stop();
private slots:
  void endThread();
private:
  QList<SumoG> decomposer(SumoG jeu);
  QList<SumoG> decomposerEn(SumoG jeu, int min);
signals:
  void finished();
private:
  QList<SudokuThread*> _tlist;
  int _cpu;
  QList<SumoG> _jeux;
  int _status;
};

#include <QTextStream>
extern QTextStream cout; // should be in its own file.
#endif // THREADHELPER_H
