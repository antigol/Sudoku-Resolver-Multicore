#include "sudokuwidget.h"
#include "sudokutables.h"

SudokuWidget::SudokuWidget()
{
    QGridLayout* layout = new QGridLayout(this);
    QFrame* frames[9];

    for(int i=0; i<9; i++) {
        frames[i] = new QFrame(this);
        QGridLayout* frameLayout = new QGridLayout(frames[i]);
        frameLayout->setSpacing(3);
        frames[i]->setFrameShadow(QFrame::Raised);
        frames[i]->setFrameShape(QFrame::Box);
        layout->addWidget(frames[i], i/3, i%3);
    }

    for(int i=0; i<81; i++) {
        _cases[i] = new SudokuCaseWidget(this);
        _cases[i]->setFixedSize(28, 28);
        connect(_cases[i], SIGNAL(valueEdited(int)), this, SLOT(chercherErreurs()));
        _cases[i]->setRange(1, 9);
        _cases[i]->setNullValue(0);
        ((QGridLayout*)frames[i/9]->layout())->addWidget(_cases[i], i/3, i%3);
    }

    setLayout(layout);
}

SumoData SudokuWidget::getGrille()
{
    SumoData data;
    for(int i=0; i<81; i++)
        data.set((char)_cases[i]->intValue(), i);
    return data;
}

void SudokuWidget::setGrille(SumoData data)
{
    for(int i=0; i<81; i++)
        _cases[i]->display((int)data[i]);
}

void SudokuWidget::setAllDisplayMode(SudokuCaseWidget::DisplayMode mode)
{
    for(int i=0; i<81; i++)
        _cases[i]->setDisplayMode(mode);
}

void SudokuWidget::focusCentralCase()
{
    _cases[grille[0][4][4]]->setFocus(Qt::TabFocusReason);
}

void SudokuWidget::keyPressEvent(QKeyEvent* event)
{
    int id(0);
    for(int i(0); i<81; ++i)
        if(_cases[i] == focusWidget()) id = i;

    int x(0), y(0);
    for(int i(0); i<81; ++i)
        if(grille[0][i/9][i%9] == id)
        { x = i%9; y = i/9; }
    switch(event->key())
    {
    case Qt::Key_Left:
        if(x>0)
            id = grille[0][y][x-1];
        break;
    case Qt::Key_Up:
        if(y>0)
            id = grille[0][y-1][x];
        break;
    case Qt::Key_Right:
        if(x<8)
            id = grille[0][y][x+1];
        break;
    case Qt::Key_Down:
        if(y<8)
            id = grille[0][y+1][x];
        break;
    default:
        event->ignore();
        return;
    }
    if(id>=0 && id<81) _cases[id]->setFocus(Qt::TabFocusReason);
}

void SudokuWidget::chercherErreurs()
{
    setAllDisplayMode(SudokuCaseWidget::NoError);
    for (int i=0; i<3; ++i) {
        for (int j=0; j<9; ++j) {
            for (int k=0; k<9; ++k) {
                if (_cases[grille[i][j][k]]->intValue()) {
                    const int numero = _cases[grille[i][j][k]]->intValue();
                    for(int l=0; l<9; l++) {
                        if(l != k && _cases[grille[i][j][l]]->intValue() == numero) {
                            _cases[grille[i][j][k]]->setDisplayMode(SudokuCaseWidget::Error);
                        }
                    }
                }
            }
        }
    }
}
