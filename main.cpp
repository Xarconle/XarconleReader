#include <QApplication>
#include <QQmlApplicationEngine>

#include "HorizontalHistogram.h"
#include "ReaderBackend.h"

int
main(int argc, char* argv[])
{
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterSingletonType<ReaderBackend>(
        "ReaderBackend", 1, 0, "ReaderBackend", &ReaderBackend::create);

    qmlRegisterType<HorizontalHistogram>("HorizontalHistogramCpp", 1, 0, "HorizontalHistogramCpp");

    const QUrl url(u"qrc:/XarconleReader/main.qml"_qs);
    //    QObject::connect(
    //        &engine,
    //        &QQmlApplicationEngine::objectCreated,
    //        &app,
    //        [url](QObject* obj, const QUrl& objUrl)
    //        {
    //            if (!obj && url == objUrl)
    //                QCoreApplication::exit(-1);
    //        },
    //        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
