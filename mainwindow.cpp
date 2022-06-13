#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "string"

#include <QItemDelegate>
#include <QSpinBox>
#include <QStyledItemDelegate>
#include <CustomDelegate.h>
#include <LineDelegate.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* Первым делом необходимо создать объект, который будет использоваться для работы с данными нашей БД
     * и инициализировать подключение к базе данных
     * */
    db = new DataBase();
    db->connectToDataBase();

    /* После чего производим наполнение таблицы базы данных
     * контентом, который будет отображаться в TableView
     * */
    QVector<QString> names;
    QVector<QString> breeds;
    QVector<int> ages;
    names << "Шарик" << "Машина" << "Бублик" << "Рыжик" << "Барсик"
          << "Макарон" << "Дошик" << "Граф" << "Собака9" << "Малыш";
    breeds << "Померанский шпиц" << "Бигль" << "Сиба-ину" << "Терьер"
           << "Доберман" << "Лабрадор" << "Алабай" << "Йорк" << "Кане-Корсо" << "Чихуа-хуа";
    ages << 5 << 9 << 6 << 8 << 3 << 7 << 4 << 3 << 9 << 6;

    for(int i = 0; i < names.length(); i++){
        QVariantList data;
        data.append(names[i]);
        data.append(breeds[i]);
        data.append(ages[i]);
        // Вставляем данные в БД
        db->inserIntoTable(data);
    }
    /* Инициализируем модель для представления данных
     * с заданием названий колонок
     * */
    this->setupModel(TABLE,
                     QStringList() << "id"
                                   << "Имя"
                                   << "Порода"
                                   << "Возраст"
               );

    /* Инициализируем внешний вид таблицы с данными
     * */
    this->createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/* Метод для инициализации модеи представления данных
 * */
void MainWindow::setupModel(const QString &tableName, const QStringList &headers)
{
    /* Производим инициализацию модели представления данных
     * с установкой имени таблицы в базе данных, по которому
     * будет производится обращение в таблице
     * */
    model = new QSqlTableModel(this);
    model->setTable(tableName);

    /* Устанавливаем названия колонок в таблице с сортировкой данных
     * */
    for(int i = 0, j = 0; i < model->columnCount(); i++, j++){
        model->setHeaderData(i,Qt::Horizontal,headers[j]);
    }
    // Устанавливаем сортировку по возрастанию данных по нулевой колонке
    model->setSort(0,Qt::AscendingOrder);
}

void MainWindow::createUI()
{
    ui->tableView->setModel(model);     // Устанавливаем модель на TableView
    // Разрешаем выделение строк
    ui->tableView->setColumnHidden(0, true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    // Устанавливаем режим выделения лишь одно строки в таблице
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    // Устанавливаем размер колонок по содержимому
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    ui->tableView->setItemDelegateForColumn(1, new LineDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(2, new LineDelegate(ui->tableView));
    ui->tableView->setItemDelegateForColumn(3, new CustomDelegate(ui->tableView));
    model->select(); // Делаем выборку данных из таблицы
}


void MainWindow::on_checkBox_stateChanged(int arg1)
{
    if (arg1 == Qt::Checked) {
        ui->tableView->setModel(model);
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
        ui->create_btn->setEnabled(true);
        ui->delete_btn->setEnabled(false);
        model->select();
    } else {
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->create_btn->setEnabled(false);
        ui->delete_btn->setEnabled(true);
        model->select();
    }
}

void MainWindow::on_delete_btn_clicked()
{
    QModelIndex             index;
    QItemSelectionModel    *selectModel;
    QModelIndexList         indexes;
    selectModel = ui->tableView->selectionModel();
    indexes = selectModel->selectedIndexes();
    foreach(index, indexes) {
        model->removeRow(index.row());
    }
    model->select();
}

void MainWindow::on_create_btn_clicked()
{
    int lastRow = model->rowCount();
        model->insertRow(lastRow);
        model->setData(model->index(lastRow,1), "Имя собаки");
        model->setData(model->index(lastRow,2), "Кличка собаки");
        model->setData(model->index(lastRow,3), 1);
        ui->tableView->selectRow(lastRow);
        ui->tableView->setFocus();
}
