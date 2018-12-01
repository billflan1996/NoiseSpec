#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAudioInput>
#include <QBuffer>
#include <QFile>
#include <QtCharts>
#include <QVector>
#include <QtWidgets/QWidget>
#include <QtCharts/QChartGlobal>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtWidgets/QVBoxLayout>
#include <QtCharts/QValueAxis>

#include <tsignalsettings.h>
#include <tmiclistener.h>
#include <tdatapointarray.h>
#include <noisespecmaths.h>

QT_CHARTS_BEGIN_NAMESPACE
class QLineSeries;
class QChart;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

// Class which emits a signal when the widget attached loses focus (to get out of operator mode)
class TOperatorModeUI : public QObject {
    Q_OBJECT

public: TOperatorModeUI(QObject *parent = 0): QObject(parent) {}
        ~TOperatorModeUI() {}

        bool OpModeEnabled = false; // only let parent change this

signals:
    void LostFocus();
    void EnableOperatorMode();
    void ReturnPressed();

protected:
    bool eventFilter(QObject *obj, QEvent *event) {
        // Capture event
        bool captureEvent = false;

        if (OpModeEnabled) {
            // Operator mode on, so cancel if these conditions are met:

            if (event->type() == QEvent::FocusOut) {
                // Capture lost focus
                QFocusEvent * FocusChangeEvent = static_cast<QFocusEvent*>(event);
                captureEvent = FocusChangeEvent->lostFocus();
            }
            if (event->type() == QEvent::KeyPress) {
                // Capture ESC press
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                captureEvent = captureEvent || (keyEvent->key()==Qt::Key_Escape);
            } // ...more conditions can be added here if needed...

            if (captureEvent) {
                // emit LostFocus if esc pressed or focus changed ...
                emit LostFocus();
                return true;
            }

            // if enter (return) is pressed, also give a signal (to enable keyboard control)
            if (event->type() == QEvent::KeyPress) {
                // Capture ESC press
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                if (keyEvent->key()==Qt::Key_Return) {
                    emit ReturnPressed();
                    return true;
                }
            }

        }
        else {
            if (event->type() == QEvent::KeyPress) {
                // Capture subtract key press
                QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
                captureEvent = captureEvent || (keyEvent->key()==Qt::Key_Minus);
            }

            if (captureEvent) {
                // emit LostFocus if esc pressed or focus changed ...
                emit EnableOperatorMode();
                return true;
            }
        }

        // if we've got to here, use default event handler...
        return QObject::eventFilter(obj, event);
    }
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector<TDataPointArray*> DataPointArrayVector;

private slots:

    // DPA table
    void on_RawDataRadio_toggled(bool checked);
    void on_AddButton_clicked();
    void on_deleteButton_clicked();
    void on_DPATable_doubleClicked(const QModelIndex &index);

    // Axis limits
    void on_xMinBox_returnPressed();
    void on_xMaxBox_returnPressed();
    void on_yMinBox_returnPressed();
    void on_yMaxBox_returnPressed();
    void on_LogXCheckBox_toggled(bool checked);
    void on_LogYCheckBox_toggled(bool checked);

    // FFT user options
    void on_WindowSelectBox_currentIndexChanged(const QString &arg1);

    // Export pressed
    void on_actionExport_triggered();

    // generate sample data
    void generateSampleData();

    // Operator mode
    void MinusOperatorPressed();
    void CancelOperatorMode();
    void on_DPATable_clicked(const QModelIndex &index);
    void DPATable_ReturnPressed();

    void on_FFTAverageBox_currentIndexChanged(const QString &arg1);

    // DPA context menu stuff
    void ShowDPATableContext(const QPoint &pos);
    void DPAContext_ItemClicked(QAction *action);
    
    void on_actionChop_Beginning_triggered();
    void on_actionChop_End_triggered();

    void on_actionRemove_Offset_triggered();

    void on_actionExport_chart_triggered();

private:
    void DoPlot(bool ResetAxis = false, bool exporting = false); // Plot the graph on the GUI or PDF writer
    void RePaintUI(bool ResetAxis = false);

    void AddDPATableItem(int VectorIndex);

    void OperatorListeningMode();

    void updateAllFouriers(bool RePlot = true);
    void SubtractDPA();

    void UpdateMeasurementTable();

    Ui::MainWindow *ui;

    // Chart stuff
    QChart *GUIChart;
    QChartView *GUIChartView;
    QVector<QLineSeries*> GUIChartSeries;
    QChart *ExportChart;
    QChartView *ExportChartView;
    QVector<QLineSeries*> ExportChartSeries;

    QLineSeries *m_series;

    // Model to populate the table
    QStandardItemModel * DPATableModel;
    QStandardItemModel * MeasureTableModel;

    // Operator mode
    TOperatorModeUI * OperatorModeUI; // UI (handles user actions which might disenable operator mode)
    bool OperatorModeEnabled = false;
    TDataPointArray * OpModeMinuend;
    TDataPointArray * OpModeSubtrahend;

    // Settings for recording
    AudioFormatParameters * LastAudioFormat;

    // DPA context menu actions
    QAction * DPAActionSetAsNoise;
    QAction * DPAActionDelete;
    QAction * DPAActionChopBeginning;
    QAction * DPAActionChopEnd;
    QAction * DPAActionRemoveOffset;
    QAction * DPAActionShowHide;
    QAction * DPAActionChangeColour;
    QAction * DPAActionBringToFront;
    void DPAChopBeginning(int DPALocation);
    void DPAChopEnd(int DPALocation);
    void DPAShowHide(int DPALocation);
    void DPABringToFront(int DPALocation);
    void DPASetAsNoise(int DPALocation);

    // noise indices
    QVector<int> NoiseDPAs;
};

#endif // MAINWINDOW_H
