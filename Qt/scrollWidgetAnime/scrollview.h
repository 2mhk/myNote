#ifndef SCROLLVIEW_H
#define SCROLLVIEW_H

#include <QWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

class ScrollView : public QWidget
{
public:
    ScrollView(QWidget *parent = nullptr);
    ~ScrollView();

protected:
    enum PosType {
        Type_LL,
        Type_L,
        Type_M,
        Type_R,
        Type_RR
    };
    QPoint getPos(PosType type);
    QWidget *getWidget(PosType type);

protected:
    void wheelEvent(QWheelEvent *event) override;

    void initFistSight();
    void initAnimation();
    void scrollPre();
    void scrollNext();

private:
    QList<QWidget *> m_widgetList;
    QAnimationGroup *m_animationGroup;
    int m_currentIndex;
};

#endif // SCROLLVIEW_H

