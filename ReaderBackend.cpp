#include "ReaderBackend.h"

#include <QApplication>
#include <QThread>

#include "Defs.h"
#include "FileProcessor.h"

//
//-----ReaderBackend-----
//

// public:

ReaderBackend*
ReaderBackend::create(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
{
    return new ReaderBackend(qmlEngine, jsEngine);
}

QString
ReaderBackend::getAppName() const
{
    return m_appName;
}

QList<QPair<QString, int>>
ReaderBackend::getTop15() const
{
    return m_top15;
}

double
ReaderBackend::status() const
{
    return m_status;
}

void
ReaderBackend::openFile(const QString& fileName)
{
    m_fileName = fileName;
}

void
ReaderBackend::processFile(int length)
{
    FileProcessor* processor = new FileProcessor(length);

    if (!processor->openFile(m_fileName))
    {
        delete processor;
        return;
    }

    connect(this, &ReaderBackend::propel, processor, &FileProcessor::propel, Qt::DirectConnection);
    connect(this, &ReaderBackend::pause, processor, &FileProcessor::pause, Qt::DirectConnection);
    connect(this, &ReaderBackend::stop, processor, &FileProcessor::stop, Qt::DirectConnection);

    QThread* thread = new QThread;
    processor->moveToThread(thread);

    connect(thread, &QThread::started, processor, &FileProcessor::run);

    connect(processor, &FileProcessor::updateStatus, this, &ReaderBackend::onUpdateStatus);

    connect(processor, &FileProcessor::finished, this, &ReaderBackend::finished);
    connect(processor, &FileProcessor::finished, thread, &QThread::exit);
    connect(processor, &FileProcessor::finished, processor, &FileProcessor::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}

QColor
ReaderBackend::mainColor() const
{
    return CONSTANTS::MAIN_COLOR;
}

QColor
ReaderBackend::mainBgColor() const
{
    return CONSTANTS::MAIN_BG_COLOR;
}

QColor
ReaderBackend::secondBgColor() const
{
    return CONSTANTS::SECOND_BG_COLOR;
}

QColor
ReaderBackend::borderColor() const
{
    return CONSTANTS::BORDER_COLOR;
}

int
ReaderBackend::margin() const
{
    return CONSTANTS::MARGIN;
}

int
ReaderBackend::padding() const
{
    return CONSTANTS::PADDING;
}

int
ReaderBackend::spacing() const
{
    return CONSTANTS::SPACING;
}

int
ReaderBackend::mainHeight() const
{
    return CONSTANTS::MAIN_HEIGHT;
}

int
ReaderBackend::secondHeight() const
{
    return CONSTANTS::SECOND_HEIGHT;
}

// private:

ReaderBackend::ReaderBackend(QQmlEngine* qmlEngine, QJSEngine* jsEngine)
    : QObject(qmlEngine)
    , m_engine(qmlEngine)
{
}

void
ReaderBackend::onUpdateStatus(double status, const QList<QPair<QString, int>>& top15)
{
    m_status = status;
    m_top15 = top15;
    emit this->updateStatus();
}
