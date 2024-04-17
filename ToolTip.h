#ifndef TOOLTIP_H
#define TOOLTIP_H

#include <QQuickPaintedItem>

class ToolTip : public QQuickPaintedItem
{
    Q_OBJECT
public:
    ToolTip(const QString& text, QQuickItem* parent = nullptr);

    virtual void paint(QPainter* painter) override;

    void setText(const QString& text);

private:
    void paintRectangle(QPainter* painter);
    void paintText(QPainter* painter);

private:
    QString m_text;
};

#endif // TOOLTIP_H
