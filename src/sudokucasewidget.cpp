#include "sudokucasewidget.h"
#include "sudokuwidget.h"
#include "sudokutables.h"

SudokuCaseWidget::SudokuCaseWidget(SudokuWidget* parent)
    : QLCDNumber(parent), _min(0), _max(10), _nul(-1), displayMode(Normal), errorMode(false)
{
    setSegmentStyle(QLCDNumber::Flat);
    setNumDigits(0);
    setFocusPolicy(Qt::StrongFocus);
}

void SudokuCaseWidget::display(int num, DisplayMode mode)
{
    if(num == _nul)
        setNumDigits(0);
    else if(num >= _min && num <= _max)
        setNumDigits(1);
    else return;

    if(mode == Edit) {
        setDisplayMode(Edit);
    } else {
        if(num != intValue() && num != _nul)
            setDisplayMode(Normal);
        else if(num == _nul)
            setDisplayMode(Edit);
    }

    if (num != intValue()) {
        QLCDNumber::display(num);
        emit valueChanged(num);
        if (mode == Edit)
            emit valueEdited(num);
    }
}

void SudokuCaseWidget::setDisplayMode(DisplayMode mode)
{
    QPalette pal = palette();
    switch (mode) {
    case Error:
        errorMode = true;
        break;
    case NoError:
        errorMode = false;
        break;
    default:
        displayMode = mode;
        break;
    }

    if (errorMode) {
        pal.setColor(QPalette::Foreground, Qt::red);
    } else {
        switch(displayMode)
        {
        case Error:
            break;
        case NoError:
            break;
        case Edit:
            pal.setColor(QPalette::Foreground, Qt::black);
            break;
        case Normal:
            pal.setColor(QPalette::Foreground, Qt::darkGreen);
            break;
        }
    }
    setPalette(pal);
}

void SudokuCaseWidget::wheelEvent(QWheelEvent* event)
{
    if(event->delta() > 0)
        display(intValue()+1, Edit);

    if(event->delta() < 0)
        display(intValue()-1, Edit);
}

void SudokuCaseWidget::mouseDoubleClickEvent(QMouseEvent* /*event*/)
{
    display(_nul, Edit);
}

void SudokuCaseWidget::focusInEvent(QFocusEvent* /*event*/)
{
    this->setFrameShadow(QFrame::Plain);
}

void SudokuCaseWidget::focusOutEvent(QFocusEvent* /*event*/)
{
    this->setFrameShadow(QFrame::Raised);
}

void SudokuCaseWidget::keyPressEvent(QKeyEvent* event)
{
    switch(event->key())
    {
    case Qt::Key_Delete:
    case Qt::Key_Backspace:
        display(_nul, Edit);
        break;
    case Qt::Key_0: display(0, Edit);
        break;
    case Qt::Key_1: display(1, Edit);
        break;
    case Qt::Key_2: display(2, Edit);
        break;
    case Qt::Key_3: display(3, Edit);
        break;
    case Qt::Key_4: display(4, Edit);
        break;
    case Qt::Key_5: display(5, Edit);
        break;
    case Qt::Key_6: display(6, Edit);
        break;
    case Qt::Key_7: display(7, Edit);
        break;
    case Qt::Key_8: display(8, Edit);
        break;
    case Qt::Key_9: display(9, Edit);
        break;
    case Qt::Key_A: display(0xA, Edit);
        break;
    case Qt::Key_B: display(0xB, Edit);
        break;
    case Qt::Key_C: display(0xC, Edit);
        break;
    case Qt::Key_D: display(0xD, Edit);
        break;
    case Qt::Key_E: display(0xE, Edit);
        break;
    case Qt::Key_F: display(0xF, Edit);
        break;
    case Qt::Key_Plus:
        display(intValue()+1, Edit);
        break;
    case Qt::Key_Minus:
        display(intValue()-1, Edit);
        break;
    default:
        event->ignore();
        break;
    }
}
