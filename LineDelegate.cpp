#include "LineDelegate.h"
#include <string>
#include <QAbstractItemView>
#include <QLineEdit>
#include <QDebug>

LineDelegate::LineDelegate (QObject *parent)
:QItemDelegate(parent)
{
}

QWidget *LineDelegate::createEditor(QWidget *parent,
const QStyleOptionViewItem &option, const QModelIndex &index) const
{
QLineEdit *dlg = new QLineEdit; //создаем наше поле ввода с кнопкой
return dlg;
}

void LineDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
//в этой функции на входе данные из модели и указатель на виджет редактора
QString value = index.model()->data(index).toString(); //получаем что уже есть в модели
QLineEdit *dg = static_cast<QLineEdit*> (editor); //преобразуем указатель
dg->setText(value); //устанавливаем текст
}

void LineDelegate::setModelData(QWidget *editor,
QAbstractItemModel *model, const QModelIndex &index) const
{
//сюда попадаем когда редактор делегата теряем фокус/закрывается
QLineEdit *md = static_cast<QLineEdit*> (editor);
if (md->text().isEmpty()) {
    qDebug() << "Пусто";
} else {
   model->setData(index, md->text());
}
}
