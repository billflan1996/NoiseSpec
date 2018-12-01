/********************************************************************************
** Form generated from reading UI file 'tsignalsettings.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TSIGNALSETTINGS_H
#define UI_TSIGNALSETTINGS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_TSignalSettings
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLineEdit *NameBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_5;
    QDoubleSpinBox *RecordTimeBox;
    QLabel *label_3;
    QComboBox *AudioDeviceSelector;
    QComboBox *AudioBitRateSelector;
    QLabel *label_4;
    QComboBox *AudioSampleRateBox;
    QLabel *ListeningStatusLabel;
    QPushButton *RecordButton;
    QProgressBar *ListeningStatusBar;
    QPushButton *CancelButton;

    void setupUi(QDialog *TSignalSettings)
    {
        if (TSignalSettings->objectName().isEmpty())
            TSignalSettings->setObjectName(QStringLiteral("TSignalSettings"));
        TSignalSettings->resize(324, 299);
        gridLayout_2 = new QGridLayout(TSignalSettings);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        NameBox = new QLineEdit(TSignalSettings);
        NameBox->setObjectName(QStringLiteral("NameBox"));

        gridLayout->addWidget(NameBox, 0, 1, 1, 1);

        label = new QLabel(TSignalSettings);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setPointSize(13);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_2 = new QLabel(TSignalSettings);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label_5 = new QLabel(TSignalSettings);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 2, 0, 1, 1);

        RecordTimeBox = new QDoubleSpinBox(TSignalSettings);
        RecordTimeBox->setObjectName(QStringLiteral("RecordTimeBox"));
        RecordTimeBox->setDecimals(3);
        RecordTimeBox->setMinimum(0.001);
        RecordTimeBox->setValue(1);

        gridLayout->addWidget(RecordTimeBox, 1, 1, 1, 1);

        label_3 = new QLabel(TSignalSettings);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 1);

        AudioDeviceSelector = new QComboBox(TSignalSettings);
        AudioDeviceSelector->setObjectName(QStringLiteral("AudioDeviceSelector"));

        gridLayout->addWidget(AudioDeviceSelector, 2, 1, 1, 1);

        AudioBitRateSelector = new QComboBox(TSignalSettings);
        AudioBitRateSelector->setObjectName(QStringLiteral("AudioBitRateSelector"));

        gridLayout->addWidget(AudioBitRateSelector, 3, 1, 1, 1);

        label_4 = new QLabel(TSignalSettings);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 4, 0, 1, 1);

        AudioSampleRateBox = new QComboBox(TSignalSettings);
        AudioSampleRateBox->setObjectName(QStringLiteral("AudioSampleRateBox"));

        gridLayout->addWidget(AudioSampleRateBox, 4, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 1, 2);

        ListeningStatusLabel = new QLabel(TSignalSettings);
        ListeningStatusLabel->setObjectName(QStringLiteral("ListeningStatusLabel"));

        gridLayout_2->addWidget(ListeningStatusLabel, 1, 0, 1, 1);

        RecordButton = new QPushButton(TSignalSettings);
        RecordButton->setObjectName(QStringLiteral("RecordButton"));

        gridLayout_2->addWidget(RecordButton, 1, 1, 1, 1);

        ListeningStatusBar = new QProgressBar(TSignalSettings);
        ListeningStatusBar->setObjectName(QStringLiteral("ListeningStatusBar"));
        ListeningStatusBar->setValue(0);

        gridLayout_2->addWidget(ListeningStatusBar, 2, 0, 1, 1);

        CancelButton = new QPushButton(TSignalSettings);
        CancelButton->setObjectName(QStringLiteral("CancelButton"));

        gridLayout_2->addWidget(CancelButton, 2, 1, 1, 1);


        retranslateUi(TSignalSettings);
        QObject::connect(CancelButton, SIGNAL(clicked()), TSignalSettings, SLOT(reject()));

        QMetaObject::connectSlotsByName(TSignalSettings);
    } // setupUi

    void retranslateUi(QDialog *TSignalSettings)
    {
        TSignalSettings->setWindowTitle(QApplication::translate("TSignalSettings", "Add Signal", Q_NULLPTR));
        label->setText(QApplication::translate("TSignalSettings", "Name", Q_NULLPTR));
        label_2->setText(QApplication::translate("TSignalSettings", "Duration", Q_NULLPTR));
        label_5->setText(QApplication::translate("TSignalSettings", "Input Device", Q_NULLPTR));
        label_3->setText(QApplication::translate("TSignalSettings", "Bit Rate", Q_NULLPTR));
        label_4->setText(QApplication::translate("TSignalSettings", "Sample Rate", Q_NULLPTR));
        ListeningStatusLabel->setText(QApplication::translate("TSignalSettings", "Not Listening", Q_NULLPTR));
        RecordButton->setText(QApplication::translate("TSignalSettings", "Record", Q_NULLPTR));
        CancelButton->setText(QApplication::translate("TSignalSettings", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class TSignalSettings: public Ui_TSignalSettings {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TSIGNALSETTINGS_H
