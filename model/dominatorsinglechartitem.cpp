#include "dominatorsinglechartitem.h"
#include<QDebug>

DominatorSingleChartItem::DominatorSingleChartItem(QString* color, int shift, double startX, double startY, double endX, double endY)
    : color(color)
    , shift(shift)
    , startX(startX)
    , startY(startY)
    , endX(endX)
    , endY(endY)
{
}

int DominatorSingleChartItem::getShift() const
{
    return this->shift;
}

double DominatorSingleChartItem::getStartX() const
{
    return this->startX;
}

double DominatorSingleChartItem::getStartY() const
{
    return this->startY;
}

double DominatorSingleChartItem::getEndX() const
{
    return this->endX;
}

double DominatorSingleChartItem::getEndY() const
{
    return this->endY;
}

QString* DominatorSingleChartItem::getColor() const
{
    return this->color;
}
