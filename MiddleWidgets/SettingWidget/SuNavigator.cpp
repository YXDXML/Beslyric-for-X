﻿#include "SuNavigator.h"
#include <QPainter>
#include <QPixmap>

SuNavigator::SuNavigator(QVector<ISettingUnit*>& settingUnits, QWidget *parent)
    : QWidget(parent), pSettings(&settingUnits),nCurrentIndex(0)
{
    this->setMouseTracking(true);//详见 BesFramelessWidget.h 注释

    initEntity();
    initLayout();
    initConnection();
}

SuNavigator::~SuNavigator()
{

}

void SuNavigator::initEntity()
{

}

void SuNavigator::initLayout()
{

}

void SuNavigator::initConnection()
{

}

void SuNavigator::paintEvent(QPaintEvent *event)
{
    int marginTop = 10;

    QPainter p(this);
    //p.setPen(Qt::transparent);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(QColor(99,99,99,66),1));      //画笔颜色
    p.setBrush(QColor(99,99,99,66));            //画刷颜色

    int nRight = 40;
    int nTop = 40;
    int nStep = 40;
    int nr = 3;
    int nR = 5;

    //先画右侧的滑动槽 （2个小圆1条直线）
    if(pSettings->size() >= 1)
    {
        QPoint pt1 = QPoint(this->width() - nRight, nTop);
        QPoint pt2 = QPoint(this->width() - nRight, nTop + (pSettings->size() -1) * nStep);

        p.drawLine(QPoint(pt1.x(), pt1.y() + nr),QPoint(pt2.x(), pt2.y() - nr-1));

        p.setPen(QPen(QColor(99,99,99,00),1));  //画填充圆的时候，边缘画笔透明
        p.drawEllipse(pt1, nr, nr);
        p.drawEllipse(pt2, nr, nr);
    }

    //再画当前节点 红点高亮

    QPoint pt = QPoint(this->width() - nRight, nTop + nCurrentIndex * nStep);
    p.setBrush(QColor("#b82525"));            //画刷颜色
    p.drawEllipse(pt, nR, nR);

    QColor colorText;

    int textHeight = 26;

    //绘制文字
    for(int i =0; i < pSettings->size() ; i++)
    {
        if( i == nCurrentIndex)
            colorText = QColor("#b82525");
        else
            colorText = QColor("#828385");

        p.setPen(colorText);

        QRect r(this->width() - nRight-28 - 200, nTop + i * nStep - textHeight/ 2
                ,this->width() - nRight-28,  nTop + i * nStep + textHeight/ 2  );

        p.drawText(r,Qt::AlignRight, pSettings->at(i)->getName());
    }

    QWidget::paintEvent(event);
}

void SuNavigator::OnSettingUnitPanelPosChanged(int pos)
{
    pos += 100;  //当前导航是哪一个，并不严格看实际位置 pos
                //比如 加入有2个设置单元，当上一个设置单元只能看到 25px 大小时，
                //  其实上面那个设置基本看不到了，这是理应该认为是在看下面一个
                //  这里通过 将位置 + 50 ,效果是，当上一个剩下小于 50 ，会认为是下一个

    nCurrentIndex = 0;

    int nCumulate = 0;
    for(int i = 0; i< pSettings->size(); i++)
    {
        nCumulate += pSettings->at(i)->getUnitHeight();
        if(pos < nCumulate)
        {
            nCurrentIndex = i;
            break;
        }
    }

    update();
}
