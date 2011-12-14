#ifndef SUDOKUWIDGET_H
#define SUDOKUWIDGET_H

#include "sudokucasewidget.h"
#include <QWidget>
#include <QGridLayout>
#include <QKeyEvent>
#include "sumolib.h"

class SudokuWidget : public QWidget
{
  Q_OBJECT
public:
  SudokuWidget();
  SudokuData getGrille();
  void setGrille(SudokuData data);
  void setAllDisplayMode(SudokuCaseWidget::DisplayMode mode);
  void focusCentralCase();
protected:
  virtual void keyPressEvent(QKeyEvent* event);
private slots:
  void chercherErreurs();
private:
  SudokuCaseWidget* _cases[81];
};

#endif // SUDOKUWIDGET_H
