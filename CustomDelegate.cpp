#include "CustomDelegate.h"

#include <QSpinBox>
#include <QAbstractItemView>

CustomDelegate::CustomDelegate(QObject* parent) : BaseClass(parent)
{
}

QWidget *CustomDelegate::createEditor(QWidget *parent,
                                      const QStyleOptionViewItem &option, const QModelIndex &index) const {
    QSpinBox* editor = new QSpinBox(parent);
    editor->setRange(1, 25);
    return editor;
}
