// CPP program to demonstrate multithreading 
// using three different callables. 
#include "multithread.h"

using namespace std;

int globalt;

mutex mtx;
condition_variable cv;

int ganjil = 0;
int type;
bool shipment_available() { return ganjil != 0; }

// A dummy function 


void thGenap(int Z)
{

    for (int i = 0; i < Z; i++) {
        if (i % 2 == 0) {
            cout << "\nGenap: " << i << "\n";
            Sleep(1);

        }
        
    }
}

void thGanjil(int Z)
{

    for (int i = 0; i < Z; i++) {
        if (i % 2 != 0) {
            cout << "\nGanjil: " << i << "\n";
            Sleep(1);

        }
       
        

    }
}


void threadGanjil(int n) {
    for (int i = 0; i < n; ++i) {
        std::unique_lock<std::mutex> lck(mtx);
        cv.wait(lck, shipment_available);
        // Hanya menampilkan ganjil
        if (ganjil % 2 != 0) {
            std::cout << "\n Ganjil:" << ganjil << '\n';
        }
        ganjil = 0; //selang-seling 
    }
}

void threadGenap() {
    for (int i = 0; i < 100; ++i) {
        while (shipment_available()) std::this_thread::yield();
        unique_lock<mutex> lck(mtx);
        ganjil = i + 1; //selang-seling biar jadi genap 
        // hanya menampilkan Genap
        if (i % 2 == 0) {
            cout << "\n Genap:" << i << "\n";
        }

        cv.notify_one();
    }
}




void MultiThreadRandom() {
    cout << "Contoh Aplikasi MultiThread Ganjil dan Genap secara RANDOM" << endl;

    // This thread is launched by using  
    // function pointer as callable 

    thread th1(thGenap, 100);
    thread th2(thGanjil, 100);



    th1.join();
    th2.join();



}

void MultiThreadBerurutan() {
    cout << "Contoh Aplikasi MultiThread Ganjil dan Genap secara BERURUTAN" << endl;
    thread thread1(threadGanjil, 100);
    thread thread2(threadGenap);

    // produce 10 items when needed:
    //threadGenap();

    thread1.join();
    thread2.join();
}



int main()
{
    cout << "Aplikasi MultiThread, pilih salah satu \n: Ingin RANDOM (1) atau Berurutan (2):" << endl;
    cin >> type;
    if (type == 1) {
        MultiThreadRandom();
        cin >> globalt;
    }
    else if (type == 2) {
        MultiThreadBerurutan();
        cin >> globalt;
    }
    else {
        cout << "Maaf, Pilihan Tidak Tersedia..." << endl;
        cin >> globalt;
    }


    return 0;
}