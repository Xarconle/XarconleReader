#ifndef HORIZONTALBAR_H
#define HORIZONTALBAR_H

#include <QMutex>
#include <QPen>
#include <QQuickPaintedItem>
#include <QTimer>

class ToolTip;

/*
 * HorizontalBar
 *
 *
 */

class HorizontalBar : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    HorizontalBar(int axisThickness, QQuickItem* parent = nullptr);
    ~HorizontalBar();

    virtual void paint(QPainter* painter) override;

    void setLabel(const QString& label);
    QString label() const;

    void setValue(int innerValue, double value);
    int innerValue() const;

signals:
    void updateToolTip(const QString& innerValue);

protected:
    virtual void hoverEnterEvent(QHoverEvent* event) override;
    virtual void hoverMoveEvent(QHoverEvent* event) override;
    virtual void hoverLeaveEvent(QHoverEvent* event) override;

private:
    void paintText(QPainter* painter);
    void paintBar(QPainter* painter);

    void showToolTip();

private:
    QPen m_borderPen;
    int m_axisThickness;

    QRectF m_barRect;
    QRectF m_textRect;
    QString m_label;
    int m_innerValue;
    double m_value;

    bool m_isText = false;
    QString m_toolTipText;
    ToolTip* m_toolTip = nullptr;
    QPointF m_toolTipPos;
    QTimer m_toolTipTimer;

    QMutex m_mutex;
};

#endif // HORIZONTALBAR_H
