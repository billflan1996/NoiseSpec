#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Set up plot area
    GUIChart = new QChart();
    GUIChartView = new QChartView(GUIChart);
    GUIChartView->setMinimumSize(800, 600);
    GUIChart->setDropShadowEnabled(false);
    ui->ChartLayout->addWidget(GUIChartView);

    // Turn off the log check boxes initially (since we're plotting raw data)
    ui->LogXCheckBox->setVisible(false);
    ui->LogYCheckBox->setVisible(false);

    // Set up table of datasets
    DPATableModel = new QStandardItemModel(0, 5, this);
    DPATableModel->setHorizontalHeaderItem(0, new QStandardItem());
    DPATableModel->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    DPATableModel->setHorizontalHeaderItem(2, new QStandardItem("Duration /s"));
    DPATableModel->setHorizontalHeaderItem(3, new QStandardItem("Sample Rate /Hz"));
    DPATableModel->setHorizontalHeaderItem(4, new QStandardItem("Bitrate"));
    ui->DPATable->setModel(DPATableModel);
    ui->DPATable->horizontalHeader()->resizeSection(0, 30);


    // Set up measure table
    MeasureTableModel = new QStandardItemModel(0, 4, this);
    MeasureTableModel->setHorizontalHeaderItem(0, new QStandardItem());
    MeasureTableModel->setHorizontalHeaderItem(1, new QStandardItem("Name"));
    MeasureTableModel->setHorizontalHeaderItem(2, new QStandardItem("FFT Max /Hz"));
    MeasureTableModel->setHorizontalHeaderItem(3, new QStandardItem("Integrated FFT"));
    ui->MeasurementTable->setModel(MeasureTableModel);
    ui->MeasurementTable->horizontalHeader()->resizeSection(0, 30);

    // Set up vailidation for the limit boxes
    ui->xMinBox->setValidator(new QDoubleValidator(this));
    ui->xMaxBox->setValidator(new QDoubleValidator(this));
    ui->yMinBox->setValidator(new QDoubleValidator(this));
    ui->yMaxBox->setValidator(new QDoubleValidator(this));

    // Link F7 pressing with sample data generation
    QShortcut * sampledata = new QShortcut(QKeySequence(tr("F7")), this);
    connect(sampledata, SIGNAL(activated()), this, SLOT(generateSampleData()));

    // Set up audio format with default values
    LastAudioFormat = new AudioFormatParameters;
    LastAudioFormat->RecordDevice = QAudioDeviceInfo::defaultInputDevice();
    LastAudioFormat->RecordTime = 1.;
    LastAudioFormat->BitRate = LastAudioFormat->RecordDevice.preferredFormat().sampleSize();
    LastAudioFormat->SampleRate = LastAudioFormat->RecordDevice.preferredFormat().sampleRate();

    // On startup, hide the plot edit buttons since no data plotted
    ui->PlotAxisGroupBox->setEnabled(false);

    // enable context menu on DPATable
    connect(ui->DPATable, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(ShowDPATableContext(const QPoint &)));

    // Set up operator mode UI (so that the keyboard shortcuts can work only if DPATable has focus
    OperatorModeUI = new TOperatorModeUI(this);

    ui->DPATable->installEventFilter(OperatorModeUI);
    connect(OperatorModeUI, SIGNAL(LostFocus()), this, SLOT(CancelOperatorMode()));
    connect(OperatorModeUI, SIGNAL(EnableOperatorMode()), this, SLOT(MinusOperatorPressed()));
    connect(OperatorModeUI, SIGNAL(ReturnPressed()), this, SLOT(DPATable_ReturnPressed()));

    // make status bar
    ui->statusBar->showMessage("Ready");
}

MainWindow::~MainWindow()
{
    delete ui;
    delete LastAudioFormat;
}

void MainWindow::generateSampleData()
{
    // Sample data generation: Happens when F7 is pressed
    float sampleRate = 2048.;
    float maxTime = 2.;
    //float frequency = 1024*(rand()/(1.*RAND_MAX));
    float frequency = 220;

    QVector<float> data;

    int noPoints = maxTime*sampleRate;

    float dTime = 1./sampleRate;
    float time = 0.;
    for (int i=0; i<noPoints; i++) {
        time=dTime*i;
        data.append(sin(2.*3.1415926*frequency*time));
    }

    this->DataPointArrayVector.append(new TDataPointArray(data));
    this->DataPointArrayVector[this->DataPointArrayVector.size()-1]->SampleRate = sampleRate;
    this->DataPointArrayVector[this->DataPointArrayVector.size()-1]->SetUiName(QString::number(frequency).append(QString("Hz Sample")));

    this->AddDPATableItem(this->DataPointArrayVector.size()-1);
    RePaintUI(this->DataPointArrayVector.size()==1);
}

void MainWindow::MinusOperatorPressed() {
    // Turn on operator listening mode
    this->OperatorListeningMode();
}

void MainWindow::OperatorListeningMode() {
    // Get the current selection of the DPATable
    QModelIndexList indexList = ui->DPATable->selectionModel()->selectedIndexes();
    int row=-1;
    foreach (QModelIndex index, indexList) {
        if (row!=index.row()) {
            row = index.row();
        }
    }
    // Set this as the minuend
    OpModeMinuend = DataPointArrayVector[row];

    // Make the top label give instructions
    ui->PlotDataLabel->setText("Select subtrahend");
    ui->PlotDataLabel->setFont(QFont(font().family(), 20, 10));

    // tell the OMUI that it should now listen for escape actions
    OperatorModeUI->OpModeEnabled = true;

    // tell this class op mode is on
    OperatorModeEnabled = true;

    ui->statusBar->showMessage("Operator mode on");

}

void MainWindow::CancelOperatorMode() {
    // Operator mode cancelled by user, so make everything back to normal
    ui->PlotDataLabel->setText("Plot Data");
    ui->PlotDataLabel->setFont(QFont());

    // tell OMUI that operator mode is no longer on
    OperatorModeUI->OpModeEnabled = false;

    // tell this class op mode is off
    OperatorModeEnabled = false;

    ui->statusBar->showMessage("Ready");
}

void MainWindow::on_DPATable_clicked(const QModelIndex &index)
{
    // if operator mode is not enabled, don't do anything
    if (!OperatorModeEnabled) return;

    // get selected row
    int row = index.row();
    // make this the minuend
    OpModeSubtrahend = DataPointArrayVector[row];

    // Apply subtraction
    ui->statusBar->showMessage("Subtracting...");
    SubtractDPA();

    // Get out of operator mode
    CancelOperatorMode();
}

void MainWindow::DPATable_ReturnPressed() {
    // have no effect if operator mode not enabled
    if (!OperatorModeEnabled) return;

    // Get the current selection of the DPATable
    QModelIndexList indexList = ui->DPATable->selectionModel()->selectedIndexes();
    int row=-1;
    foreach (QModelIndex index, indexList) {
        if (row!=index.row()) {
            row = index.row();
        }
    }
    // Set this as the minuend
    OpModeSubtrahend = DataPointArrayVector[row];

    // Apply subtraction
    ui->statusBar->showMessage("Subtracting...");
    SubtractDPA();

    // Get out of operator mode
    CancelOperatorMode();
}

void MainWindow::SubtractDPA() {
    TDataPointArray * subtracted = new TDataPointArray((*OpModeMinuend)-(*OpModeSubtrahend));
    DataPointArrayVector.push_back(subtracted);
    AddDPATableItem(DataPointArrayVector.size()-1);
    DoPlot(false);
}

void MainWindow::DoPlot(bool ResetAxis, bool exporting)
{
    // if exporting, use ChartView which is
    ui->statusBar->showMessage("Redrawing plot");
    QChart * m_chart;

    if (exporting) {
        // use ExportChart and ExportChartView if exporting
        ExportChart = new QChart();
        ExportChartView = new QChartView(ExportChart);
        ExportChartView->setSceneRect(0,0,1000,1000);
        ExportChart->setDropShadowEnabled(false);
        m_chart = ExportChart;
    } else {
        // if not exporting, use the one already there
        m_chart = GUIChart;
        // Clean up old series and chart objects
        GUIChartSeries.clear();
        m_chart->removeAllSeries();
        delete m_chart->axisX();
        delete m_chart->axisY();
    }

    // m_chart now corresponds to either the GUI chart or the export graphic

    // get plot type from UI components (no longer in argument)
    bool doFFT = ui->FFTRadio->isChecked();
    // only allow log axis if doFFT is selected
    bool doLogX = ui->LogXCheckBox->isChecked() && doFFT;
    bool doLogY = ui->LogYCheckBox->isChecked() && doFFT;

    // see if anything wants to be auto
    bool AutoXmin = false;
    bool AutoXmax = false;
    bool AutoYmin = false;
    bool AutoYmax = false;

    if (ui->xMinBox->text()=="auto") AutoXmin = true;
    if (ui->xMaxBox->text()=="auto") AutoXmax = true;
    if (ui->yMinBox->text()=="auto") AutoYmin = true;
    if (ui->yMaxBox->text()=="auto") AutoYmax = true;

    if (ResetAxis) {
        AutoXmin = true;
        AutoXmax = true;
        AutoYmin = true;
        AutoYmax = true;
    }

    QLogValueAxis * LogAxisX;
    QValueAxis * axisX;
    QLogValueAxis * LogAxisY;
    QValueAxis * axisY;

    QAbstractAxis * abstractX;
    QAbstractAxis * abstractY;

    // is there data? count how many DPAS there are
    QVector<TDataPointArray*> PlotDPAs;
    foreach (TDataPointArray * DPA, DataPointArrayVector)
        if (DPA->ShowInGraph) PlotDPAs.push_back(DPA);

    // if there is >0 DPAs to be plotted
    if (PlotDPAs.size()>0) {

        // set up axis
        if (doLogX) {
            LogAxisX = new QLogValueAxis();
            LogAxisX->setLabelFormat("%g");
            abstractX = LogAxisX;
        } else {
            axisX = new QValueAxis();
            axisX->setLabelFormat("%g");
            abstractX = axisX;
        }

        if (doLogY) {
            LogAxisY = new QLogValueAxis();
            LogAxisY->setLabelFormat("%g");
            abstractY = LogAxisY;
        } else {
            axisY = new QValueAxis();
            axisY->setLabelFormat("%g");
            abstractY = axisY;
        }


        for (int i = 0; i<PlotDPAs.size(); i++) {
            // if show is enabled
            if (PlotDPAs[i]->ShowInGraph) {
                if (exporting) {
                    ExportChartSeries.push_back(PlotDPAs[i]->GetScatterData(doFFT));
                    ExportChartSeries[i]->setUseOpenGL(false); // only use openGL if not exporting
                    ExportChartSeries[i]->setName(PlotDPAs[i]->GetUiName());
                    m_chart->addSeries(ExportChartSeries[i]);
                } else {
                    GUIChartSeries.push_back(PlotDPAs[i]->GetScatterData(doFFT));
                    GUIChartSeries[i]->setUseOpenGL(true); // only use openGL if not exporting
                    GUIChartSeries[i]->setName(PlotDPAs[i]->GetUiName());
                    m_chart->addSeries(GUIChartSeries[i]);
                }
            }
        }

        m_chart->legend()->setVisible(exporting); // show legend if exporting

        // Do axis
        m_chart->createDefaultAxes();
        // For each series in chart, attach both axis to it
        for (int i=0; i<PlotDPAs.size(); i++) {
            if (!AutoXmin) abstractX->setMin(ui->xMinBox->text().toFloat());
            if (!AutoXmax) abstractX->setMax(ui->xMaxBox->text().toFloat());
            if (!AutoYmin) abstractY->setMin(ui->yMinBox->text().toFloat());
            if (!AutoYmax) abstractY->setMax(ui->yMaxBox->text().toFloat());

            if (AutoXmin && AutoXmax) abstractX->setRange(0,0);
            if (AutoYmin && AutoYmax) abstractY->setRange(0,0);

            if (exporting) {
                m_chart->setAxisX(abstractX, ExportChartSeries[i]);
                m_chart->setAxisY(abstractY, ExportChartSeries[i]);
            } else {
                m_chart->setAxisX(abstractX, GUIChartSeries[i]);
                m_chart->setAxisY(abstractY, GUIChartSeries[i]);
            }
        }

        doFFT ? m_chart->axisX()->setTitleText("Frequency /Hz") : m_chart->axisX()->setTitleText("Time /s");
        m_chart->axisY()->setTitleText("Amplitude (arb. units)");

        // start x at 0 if auto axis set
        if (ResetAxis) m_chart->axisX()->setMin(0);

        // Fill out the axis range boxes
        if (ResetAxis) {
            ui->xMaxBox->setText("auto");
            ui->xMinBox->setText("auto");
            ui->yMinBox->setText("auto");
            ui->yMaxBox->setText("auto");
        }
    }
    ui->statusBar->showMessage("Ready");
}

void MainWindow::on_LogXCheckBox_toggled(bool /*checked*/)
{
    this->DoPlot(true);
}

void MainWindow::on_LogYCheckBox_toggled(bool /*checked*/)
{
    this->DoPlot(true);
}


void MainWindow::on_RawDataRadio_toggled(bool checked)
{
    this->DoPlot(!checked);

    ui->LogYCheckBox->setVisible(!checked); //this disables the log feature for the time domain plot as it is unecessary;
    ui->LogXCheckBox->setVisible(!checked);

}

void MainWindow::on_AddButton_clicked()
{
    TSignalSettings * SignalAddBox = new TSignalSettings(LastAudioFormat, this);
    SignalAddBox->exec();

    if (SignalAddBox->result() == QDialog::Accepted) {
        DataPointArrayVector.append(SignalAddBox->OutputDPA);
        DoPlot(this->DataPointArrayVector.size()==1);
        this->AddDPATableItem(DataPointArrayVector.size()-1);
        ui->PlotAxisGroupBox->setEnabled(true);
    }
    delete SignalAddBox;
}

void MainWindow::AddDPATableItem(int VectorIndex) {
    QList<QStandardItem*> DPATableRow;

    // Get information to put into row
    QString Name = DataPointArrayVector[VectorIndex]->GetUiName();
    QString Duration = QString::number(DataPointArrayVector[VectorIndex]->GetData().size() * 1.0 / (1.*DataPointArrayVector[VectorIndex]->SampleRate));
    QString SampleRate = QString::number(DataPointArrayVector[VectorIndex]->SampleRate);
    QString BitRate = QString::number(DataPointArrayVector[VectorIndex]->BitRate);

    QPixmap pixmap(100,100);
    pixmap.fill(DataPointArrayVector[VectorIndex]->plotColor);
    QIcon Icon(pixmap);

    // if hidden, append "Hidden" to the name
    if (!DataPointArrayVector[VectorIndex]->ShowInGraph) Name = "(Hidden)" + Name;

    DPATableRow.append(new QStandardItem(Icon, QString("")));
    DPATableRow.append(new QStandardItem(Name));
    DPATableRow.append(new QStandardItem(Duration));
    DPATableRow.append(new QStandardItem(SampleRate));
    DPATableRow.append(new QStandardItem(BitRate));
    DPATableModel->appendRow(DPATableRow);

    ui->DPATable->selectRow(VectorIndex);
    ui->deleteButton->setEnabled(true);

    // Redo Measurements
    this->UpdateMeasurementTable();
}

void MainWindow::RePaintUI(bool ResetAxis) {
    QModelIndexList SelectedRow = ui->DPATable->selectionModel()->selectedIndexes();
    // Remove all rows from table of plots
    this->DPATableModel->removeRows(0,this->DataPointArrayVector.size());
    // Repopulate the table
    for (int i=0; i<this->DataPointArrayVector.size(); i++) {
        this->AddDPATableItem(i);
    }

    // if there's a data array, then select something
    if (DataPointArrayVector.size()>0) {
        ui->DPATable->selectionModel()->select(SelectedRow[0],QItemSelectionModel::Rows | QItemSelectionModel::ClearAndSelect);
    }

    // Enable the plot axis settings iff there's data available
    ui->PlotAxisGroupBox->setEnabled(DataPointArrayVector.size()>0);

    // Replot the data
    this->DoPlot(ResetAxis);

    // Redo Measurements
    this->UpdateMeasurementTable();
}

void MainWindow::UpdateMeasurementTable() {
    // remove all entries in measure table
    this->MeasureTableModel->clear();

    for (int i=0; i<DataPointArrayVector.size(); i++) {
        // repopulate the measure table
        QList<QStandardItem*> MeasurementTableRow;

        // coloured icon
        QPixmap pixmap(100,100);
        pixmap.fill(DataPointArrayVector[i]->plotColor);
        QIcon Icon(pixmap);

        MeasurementTableRow.append(new QStandardItem(Icon, QString("")));
        MeasurementTableRow.append(new QStandardItem(DataPointArrayVector[i]->GetUiName()));
        MeasurementTableRow.append(new QStandardItem(QString::number(DataPointArrayVector[i]->getFFTPeak())));

        MeasureTableModel->appendRow(MeasurementTableRow);
    }
}

void MainWindow::on_deleteButton_clicked()
{
    // if operator mode was enabled, cancel it
    if (OperatorModeEnabled) {
        CancelOperatorMode();
    }

    QModelIndexList indexList = ui->DPATable->selectionModel()->selectedIndexes();
    int row=-1;

    foreach (QModelIndex index, indexList) {
        // Prevent deleting the same row twice
        if (row!=index.row()) {
            row = index.row();
            DPATableModel->removeRow(row);
            delete(DataPointArrayVector[row]);
            DataPointArrayVector.remove(row);
        }
    }

    // if no more datasets left, disable delete button
    if (DPATableModel->rowCount()==0) {
        ui->deleteButton->setEnabled(false);
    }

    // Update the plot
    this->DoPlot(ui->FFTRadio->isChecked());

}

void MainWindow::on_DPATable_doubleClicked(const QModelIndex &index)
{
    // double click changes colour
    int row = index.row();
    DataPointArrayVector[row]->generateColor();
    this->RePaintUI();
}

void MainWindow::ShowDPATableContext(const QPoint &pos) {
    if (DataPointArrayVector.size()>0) {
        QMenu * ContextMenu = new QMenu(this);

        // Get the selected row
        int SelectedRow = ui->DPATable->selectionModel()->selectedIndexes()[0].row();

        // Items in the context menu
        if (this->DataPointArrayVector[SelectedRow]->ShowInGraph) DPAActionShowHide = new QAction("Hide", this);
        else DPAActionShowHide = new QAction("Show", this);
        ContextMenu->addAction(DPAActionShowHide);
        if (this->DataPointArrayVector.size()>1) {
            DPAActionSetAsNoise = new QAction("Set as noise");
            ContextMenu->addAction(DPAActionSetAsNoise);
        }
        DPAActionBringToFront = new QAction("Bring to front");
        ContextMenu->addAction(DPAActionBringToFront);
        DPAActionChangeColour = new QAction("Change Colour", this);
        ContextMenu->addAction(DPAActionChangeColour);
        ContextMenu->addSeparator();
        DPAActionChopBeginning = new QAction("Chop Beginning", this);
        ContextMenu->addAction(DPAActionChopBeginning);
        DPAActionChopEnd = new QAction("Chop End", this);
        ContextMenu->addAction(DPAActionChopEnd);
        DPAActionRemoveOffset = new QAction("Remove Offset", this);
        ContextMenu->addAction(DPAActionRemoveOffset);
        ContextMenu->addSeparator();
        DPAActionDelete = new QAction("Delete " + this->DataPointArrayVector[SelectedRow]->GetUiName(), this);
        ContextMenu->addAction(DPAActionDelete);

        connect(ContextMenu, SIGNAL(triggered(QAction*)), this, SLOT(DPAContext_ItemClicked(QAction*)));
        ContextMenu->exec(ui->DPATable->mapToGlobal(pos));
    }
}

void MainWindow::DPAContext_ItemClicked(QAction *action) {
    // add in actions here for the DPA table context menu
    int SelectedDPAIndex = this->ui->DPATable->selectionModel()->currentIndex().row();
    if (action==DPAActionDelete) {
        this->on_deleteButton_clicked();
    } else if (action==DPAActionBringToFront) {
        this->DPABringToFront(SelectedDPAIndex);
    } else if (action==DPAActionChangeColour) {
        this->on_DPATable_doubleClicked(this->ui->DPATable->selectionModel()->currentIndex());
    } else if (action==DPAActionChopBeginning) {
        this->DPAChopBeginning(SelectedDPAIndex);
    } else if (action==DPAActionRemoveOffset) {
        this->DataPointArrayVector[SelectedDPAIndex]->RemoveOffset();
        this->DoPlot(true);
    } else if (action==DPAActionChopEnd) {
        this->DPAChopEnd(SelectedDPAIndex);
    } else if (action==DPAActionShowHide) {
        this->DPAShowHide(SelectedDPAIndex);
    } else if (action==DPAActionSetAsNoise) {
        this->DPASetAsNoise(SelectedDPAIndex);
    }

}

void MainWindow::DPASetAsNoise(int DPALocation) {
    // (Un)Set this one as the noise signal

    if (NoiseDPAs.contains(DPALocation)) {
        this->NoiseDPAs.remove(this->NoiseDPAs.indexOf(DPALocation));
        this->DataPointArrayVector[DPALocation]->SetUiName(this->DataPointArrayVector[DPALocation]->GetUiName().remove(0, 6));
    } else {
        // add to the noise array
        this->NoiseDPAs.push_back(DPALocation);
        this->DataPointArrayVector[DPALocation]->SetUiName("Noise "+this->DataPointArrayVector[DPALocation]->GetUiName());
        this->DataPointArrayVector[DPALocation]->ShowInGraph = false;
    }

    // update all the fouriers
    this->updateAllFouriers();

    // repaint the UI
    this->RePaintUI(true);
}

void MainWindow::DPAChopBeginning(int DPALocation) {
    // get total time
    float TotalTime = this->DataPointArrayVector[DPALocation]->getTotalTime();
    float TimeToChop = QInputDialog::getDouble(this, tr("Chop Beginning"), tr("Seconds to chop off beginning:"),
                                                   0, 0, TotalTime, 3);
    this->DataPointArrayVector[DPALocation]->ChopBeginning(TimeToChop);
    this->RePaintUI(true);
}

void MainWindow::DPAChopEnd(int DPALocation) {
    float TotalTime = this->DataPointArrayVector[DPALocation]->getTotalTime();
    float TimeToChop = QInputDialog::getDouble(this, tr("Chop End"), tr("Seconds to chop from end:"),
                                                   0, 0, TotalTime, 3);
    this->DataPointArrayVector[DPALocation]->ChopEnd(this->DataPointArrayVector[DPALocation]->getTotalTime()-TimeToChop);
    this->RePaintUI(true);
}

void MainWindow::DPAShowHide(int DPALocation) {
    this->DataPointArrayVector[DPALocation]->ShowInGraph = !this->DataPointArrayVector[DPALocation]->ShowInGraph;

    this->RePaintUI(false);

}

void MainWindow::DPABringToFront(int DPALocation) {
    // get a pointer to the array being brought to the front
    TDataPointArray * CurrentSelectedDPA = this->DataPointArrayVector[DPALocation];
    // remove the pointer from DPAVector
    this->DataPointArrayVector.removeAt(DPALocation);
    // add the pointer to the end of the array
    this->DataPointArrayVector.push_back(CurrentSelectedDPA);

    // repaint UI
    this->RePaintUI(false);

    // select the last row
    QModelIndex LastRowIndex = ui->DPATable->model()->index(this->DataPointArrayVector.size() - 1,1);
    ui->DPATable->selectionModel()->select(LastRowIndex,QItemSelectionModel::Rows | QItemSelectionModel::ClearAndSelect);
}

void MainWindow::on_xMinBox_returnPressed()
{
    GUIChart->axisX()->setMin(ui->xMinBox->text().toDouble());
}

void MainWindow::on_xMaxBox_returnPressed()
{
    GUIChart->axisX()->setMax(ui->xMaxBox->text().toDouble());
}


void MainWindow::on_yMinBox_returnPressed()
{
    GUIChart->axisY()->setMin(ui->yMinBox->text().toDouble());
}

void MainWindow::on_yMaxBox_returnPressed()
{
    GUIChart->axisY()->setMax(ui->yMaxBox->text().toDouble());
}

void MainWindow::updateAllFouriers(bool RePlot) {
    ui->statusBar->showMessage("Updating Fouriers...");
    // Find the amount to average by
    int AverageLength = -1;
    if (ui->FFTAverageBox->currentText()=="None") {
        AverageLength = -1; // length=-1 just makes it default to no averaging
    } else {
        AverageLength = ui->FFTAverageBox->currentText().toInt();
    }

    FFTWindow Window = FFTWindow::oldWindow;


    // Decide upon window function
    if (ui->WindowSelectBox->currentText()=="Hann")
        Window = FFTWindow::Hanning;
    else if (ui->WindowSelectBox->currentText()=="Hamming")
        Window = FFTWindow::Hamming;
    else if (ui->WindowSelectBox->currentText()=="Blackman")
        Window = FFTWindow::Blackman;
    else if (ui->WindowSelectBox->currentText()=="None")
        Window = FFTWindow::noWindow;


    // do the fourier:

    // first the noise signals
    for (int j=0; j<NoiseDPAs.size(); j++)
        DataPointArrayVector[NoiseDPAs[j]]->UpdateFourier(AverageLength, Window);

    // now the rest (but don't do the noise)
    for (int i=0; i<DataPointArrayVector.size(); i++)
        if (!(NoiseDPAs.contains(i))) {
            DataPointArrayVector[i]->UpdateFourier(AverageLength, Window);
            // now remove the nosie
            for (int j=0; j<NoiseDPAs.size(); j++)
                DataPointArrayVector[i]->RemoveNoise(DataPointArrayVector[NoiseDPAs[j]]);
        }

    // Update the plot
    if (RePlot) this->DoPlot(false);

    ui->statusBar->showMessage("Ready");
}

void MainWindow::on_WindowSelectBox_currentIndexChanged(const QString &/*arg1*/)
{
    this->updateAllFouriers();
}


void MainWindow::on_FFTAverageBox_currentIndexChanged(const QString &/*arg1*/)
{
    this->updateAllFouriers();
}

void MainWindow::on_actionChop_Beginning_triggered()
{
    // Chop off the first x seconds from all tracks

    // get the largest time for all the DPAs
    float LargestTime = 0;
    foreach (TDataPointArray * DPA, this->DataPointArrayVector)
        if (DPA->getTotalTime() > LargestTime) LargestTime = DPA->getTotalTime();

    float TimeToChop = QInputDialog::getDouble(this, tr("Chop Beginning"), tr("Seconds to chop off beginning:"),
                                               0, 0, LargestTime, 3);

    // Chop each DPA
    foreach (TDataPointArray * DPA, this->DataPointArrayVector)
        DPA->ChopBeginning(TimeToChop);

    // Reset FFT to the default settings
//    ui->FFTAverageBox->setCurrentIndex(0);
//    ui->WindowSelectBox->setCurrentIndex(0);

    this->RePaintUI(true);
}

void MainWindow::on_actionChop_End_triggered()
{
    // remove the last y seconds from all tracks

    // get the largest time for all the DPAs
    float LargestTime = 0;
    foreach (TDataPointArray * DPA, this->DataPointArrayVector)
        if (DPA->getTotalTime() > LargestTime) LargestTime = DPA->getTotalTime();

    float TimeToChop = QInputDialog::getDouble(this, tr("Chop End"), tr("Seconds to chop from end:"),
                                               0, 0, LargestTime, 3);

    // Chop each DPA
    foreach (TDataPointArray * DPA, this->DataPointArrayVector)
        DPA->ChopEnd(DPA->getTotalTime()-TimeToChop);

//    // Reset FFT to the default settings
//    ui->FFTAverageBox->setCurrentIndex(0);
//    ui->WindowSelectBox->setCurrentIndex(0);

    this->RePaintUI(true);
}

void MainWindow::on_actionRemove_Offset_triggered()
{
    // remove offset from each DPA
    foreach (TDataPointArray * DPA, this->DataPointArrayVector)
        DPA->RemoveOffset();

    this->RePaintUI(true);
}

void MainWindow::on_actionExport_triggered()
{
    // Make a save file dialog to get the location
    QString ExportFileLocation = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first().append("/exportFile.csv");
    ExportFileLocation = QFileDialog::getSaveFileName(this, tr("Export file"), ExportFileLocation, tr("CSV file (*.csv)"));

    QFile ExportFile;
    ExportFile.setFileName(ExportFileLocation);

    QTextStream FileWriteStream(&ExportFile);

    // Open file
    if (ExportFile.open( QIODevice::WriteOnly)) {
        // Write to file routine
        QString CurrentFileLine;

        // write the col headings:
        CurrentFileLine = QString("time,");

        /* Due to potentially differing sample rates, the times of the samples may be out of sync.
         * Hence, we need to:
         * - Find the largest sample rate of all the tracks, use this to base the times off of
         * - Get the total time off each of the datasets
         * - Go up in steps of 1/SR_max, incrementing i:
         *      fe TDPA
         *        is i/SR_max < TDPA.Tmax?
         *            y: if SR_max = TDPA.SR, just get the result and print onto line
         *                  otherwise linearly interpolate
         *            n: don't worry
         */

        // Find the largest sample rate and longest time
        float SR_max = 0.;
        float time_max = 0.;
        for (int i = 0; i<this->DataPointArrayVector.size(); i++) {
            if (this->DataPointArrayVector[i]->SampleRate>SR_max) {
                SR_max = this->DataPointArrayVector[i]->SampleRate;
            }
            if (this->DataPointArrayVector[i]->getTotalTime()>time_max) {
                time_max = this->DataPointArrayVector[i]->getTotalTime();
            }

            // while we're looping over the DPAs, might as well add in the file heading here:
            CurrentFileLine.append(this->DataPointArrayVector[i]->GetUiName().append(","));
        }

        // use the largest sample rate as the time increment
        float timeIncrement = 1./(1.*SR_max);

        // go up the time
        for (float time = 0; time<time_max; time+=timeIncrement) {
            // write the time onto the line
            CurrentFileLine = QString::number(time).append(",");
            // go through each DPA
            for (int i=0; i<this->DataPointArrayVector.size(); i++) {
                // print out data at this time (everything else is automatic)
                CurrentFileLine.append(QString::number(this->DataPointArrayVector[i]->getInterpolatedData(time)).append(","));
            }

            // write to file
            FileWriteStream << CurrentFileLine << "\n";
        }

        // close file
        ExportFile.close();


    } else {
        // file write failed
        // Notify the user
        QMessageBox box;
        box.setText("File write failed.");
        box.show();
        // TODO: BOX NOT SHOWING
    }
}

void MainWindow::on_actionExport_chart_triggered()
{
    // PDF writing inspired by: https://stackoverflow.com/questions/27530390/qt-charts-rendering-problems-on-a-pdf

    // create save file dialog, get location
    QString ExportFileLocation = QStandardPaths::standardLocations(QStandardPaths::HomeLocation).first().append("/exportGraph.pdf");
    ExportFileLocation = QFileDialog::getSaveFileName(this, tr("Export chart file"), ExportFileLocation, tr("PDF file (*.pdf)"));

    // save the file to the location specified:

    // create PDF writer
    QPdfWriter writer(ExportFileLocation);
    writer.setCreator("NoiseSpec");
    writer.setPageSize(QPagedPaintDevice::A4);

    // prepare the plot
    this->DoPlot(false, true);

    // disguise the bug as a 'preview window', nobody will suspect a thing...
    ExportChartView->show();
    ExportChartView->setWindowTitle("Exported Graph Preview");
    ExportChartView->setWindowFlags(Qt::Popup | Qt::WindowCloseButtonHint);

    // paint the chart in the PDF
    QPainter painter(&writer);
    ExportChartView->render(&painter);
    painter.end();

    // delete the pointers
    delete ExportChart;
    delete ExportChartView;

}
