#ifndef SUDOKUCASEWIDGET_H
#define SUDOKUCASEWIDGET_H

#include <QLCDNumber>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QFocusEvent>
#include <QKeyEvent>
class SudokuWidget;

class SudokuCaseWidget : public QLCDNumber
{
  Q_OBJECT
public:
  Q_ENUMS(DisplayMode)
  enum DisplayMode {
    Edit, Normal, Error, NoError
  };
  SudokuCaseWidget(SudokuWidget* parent);
  void setRange(int min, int max) {_min = min; _max = max;}
  void setNullValue(int nul) { _nul = nul; }
public slots:
  void display(int num, DisplayMode mode = Normal);
  void setDisplayMode(DisplayMode mode);
signals:
  void valueChanged(int value);
  void valueEdited(int value);
protected:
  virtual void wheelEvent(QWheelEvent* event);
  virtual void mouseDoubleClickEvent(QMouseEvent* /*event*/);
  virtual void focusInEvent(QFocusEvent* /*event*/);
  virtual void focusOutEvent(QFocusEvent* /*event*/);
  virtual void keyPressEvent(QKeyEvent* event);
private:
  int _min, _max;
  int _nul;
  DisplayMode displayMode;
  bool errorMode;
};

#endif // SUDOKUCASEWIDGET_H
