#ifndef LINEDELEGATE_H
#define LINEDELEGATE_H

#include <QItemDelegate>


class LineDelegate : public QItemDelegate
{
public:
LineDelegate (QObject *parent = 0);
QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
const QModelIndex &index) const; //создаем редактор делегата - это наш виджет
void setEditorData(QWidget *editor, const QModelIndex &index) const; //устанавливаем данные в редакторе
void setModelData(QWidget *editor, QAbstractItemModel *model,
const QModelIndex &index) const; //а здесь данные из редактора передаем уже в модель
};


#endif // LINEDELEGATE_H
