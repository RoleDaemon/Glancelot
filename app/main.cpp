#include "glancelot/viewer_controller.hpp"
#include "image_canvas.hpp"
#include "glancelot/theme_manager.hpp"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QQuickWindow>
#include <QQuickStyle>
#include <QCommandLineParser>
#include <QElapsedTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTimer>
#include <cstdio>
#include <QIcon>

int main(int argc,char** argv) {
    QGuiApplication app(argc,argv);
    QCoreApplication::setApplicationName("Glancelot");
    QCoreApplication::setOrganizationName("Glancelot");
    QCoreApplication::setApplicationVersion("0.1.0-alpha.1");
    QQuickStyle::setStyle("Basic");
    QCommandLineParser parser;
    parser.setApplicationDescription("A local-first native photo viewer. JPEG/PNG alpha.");
    parser.addHelpOption();parser.addVersionOption();
    parser.addPositionalArgument("image","Image to open.","[image]");
    parser.addOption({"quit-after","Exit after the given milliseconds (test automation).","milliseconds"});
    parser.addOption({"screenshot","Save a canvas/window screenshot before timed exit.","path"});
    parser.addOption({"report","Write local JSON startup/render evidence before timed exit.","path"});
    parser.addOption({"theme","Select a built-in family (saved preference).","id"});
    parser.addOption({"theme-mode","Select system, dark, or light (saved preference).","mode"});
    parser.addOption({"show-themes","Open the theme picker at startup (test automation)."});
    parser.process(app);
    QElapsedTimer elapsed;elapsed.start();
    ViewerController viewer;
    ThemeManager theme;
    if(parser.isSet("theme"))theme.setFamily(parser.value("theme"));
    if(parser.isSet("theme-mode"))theme.setMode(parser.value("theme-mode"));
    app.setWindowIcon(QIcon(":/brand/icons/app/dark/glancelot-256.png"));
    qmlRegisterType<ImageCanvas>("Glancelot",1,0,"ImageCanvas");
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("viewer",&viewer);
    engine.rootContext()->setContextProperty("theme",&theme);
    QObject::connect(&engine,&QQmlApplicationEngine::objectCreationFailed,&app,[]{QCoreApplication::exit(2);},Qt::QueuedConnection);
    engine.loadFromModule("Glancelot","Main");
    if(engine.rootObjects().isEmpty())return 2;
    if(parser.isSet("show-themes"))QTimer::singleShot(100,engine.rootObjects().first(),[&]{QMetaObject::invokeMethod(engine.rootObjects().first(),"openThemes");});
    auto* window=qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    qint64 firstImage=-1,firstFrame=-1; int frames=0;
    QObject::connect(&viewer,&ViewerController::imageChanged,&app,[&]{if(firstImage<0&&!viewer.image().isNull())firstImage=elapsed.elapsed();});
    if(window)QObject::connect(window,&QQuickWindow::frameSwapped,&app,[&]{++frames;if(firstFrame<0&&!viewer.image().isNull())firstFrame=elapsed.elapsed();});
    if(!parser.positionalArguments().isEmpty())QTimer::singleShot(0,&viewer,[&]{viewer.open(parser.positionalArguments().first());});
    if(parser.isSet("quit-after")) {
        bool valid=false;const int duration=parser.value("quit-after").toInt(&valid);
        if(!valid || duration<100 || duration>3600000)return 2;
        QTimer::singleShot(duration,&app,[&]{
            if(window&&parser.isSet("screenshot"))window->grabWindow().save(parser.value("screenshot"));
            if(parser.isSet("report")) {
                QJsonObject report{{"version",QCoreApplication::applicationVersion()},{"qt",qVersion()},
                    {"decoded_ms",firstImage},{"first_image_frame_ms",firstFrame},{"frames",frames},
                    {"width",viewer.imageWidth()},{"height",viewer.imageHeight()},
                    {"loading",viewer.loading()},{"status",viewer.status()},
                    {"theme",theme.family()},{"theme_mode",theme.mode()},
                    {"graphics_api",window?int(window->rendererInterface()->graphicsApi()):0},
                    {"device_pixel_ratio",window?window->devicePixelRatio():1.0}};
                QFile file(parser.value("report"));if(file.open(QIODevice::WriteOnly))file.write(QJsonDocument(report).toJson());
            }
            app.exit(viewer.loading()?3:0);
        });
    }
    return app.exec();
}
