#include "qconvoyswidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QImage>

#define NO_CELL_PRESENT 0
#define CELL_IS_LIVE    1
#define CELL_IS_DEAD    2


QConvoysWidget::QConvoysWidget(QWidget *parent) :
    QWidget(parent),
    m_width(0),
    m_height(0),
    m_stepTimer(0),
    m_ShowMatrix(0),
    m_GenerateMatrix(1),
    m_running(false)
{
    newImage();
}

void QConvoysWidget::newImage()
{
    m_ShowMatrix = 0;
    m_GenerateMatrix = 1;

    m_width = width() / 2;
    m_height = height() / 2;

    m_matrix[m_ShowMatrix].resize(m_width * m_height);
    m_matrix[m_ShowMatrix].fill(0);
    m_matrix[m_GenerateMatrix].resize(m_width * m_height);
    m_matrix[m_GenerateMatrix].fill(0);

    regeneratePixmap();

    update();
}

void QConvoysWidget::step()
{
    recalculateLife();

    update();
}

void QConvoysWidget::animate()
{
    if (m_running)
    {
        killTimer(m_stepTimer);
        m_stepTimer = 0;
        m_running = false;
        emit stopAnimation();
    } else {
        m_stepTimer = startTimer(100);
        m_running = true;
        emit startAnimation();
    }
}

void QConvoysWidget::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    recalculateLife();

    update();
}

void QConvoysWidget::paintEvent(QPaintEvent *paintEvent)
{
    Q_UNUSED(paintEvent);

    QPainter painter(this);

    painter.drawPixmap(rect(), m_pixmap);
}

void QConvoysWidget::mouseMoveEvent(QMouseEvent *mouseEvent)
{
    if (mouseEvent->buttons() & Qt::LeftButton)
    {
        int x = mouseEvent->x();
        int y = mouseEvent->y();

        setCellAtPos(m_ShowMatrix, x / 2, y / 2, CELL_IS_LIVE);

        regeneratePixmap();

        update();

        mouseEvent->accept();
    }
}

void QConvoysWidget::resizeEvent(QResizeEvent *resizeEvent)
{
    Q_UNUSED(resizeEvent);

    if (!m_running)
    {
        newImage();
    }
}

void QConvoysWidget::regeneratePixmap()
{
    QImage img(m_width, m_height, QImage::Format_RGB32);

    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            uint color = 0;

            switch (cellAtPos(m_ShowMatrix, x, y)) {
            case CELL_IS_LIVE:
                color = QColor(Qt::green).rgb();
                break;
            case CELL_IS_DEAD:
                color = QColor(Qt::gray).rgb();
                break;
            }

            img.setPixel(x, y, color);
        }
    }

    m_pixmap.convertFromImage(img);
}

void QConvoysWidget::recalculateLife()
{
    for (int y = 0; y < m_height; y++)
    {
        for (int x = 0; x < m_width; x++)
        {
            char state = cellAtPos(m_ShowMatrix, x, y);

            int neighbours = numOfNeigboursAtPos(m_ShowMatrix, x, y);

            if (state == CELL_IS_LIVE)
            {
                if ((state == CELL_IS_LIVE)&&((neighbours < 2)||(neighbours > 3)))
                {
                    state = CELL_IS_DEAD;
                }
                else
                {
                    state = CELL_IS_LIVE;
                }
            }
            else
            {
                if (neighbours == 3)
                {
                    state = CELL_IS_LIVE;
                }
            }

            setCellAtPos(m_GenerateMatrix, x, y, state);
        }
    }

    m_ShowMatrix ^= 1;
    m_GenerateMatrix ^= 1;

    regeneratePixmap();
}

int QConvoysWidget::numOfNeigboursAtPos(int matrix, int x, int y)
{
    int ret = 0;

    for (int _y = -1; _y <= 1; _y++)
    {
        for (int _x = -1; _x <= 1; _x++)
        {
            if ((_x == 0)&&(_y == 0))
            {
                continue;
            }

            if (cellAtPos(matrix, x + _x, y + _y) == CELL_IS_LIVE)
            {
                ret++;
            }
        }
    }


    return ret;
}

char QConvoysWidget::cellAtPos(int matrix, int x, int y)
{
    while (x < 0)
    {
        x += m_width;
    }

    x %= m_width;

    while (y < 0)
    {
        y += m_height;
    }

    y %= m_height;

    matrix %= 2;

    return m_matrix[matrix].at((y * m_width) + x);
}

void QConvoysWidget::setCellAtPos(int matrix, int x, int y, char state)
{
    while (x < 0)
    {
        x += m_width;
    }

    x %= m_width;

    while (y < 0)
    {
        y += m_height;
    }

    y %= m_height;

    m_matrix[matrix][(y * m_width) + x] = state;
}
