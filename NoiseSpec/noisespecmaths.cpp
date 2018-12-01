#define SWAP(a,b) tempr=(a);(a)=(b);(b)=tempr;

#include <noisespecmaths.h>

int round2(int number)
{
    return pow(2,ceil(log(number)/log(2)));
}

QVector<float> PowerFFT(float *data, unsigned int N) {
    // nn:= number of [re im] pairs to FFT
    unsigned int nn = round2(N);

    // Define vector for [re im re im] data
    QVector<float> FFTData;

    FFTData.resize(nn*2);

    // put data into array
    for (unsigned int i=0; i<N; i++) {
        FFTData[2*i] = data[i]; // Re
        FFTData[2*i+1] = 0.; // Im
    }

    // zero-pad the rest of the array
    for (unsigned int i=2*N; i<nn*2; i++) {
        FFTData[i] = 0.;
    }

    // do FFT
    four1(&(FFTData[0]), nn, -1);

    // put FFT data into data[..]

    for (unsigned int i=0; i<nn; i++) {
        FFTData[i] = sqrt(pow(FFTData[2*i],2.) + pow(FFTData[2*i+1],2.));
        // ban any result from being 0
        if (FFTData[i]==0.) FFTData[i] = 0.0000001;
    }

    // Resize: /2 for re im re im
    FFTData.resize(round(FFTData.size()/2));

    return FFTData;

}

void four1(float * data, unsigned int nn, int isign)
{
    // Replaced all [x] with [x-1]... so now arrays start at 0

    unsigned long n,mmax,m,j,istep,i;
    double wtemp,wr,wpr,wpi,wi,theta; //Double precision for the trigonometfloat
    float tempr,tempi; //ric recurrences.
    n=nn << 1;
    j=1;// replaced 1<->0
    for (i=1;i<n;i+=2) { // replaced i=1<->0
        if (j > i) {
            SWAP(data[j-1],data[i-1]); //Exchange the two complex numbers.
            SWAP(data[j],data[i]);
        }
        m=nn;
        while (m >= 2 && j > m) {
            j -= m;
            m >>= 1;
        }
        j += m;
    }

    mmax=2;
    while (n > mmax) { //Outer loop executed log2 nn times.
        istep=mmax << 1;
        theta=isign*(6.28318530717959/mmax); //Initialize the trigonometric recurrence.
        wtemp=sin(0.5*theta);
        wpr = -2.0*wtemp*wtemp;
        wpi=sin(theta);
        wr=1.0;
        wi=0.0;
        for (m=1;m<mmax;m+=2) {// Here are the two nested inner loops. // replaced m=1<->0
            for (i=m;i<=n;i+=istep) {
                j=i+mmax;// This is the Danielson-Lanczos fortempr=wr*data[j]-wi*data[j+1];
                tempi=wr*data[j]+wi*data[j-1];
                data[j-1]=data[i-1]-tempr;
                data[j]=data[i]-tempi;
                data[i-1] += tempr;
                data[i] += tempi;
            }
            wr=(wtemp=wr)*wpr-wi*wpi+wr;// Trigonometric recurrence.
            wi=wi*wpr+wtemp*wpi+wi;
        }
        mmax=istep;
    }


}

void Sort(QList<int> &Data) {
    // Bubble sort routine

    int tempr; // var for SWAP
    int noSwaps; // no swaps counter

    do {
        noSwaps = 0;

        // for each pair...
        for (int i=0; i<(Data.size()-1); ++i){
            // ... swap if previous is greater than current
            if (Data[i]>Data[i+1]) {
                noSwaps++;
                SWAP(Data[i], Data[i+1]);
            }
        }
    } while (noSwaps!=0);
}

float HannWindow(float fracTime) {
    return sin(3.14159*fracTime)*sin(3.14159*fracTime);
}

float NoWindow(float /*fracTime*/) {
    return 1.;
}

float HammingWindow(float fracTime) {
    return 0.54 - 0.46*cos(2*3.14159*fracTime);
}

float BlackmanWindow(float fracTime) {
    return 0.42659 - 0.49656*cos(2*3.14159*fracTime) + 0.076849*cos(4*3.1415926*fracTime);
}
