#ifndef FILEPROCESSOR_H
#define FILEPROCESSOR_H

#include <QFile>
#include <QObject>
#include <QString>

/*
 * FileProcessor
 *
 *
 */

class FileProcessor : public QObject
{
    Q_OBJECT

public:
    FileProcessor(int length, QObject* parent = nullptr);

    bool openFile(const QString& fileName);

    void run();
    void propel();
    void pause();
    void stop();

    void onTimeout();

signals:
    void finished(int exitCode = 0);
    void updateStatus(double status, const QList<QPair<QString, int>>& top15);

private:
    QFile m_file;

    std::atomic<int> m_length = 0;

    std::atomic<bool> m_pause = false;
    std::atomic<bool> m_stop = false;

    std::atomic<double> m_curStatus = 0;

    QList<QPair<QString, int>> m_top15;
};

#endif // FILEPROCESSOR_H
