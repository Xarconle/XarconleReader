#include "ToolTip.h"

#include <QBrush>
#include <QPainter>
#include <QPen>

#include "Defs.h"

constexpr int ROUNDED = 8;

ToolTip::ToolTip(const QString& text, QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , m_text(text)
{
}

void
ToolTip::paint(QPainter* painter)
{
    paintRectangle(painter);
    paintText(painter);
}

void
ToolTip::setText(const QString& text)
{
    m_text = text;
    update(boundingRect().toRect());
}

void
ToolTip::paintRectangle(QPainter* painter)
{
    QBrush brush(CONSTANTS::MAIN_BG_COLOR);
    QPen pen(CONSTANTS::BORDER_COLOR);

    painter->setBrush(brush);
    painter->setPen(pen);
    painter->setRenderHint(QPainter::RenderHint::Antialiasing);

    QRectF textRect = painter->boundingRect(
        boundingRect(), m_text, QTextOption(Qt::AlignLeft | Qt::AlignVCenter));

    textRect.setWidth(textRect.width() + CONSTANTS::PADDING * 2);
    setWidth(qMax(textRect.width(), width()));

    painter->drawRoundedRect(boundingRect(), ROUNDED, ROUNDED);
    painter->setRenderHint(QPainter::Antialiasing, false);
}

void
ToolTip::paintText(QPainter* painter)
{
    QPen pen(Qt::GlobalColor::black);

    painter->setPen(pen);

    QRectF textRect = painter->boundingRect(
        boundingRect(), m_text, QTextOption(Qt::AlignHCenter | Qt::AlignVCenter));

    textRect.setWidth(textRect.width());

    painter->drawText(textRect, m_text);
}
