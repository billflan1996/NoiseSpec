/* TDataPointArray: Class which holds an array of data harvested from the input
 *
 *
 */

#ifndef TDATAPOINTARRAY_H
#define TDATAPOINTARRAY_H

#include <QObject>
#include <QVector>
#include <QIODevice>
#include <QDataStream>
#include <QAudioFormat>
#include <cmath>
#include <QLineSeries>
#include <noisespecmaths.h>

class TDataPointArray : public QObject
{
    Q_OBJECT
public:
    TDataPointArray(QObject *parent = 0);
    TDataPointArray(const TDataPointArray &old);
    TDataPointArray(QVector<float> &data, QObject *parent = 0);
    TDataPointArray(QIODevice *IODevice, QAudioFormat *m_AudioFormat, QObject *parent = 0);
    TDataPointArray(QIODevice *IODevice, QAudioFormat *m_AudioFormat, QString UIName, QObject *parent = 0);
    TDataPointArray(QIODevice *IODevice, QAudioFormat *m_AudioFormat, QString UIName, float DesiredTime, QObject *parent = 0);

    // subtraction operator
    TDataPointArray operator-(TDataPointArray &a);

    QtCharts::QLineSeries* GetScatterData(bool FFT = false) const;
    QVector<float> GetData(bool FFT = false) const;

    float getInterpolatedData(float time); // get data at any time

    void SetData(QVector<float> data); // Set data with a vector
    void SetData(QIODevice *IODevice, QAudioFormat *m_AudioFormat4); // Set data with an IODevice (microphone)

    void RemoveNoise(TDataPointArray * NoiseData);
  //  void four1(int isign); // FFT algorithm - moved to NSmaths so can be re-used elsewhere

    // GUI parameters
    inline void SetUiName(QString Name) { UI_Name = Name; }
    inline QString GetUiName() const { return UI_Name; }
    void generateColor();
    bool ShowInGraph = true;

    float getTotalTime() const { return 1.*(this->DataPointVector.size()-1)/(1.*SampleRate); } // size-1 due to DPV[0]<=>(t=0)
    int getArrayLocation(float time);

    // Altering functions
    void ChopBeginning(float ChopTime);
    void ChopEnd(float NewEndTime);
    void RemoveOffset();

    // Measurement functions
    float getFFTPeak();
    float getIntegratedFFT();

    QColor plotColor;

    int SampleRate = 1;
    int BitRate = 0;


    // FFT
    void UpdateFourier(int Averagelength = -1, FFTWindow Window = oldWindow);

    // when averaging is turned on
    int FFTAverageLength = 1;

    FFTWindow WindowFunction = noWindow;

    QVector<float> FFTData;
signals:

public slots:

private:
    QVector<float> DataPointVector; // The actual data

    // do FFT on all the data
   // void DoFFT() { FFTData = PowerFFT(&(this->DataPointVector[0]), this->DataPointVector.size());}

    QString UI_Name; // name to put on the UI
};

#endif // TDATAPOINTARRAY_H
