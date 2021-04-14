#pragma once

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <QWheelEvent>

#include <osgViewer/Viewer>
#include <osg/ref_ptr>
#include <osg/ShapeDrawable>
#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>
#include <osg/Material>
#include <osg/StateSet>
#include <osg/Camera>
#include <osgViewer/GraphicsWindow>

class QOSGWidget : public QOpenGLWidget
{
public:
    QOSGWidget(qreal sx, qreal sy, QWidget *parent);
    virtual ~QOSGWidget() {}
    void setScale(qreal sx, qreal sy);

protected:
    virtual void paintGL();
    virtual void resizeGL(int w, int h);
    virtual void initializeGL();
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void wheelEvent(QWheelEvent *event);
    virtual bool event(QEvent *event);

private:
    osg::ref_ptr<osgViewer::Viewer> viewer;
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> window;
    qreal scaleX, scaleY;
};
