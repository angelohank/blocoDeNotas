#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
#include <QPrintDialog>
#include <QPrinter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->txtPrincipal);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbrir_triggered()
{
    QString filter = "Arquivos de Texto ( *.txt )";
    QString fileName = QFileDialog::getOpenFileName(this, "Abrir", defaultDir, filter);

    qDebug() << fileName;

    //criaArquivo
    QFile file(fileName);

    filePath = fileName;

    //verificarAberturaDoArquivo
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Abrir(37) - Abertura do arquivo falhou";

        QMessageBox::warning(this, "Atenção", "Não foi possível abrir o arquivo selecionado.");
        return;
    }

    //lerArquivo
    QTextStream input(&file);
    QString text = input.readAll();

    ui->txtPrincipal->setText(text);

    //fecharArquivo
    file.close();

}

void MainWindow::on_actionNovo_triggered()
{
    //preparaNovoArquivo
    filePath = "";
    ui->txtPrincipal->clear();
    ui->txtPrincipal->setFocus();
}

void MainWindow::on_actionSalvar_Como_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Salvar Como");
    QFile file(fileName);

    //setandoCaminhoDoArquivo
    filePath = fileName;

    //verificarAberturaDoArquivo
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Salvar_Como(69) - Abertura do arquivo falhou";

        QMessageBox::warning(this, "Atenção", "Não foi possível salvar o arquivo.");
        return;
    }

    //lerArquivo
    QTextStream output(&file);
    QString text = ui->txtPrincipal->toPlainText();

    output << text;
    file.flush();

    //fecharArquivo
    file.close();
}

void MainWindow::on_actionSalvar_triggered()
{
    QFile file(filePath);

    //verificarAberturaDoArquivo
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "Salvar(94) - Abertura do arquivo falhou";

        QMessageBox::warning(this, "Atenção", "Não foi possível salvar o arquivo.");
        return;
    }

    //lerArquivo
    QTextStream output(&file);
    QString text = ui->txtPrincipal->toPlainText();

    output << text;
    file.flush();

    //fecharArquivo
    file.close();
}

void MainWindow::on_actionFechar_triggered()
{
    close();
}

void MainWindow::on_actionCopiar_triggered()
{
    ui->txtPrincipal->copy();
}

void MainWindow::on_actionRecortar_triggered()
{
    ui->txtPrincipal->cut();
}

void MainWindow::on_actionColar_triggered()
{
    ui->txtPrincipal->paste();
}

void MainWindow::on_actionDesfazer_triggered()
{
    ui->txtPrincipal->undo();
}

void MainWindow::on_actionRefazer_triggered()
{
    ui->txtPrincipal->redo();
}

void MainWindow::on_actionFonte_triggered()
{
    bool fontOk;

    QFont font = QFontDialog::getFont(&fontOk, this);

    //setaFonte
    if ( fontOk ) {
        ui->txtPrincipal->setFont(font);
    } else {
        qDebug() << "Selecionar_Fonte(154) - Erro ao selecionar fonte";
        return;
    }
}

void MainWindow::on_actionCor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Alterando cor");

    if ( color.isValid() ) {
        //aplicarCor
        ui->txtPrincipal->setTextColor(color);
    }
}

void MainWindow::on_actionCor_de_Fundo_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "Alterando cor");

    if ( color.isValid() ) {
        //aplicarCor
        ui->txtPrincipal->setTextBackgroundColor(color);
    }
}

void MainWindow::on_actionImprimir_triggered()
{
    QPrinter printer;
    printer.setPrinterName("Impressora padrao");

    QPrintDialog impBox(&printer, this);

    //verificaSeImprimiu
    if ( impBox.exec() == QDialog::Rejected ) {
        qDebug() << "Impressão não realizada";
        return;
    }

    ui->txtPrincipal->print(&printer);
}
