#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    void OpenFile(QString);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_coatCheckBox_stateChanged();

    void on_chooseMaterialShapeComboBox_currentIndexChanged(int index);

    void on_chooseMaterialTypeComboBox_currentIndexChanged(int index);

    void on_chooseMaterialGenreComboBox_currentIndexChanged(int index);

    void on_dimension1TextBox_editingFinished();

    void on_dimension2TextBox_editingFinished();

    void on_dimension3TextBox_editingFinished();

    void on_dimension4TextBox_editingFinished();

    void on_materialPriceTextBox_editingFinished();

private:
    Ui::MainWindow *ui;
    void LoadComboboxes();
    void AcceptOnlyDouble();
    void CalculateMass();
    void SetMaterialDensity();
};
#endif // MAINWINDOW_H
