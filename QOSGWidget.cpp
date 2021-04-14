#include "QOSGWidget.h"

QOSGWidget::QOSGWidget(qreal sx, qreal sy, QWidget *parent) :
    QOpenGLWidget(parent),
    viewer(new osgViewer::Viewer),
    window(new osgViewer::GraphicsWindowEmbedded(x(), y(), width(), height())),
    scaleX(sx),
    scaleY(sy)
{
    osg::Cylinder *cylinder = new osg::Cylinder(osg::Vec3(0.f, 0.f, 0.f), 0.25f, 0.5f);
    osg::ShapeDrawable *shape = new osg::ShapeDrawable(cylinder);
    shape->setColor(osg::Vec4(0.8f, 0.5f, 0.2f, 1.f));
    osg::Geode *geode = new osg::Geode;

    osg::Camera *camera = new osg::Camera;
    camera->setViewport(0, 0, width(), height());
    camera->setClearColor(osg::Vec4(0.9f, 0.9f, 1.f, 1.f));
    camera->setProjectionMatrixAsPerspective(30.f, (float)width() / (float)height(), 1.f, 1000.f);
    camera->setGraphicsContext(window);

    viewer->setCamera(camera);
    geode->addDrawable(shape);
    osgGA::TrackballManipulator *manipulator = new osgGA::TrackballManipulator;
    manipulator->setAllowThrow(false);
    setMouseTracking(true);
    viewer->setCameraManipulator(manipulator);
    viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
    viewer->setSceneData(geode);
    viewer->realize();
}

void QOSGWidget::setScale(qreal x, qreal y)
{
    scaleX = x;
    scaleY = y;
    resizeGL(width(), height());
}

void QOSGWidget::paintGL()
{
    viewer->frame();
}

void QOSGWidget::resizeGL(int w, int h)
{
    window->getEventQueue()->windowResize(x() * scaleX, y()*scaleY, w * scaleX, h * scaleY);
    window->resized(x() * scaleX, y() * scaleY, w * scaleX, h * scaleY);
    osg::Camera *camera = viewer->getCamera();
    camera->setViewport(0, 0, width() * scaleX, height() * scaleY);
}

void QOSGWidget::initializeGL()
{
    osg::Geode *geode = dynamic_cast<osg::Geode *>(viewer->getSceneData());
    osg::StateSet *state = geode->getOrCreateStateSet();
    osg::Material *mat = new osg::Material;
    mat->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);
    state->setAttributeAndModes(mat, osg::StateAttribute::ON);
    state->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);
}

void QOSGWidget::mouseMoveEvent(QMouseEvent * event)
{
    window->getEventQueue()->mouseMotion(event->x() * scaleX, event->y() * scaleY);
}

void QOSGWidget::mousePressEvent(QMouseEvent * event)
{
    unsigned int button = 0;
    switch (event->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MiddleButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    default:
        break;
    }
    window->getEventQueue()->mouseButtonPress(event->x() * scaleX, event->y() * scaleY, button);
}

void QOSGWidget::mouseReleaseEvent(QMouseEvent * event)
{
    unsigned int button = 0;
    switch (event->button())
    {
    case Qt::LeftButton:
        button = 1;
        break;
    case Qt::MiddleButton:
        button = 2;
        break;
    case Qt::RightButton:
        button = 3;
        break;
    default:
        break;
    }
    window->getEventQueue()->mouseButtonRelease(event->x() * scaleX, event->y() * scaleY, button);
}

void QOSGWidget::wheelEvent(QWheelEvent * event)
{
    osgGA::GUIEventAdapter::ScrollingMotion motion = event->delta() > 0 ? osgGA::GUIEventAdapter::SCROLL_UP : osgGA::GUIEventAdapter::SCROLL_DOWN;
}

bool QOSGWidget::event(QEvent * event)
{
    bool handle = QOpenGLWidget::event(event);
    update();
    return handle;
}

