#include "HorizontalHistogram.h"

#include <QBrush>
#include <QPainter>
#include <QThreadPool>

#include "Defs.h"
#include "HorizontalBar.h"

HorizontalHistogram::HorizontalHistogram(QQuickItem* parent)
    : QQuickPaintedItem(parent)
{
}

void
HorizontalHistogram::paint(QPainter* painter)
{
    paintBackground(painter);
    paintAxis(painter);
    paintBars(painter);
}

void
HorizontalHistogram::updateTop(QList<QPair<QString, int>> top)
{
    for (const QPair<QString, int>& elem : top)
        addBar(elem.first, elem.second);
}

void
HorizontalHistogram::clear()
{
    for (HorizontalBar* bar : m_bars)
        bar->deleteLater();

    m_bars.clear();
    m_maxValue = 100;
    update(boundingRect().toRect());
}

void
HorizontalHistogram::paintBackground(QPainter* painter)
{
    QBrush brush(CONSTANTS::SECOND_BG_COLOR);

    painter->setBrush(brush);
    painter->setPen(CONSTANTS::BORDER_COLOR);
    painter->setRenderHint(QPainter::Antialiasing);

    QSizeF itemSize = size();
    painter->drawRect(0, 0, itemSize.width(), itemSize.height());

    painter->setRenderHint(QPainter::Antialiasing, false);
}

void
HorizontalHistogram::paintAxis(QPainter* painter)
{
    QBrush brush(CONSTANTS::AXIS_COLOR);
    QPen axisPen(brush, CONSTANTS::AXIS_THICKNESS);

    painter->setPen(axisPen);
    painter->setRenderHint(QPainter::Antialiasing);

    QSizeF itemSize = size();
    int width = itemSize.width() - CONSTANTS::RIGHT_X;
    int height = itemSize.height();
    painter->drawLine(CONSTANTS::AXIS_X, CONSTANTS::AXIS_Y, CONSTANTS::AXIS_X, itemSize.height());
    painter->drawLine(CONSTANTS::AXIS_X, CONSTANTS::AXIS_Y, width, CONSTANTS::AXIS_Y);

    QPen numPen(CONSTANTS::TEXT_COLOR);
    QPen addAxisPen(Qt::GlobalColor::gray);
    addAxisPen.setStyle(Qt::PenStyle::DashLine);

    auto drawLineLambda = [&](int cur, int max)
    {
        int textX = (width - CONSTANTS::AXIS_X) * cur / max + CONSTANTS::AXIS_X;
        painter->setPen(numPen);
        painter->drawText(
            textX - 5, CONSTANTS::AXIS_Y - 5, QString::number(m_maxValue * cur / max));
        painter->setPen(addAxisPen);
        painter->drawLine(textX, CONSTANTS::AXIS_Y, textX, height);
    };

    for (int i = 1; i <= 4; ++i)
        drawLineLambda(i, 4);

    painter->setRenderHint(QPainter::Antialiasing, false);
}

void
HorizontalHistogram::paintBars(QPainter* painter)
{
    updateBars();
    for (HorizontalBar* bar : m_bars)
    {
        bar->setWidth(width() - CONSTANTS::RIGHT_X);
        bar->update(bar->boundingRect().toRect());
    }
}

void
HorizontalHistogram::addBar(const QString& name, int value)
{
    HorizontalBar* bar = get(name);
    if (bar)
    {
        if (bar->innerValue() == value)
            return;

        bar->setValue(value, static_cast<double>(value) / m_maxValue);
    }
    else
    {
        bar = new HorizontalBar(CONSTANTS::AXIS_THICKNESS, this);
        bar->setLabel(name);

        if (value > m_maxValue)
        {
            m_maxValue = value;

            for (HorizontalBar* bar : m_bars)
            {
                int value = bar->innerValue();
                bar->setValue(value, static_cast<double>(value) / m_maxValue);
            }
        }

        if (m_bars.size() >= CONSTANTS::MAX_TOP)
        {
            auto tmp = m_bars.last();
            m_bars.removeLast();
            delete tmp;
        }

        m_bars.push_back(bar);
        bar->setValue(value, static_cast<double>(value) / m_maxValue);
    }

    if (value > m_maxValue)
    {
        m_maxValue = value;

        for (HorizontalBar* bar : m_bars)
        {
            int value = bar->innerValue();
            bar->setValue(value, static_cast<double>(value) / m_maxValue);
        }
    }

    updateBars();
    sortBars();
    update(boundingRect().toRect());
}

void
HorizontalHistogram::updateBars()
{
    qreal barThickness = (height() - CONSTANTS::AXIS_Y) / (m_bars.length() * 2 + 1);
    qreal barY = barThickness + CONSTANTS::AXIS_Y;
    for (HorizontalBar* bar : m_bars)
    {
        bar->setY(barY);
        bar->setHeight(barThickness);
        barY += barThickness * 2;
    }
}

void
HorizontalHistogram::sortBars()
{
    for (int i = 0; i < m_bars.length(); ++i)
    {
        for (int j = 0; j < m_bars.length() - 1; ++j)
        {
            if (m_bars[j]->innerValue() < m_bars[j + 1]->innerValue())
            {
                HorizontalBar* tmpStr = m_bars[j];
                m_bars[j] = m_bars[j + 1];
                m_bars[j + 1] = tmpStr;

                int tmp = m_bars[j]->y();
                m_bars[j]->setY(m_bars[j + 1]->y());
                m_bars[j + 1]->setY(tmp);
            }
        }
    }
}

HorizontalBar*
HorizontalHistogram::get(const QString& name) const
{
    for (int i = 0; i < m_bars.size(); ++i)
        if (m_bars[i]->label() == name)
            return m_bars[i];
    return nullptr;
}
