#include "tdatapointarray.h"
#include <fstream>

TDataPointArray::TDataPointArray(QObject *parent) : QObject(parent)
{
    this->generateColor();
}

TDataPointArray::TDataPointArray(const TDataPointArray & old) : QObject(old.parent())
{
    this->SampleRate = old.SampleRate;
    this->BitRate = old.BitRate;
    this->plotColor = old.plotColor;
    this->SetUiName(old.GetUiName());
    this->SetData(old.GetData(false));
}

TDataPointArray::TDataPointArray(QVector<float> &data, QObject *parent) : QObject(parent)
{
    this->SetData(data);
    //HannWindow(&(this->DataPointVector[0]), this->DataPointVector.size());
    this->generateColor();
    this->UpdateFourier();
}

TDataPointArray::TDataPointArray(QIODevice *IODevice, QAudioFormat *m_AudioFormat, QObject *parent) : QObject(parent)
{
    this->SetData(IODevice, m_AudioFormat);
    this->generateColor();
    this->UpdateFourier();
}

TDataPointArray::TDataPointArray(QIODevice *IODevice, QAudioFormat *m_AudioFormat, QString p_UIName, QObject *parent):
    QObject(parent), UI_Name(p_UIName)
{
    this->SetData(IODevice, m_AudioFormat);
    this->generateColor();
    this->UpdateFourier();
}

TDataPointArray::TDataPointArray(QIODevice *IODevice, QAudioFormat *m_AudioFormat, QString p_UIName, float DesiredTime, QObject *parent):
    QObject(parent), UI_Name(p_UIName)
{
    this->SetData(IODevice, m_AudioFormat);

    // shave off the extra time
    int noDesiredElements = round(m_AudioFormat->sampleRate()*DesiredTime);
    this->DataPointVector.resize(noDesiredElements);

    this->generateColor();
    this->UpdateFourier();
}

TDataPointArray TDataPointArray::operator-(TDataPointArray & subtrahend)
{
    QVector<float> outputVector;

    float TotalTime;
    float SampleRate;

    // Find the highest sample rate
    if (this->SampleRate>=subtrahend.SampleRate) {
        // Use this sample rate
        SampleRate = this->SampleRate*1.;
    } else {
        SampleRate = subtrahend.SampleRate*1.;
    }

    // Find largest total time
    float ThisTotalTime = 1.*this->getTotalTime();
    float SubtTotalTime = 1.*subtrahend.getTotalTime();

    if (ThisTotalTime>=SubtTotalTime) {
        TotalTime = ThisTotalTime;
    } else {
        TotalTime = SubtTotalTime;
    }

    // find Np
    int noPoints = ceil(TotalTime*SampleRate)+1;
    float time=0.;
    float dTime = 1./(SampleRate*1.);

    // Go up in steps of 1/SR until both arrays finished
    for (int i=0; i<noPoints; i++) {
        // calculate time
        time = dTime*i;
        // Do the subtraction
        outputVector.append(this->getInterpolatedData(time) - subtrahend.getInterpolatedData(time));

    }

    TDataPointArray OutputDPA = TDataPointArray(this->parent());

    OutputDPA.SampleRate = SampleRate;
    OutputDPA.SetData(outputVector);
    OutputDPA.SetUiName(this->GetUiName() + "-" + subtrahend.GetUiName());
    OutputDPA.plotColor = QColor::fromRgb(round((this->plotColor.red()+subtrahend.plotColor.red())/2),
                                           round((this->plotColor.green()+subtrahend.plotColor.green())/2),
                                           round((this->plotColor.blue()+subtrahend.plotColor.blue())/2) );

    return OutputDPA;
}

void TDataPointArray::UpdateFourier(int Averagelength, FFTWindow Window) {
    // Updates fourier transform with the averaging as given by AverageLength and the window given by Window(..)

    // if AverageLength==-1 OR not a power of 2, just do a standard FFT on all the data
    // if AverageLength==-2, then use what we used before

    if (Averagelength==-1) Averagelength = this->DataPointVector.size();
    if (Averagelength==-2) Averagelength = this->FFTAverageLength;

    // cap average length to the size of the DPA
    if (Averagelength>this->DataPointVector.size()) Averagelength = this->DataPointVector.size();

    // find the window function:

    float (*WindowFn)(float); // define window function

    if (Window==oldWindow) Window = WindowFunction; // if old window selected, just use that
    switch (Window) {
        case noWindow: WindowFn = NoWindow;
            break;
        case Hanning: WindowFn = HannWindow;
            break;
        case Hamming: WindowFn = HammingWindow;
            break;
        case Blackman: WindowFn = BlackmanWindow;
            break;
        default: WindowFn = NoWindow;
    }

    float log2length = log(Averagelength*1.)/log(2.);

    if (round(log2length) == log2length) {
        // if the length is a power of 2, then it is (probably)

        // create vector paddedData[] which is a power of 2 length to mimic what the FFT algorithm normally does
        QVector<float> paddedData = QVector<float>(round2(this->DataPointVector.size()));

        // put the data into it
        paddedData.append(this->DataPointVector);

        // keep track of the current averaging length being used
        this->FFTAverageLength = Averagelength;

        // Clean FFTData
        this->FFTData = QVector<float>(Averagelength);

        // increment i=0 to data.size()/AverageLength (for each segment to FFT)
        for (int i=0; i<paddedData.size()/Averagelength; i++) {
            // Apply window function
            for (int j=0; j<Averagelength;j++) paddedData[i*Averagelength+j]*=WindowFn(j*1./(1.*(Averagelength-1)));

            // do the FFT
            QVector<float> FFTRun = PowerFFT(&(paddedData[i*Averagelength]), Averagelength);

            // for each j value in FFTRun
                // increment FFTData[j]

            for (int j=0; j<FFTRun.size(); j++) this->FFTData[j] += FFTRun[j];
        }


    } else {
        // clear the old FFTData out
        FFTData.clear();

        // put the current DPA into FFTData
        FFTData.append(this->DataPointVector);

        // Record AverageLength
        this->FFTAverageLength = this->FFTData.size();

        // Apply window function
        for (int i=0; i<Averagelength; i++) FFTData[i]*=WindowFn(i*1./(1.*(this->FFTData.size()-1)));

        // do FFT
        FFTData = PowerFFT(&(this->FFTData[0]), this->FFTData.size());
    }

    // chop off the end
    FFTData.resize(FFTData.size()/2);

    // remember window function
    this->WindowFunction = Window;
}

void TDataPointArray::RemoveNoise(TDataPointArray *NoiseData) {
    // remove noise using the data in NoiseData

    // check sampling rates are the same, if not do nothing
    if (NoiseData->SampleRate!=this->SampleRate) return;

    // also check that the current FFT's window and averages are all the same
    if (NoiseData->FFTAverageLength!=this->FFTAverageLength) return;
    if (NoiseData->WindowFunction!=this->WindowFunction) return;

    // finally that the number of points is both the same (avoids weird bugs)
    if (NoiseData->GetData(true).size()!=this->FFTData.size()) return;

    // do the subtraction
    for (int i=0; i<this->FFTData.size(); i++) {
        this->FFTData[i]-= NoiseData->FFTData[i];
    }

}

QVector<float> TDataPointArray::GetData(bool FFT) const {
    return FFT ? (this->FFTData) : (this->DataPointVector);
}

float TDataPointArray::getInterpolatedData(float time)
{
    // is the time requested in the time range for this signal?
    if (time<=this->getTotalTime()) {
        // Interpolate between two points to get the signal at the time requested.
        int beginningIndex, endIndex;
        float index;

        // index = the exact index
        index = time*(this->SampleRate*1.);
        beginningIndex = floor(index);
        endIndex = ceil(index);

        // is the time exact?
        if (index==1.*beginningIndex) {
            // no interpolation needed
            return this->DataPointVector[index];
        } else {
            // need to interpolate
            return this->DataPointVector[beginningIndex]*(1.-index+beginningIndex*1.) + this->DataPointVector[endIndex]*(index-beginningIndex*1.);
        }
    } else {
        // time not in signal range
        return 0.;
    }
}

void TDataPointArray::SetData(QVector<float> data) {
    this->DataPointVector = data;
    this->UpdateFourier();
}

void TDataPointArray::SetData(QIODevice *IODevice, QAudioFormat * m_AudioFormat) {
    // Delete all previous array elements
    this->DataPointVector.clear();
    this->FFTData.clear();

    // Define a stream to get the data from the IODevice
    QDataStream InStream(IODevice);
    // Go to the beginning of the data
    IODevice->seek(0);
    // Same byte order as audio input
    InStream.setByteOrder(QDataStream::LittleEndian);

    this->BitRate = m_AudioFormat->sampleSize();

    // For each xx bits as defined by the format, convert to float and add to the end of the array
    switch (m_AudioFormat->sampleSize()) {
    case 8:
        qint8 AudioSegment8;
        while (!InStream.atEnd()) {
            InStream >> AudioSegment8;
            this->DataPointVector.append(AudioSegment8*1.0);
        }
        break;
    case 16:
        qint16 AudioSegment16;
        while (!InStream.atEnd()) {
            InStream >> AudioSegment16;
            this->DataPointVector.append(AudioSegment16*1.0);
        }
        break;
    case 32:
        qint32 AudioSegment32;
        while (!InStream.atEnd()) {
            InStream >> AudioSegment32;
            this->DataPointVector.append(AudioSegment32*1.0);
        }
        break;
    case 64:
        qint64 AudioSegment64;
        while (!InStream.atEnd()) {
            InStream >> AudioSegment64;
            this->DataPointVector.append(AudioSegment64*1.0);
        }
        break;
    }

    this->SampleRate = m_AudioFormat->sampleRate();
}

QtCharts::QLineSeries* TDataPointArray::GetScatterData(bool FFT) const {
    QtCharts::QLineSeries* series = new QtCharts::QLineSeries();

    if (FFT) {
        float FreqIncrement = (this->SampleRate*1.0)/(2.0*this->FFTData.size());
        for (int i=0; i<this->FFTData.size(); i++) {
            series->append(FreqIncrement*(i), this->FFTData[i]);
        }
    } else {
        // not FFT, plot raw data
        for (int i=0; i<this->DataPointVector.size(); i++) {
            series->append((i)/(1.0*this->SampleRate), this->DataPointVector[i]);
        }
    }
    series->setColor(this->plotColor);
    return series;
}

void TDataPointArray::generateColor() {
    // Set color
    int red = 0;
    int green = 0;
    int blue = 0;
    // Enforce Prettiness rules - dont allow dark or white-like colours
    while (((red>200) && (green>200) && (blue>200)) || ((red<150) && (green<150) && (blue<150))) {
        red = round(rand()%255);
        green = round(rand()%255);
        blue = round(rand()%255);
    }

    this->plotColor = QColor(red, green, blue);
}

float TDataPointArray::getIntegratedFFT() {
    return 0;
}

float TDataPointArray::getFFTPeak() {
    int Imax = 0;
    float MaxAmplitude = 0.;
    for (int i=0; i<this->FFTData.size(); i++) {
        if (this->FFTData[i]>MaxAmplitude) {
            Imax = i;
            MaxAmplitude = this->FFTData[i];
        }
    }
    return Imax*(this->SampleRate*1.0)/(2.0*this->FFTData.size());
}

int TDataPointArray::getArrayLocation(float time) {
    // get the location in DataPointArray
    int location = round(time*SampleRate*1.);
    if (time<this->getTotalTime()) return location;
    else return 0;
}

void TDataPointArray::ChopBeginning(float ChopTime) {
    // chop off the first ChopTime seconds from the front

    // get the array location
    int NewArrayStart = getArrayLocation(ChopTime);
    // remove the values up to NewArrayStart
    if (NewArrayStart!=0) this->DataPointVector.remove(0, NewArrayStart);

    // fourier will have changed, so update
    this->UpdateFourier(-2, oldWindow);
}

void TDataPointArray::ChopEnd(float NewEndTime) {
    // Resize the array up to NewEndTime

    // get the array location
    int NewArrayEnd = getArrayLocation(NewEndTime);
    // remove the values up to NewArrayStart
    if (NewArrayEnd>0) this->DataPointVector.resize(NewArrayEnd+1);

    // fourier will have changed, so update
    this->UpdateFourier(-2, oldWindow);
}

void TDataPointArray::RemoveOffset() {
    // removes offset on the data (shifts by -average of all the data)

    // calculate average
    float average = 0;
    for (int i=0; i<this->DataPointVector.size(); i++)
        average += this->DataPointVector[i]/this->DataPointVector.size();

    // shift each element by -average
    for (int i=0; i<this->DataPointVector.size(); i++)
        this->DataPointVector[i] -= average;

    this->UpdateFourier(-2, oldWindow);
}
