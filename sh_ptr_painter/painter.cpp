#include "painter.h"

Painter::Painter(QWidget *parent)
    : QWidget(parent),
      lay(new QGridLayout),
      enter(new QPushButton("Enter")),
      cmdLine(new QLineEdit),
      block(new shared_ptr<QLabel>[10]),
      blockColor(new shared_ptr<QColor>[10])
{
    QPixmap k(30,30);
    for(int i = 0; i < 10; ++i)
    {
        blockColor[i]=new QColor(0,0,0);
        k.fill(*blockColor[i]);
        block[i] = new QLabel;
        block[i]->setPixmap(k);
        lay->addWidget(block[i].getPointer(),0,i);
    }
    lay->addWidget(cmdLine.getPointer(),1,0,1,8);
    lay->addWidget(enter.getPointer(), 1, 8, 1,2);

    connect(enter.getPointer(),SIGNAL(clicked()), this, SLOT(repaint()));

    setLayout(lay.getPointer());
}

Painter::~Painter()
{

}

void Painter::redrow(int num, int col, int subnum)
{
    QPixmap k(30,30);
    if(subnum < 0)
    {
        switch (col) {
        case 0:
            blockColor[num]->setRgb(255,0,0);
            break;
        case 1:
            blockColor[num]->setRgb(0,255,0);
            break;
        case 2:
            blockColor[num]->setRgb(0,0,255);
            break;
        }
    }
    else
    {
        int colorR, colorG, colorB;
        switch (col) {
        case 0:
        {
            if((colorR=(blockColor[subnum]->red()+60))>255) colorR = 255;
            if((colorG=(blockColor[subnum]->green()-60))<0) colorG = 0;
            if((colorB=(blockColor[subnum]->blue()-60))<0) colorB = 0;
            break;
        }
        case 1:
        {
            if((colorR=(blockColor[subnum]->red()-60))<0) colorR = 0;
            if((colorG=(blockColor[subnum]->green()+60))>255) colorG = 255;
            if((colorB=(blockColor[subnum]->blue()-60))<0) colorB = 0;
            break;
        }
        case 2:
        {
            if((colorR=(blockColor[subnum]->red()-60))<0) colorR = 0;
            if((colorG=(blockColor[subnum]->green()-60))<0) colorG = 0;
            if((colorB=(blockColor[subnum]->blue()+60))>255) colorB = 255;
            break;
        }
        }
        blockColor[num]->setRgb(colorR, colorG, colorB);
    }
    k.fill(*blockColor[num]);
    block[num]->setPixmap(k);
}

void Painter::useComand(QString comand)
{
    try{
        QString place = comand.section(' ', 0, 0, QString::SectionSkipEmpty);
        bool fl;
        int i,c,l;
        for(i = 0, fl = true; i<10 && fl; ++i)
            if(places[i] == place) fl =false;
        if(!fl)
        {
            QString subcolor,color = comand.section(" ", 1,1, QString::SectionSkipEmpty);
            for(c = 0, fl = true; c<3 && fl; ++c)
                if(colors[c] == color) fl =false;
            if(!fl)
                redrow(i-1,c-1);
            else
            {
                subcolor = color.section(',',0,0);
                for(c = 0, fl = true; c<3 && fl; ++c)
                    if(subcolors[c] == subcolor)
                        fl =false;
                if(fl)
                    throw(PaintException("Wrong command(color): "+ subcolor));
                else if(color != subcolor+',')
                    throw(PaintException("Wrong punctuation"));
                else if(comand.section(" ", 2,2, QString::SectionSkipEmpty) == "чем")
                {
                    QString subplace = comand.section(" ", 3,3, QString::SectionSkipEmpty);
                    for(l = 0, fl = true; l<10 && fl; ++l)
                        if(places[l] == subplace) fl =false;
                    if(!fl)
                        redrow(i-1,c-1,l-1);
                    else
                        throw(PaintException("Wrong command(subplace): " + subplace));
                }
                else
                    throw(PaintException("Wrong subdescription: " + comand.section(" ", 2,2, QString::SectionSkipEmpty)));
            }
        }
        else
            throw(PaintException("Wrong command(place): " + place));
    }
    catch(PaintException &m){
        cmdLine->setText(cmdLine->text()+m.exep+". ");
    }
}


void Painter::repaint()
{
    QString comand = cmdLine->text(),workComand;
    cmdLine->setText("");
    int count = comand.count(';');
    if(count){
        workComand = comand.section(';', 0,0);
        if(workComand != "")
            useComand(workComand);
        for(int i = 1; i < count; ++i)
        {
            workComand = comand.section(';', i,i);
            if(workComand != "")
                useComand(workComand);
        }
    }
    else
        try{
        throw(PaintException("Not found ';'"));
    }
    catch(PaintException &m){
        cmdLine->setText(cmdLine->text()+m.exep+". ");
    }
}
