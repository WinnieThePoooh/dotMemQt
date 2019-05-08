#include <QObject>
#include <QDateTime>
#include <QString>

#ifndef DOMINATORSINGLECHARTITEM_H
#define DOMINATORSINGLECHARTITEM_H


class DominatorSingleChartItem
{
public:
    DominatorSingleChartItem(QString* color, int shift, double startX, double startY, double endX, double endY);
    QString* getColor() const;
    int getShift() const;
    double getStartX() const;
    double getStartY() const;
    double getEndX() const;
    double getEndY() const;
private:
    QString* color;
    int shift;
    double startX;
    double startY;
    double endX;
    double endY;
};

#endif // DOMINATORSINGLECHARTITEM_H
