#include "menu.h"
#include "ui_menu.h"

#include <QFile>

Menu::Menu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);

    QString fileName = "wynik.txt";

    QFile file(fileName);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
        qDebug() << "Nie można otworzyć pliku.";
    }

    QStringList lines;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        lines.append(line);
    }
    file.close();

    std::sort(lines.begin(), lines.end(), [](const QString &a, const QString &b) {
        QStringList partsA = a.split(" ");
        QStringList partsB = b.split(" ");
        int scoreA = partsA.size() > 1 ? partsA.last().toInt() : 0;
        int scoreB = partsB.size() > 1 ? partsB.last().toInt() : 0;
        return scoreA > scoreB;
    });

    for (const QString &line : lines) {
        QListWidgetItem *item = new QListWidgetItem(line);
        ui->ListaWynik->addItem(item);
    }


}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_NowaGraBtn_clicked()
{
    this->close();
}


void Menu::on_ZakonczBtn_clicked()
{
    emit zakonczClicked();
}

