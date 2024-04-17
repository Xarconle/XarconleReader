#include "HorizontalBar.h"

#include <QBrush>
#include <QMutexLocker>
#include <QPainter>
#include <QPen>

#include "Defs.h"
#include "ToolTip.h"

static const QPen OUTLINE_PEN(Qt::GlobalColor::black, 2, Qt::PenStyle::SolidLine);
static const QPen TRANSPARENT_PEN(Qt::GlobalColor::transparent);

//
//-----HorizontalBar-----
//

// public:

HorizontalBar::HorizontalBar(int axisThickness, QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , m_borderPen(TRANSPARENT_PEN)
    , m_axisThickness(axisThickness)
{
    this->setAntialiasing(true);
    this->setAcceptHoverEvents(true);

    m_toolTipTimer.setSingleShot(true);
    connect(&m_toolTipTimer, &QTimer::timeout, this, &HorizontalBar::showToolTip);
}

HorizontalBar::~HorizontalBar()
{
    if (m_toolTip)
        m_toolTip->deleteLater();
}

void
HorizontalBar::paint(QPainter* painter)
{
    paintText(painter);
    paintBar(painter);
}

void
HorizontalBar::setLabel(const QString& label)
{
    QMutexLocker locker(&m_mutex);
    m_label = label;
}

QString
HorizontalBar::label() const
{
    return m_label;
}

void
HorizontalBar::setValue(int innerValue, double value)
{
    m_innerValue = innerValue;
    m_value = value;

    emit updateToolTip(QString::number(m_innerValue));
}

int
HorizontalBar::innerValue() const
{
    return m_innerValue;
}

// protected:

void
HorizontalBar::hoverEnterEvent(QHoverEvent* event)
{
    if (m_barRect.contains(event->position()))
    {
        m_borderPen = OUTLINE_PEN;
        this->update(boundingRect().toRect());
    }
    QQuickPaintedItem::hoverEnterEvent(event);
}

void
HorizontalBar::hoverMoveEvent(QHoverEvent* event)
{
    const bool isBar = m_barRect.contains(event->position());
    const bool isText = m_textRect.contains(event->position());

    if (isBar || isText)
    {
        if (isBar)
        {
            m_borderPen = OUTLINE_PEN;
            this->update(boundingRect().toRect());
            m_toolTipText = QString::number(m_innerValue);
        }
        else
        {
            m_borderPen = TRANSPARENT_PEN;
            this->update(boundingRect().toRect());
            m_toolTipText = m_label;
        }

        m_isText = isText;

        QPointF curPoint = parentItem()->mapFromItem(this, event->position());

        if (!m_toolTip && curPoint != m_toolTipPos)
        {
            m_toolTipTimer.start(700);
        }
        else if (m_toolTip && curPoint != m_toolTipPos)
        {
            m_toolTip->deleteLater();
            m_toolTip = nullptr;
        }

        m_toolTipPos = curPoint;
        m_isText = false;
    }
    else
    {
        m_borderPen = TRANSPARENT_PEN;
        this->update(boundingRect().toRect());

        m_toolTipTimer.stop();

        if (m_toolTip)
        {
            m_toolTip->deleteLater();
            m_toolTip = nullptr;
        }
    }

    QQuickPaintedItem::hoverMoveEvent(event);
}

void
HorizontalBar::hoverLeaveEvent(QHoverEvent* event)
{
    m_borderPen = TRANSPARENT_PEN;
    this->update(boundingRect().toRect());

    m_toolTipTimer.stop();

    if (m_toolTip)
    {
        m_toolTip->deleteLater();
        m_toolTip = nullptr;
    }

    QQuickPaintedItem::hoverLeaveEvent(event);
}

// private:

void
HorizontalBar::paintText(QPainter* painter)
{
    QPen pen(CONSTANTS::TEXT_COLOR);

    painter->setPen(pen);
    painter->setRenderHint(QPainter::TextAntialiasing);

    QString label = m_label;
    if (m_label.size() > 9)
        label =
            QString("%1%2%3").arg(m_label.mid(0, 3), "...", m_label.mid(m_label.length() - 2, 2));

    QRectF textRect = boundingRect();
    textRect.setWidth(CONSTANTS::AXIS_X);

    m_textRect =
        painter->boundingRect(textRect, label, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));

    painter->drawText(m_textRect, label, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));

    painter->setRenderHint(QPainter::TextAntialiasing, false);
}

void
HorizontalBar::paintBar(QPainter* painter)
{
    QBrush brush(CONSTANTS::MAIN_COLOR);

    painter->setBrush(brush);
    painter->setPen(m_borderPen);
    painter->setRenderHint(QPainter::Antialiasing);

    QSizeF itemSize = size();
    int x1 = CONSTANTS::AXIS_X - x() + m_axisThickness / 2 + m_axisThickness % 2;
    int x2 = m_value * (itemSize.width() - x1);
    m_barRect = QRectF(x1, 0, x2, height());

    painter->drawRect(m_barRect);

    painter->setRenderHint(QPainter::Antialiasing, false);
}

void
HorizontalBar::showToolTip()
{
    m_toolTip = new ToolTip(m_toolTipText, this->parentItem());

    m_toolTip->setX(m_toolTipPos.x());
    m_toolTip->setY(m_toolTipPos.y() - CONSTANTS::TOOLTIP_HEIGHT);
    m_toolTip->setWidth(CONSTANTS::TOOLTIP_WIDHT);
    m_toolTip->setHeight(CONSTANTS::TOOLTIP_HEIGHT);

    if (!m_isText)
        connect(this, &HorizontalBar::updateToolTip, m_toolTip, &ToolTip::setText);
}
