
//#include <QGuiApplication>
//#include <QQmlApplicationEngine>
//#include <QQmlContext>
#include <QDebug>
#include "math.h"
#include "model/dominatorsinglechartitem.h"

static std::string toHex(int c)
{
    auto divRes = c % 16;
    if (divRes < 10) {
        return std::to_string(divRes);
    }

    switch(divRes)
    {
        case 10: return "A";
        case 11: return "B";
        case 12: return "C";
        case 13: return "D";
        case 14: return "E";
        case 15: return "F";
    }
    throw 5;
}
static std::string createRGB(int r, int g, int b)
{
    auto cR = toHex(r/16) + toHex(r%16);
    auto cG = toHex(g/16) + toHex(g%16);
    auto cB = toHex(b/16) + toHex(b%16);
    auto res = "#" + cR + cG + cB;
    qInfo() << QString::fromStdString("create color " +
                                      std::to_string(r) + " " +
                                      std::to_string(g) + " " +
                                      std::to_string(b) + " " +
                                      res);
    return res;
}

static double calcDiff(double angle, double anchor)
{
    auto res = (std::abs(angle - anchor) / M_PI);
    if (res <= 1)
        return res;
    return 2 - res;
}

static void generateNextLayer(std::vector<DominatorSingleChartItem*>* result, int shift, int angleBegin, int angleEnd, std::string* colorPres)
{
    if (shift == 5){
        return;
    }

    auto count = shift == 0 ? 20: std::rand() % 20 + 2;
    auto lengths = std::vector<int>();
    auto elapsed = 100;
    for (auto i = 0; i < count; i++) {
        int val = (std::rand() % elapsed);//) / 2;
        if (val == 0) {
            continue;
        }
        elapsed = elapsed - val;
        lengths.push_back(val);
    }

    if (lengths.size() == 0)
    {
        return;
    }

    if (lengths.size() > 1)
    {
        std::sort(lengths.begin(), lengths.end());
        std::reverse(lengths.begin(), lengths.end());
    }

    auto itemAngleBegin = angleBegin;
    count = lengths.size();
    for (auto i = 0; i < count; i++) {
        auto length = lengths.at(i);
        if (length == 0) {
            continue;
        }
        double itemLength = (angleEnd - angleBegin) * length / 100;
        double itemAngleEnd = itemAngleBegin + itemLength;

        double itemAngleBeginRad = M_PI * itemAngleBegin/180;
        double itemAngleEndRad = M_PI * itemAngleEnd/180;
        double startX = std::cos(itemAngleBeginRad);
        double startY = std::sin(itemAngleBeginRad);
        double endX = std::cos(itemAngleEndRad);
        double endY = std::sin(itemAngleEndRad);
        std::string* currentColorPres = nullptr;
        if (colorPres == NULL) {
            double redAnchorAngle = 0;
            double greenAnchorAngle = M_PI * 2/3;
            double blueAnchorAngle = M_PI * 4/3;
            double redDiff = calcDiff(itemAngleBeginRad, redAnchorAngle);
            double greenDiff = calcDiff(itemAngleBeginRad, greenAnchorAngle);
            double blueDiff = calcDiff(itemAngleBeginRad, blueAnchorAngle);
            int redDec = 255 * (1 - redDiff);
            int greenDec = 255 * (1 - greenDiff);
            int blueDec = 255 * (1 - blueDiff);
            currentColorPres = new std::string(createRGB(redDec, greenDec, blueDec));
        }
        else {
            currentColorPres = new std::string(*colorPres);
        }

        generateNextLayer(result, shift + 1, itemAngleBegin, itemAngleEnd, currentColorPres);

        auto item = new DominatorSingleChartItem(
                    new QString(QString::fromStdString(*currentColorPres)),
                    shift,
                    startX,
                    startY,
                    endX,
                    endY);
        result->push_back(item);
        itemAngleBegin = itemAngleEnd;
    }
}

std::vector<DominatorSingleChartItem*>* generate()
{
    auto items = new std::vector<DominatorSingleChartItem*>();
    generateNextLayer(items, 0, 0, 360, nullptr);
    return items;
}
