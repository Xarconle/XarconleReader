#include "FileProcessor.h"

#include <QDateTime>
#include <QHash>
#include <QRegularExpression>
#include <QTextStream>
#include <QThread>
#include <QTimer>

#include "Defs.h"

static const QRegularExpression WORD_REG_EXP("^[a-zA-Zа-яА-Я]+$");
static const QRegularExpression NOT_WORD_REG_EXP("[^a-zA-Zа-яА-Я]");

//
//-----FileProcessor-----
//

// public:

FileProcessor::FileProcessor(int length, QObject* parent)
    : QObject(parent)
    , m_length(length)
{
}

bool
FileProcessor::openFile(const QString& fileName)
{
    if (!QFile::exists(fileName))
        return false;

    if (m_file.openMode() != QFile::OpenModeFlag::NotOpen)
        m_file.close();

    m_file.setFileName(fileName);

    return true;
}

void
FileProcessor::run()
{
    if (!m_file.open(QFile::OpenModeFlag::ReadOnly))
    {
        emit finished();
        return;
    }

    m_stop = false;
    m_pause = false;

    QTextStream in(&m_file);
    QHash<QString, uint64_t> frequencies;
    QString curWord;

    QTimer timer(this);
    timer.setSingleShot(true);
    timer.start(100);

    while (!in.atEnd())
    {
        if (timer.remainingTime() == 0 || !timer.isActive())
        {
            this->onTimeout();
            timer.start(100);
        }

        while (m_pause && !m_stop)
        {
            timer.stop();
        }

        if (m_stop)
        {

            m_file.close();
            timer.stop();
            emit finished();
            return;
        }

        in >> curWord;
        double tmp = in.pos() * 100 / m_file.size();
        m_curStatus = tmp;

        curWord.remove(NOT_WORD_REG_EXP);
        curWord = curWord.toLower();

        if (!WORD_REG_EXP.match(curWord).hasMatch() || curWord.size() < m_length)
            continue;

        ++frequencies[curWord];

        bool contains = false;
        int cur = 0;
        int min = 0;
        for (int i = 0; i < m_top15.size(); ++i)
        {
            if (m_top15[i].first == curWord)
            {
                m_top15[i].second = frequencies[m_top15[i].first];
                cur = i;
                contains = true;
                break;
            }

            if (frequencies[m_top15[i].first] < frequencies[m_top15[min].first])
                min = i;
        }

        if (m_top15.size() < CONSTANTS::MAX_TOP)
        {
            if (!contains)
                m_top15.push_back({curWord, frequencies[curWord]});
            else
                m_top15[cur].second = frequencies[curWord];
            continue;
        }

        if (!contains && frequencies[curWord] > frequencies[m_top15[min].first])
        {
            m_top15.removeAt(min);
            m_top15.push_back({curWord, frequencies[curWord]});
        }
    }

    m_file.close();
    timer.stop();
    emit finished();
}

void
FileProcessor::propel()
{
    m_pause = false;
}

void
FileProcessor::pause()
{
    m_pause = true;
}

void
FileProcessor::stop()
{
    m_stop = true;
}

void
FileProcessor::onTimeout()
{
    emit updateStatus(m_curStatus, m_top15);
}
