#ifndef WXR_DEMO_REFLECTIVITY_OBJECT_H
#define WXR_DEMO_REFLECTIVITY_OBJECT_H
#include <QWidget>
#include <vector>

#define RANGE_BIN_NUMBER 512
#define HAZARD_BUS_RANGE_RESOLUTION 0.0625
#define WINDSHEAR_SYMBOL_STRIP_LENTH 2

struct WindShearStruct
{
    unsigned int StartAngle:7;
    unsigned int EndAngle:7;
    unsigned int StartRange:7;
    unsigned int EndRange:7;
};

class Pie : public QPainterPath
{
    public:
        Pie(QPointF StartPoint, float Radius, float StartAngle, float EndAngle);
        QPainterPath GetArc();
        void GetArcStartEndPoint(QPointF* StartPoint, QPointF* EndPoint);
        ~Pie();
    private:
        QPainterPath m_ArcOfThePie;
        QPointF m_StartPoint;
        float m_Radius;
        float m_StartAngle;
        float m_EndAngle;
};


class RangeBinObject : public QLineF
{
    public:
        RangeBinObject(unsigned short data);
        ~RangeBinObject();
        void SetCoord(QPointF Start, QPointF End);
        QColor GetColour();
    
    private:
        unsigned short a_level;
        Qt::GlobalColor objColour;
};

class SectorObject
{
    public:
        SectorObject(unsigned short* data, float angle, float radius, QPointF scanCentre);
        ~SectorObject();
        std::vector<RangeBinObject*> GetSector();
    
    private:
        void CalcSector();
        
        float a_angle;
        float a_radius;
        QPointF a_scancentre;   
        float a_deltaX;
        float a_deltaY;
        unsigned short a_id;
        std::vector<RangeBinObject*> RangeBinVector;
};

class WindshearObject
{
    public:
        WindshearObject(QPointF Origin, WindShearStruct ShapeStruct, float radius, float NM);
        ~WindshearObject();
        QPainterPath GetWSDirectionIcon();
        std::vector<QPainterPath> GetWSSymbolIcon();

    private:

        QPointF a_Origin;
        std::vector<QPainterPath> a_WSSymbolIconGroup;
        QPainterPath a_WSDirectionIcon;
        float a_Radius;
        float a_NM;

        void GenerateShape();
        WindShearStruct a_ShapeStruct;
    

};

#endif //WXR_DEMO_REFLECTIVITY_OBJECT_H