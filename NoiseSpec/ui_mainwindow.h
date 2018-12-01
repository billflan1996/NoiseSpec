/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionExport;
    QAction *actionPrint;
    QAction *actionNew;
    QAction *actionManual;
    QAction *actionAutomatic;
    QAction *actionChop_End;
    QAction *actionChop_Beginning;
    QAction *actionRemove_Offset;
    QAction *actionExport_chart;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QSplitter *MainWindowSplitter;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *ChartLayout;
    QTabWidget *SettingsTabWidget;
    QWidget *PlotSettingsTab;
    QVBoxLayout *verticalLayout_4;
    QSplitter *PlotSettingsSplitter;
    QWidget *layoutWidget;
    QVBoxLayout *PlotDataLayout;
    QLabel *PlotDataLabel;
    QTableView *DPATable;
    QHBoxLayout *PlotDataButtonsLayout;
    QPushButton *deleteButton;
    QPushButton *AddButton;
    QGroupBox *PlotAxisGroupBox;
    QVBoxLayout *verticalLayout;
    QFrame *PlotTypeFrame;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *RawDataRadio;
    QRadioButton *FFTRadio;
    QHBoxLayout *horizontalLayout_2;
    QFormLayout *xAxisBoundsLayout;
    QLabel *label_6;
    QLineEdit *xMinBox;
    QLabel *label_7;
    QLineEdit *xMaxBox;
    QFormLayout *yAxisBoundsLayout;
    QLabel *label;
    QLineEdit *yMinBox;
    QLabel *label_2;
    QLineEdit *yMaxBox;
    QGridLayout *gridLayout;
    QCheckBox *LogXCheckBox;
    QCheckBox *LogYCheckBox;
    QSpacerItem *verticalSpacer;
    QWidget *FFTSettingsTab;
    QWidget *layoutWidget1;
    QFormLayout *FFTSettingsLayout;
    QLabel *Window;
    QComboBox *WindowSelectBox;
    QLabel *label_3;
    QComboBox *FFTAverageBox;
    QWidget *MeasureTab;
    QTableView *MeasurementTable;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(481, 684);
        MainWindow->setDocumentMode(false);
        MainWindow->setTabShape(QTabWidget::Rounded);
        MainWindow->setUnifiedTitleAndToolBarOnMac(false);
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QStringLiteral("actionSave"));
        actionExport = new QAction(MainWindow);
        actionExport->setObjectName(QStringLiteral("actionExport"));
        actionPrint = new QAction(MainWindow);
        actionPrint->setObjectName(QStringLiteral("actionPrint"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QStringLiteral("actionNew"));
        actionManual = new QAction(MainWindow);
        actionManual->setObjectName(QStringLiteral("actionManual"));
        actionManual->setCheckable(true);
        actionAutomatic = new QAction(MainWindow);
        actionAutomatic->setObjectName(QStringLiteral("actionAutomatic"));
        actionAutomatic->setCheckable(true);
        actionChop_End = new QAction(MainWindow);
        actionChop_End->setObjectName(QStringLiteral("actionChop_End"));
        actionChop_Beginning = new QAction(MainWindow);
        actionChop_Beginning->setObjectName(QStringLiteral("actionChop_Beginning"));
        actionRemove_Offset = new QAction(MainWindow);
        actionRemove_Offset->setObjectName(QStringLiteral("actionRemove_Offset"));
        actionExport_chart = new QAction(MainWindow);
        actionExport_chart->setObjectName(QStringLiteral("actionExport_chart"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        MainWindowSplitter = new QSplitter(centralWidget);
        MainWindowSplitter->setObjectName(QStringLiteral("MainWindowSplitter"));
        MainWindowSplitter->setOrientation(Qt::Horizontal);
        MainWindowSplitter->setHandleWidth(7);
        MainWindowSplitter->setChildrenCollapsible(true);
        horizontalLayoutWidget = new QWidget(MainWindowSplitter);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        ChartLayout = new QHBoxLayout(horizontalLayoutWidget);
        ChartLayout->setSpacing(6);
        ChartLayout->setContentsMargins(11, 11, 11, 11);
        ChartLayout->setObjectName(QStringLiteral("ChartLayout"));
        ChartLayout->setContentsMargins(0, 0, 0, 0);
        MainWindowSplitter->addWidget(horizontalLayoutWidget);
        SettingsTabWidget = new QTabWidget(MainWindowSplitter);
        SettingsTabWidget->setObjectName(QStringLiteral("SettingsTabWidget"));
        SettingsTabWidget->setMinimumSize(QSize(400, 0));
        SettingsTabWidget->setBaseSize(QSize(400, 0));
        SettingsTabWidget->setTabShape(QTabWidget::Rounded);
        PlotSettingsTab = new QWidget();
        PlotSettingsTab->setObjectName(QStringLiteral("PlotSettingsTab"));
        verticalLayout_4 = new QVBoxLayout(PlotSettingsTab);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        PlotSettingsSplitter = new QSplitter(PlotSettingsTab);
        PlotSettingsSplitter->setObjectName(QStringLiteral("PlotSettingsSplitter"));
        PlotSettingsSplitter->setOrientation(Qt::Vertical);
        layoutWidget = new QWidget(PlotSettingsSplitter);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        PlotDataLayout = new QVBoxLayout(layoutWidget);
        PlotDataLayout->setSpacing(6);
        PlotDataLayout->setContentsMargins(11, 11, 11, 11);
        PlotDataLayout->setObjectName(QStringLiteral("PlotDataLayout"));
        PlotDataLayout->setContentsMargins(0, 0, 0, 0);
        PlotDataLabel = new QLabel(layoutWidget);
        PlotDataLabel->setObjectName(QStringLiteral("PlotDataLabel"));

        PlotDataLayout->addWidget(PlotDataLabel);

        DPATable = new QTableView(layoutWidget);
        DPATable->setObjectName(QStringLiteral("DPATable"));
        DPATable->setContextMenuPolicy(Qt::CustomContextMenu);
        DPATable->setAutoFillBackground(false);
        DPATable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        DPATable->setAlternatingRowColors(true);
        DPATable->setSelectionMode(QAbstractItemView::SingleSelection);
        DPATable->setSelectionBehavior(QAbstractItemView::SelectRows);
        DPATable->setShowGrid(true);
        DPATable->horizontalHeader()->setVisible(false);
        DPATable->horizontalHeader()->setHighlightSections(false);
        DPATable->verticalHeader()->setVisible(false);
        DPATable->verticalHeader()->setHighlightSections(false);

        PlotDataLayout->addWidget(DPATable);

        PlotDataButtonsLayout = new QHBoxLayout();
        PlotDataButtonsLayout->setSpacing(6);
        PlotDataButtonsLayout->setObjectName(QStringLiteral("PlotDataButtonsLayout"));
        deleteButton = new QPushButton(layoutWidget);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setEnabled(false);
        deleteButton->setFocusPolicy(Qt::ClickFocus);

        PlotDataButtonsLayout->addWidget(deleteButton);

        AddButton = new QPushButton(layoutWidget);
        AddButton->setObjectName(QStringLiteral("AddButton"));
        AddButton->setFocusPolicy(Qt::ClickFocus);

        PlotDataButtonsLayout->addWidget(AddButton);


        PlotDataLayout->addLayout(PlotDataButtonsLayout);

        PlotSettingsSplitter->addWidget(layoutWidget);
        PlotAxisGroupBox = new QGroupBox(PlotSettingsSplitter);
        PlotAxisGroupBox->setObjectName(QStringLiteral("PlotAxisGroupBox"));
        verticalLayout = new QVBoxLayout(PlotAxisGroupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        PlotTypeFrame = new QFrame(PlotAxisGroupBox);
        PlotTypeFrame->setObjectName(QStringLiteral("PlotTypeFrame"));
        PlotTypeFrame->setFrameShape(QFrame::NoFrame);
        PlotTypeFrame->setFrameShadow(QFrame::Plain);
        verticalLayout_2 = new QVBoxLayout(PlotTypeFrame);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        RawDataRadio = new QRadioButton(PlotTypeFrame);
        RawDataRadio->setObjectName(QStringLiteral("RawDataRadio"));
        RawDataRadio->setChecked(true);

        verticalLayout_2->addWidget(RawDataRadio);

        FFTRadio = new QRadioButton(PlotTypeFrame);
        FFTRadio->setObjectName(QStringLiteral("FFTRadio"));

        verticalLayout_2->addWidget(FFTRadio);


        verticalLayout->addWidget(PlotTypeFrame);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        xAxisBoundsLayout = new QFormLayout();
        xAxisBoundsLayout->setSpacing(6);
        xAxisBoundsLayout->setObjectName(QStringLiteral("xAxisBoundsLayout"));
        label_6 = new QLabel(PlotAxisGroupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        xAxisBoundsLayout->setWidget(0, QFormLayout::LabelRole, label_6);

        xMinBox = new QLineEdit(PlotAxisGroupBox);
        xMinBox->setObjectName(QStringLiteral("xMinBox"));

        xAxisBoundsLayout->setWidget(0, QFormLayout::FieldRole, xMinBox);

        label_7 = new QLabel(PlotAxisGroupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        xAxisBoundsLayout->setWidget(1, QFormLayout::LabelRole, label_7);

        xMaxBox = new QLineEdit(PlotAxisGroupBox);
        xMaxBox->setObjectName(QStringLiteral("xMaxBox"));

        xAxisBoundsLayout->setWidget(1, QFormLayout::FieldRole, xMaxBox);


        horizontalLayout_2->addLayout(xAxisBoundsLayout);

        yAxisBoundsLayout = new QFormLayout();
        yAxisBoundsLayout->setSpacing(6);
        yAxisBoundsLayout->setObjectName(QStringLiteral("yAxisBoundsLayout"));
        label = new QLabel(PlotAxisGroupBox);
        label->setObjectName(QStringLiteral("label"));

        yAxisBoundsLayout->setWidget(0, QFormLayout::LabelRole, label);

        yMinBox = new QLineEdit(PlotAxisGroupBox);
        yMinBox->setObjectName(QStringLiteral("yMinBox"));

        yAxisBoundsLayout->setWidget(0, QFormLayout::FieldRole, yMinBox);

        label_2 = new QLabel(PlotAxisGroupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        yAxisBoundsLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        yMaxBox = new QLineEdit(PlotAxisGroupBox);
        yMaxBox->setObjectName(QStringLiteral("yMaxBox"));

        yAxisBoundsLayout->setWidget(1, QFormLayout::FieldRole, yMaxBox);


        horizontalLayout_2->addLayout(yAxisBoundsLayout);


        verticalLayout->addLayout(horizontalLayout_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        LogXCheckBox = new QCheckBox(PlotAxisGroupBox);
        LogXCheckBox->setObjectName(QStringLiteral("LogXCheckBox"));

        gridLayout->addWidget(LogXCheckBox, 0, 0, 1, 1);

        LogYCheckBox = new QCheckBox(PlotAxisGroupBox);
        LogYCheckBox->setObjectName(QStringLiteral("LogYCheckBox"));

        gridLayout->addWidget(LogYCheckBox, 0, 1, 1, 1);


        verticalLayout->addLayout(gridLayout);

        verticalSpacer = new QSpacerItem(20, 30, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout->addItem(verticalSpacer);

        PlotSettingsSplitter->addWidget(PlotAxisGroupBox);

        verticalLayout_4->addWidget(PlotSettingsSplitter);

        SettingsTabWidget->addTab(PlotSettingsTab, QString());
        FFTSettingsTab = new QWidget();
        FFTSettingsTab->setObjectName(QStringLiteral("FFTSettingsTab"));
        layoutWidget1 = new QWidget(FFTSettingsTab);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(50, 40, 264, 52));
        FFTSettingsLayout = new QFormLayout(layoutWidget1);
        FFTSettingsLayout->setSpacing(6);
        FFTSettingsLayout->setContentsMargins(11, 11, 11, 11);
        FFTSettingsLayout->setObjectName(QStringLiteral("FFTSettingsLayout"));
        FFTSettingsLayout->setContentsMargins(0, 0, 0, 0);
        Window = new QLabel(layoutWidget1);
        Window->setObjectName(QStringLiteral("Window"));

        FFTSettingsLayout->setWidget(0, QFormLayout::LabelRole, Window);

        WindowSelectBox = new QComboBox(layoutWidget1);
        WindowSelectBox->setObjectName(QStringLiteral("WindowSelectBox"));

        FFTSettingsLayout->setWidget(0, QFormLayout::FieldRole, WindowSelectBox);

        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        FFTSettingsLayout->setWidget(1, QFormLayout::LabelRole, label_3);

        FFTAverageBox = new QComboBox(layoutWidget1);
        FFTAverageBox->setObjectName(QStringLiteral("FFTAverageBox"));
        FFTAverageBox->setInsertPolicy(QComboBox::InsertAlphabetically);

        FFTSettingsLayout->setWidget(1, QFormLayout::FieldRole, FFTAverageBox);

        SettingsTabWidget->addTab(FFTSettingsTab, QString());
        MeasureTab = new QWidget();
        MeasureTab->setObjectName(QStringLiteral("MeasureTab"));
        MeasurementTable = new QTableView(MeasureTab);
        MeasurementTable->setObjectName(QStringLiteral("MeasurementTable"));
        MeasurementTable->setGeometry(QRect(10, 20, 421, 231));
        MeasurementTable->verticalHeader()->setVisible(false);
        SettingsTabWidget->addTab(MeasureTab, QString());
        MainWindowSplitter->addWidget(SettingsTabWidget);

        verticalLayout_3->addWidget(MainWindowSplitter);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 481, 22));
        menuBar->setNativeMenuBar(true);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);
#ifndef QT_NO_SHORTCUT
        label_6->setBuddy(xMinBox);
        label_7->setBuddy(xMaxBox);
        label->setBuddy(yMinBox);
        label_2->setBuddy(yMaxBox);
        Window->setBuddy(WindowSelectBox);
        label_3->setBuddy(FFTAverageBox);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(DPATable, deleteButton);
        QWidget::setTabOrder(deleteButton, AddButton);
        QWidget::setTabOrder(AddButton, RawDataRadio);
        QWidget::setTabOrder(RawDataRadio, FFTRadio);
        QWidget::setTabOrder(FFTRadio, xMinBox);
        QWidget::setTabOrder(xMinBox, xMaxBox);
        QWidget::setTabOrder(xMaxBox, LogXCheckBox);
        QWidget::setTabOrder(LogXCheckBox, yMinBox);
        QWidget::setTabOrder(yMinBox, yMaxBox);
        QWidget::setTabOrder(yMaxBox, LogYCheckBox);
        QWidget::setTabOrder(LogYCheckBox, SettingsTabWidget);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuFile->addAction(actionNew);
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionExport);
        menuFile->addAction(actionExport_chart);
        menuEdit->addAction(actionChop_Beginning);
        menuEdit->addAction(actionChop_End);
        menuEdit->addAction(actionRemove_Offset);

        retranslateUi(MainWindow);

        SettingsTabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "NoiseSpec", Q_NULLPTR));
#ifndef QT_NO_STATUSTIP
        MainWindow->setStatusTip(QString());
#endif // QT_NO_STATUSTIP
        actionOpen->setText(QApplication::translate("MainWindow", "Open", Q_NULLPTR));
        actionSave->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
        actionExport->setText(QApplication::translate("MainWindow", "Export Data", Q_NULLPTR));
        actionExport->setShortcut(QApplication::translate("MainWindow", "Ctrl+E", Q_NULLPTR));
        actionPrint->setText(QApplication::translate("MainWindow", "Print", Q_NULLPTR));
        actionNew->setText(QApplication::translate("MainWindow", "New", Q_NULLPTR));
        actionManual->setText(QApplication::translate("MainWindow", "Manual", Q_NULLPTR));
        actionAutomatic->setText(QApplication::translate("MainWindow", "Automatic", Q_NULLPTR));
        actionChop_End->setText(QApplication::translate("MainWindow", "Chop End", Q_NULLPTR));
        actionChop_Beginning->setText(QApplication::translate("MainWindow", "Chop Beginning", Q_NULLPTR));
        actionChop_Beginning->setShortcut(QApplication::translate("MainWindow", "Ctrl+B", Q_NULLPTR));
        actionRemove_Offset->setText(QApplication::translate("MainWindow", "Remove Offset", Q_NULLPTR));
        actionExport_chart->setText(QApplication::translate("MainWindow", "Export Graph", Q_NULLPTR));
        PlotDataLabel->setText(QApplication::translate("MainWindow", "Plot Data", Q_NULLPTR));
        deleteButton->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        deleteButton->setShortcut(QApplication::translate("MainWindow", "Backspace", Q_NULLPTR));
        AddButton->setText(QApplication::translate("MainWindow", "Add Signal", Q_NULLPTR));
        PlotAxisGroupBox->setTitle(QApplication::translate("MainWindow", "Axis ", Q_NULLPTR));
        RawDataRadio->setText(QApplication::translate("MainWindow", "Raw Data", Q_NULLPTR));
        FFTRadio->setText(QApplication::translate("MainWindow", "FFT", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "x min", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "x max", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "y min", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "y max", Q_NULLPTR));
        LogXCheckBox->setText(QApplication::translate("MainWindow", "Log x axis", Q_NULLPTR));
        LogYCheckBox->setText(QApplication::translate("MainWindow", "Log y axis", Q_NULLPTR));
        SettingsTabWidget->setTabText(SettingsTabWidget->indexOf(PlotSettingsTab), QApplication::translate("MainWindow", "Plot Settings", Q_NULLPTR));
        Window->setText(QApplication::translate("MainWindow", "Window", Q_NULLPTR));
        WindowSelectBox->clear();
        WindowSelectBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Hann", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Hamming", Q_NULLPTR)
         << QApplication::translate("MainWindow", "Blackman", Q_NULLPTR)
        );
        label_3->setText(QApplication::translate("MainWindow", "Averaging Length (Bins)", Q_NULLPTR));
        FFTAverageBox->clear();
        FFTAverageBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "None", Q_NULLPTR)
         << QApplication::translate("MainWindow", "32", Q_NULLPTR)
         << QApplication::translate("MainWindow", "64", Q_NULLPTR)
         << QApplication::translate("MainWindow", "128", Q_NULLPTR)
         << QApplication::translate("MainWindow", "256", Q_NULLPTR)
         << QApplication::translate("MainWindow", "512", Q_NULLPTR)
         << QApplication::translate("MainWindow", "1024", Q_NULLPTR)
         << QApplication::translate("MainWindow", "2048", Q_NULLPTR)
         << QApplication::translate("MainWindow", "4096", Q_NULLPTR)
         << QApplication::translate("MainWindow", "8192", Q_NULLPTR)
         << QApplication::translate("MainWindow", "16384", Q_NULLPTR)
        );
        SettingsTabWidget->setTabText(SettingsTabWidget->indexOf(FFTSettingsTab), QApplication::translate("MainWindow", "FFT Settings", Q_NULLPTR));
        SettingsTabWidget->setTabText(SettingsTabWidget->indexOf(MeasureTab), QApplication::translate("MainWindow", "Measure", Q_NULLPTR));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", Q_NULLPTR));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Global Transform", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
