#ifndef WXR_DEMO_WEATHER_OBJECT_H
#define WXR_DEMO_WEATHER_OBJECT_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QObject>
#include <QPainter>
#include <vector>
#include <QMouseEvent>
#include <QTimer>
#include <cstring>


class WeatherObject : public QWidget
{
    Q_OBJECT

    public:
        WeatherObject(QWidget* parent = nullptr);
        ~WeatherObject();
        
        void SetDimension(float x, float y, float radius);

    protected:
        void paintEvent(QPaintEvent* event);
        void mouseMoveEvent(QMouseEvent* e);

    private slots:
        void generateData()
        {
            unsigned short t;
            for (unsigned short i = 0; i < 512; i++)
            {   
                if (i < 102)
                {
                    t = 1;
                }
                else if (i >= 102 && i < 204)
                {
                    t = 2;
                }
                else if  (204 <= i && i < 306)
                {
                    t = 3;
                }
                else if  (306 <= i && i < 408)
                {
                    t = 5;
                }
                else if (408 <= i)
                {
                    t = 6;
                }
                memcpy(&m_055data[i], &t, sizeof(short));
            }
            a_angle += 0.0879;
            update();
            if (a_angle > 90){
                a_angle = -90;
            }
        }

    private:
        bool a_DisplayWeather;
        bool a_DisplayWindshear;
        bool m_weatherIsDrawed;
        bool m_windshaerIsDrawed;

        QTimer* timer;
        QPainter* P;

        float a_radius;
        float a_NM;
        QPointF a_scanCentre;
        QRectF a_boundingRect;
        unsigned short* m_055data;
        float  a_angle;

};

#endif //WXR_DEMO_WEATHER_OBJECT_H
