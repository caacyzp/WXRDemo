#include <QPainter>
#include <QBrush>
#include <QPen>
#include <windows.h>
#include <algorithm>
//=====================
#include "weatherobject.h"
#include "reflectivetyobject.h"
//=====================
#include <QDebug>



WeatherObject::WeatherObject(QWidget* parent) : QWidget(parent)
{
    a_DisplayWeather = true;
    a_DisplayWindshear = true;
    m_weatherIsDrawed = false;
    m_windshaerIsDrawed = false;
    
    a_angle = 45;
    m_055data = (unsigned short*) malloc(512*sizeof(short));

    memset(m_055data, 0, 512);
   
    timer = new QTimer(this);
    this->setAttribute(Qt::WA_OpaquePaintEvent);
    this->setWindowFlags(Qt::FramelessWindowHint);
    connect(timer, SIGNAL(timeout()), this, SLOT(generateData()));
    timer->start(5);
};

WeatherObject::~WeatherObject()
{
    delete this->timer;
    free(m_055data);
};
void WeatherObject::mouseMoveEvent(QMouseEvent* e)
{
    qDebug() << e->x() << e->y();
}

void WeatherObject::SetDimension(float x, float y, float Radius)
{
    a_scanCentre.setX(Radius);
    a_scanCentre.setY(Radius);
    a_radius = Radius;

    float boudingRect_x = x - a_radius;
    float boudingRect_y = y - a_radius;

    a_boundingRect = QRectF(boudingRect_x, boudingRect_y, 2*a_radius, 2*a_radius);
    this->setGeometry(boudingRect_x, boudingRect_y, 2*a_radius, a_radius);
    
}

void WeatherObject::paintEvent(QPaintEvent* event)
{
    QPainter Painter(this);
    QPen Pen;
    QBrush Brush;

    // Painter.setRenderHints(QPainter::RenderHint::HighQualityAntialiasing, true);
 
    if (a_DisplayWeather)
    {
        SectorObject* sector = new SectorObject(m_055data, a_angle, a_radius, a_scanCentre);
        for (auto rangebin : sector->GetSector())
        {
            Pen.setWidthF(1.5);
            Pen.setColor(rangebin->GetColour());
            Painter.setPen(Pen);
            Painter.drawLine(rangebin->p1(), rangebin->p2());
        }

        delete sector;
    }
    if (a_DisplayWindshear)
    {
        // Test
        WindShearStruct s;
        s.StartRange = 32;
        s.EndRange = 50;
        s.StartAngle = 16;
        s.EndAngle = 16;
        //
        WindshearObject* WSO = new WindshearObject(a_scanCentre, s, a_radius, 5);
        Pen.setColor(Qt::darkYellow);
        Pen.setWidthF(0.5);

        Painter.setPen(Pen);
        Painter.fillPath(WSO->GetWSDirectionIcon(), QBrush(Qt::yellow));

        bool ColourFlag = false;
        for (auto i : WSO->GetWSSymbolIcon())
        {
            if (ColourFlag)
            {
                Painter.fillPath(i, QBrush(Qt::black));
                ColourFlag = false;
            }
            else
            {
                Painter.fillPath(i, QBrush(Qt::darkRed));
                ColourFlag = true;
            }
        }
        Painter.end();

        delete WSO;
    }
    else
    {
        Painter.eraseRect(a_boundingRect);
    }
}