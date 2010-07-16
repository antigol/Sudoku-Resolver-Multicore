#ifndef WIDGET_H
#define WIDGET_H

#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QtGui/QWidget>
#include <QSpinBox>
#include <QList>
#include <QProgressDialog>
#include <QMessageBox>
#include <QComboBox>
#include <QTimer>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QTime>
#include "threadhelper.h"
#include "sudokuwidget.h"

namespace Ui
{
  class Widget;
}

class Widget : public QWidget
{
  Q_OBJECT
public:
  Widget(QWidget *parent = 0);
  ~Widget();
private:
  Ui::Widget *ui;
  QProgressDialog* _progress;
  QTimer *showTimer;
  QTimer *bmTimer;

  QTime chrono;
  double _temps;

  double dernierTemps;
  ulong dernierDecompte;
  unsigned int _benchmarkMode;
  SumoData _sauvegarde;
  ThreadHelper threadHelper;
  SudokuWidget plateau;
  QNetworkAccessManager networkManager;
  void sauvegarderLeScore();
private slots:
  void on_comboBox_currentIndexChanged(int index);
  void on_spinBox_valueChanged(int index);
  void on_pushButton_search_clicked();
  void on_pushButton_reset_clicked();
  void on_pushButton_restore_clicked();
  void on_pushButton_save_clicked();
  void stopEvent();
  void afficherNbr();
  void verifBenchmark();
protected:
  virtual void keyPressEvent(QKeyEvent* event);
};

QString toStrKMG(long unsigned int x);

#endif // WIDGET_H
