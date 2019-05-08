#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDebug>

#include "model/dominatorsinglechartitem.h"
#include "utils.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    auto items = generate();

    auto size = items->size();
    QVector<int> shifts;

    QVector<double> xStarts;
    QVector<double> yStarts;
    QVector<double> xEnds;
    QVector<double> yEnds;
    QVector<QString> colors;

    for (auto i = 0; i < size; i++) {
        auto item = items->at(i);
        shifts.push_back(item->getShift());

        xStarts.push_back(item->getStartX());
        yStarts.push_back(item->getStartY());
        xEnds.push_back(item->getEndX());
        yEnds.push_back(item->getEndY());
        colors.push_back(*item->getColor());
    }


    engine.rootContext()->setContextProperty("modelShifts", QVariant::fromValue(shifts));
    engine.rootContext()->setContextProperty("xStarts", QVariant::fromValue(xStarts));
    engine.rootContext()->setContextProperty("yStarts", QVariant::fromValue(yStarts));
    engine.rootContext()->setContextProperty("xEnds", QVariant::fromValue(xEnds));
    engine.rootContext()->setContextProperty("yEnds", QVariant::fromValue(yEnds));
    engine.rootContext()->setContextProperty("modelColors", QVariant::fromValue(colors));

    engine.rootContext()->setContextProperty("modelSize", size);

    return app.exec();
}
