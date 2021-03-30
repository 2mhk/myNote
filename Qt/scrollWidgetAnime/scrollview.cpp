#include "scrollview.h"
#include <QPushButton>
#include <QWheelEvent>

#define ITERM_SPACE 400

ScrollView::ScrollView(QWidget *parent)
    : QWidget(parent)
    , m_currentIndex(0)
{
    m_animationGroup = new QParallelAnimationGroup(this);

    //setup test data
    //if size of m_widgetList < 4 --> display error
    for (int i = 0; i < 8; i++) {
        QPushButton *btn = new QPushButton(this);
        btn->setFixedSize(300, 300);
        btn->setText(QString::number(i));
        btn->setVisible(false);
        m_widgetList << btn;
    }

    setMinimumSize(800, 300);
    initFistSight();
    initAnimation();
}

ScrollView::~ScrollView()
{

}

void ScrollView::wheelEvent(QWheelEvent *event)
{
    if (m_animationGroup->state() == QAnimationGroup::Running) {
        return;
    }

    if (event->delta() < 0) {
        scrollNext();
    } else {
        scrollPre();
    }
}

QPoint ScrollView::getPos(ScrollView::PosType type)
{
    auto wgt = m_widgetList.at(0);

    switch (type) {
    case Type_LL:
        return QPoint(width() / 2 - wgt->width() / 2 - ITERM_SPACE *  2, 0);
    case Type_L:
        return QPoint(width() / 2 - wgt->width() / 2 - ITERM_SPACE, 0);
    case Type_M:
        return QPoint(width() / 2 - wgt->width() / 2, 0);
    case Type_R:
        return QPoint(width() / 2 - wgt->width() / 2 + ITERM_SPACE, 0);
    case Type_RR:
        return QPoint(width() / 2 - wgt->width() / 2 + ITERM_SPACE * 2, 0);
    }
}

QWidget *ScrollView::getWidget(ScrollView::PosType type)
{
    QWidget *w;
    int index;

    switch (type) {
    case Type_LL:
        index = (m_currentIndex - 2) % m_widgetList.count();
        index = index >= 0 ? index : m_widgetList.count() + index;
        w = m_widgetList.at(index);
        break;
    case Type_L:
        index = (m_currentIndex - 1);
        index = index >= 0 ? index : m_widgetList.count() + index;
        w = m_widgetList.at(index);
        break;
    case Type_M:
        w = m_widgetList.at(m_currentIndex);
        break;
    case Type_R:
        index = (m_currentIndex + 1) % m_widgetList.count();
        w = m_widgetList.at(index);
        break;
    case Type_RR:
        index = (m_currentIndex + 2) % m_widgetList.count();
        w = m_widgetList.at(index);
        break;
    }

    return w;

}

void ScrollView::initFistSight()
{
    for (int i = 0; i < 3; i++) {
        auto w = getWidget(static_cast<PosType>(Type_L + i));
        w->move(getPos(static_cast<PosType>(Type_L + i)));
        w->setVisible(true);
    }
}

void ScrollView::initAnimation()
{
    for (int i = 0; i < 4; i++) {
        QPropertyAnimation *animation = new QPropertyAnimation(m_animationGroup);
        animation->setDuration(100);
        animation->setPropertyName("pos");
        m_animationGroup->addAnimation(animation);
    }
}

void ScrollView::scrollPre()
{
    for (int i = 0; i < 4; i++) {
        QPropertyAnimation *a1 = static_cast<QPropertyAnimation *>(m_animationGroup->animationAt(i));
        a1->setStartValue(getPos(static_cast<PosType>(Type_LL + i)));
        a1->setEndValue(getPos(static_cast<PosType>(Type_L + i)));
        auto w1 = getWidget(static_cast<PosType>(Type_LL + i));
        w1->setVisible(true);
        a1->setTargetObject(w1);
    }

    m_animationGroup->start();
    m_currentIndex = (m_currentIndex - 1);
    m_currentIndex = m_currentIndex >= 0 ? m_currentIndex : m_widgetList.count() + m_currentIndex;
}

void ScrollView::scrollNext()
{
    for (int i = 0; i < 4; i++) {
        QPropertyAnimation *a1 = static_cast<QPropertyAnimation *>(m_animationGroup->animationAt(i));
        a1->setStartValue(getPos(static_cast<PosType>(Type_L + i)));
        a1->setEndValue(getPos(static_cast<PosType>(Type_LL + i)));
        auto w1 = getWidget(static_cast<PosType>(Type_L + i));
        w1->setVisible(true);
        a1->setTargetObject(w1);
    }

    m_animationGroup->start();
    m_currentIndex = (m_currentIndex + 1) % m_widgetList.count();
}

