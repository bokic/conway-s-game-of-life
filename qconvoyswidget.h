#ifndef QCONVOYSWIDGET_H
#define QCONVOYSWIDGET_H

#include <QMouseEvent>
#include <QByteArray>
#include <QWidget>
#include <QPixmap>

class QConvoysWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QConvoysWidget(QWidget *parent = 0);
    void newImage();
    void step();

signals:
    void startAnimation();
    void stopAnimation();

public slots:
    void animate();

protected:
    virtual void timerEvent(QTimerEvent *event);
    virtual void paintEvent(QPaintEvent *paintEvent);
    virtual void mouseMoveEvent(QMouseEvent *mouseEvent);
    virtual void resizeEvent(QResizeEvent *resizeEvent);

private:
    void regeneratePixmap();
    void recalculateLife();
    int numOfNeigboursAtPos(int matrix, int x, int y);
    char cellAtPos(int matrix, int x, int y);
    void setCellAtPos(int matrix, int x, int y, char state);

    QByteArray m_matrix[2];
    QPixmap m_pixmap;
    int m_width = 0;
    int m_height = 0;
    int m_stepTimer = 0;
    int m_ShowMatrix = 0;
    int m_GenerateMatrix = 1;
    bool m_running = false;
};

#endif // QCONVOYSWIDGET_H
