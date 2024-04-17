#ifndef READERBACKEND_H
#define READERBACKEND_H

#include <QObject>
#include <QQmlEngine>
#include <QTimer>

/*
 * ReaderBackend
 *
 *
 */

class ReaderBackend final : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    static ReaderBackend* create(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

    Q_INVOKABLE QString getAppName() const;

    Q_INVOKABLE QList<QPair<QString, int>> getTop15() const;
    Q_INVOKABLE double status() const;

    Q_INVOKABLE void openFile(const QString& fileName);

    Q_INVOKABLE void processFile(int length = 0);

    Q_INVOKABLE QColor mainColor() const;
    Q_INVOKABLE QColor mainBgColor() const;
    Q_INVOKABLE QColor secondBgColor() const;
    Q_INVOKABLE QColor borderColor() const;

    Q_INVOKABLE int margin() const;
    Q_INVOKABLE int padding() const;
    Q_INVOKABLE int spacing() const;

    Q_INVOKABLE int mainHeight() const;
    Q_INVOKABLE int secondHeight() const;

signals:
    void propel();
    void pause();
    void stop();
    void finished();

    void updateStatus();

private:
    ReaderBackend(QQmlEngine* qmlEngine, QJSEngine* jsEngine);

    void onUpdateStatus(double status, const QList<QPair<QString, int>>& top15);

private:
    QQmlEngine* m_engine = nullptr;

    const QString m_appName = "XarconleReader";

    QString m_fileName;
    double m_status = 0;
    QList<QPair<QString, int>> m_top15;
};

#endif // READERBACKEND_H
