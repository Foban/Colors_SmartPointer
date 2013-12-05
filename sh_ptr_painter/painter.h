#ifndef PAINTER_H
#define PAINTER_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QLayout>
#include <QPixmap>
#include "my_shared_ptr.h"

const QString places[] = {"первый","второй","третий","четвертый","пятый",
                   "шестой","седьмой","восьмой","девятый","десятый"};
const QString colors[] = {"красный", "зеленый", "синий"};

const QString subcolors[] = {"краснее","зеленее","синее"};

class Painter : public QWidget
{
    Q_OBJECT

public:
    Painter(QWidget *parent = 0);
    ~Painter();

private:
    shared_ptr<QGridLayout> lay;
    shared_ptr<QPushButton> enter;
    shared_ptr<QLineEdit> cmdLine;
    shared_ptr<QLabel> *block;
    shared_ptr<QColor> *blockColor;
    void redrow(int num, int col, int subnum = -1);
    void useComand(QString comand);


private slots:
    void repaint();
};

class PaintException: public std::exception
{
public:
    PaintException(QString m):exep(m){}
    const QString exep;
};

#endif // PAINTER_H
