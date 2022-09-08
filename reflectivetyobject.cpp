#include <math.h>
//===============
#include "reflectivetyobject.h"
//===============
#include <QDebug>

Pie::Pie(QPointF StartPoint, float Radius, float StartAngle, float EndAngle) : QPainterPath(StartPoint)
{
    m_StartPoint = StartPoint;
    m_Radius = Radius;
    m_StartAngle = StartAngle;
    m_EndAngle = EndAngle;

    this->moveTo(m_StartPoint);
    this->arcTo(StartPoint.x() - Radius, StartPoint.y() - Radius, 2*Radius, 2*Radius, StartAngle, EndAngle-StartAngle);
    this->closeSubpath();
}

QPainterPath Pie::GetArc()
{

    m_ArcOfThePie.arcMoveTo(m_StartPoint.x() - m_Radius, m_StartPoint.y() - m_Radius, 2*m_Radius, 2*m_Radius, m_StartAngle);
    m_ArcOfThePie.arcTo(m_StartPoint.x() - m_Radius, m_StartPoint.y() - m_Radius, 2*m_Radius, 2*m_Radius, m_StartAngle, m_EndAngle-m_StartAngle);

    return m_ArcOfThePie;
}

void Pie::GetArcStartEndPoint(QPointF* StartPoint, QPointF* EndPoint)
{
    m_ArcOfThePie.arcMoveTo(m_StartPoint.x() - m_Radius, m_StartPoint.y() - m_Radius, 2*m_Radius, 2*m_Radius, m_StartAngle);
    *StartPoint = m_ArcOfThePie.currentPosition();
    m_ArcOfThePie.arcMoveTo(m_StartPoint.x() - m_Radius, m_StartPoint.y() - m_Radius, 2*m_Radius, 2*m_Radius, m_EndAngle);
    *EndPoint = m_ArcOfThePie.currentPosition();
}


Pie::~Pie()
{

}

RangeBinObject::RangeBinObject(unsigned short level) : QLineF()
{
    a_level = level;

    switch (a_level)
    {
    case 0:
        objColour = Qt::black;
        break;
    case 1:
        objColour = Qt::green;
        break;
    case 2:
        objColour = Qt::yellow;
        break;
    case 3:
        objColour = Qt::red;
        break;
    case 4:
        objColour = Qt::red;
        break;
    case 5:
        objColour = Qt::cyan;
        break;
    case 6:
        objColour = Qt::magenta;
        break;
    case 7:
        objColour = Qt::magenta;
        break;
    default:
        objColour = Qt::black;
        break;
    }

};

void RangeBinObject::SetCoord(QPointF Start, QPointF End)
{
    this->setPoints(Start, End);
}

QColor RangeBinObject::GetColour()
{
    return this->objColour;
}

RangeBinObject::~RangeBinObject()
{

};

SectorObject::SectorObject(unsigned short* data, float angle, float radius, QPointF scanCentre)
{
    a_angle = angle;
    a_scancentre = scanCentre;
    a_radius = radius;
    CalcSector();

    for (int i = 0; i < RANGE_BIN_NUMBER; i++)
    {
        RangeBinObject* obj = new RangeBinObject(data[i]);

        float PointStartX = scanCentre.x() + i * a_deltaX;
        float PointStartY = scanCentre.y() + i * a_deltaY;
        float PointEndX = scanCentre.x() + (i+1) * a_deltaX;
        float PointEndY = scanCentre.y() + (i+1) * a_deltaY;
        
        QPointF StartPoint(PointStartX, PointStartY);
        QPointF EndPoint(PointEndX, PointEndY);

        obj->SetCoord(StartPoint, EndPoint);
        RangeBinVector.push_back(obj);
    }
};

void SectorObject::CalcSector()
{
    float EndX = a_scancentre.x() - sin(a_angle*M_PI/180) * a_radius;
    float EndY = a_scancentre.y() + cos(a_angle*M_PI/180) * a_radius;
    
    a_deltaX = (a_scancentre.x() - EndX) / RANGE_BIN_NUMBER;
    a_deltaY = (a_scancentre.y() - EndY) / RANGE_BIN_NUMBER;
}

std::vector<RangeBinObject*> SectorObject::GetSector()
{
    return RangeBinVector;
}

SectorObject::~SectorObject()
{
    for (auto i : RangeBinVector)
    {
        delete i;
    }
}

WindshearObject::WindshearObject(QPointF Origin, WindShearStruct ShapeStruct, float radius, float NM)
{
    a_Origin = Origin;
    a_ShapeStruct = ShapeStruct;
    a_Radius = radius;
    a_NM = NM;
    GenerateShape();
}

WindshearObject::~WindshearObject()
{
    
}

void WindshearObject::GenerateShape()
{
    QRectF OuterBoundingRect = QRectF(0, 0, 2*a_Radius, 2*a_Radius);

    // Generate Windshear Symbol Lower pie
    float TargetStartNM = a_ShapeStruct.StartRange * HAZARD_BUS_RANGE_RESOLUTION;
    float TargetEndNM = a_ShapeStruct.EndRange * HAZARD_BUS_RANGE_RESOLUTION;

    float StartScreenLenth = TargetStartNM * a_Radius / a_NM;     // R * receive/NM = actual
    float EndScreenLenth = TargetEndNM * a_Radius / a_NM;

    float DeltaScreenLenth = EndScreenLenth - StartScreenLenth;
    float stripLenth = WINDSHEAR_SYMBOL_STRIP_LENTH * HAZARD_BUS_RANGE_RESOLUTION * a_Radius / a_NM;

    Pie LastCell = Pie(a_Origin, StartScreenLenth, 90 - a_ShapeStruct.EndAngle-0.05, 90 + a_ShapeStruct.StartAngle+0.05);
    for (float i = 1; i <= DeltaScreenLenth / stripLenth; i++)
    {
        Pie WindsherPieStrip = Pie(a_Origin, StartScreenLenth + i*stripLenth, 90 - a_ShapeStruct.EndAngle-0.05, 90 + a_ShapeStruct.StartAngle+0.05);
        a_WSSymbolIconGroup.push_back(WindsherPieStrip.subtracted(LastCell));

    }
    
    // Generate the Windshear Direction Symbol
    Pie WindShearPie = Pie(a_Origin, EndScreenLenth, 90 - a_ShapeStruct.EndAngle-0.5, 90 + a_ShapeStruct.StartAngle+0.5);
    Pie DirBackground = Pie(a_Origin, a_Radius, 90 - a_ShapeStruct.EndAngle, 90 + a_ShapeStruct.StartAngle); //Direction Indication background
    Pie DirClipCell = Pie(a_Origin, a_Radius - 5, 93 - a_ShapeStruct.EndAngle, 87 + a_ShapeStruct.StartAngle); //Direction Indication Cell

    a_WSDirectionIcon.addPath(DirBackground.subtracted(WindShearPie).subtracted(DirClipCell));    
}

QPainterPath WindshearObject::GetWSDirectionIcon()
{
    return a_WSDirectionIcon.simplified();
}

std::vector<QPainterPath> WindshearObject::GetWSSymbolIcon()
{
    std::reverse(a_WSSymbolIconGroup.begin(), a_WSSymbolIconGroup.end());
    return a_WSSymbolIconGroup;
}

