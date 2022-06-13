#ifndef CUSTOMDELEGATE_H
#define CUSTOMDELEGATE_H

#include <QStyledItemDelegate>

class CustomDelegate : public QStyledItemDelegate
{
    using BaseClass = QStyledItemDelegate;

public:
    CustomDelegate(QObject* parent = nullptr);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
    const QModelIndex &index) const;};

#endif // CUSTOMDELEGATE_H
