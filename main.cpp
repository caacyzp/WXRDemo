#include "mainwindow.h"
#include <QApplication>
#include "weatherobject.h"
#include <QDebug>
#include <string>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainWindow w;
    WeatherObject WXRObj;
    WXRObj.SetDimension(800, 800, 600);
    WXRObj.show();
    return a.exec();
}

#define  SET_BIT(arg, npos) ((arg) |= (1ULL << (npos-1)))
#define  GET_BIT(arg, npos) ((arg) >> (npos-1) & 1ULL )
#define FLIP_BIT(arg, npos) ((arg) ^= (1ULL << (npos-1)))
#define CLEAR_BIT(arg, npos) ((arg) &= ~(1ULL << (npos-1)))

struct WindShearStructTem
{
    unsigned int StartAngle:7;
    unsigned int EndAngle:7;
    unsigned int StartRange:7;
    unsigned int EndRange:7;
};

// int main()
// {
//     WindShearStructTem s;
//     unsigned int startAngle = 0b0001111;
//     unsigned int endAngle = 0b0011111;
//     s.EndAngle = endAngle;
//     s.StartAngle = startAngle;    
//     qDebug() << s.StartAngle << s.EndAngle;

//     return 0;
// }