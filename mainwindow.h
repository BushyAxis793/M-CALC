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

    void on_dimension1TextBox_textEdited(const QString &arg1);

    void on_dimension2TextBox_textEdited(const QString &arg1);

    void on_dimension3TextBox_textEdited(const QString &arg1);

    void on_dimension4TextBox_textEdited(const QString &arg1);

    void on_materialPriceTextBox_textEdited(const QString &arg1);

    void on_coatTypeComboBox_currentIndexChanged(int index);

    void on_coatPriceTextBox_textEdited(const QString &arg1);

    void on_euroRateTextBox_textEdited(const QString &arg1);

    void on_chooseMaterialGenreComboBox_currentIndexChanged(int index);

    void on_chooseMaterialTypeComboBox_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    void LoadComboboxes();
    void AcceptOnlyDouble();
    void CalculateMass();
    void SetMaterialDensity();
    void SwitchMaterialType();
    void CalculateFinalEuroPrice();
    void CalculateFinalPrice();
    void SwitchCoatType();
    void PreloadSummary();
    void LoadEuroRate();
    void SaveEuroRate();
};
#endif // MAINWINDOW_H
