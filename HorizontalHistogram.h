#ifndef HORIZONTALHISTOGRAM_H
#define HORIZONTALHISTOGRAM_H

#include <QQuickPaintedItem>
#include <set>

class HorizontalBar;

class HorizontalHistogram : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT

public:
    HorizontalHistogram(QQuickItem* parent = nullptr);

    virtual void paint(QPainter* painter) override;

    Q_INVOKABLE void updateTop(QList<QPair<QString, int>> top);
    Q_INVOKABLE void clear();

private:
    void paintBackground(QPainter* painter);
    void paintAxis(QPainter* painter);
    void paintBars(QPainter* painter);
    void paintBar(QPainter* painter, int y);

    void addBar(const QString& name, int value);
    void updateBars();
    void sortBars();
    HorizontalBar* get(const QString& name) const;

private:
    int m_maxValue = 100;

    QList<HorizontalBar*> m_bars;
};

#endif // HORIZONTALHISTOGRAM_H
