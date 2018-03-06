#ifndef NO_FOCUS_DELEGATE_H
#define NO_FOCUS_DELEGATE_H

#include <QPainter>
#include <QStyledItemDelegate>
#include <QStyleOptionViewItem>

class NoFocusDelegate : public QStyledItemDelegate
{
private:
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
    {
        QStyleOptionViewItem itemOption(option);
        if(itemOption.state & QStyle::State_HasFocus)
        {
            itemOption.state=itemOption.state^QStyle::State_HasFocus;
        }
        paint(painter, itemOption, index);
    }
};

#endif // NO_FOCUS_DELEGATE_H

