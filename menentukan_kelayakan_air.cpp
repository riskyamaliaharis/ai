#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

using namespace std;

string status;
float temp, rule[15], kondisiLayak[15], kondisiTakLayak[15];
inti,k,r,p;
float m, n;


//*Fungsi Keanggotaan pH
float fasam(float phinput){
    if (phinput<=3)
        return 1;
    else if(phinput>=7)
        return 0;
    else if ((phinput>3)&&(phinput<7))
        return (7-phinput)/4;
}

float fnetral(float phinput){
if(phinput<=3 || phinput>=11)
        return 0;
    else if (phinput == 7)
        return 1;
    else if ((phinput< 7) && (phinput> 3))
        return (phinput-3)/(7-3);
    else if ((phinput< 11) && (phinput> 7))
        return (11-phinput)/(11-7);
}

float fbasa(float phinput){
    if (phinput<=7)
        return 0;
    else if ((phinput>=11) && (phinput<=14))
        return 1;
    else if ((phinput>7)&&(phinput<11))
        return (phinput-7)/(11-7);
}

void fphtampil(float phinput){
    cout<<"Asam  : "<<fasam(phinput)<<endl;
    cout<<"Netral : "<<fnetral(phinput)<<endl;
    cout<<"Basa  : "<<fbasa(phinput)<<endl;
}




//*Fungsi Keanggotaan Suhu
float ftempdingin(float tempinput){
    if (tempinput<=20)
        return 1;
    else if(tempinput>=25)
        return 0;
    else
        return (25-tempinput)/(25-20);
}

float ftempsejuk(float tempinput){
    if (tempinput==25)
        return 1;
    else if ((tempinput<=25) && (tempinput>=20))
        return (tempinput-20)/5;
    else if ((tempinput>25)&& (tempinput<30))
        return (30-tempinput)/(30-25);
    else if(tempinput<=20 || tempinput>=30)
        return 0;
}

float ftempnormal(float tempinput){
if(tempinput<=25 || tempinput>=35)
        return 0;
    else if (tempinput==30)
        return 1;
    else if ((tempinput<30) && (tempinput>25))
        return (tempinput-25)/(30-25);
    else if ((tempinput>30) && (tempinput<35))
        return (35-tempinput)/(35-30);
}


float ftemphangat(float tempinput){
if(tempinput<=30 || tempinput>=40)
        return 0;
    else if (tempinput==35)
        return 1;
    else if ((tempinput<35) && (tempinput>30))
        return (tempinput-30)/(35-30);
    else if ((tempinput<40) && (tempinput>35))
        return (40-tempinput)/(40-35);
}

float ftemppanas(float tempinput){
    if (tempinput<35)
        return 0;
    else if (tempinput>40)
        return 1;
    else
        return (tempinput-35)/(40-35);
}

void ftemptampil(float tempinput){
    cout<<"Dingin  : "<<ftempdingin(tempinput)<<endl;
    cout<<"Sejuk  : "<<ftempsejuk(tempinput)<<endl;
    cout<<"Normal   : "<<ftempnormal(tempinput)<<endl;
    cout<<"Hangat  : "<<ftemphangat(tempinput)<<endl;
    cout<<"Panas  : "<<ftemppanas(tempinput)<<endl;
}


//Inferensi
float inferensi_layak(float max1){
    max1=0;
    for (k=1;k<=4;k++){
        if (k==1) max1=kondisiLayak[1];
        else if (kondisiLayak[k]>max1) max1=kondisiLayak[k];
    }
    cout<<"\nLayakMinum = " <<max1;
    m=max1;
    return m;
}

float inferensi_tidak_layak(float max2){
    max2=0;
    for (k=1;k<=11;k++){
        if (k==1) max2=kondisiTakLayak[1];
        else if (kondisiTakLayak[k]>max2) max2=kondisiTakLayak[k];
    }

    cout<<"\nTidakLayakMinum = " <<max2;
    n=max2;
    return n;
}

float defuzzifikasi(int sample, float max1, float max2){
    float penyebut, pembilang = 0;
	float tsample;
	float tsampleM;
	float sumsampleM, sumsampleN, sumsampleO[r];
	float o[r], tsampleO[r], penyebut3;
	float delta;
	float y;
	string kesimpulan;
    delta = 100/sample;

    cout<<"Range Tiap Sample Point = "<<delta;
    tsample += delta;

    if(m < n) {
        for(p = 1; p <= sample; p++){
            if(tsample<= 50){
                pembilang += tsample * m;
                sumsampleM += 1;
            } 
            else if(tsample>= 70) {
                pembilang += tsample * n;
                sumsampleN += 1;
            } 
            else if(( tsample> 50 ) && (tsample<70)){
                tsampleO[r] = tsample;
                o[r] = (70 - tsampleO[r])/20;
                penyebut3+=o[r]*1;
                sumsampleO[r] += 1;
                r += 1;
        }
        tsample += delta;
    }


    cout<<endl;
    penyebut=(sumsampleN*n)+(sumsampleM*m)+(penyebut3);
    cout<< "\nNumerator = " <<pembilang<<endl;
    y=(pembilang/penyebut);
    cout<<endl;
    cout<<"Nilai y = "<<y<<"%";
    cout<<endl;
    
    if (y>=60) cout<<"Kesimpulan = Air inilayakuntukdiminum";
    else cout<<"Kesimpulan = Air initidaklayakuntukdiminum";

        } else {

    for(p =1; p <= sample; p++) {
        if(tsample<= 50) {
            pembilang += tsample * n;
            sumsampleN += 1;
        } 
        else if (tsample>= 70) {
            pembilang += tsample * m;
            sumsampleM += 1;
        } 
        else if(( tsample> 50 ) && (tsample< 70)){
            tsampleO[r] = tsample;
            o[r] = (tsampleO[r] - 50)/20;
            pembilang += tsampleO[r] * o[r];
            penyebut3+=o[r]*1;
            sumsampleO[r] += 1;
            r += 1;
        }
        tsample +=delta;
    }

    cout<<endl;
    penyebut=(sumsampleN*n)+(sumsampleM*m)+(penyebut3);
    cout<< "\nNumerator  = " <<pembilang<<endl;
    y=(pembilang/penyebut);
    cout<<endl;
    cout<<"Nilai y = "<<y<<"%";
    cout<<endl;

        if (y>=60) cout<<"Kesimpulan = Air inilayakuntukdiminum";
        else cout<<"Kesimpulan = Air initidaklayakuntukdiminum";
    }
    return sample;
}


int main ()
{
    float max_l, max_tl;
    char answer;
    float ph = 0;
intsampel;
system("color E5");
    do
    {
cout<<"\n________________";
cout<<endl;
cout<<"\n==========FUZZIFIKASI==========";
cout<<endl;
cout<<"BesarpH(1-14)="; cin>>ph;

cout<<"BesarpH :"<<ph<<endl;
cout<<"Kategori :"<<endl;

fphtampil(ph);

cout<<endl;

cout<<"Besar Temperature =";cin>>temp;

cout<<"BesarTemperature :"<<temp<<endl;
cout<<"Kategori :"<<endl;

ftemptampil(temp);
cout<<endl;
cout<<"Press Any Key to Continue";
getch();
system("cls");
cout<<"\n________________";
cout<<endl;
cout<<"\n==========INFERENSI==========";
cout<<endl;
fasam(ph);
fnetral(ph);
fbasa(ph);
ftempdingin(temp);
ftempsejuk(temp);
ftempnormal(temp);
ftemphangat(temp);
ftemppanas(temp);

        if ((fasam(ph)!=0) && (ftempdingin(temp)!=0))
        {
i=1;
            if (fasam(ph)<ftempdingin(temp))
            {
             rule[i]=fasam(ph);
            }
            else rule[i]=ftempdingin(temp);
            status="layakminum";
cout<<"Rule 1 =" <<rule[1]<< " (" <<status<< ")";
kondisiLayak[1]=rule[1];
cout<<endl;
        }


        if ((fasam(ph)!=0) && (ftempsejuk(temp)!=0))
        {
i=2;
            if (fasam(ph)<ftempsejuk(temp))
            {
                rule[i]=fasam(ph);}
            else rule[i]=ftempsejuk(temp);
            status="tidaklayakminum";
cout<<"Rule 2 =" <<rule[2]<< " (" <<status<< ")";
kondisiTakLayak[1]=rule[2];
cout<<endl;
        }


        if ((fasam(ph)!=0) && (ftempnormal(temp)!=0))
        {
i=3;
            if (fasam(ph)<ftempnormal(temp))
            {
                rule[i]=fasam(ph);}
            else rule[i]=ftempnormal(temp);
            status="tidaklayakminum";
cout<<"Rule 3 =" <<rule[3]<< " (" <<status<< ")";
kondisiTakLayak[2]=rule[3];
cout<<endl;
        }


        if ((fasam(ph)!=0) && (ftemphangat(temp)!=0))
        {
i=4;
            if (fasam(ph)<ftemphangat(temp))
            {
                rule[i]=fasam(ph);}
            else rule[i]=ftemphangat(temp);
            status="tidaklayakminum";
cout<<"Rule 4 =" <<rule[4]<< " (" <<status<< ")";
kondisiTakLayak[3]=rule[4];
cout<<endl;
        }

        if ((fasam(ph)!=0) && (ftemppanas(temp)!=0))
        {
i=5;
            if (fasam(ph)<ftemppanas(temp))
            {
                rule[i]=fasam(ph);}
            else rule[i]=ftemppanas(temp);
            status="tidaklayakminum";
cout<<"Rule 5 =" <<rule[5]<< " (" <<status<< ")";
kondisiTakLayak[4]=rule[5];
cout<<endl;
        }


        if ((fnetral(ph)!=0) && (ftempdingin(temp)!=0))
        {
i=6;
            if (fnetral(ph)<ftempdingin(temp))
            {
                rule[i]=fnetral(ph);}
            else rule[i]=ftempdingin(temp);
            status="layakminum";
cout<<"Rule 6 =" <<rule[6]<< " (" <<status<< ")";
kondisiLayak[5]=rule[6];
cout<<endl;
        }


        if ((fnetral(ph)!=0) && (ftempsejuk(temp)!=0))
        {
i=7;
            if (fnetral(ph)<ftempsejuk(temp))
            {
                rule[i]=fnetral(ph);}
            else rule[i]=ftempsejuk(temp);
            status="layakminum";
cout<<"Rule 7 =" <<rule[7]<< " (" <<status<< ")";
kondisiLayak[6]=rule[7];
cout<<endl;
        }


        if ((fnetral(ph)!=0) && (ftempnormal(temp)!=0))
        {
i=8;
            if (fnetral(ph)<ftempnormal(temp))
            {
                rule[i]=fnetral(ph);}
            else rule[i]=ftempnormal(temp);
            status="layakminum";
cout<<"Rule 8 =" <<rule[8]<< " (" <<status<< ")";
kondisiLayak[2]=rule[8];
cout<<endl;
        }


        if ((fnetral(ph)!=0) && (ftemphangat(temp)!=0))
        {
i=9;
            if (fnetral(ph)<ftemphangat(temp))
            {
                rule[i]=fnetral(ph);}
            else rule[i]=ftemphangat(temp);
            status="tidaklayakminum";
cout<<"Rule 9 =" <<rule[9]<< " (" <<status<< ")";
kondisiTakLayak[7]=rule[9];
cout<<endl;
        }


        if ((fnetral(ph)!=0) && (ftemppanas(temp)!=0))
        {
i=10;
            if (fnetral(ph)<ftemppanas(temp))
            {
                rule[i]=fnetral(ph);}
            else rule[i]=ftemppanas(temp);
            status="tidaklayakminum";
cout<<"Rule 10 =" <<rule[10]<< " (" <<status<< ")";
kondisiTakLayak[8]=rule[10];
cout<<endl;
        }


        if ((fbasa(ph)!=0) && (ftempdingin(temp)!=0))
        {
i=11;
            if (fbasa(ph)<ftempdingin(temp))
            {
                rule[i]=fbasa(ph);}
            else rule[i]=ftempdingin(temp);
            status="layakminum";
cout<<"Rule 11 =" <<rule[11]<< " (" <<status<< ")";
kondisiLayak[3]=rule[11];
cout<<endl;
        }


        if ((fbasa(ph)!=0) && (ftempsejuk(temp)!=0))
        {
i=12;
            if (fbasa(ph)<ftempsejuk(temp))
            {
                rule[i]=fbasa(ph);}
            else rule[i]=ftempsejuk(temp);
            status="layakminum";
cout<<"Rule 12 =" <<rule[12]<< " (" <<status<< ")";
kondisiLayak[4]=rule[12];
cout<<endl;
        }


        if ((fbasa(ph)!=0) && (ftempnormal(temp)!=0))
        {
i=13;
            if (fbasa(ph)<ftempnormal(temp))
            {
                rule[i]=fbasa(ph);}
            else rule[i]=ftempnormal(temp);
            status="tidaklayakminum";
cout<<"Rule 13 =" <<rule[13]<< " (" <<status<< ")";
kondisiTakLayak[9]=rule[13];
cout<<endl;
        }


        if ((fbasa(ph)!=0) && (ftemphangat(temp)!=0))
        {
i=14;
            if (fbasa(ph)<ftemphangat(temp))
            {
                rule[i]=fbasa(ph);}
            else rule[i]=ftemphangat(temp);
            status="tidaklayakminum";
cout<<"Rule 14 =" <<rule[14]<< " (" <<status<< ")";
kondisiTakLayak[10]=rule[14];
cout<<endl;
        }


        if ((fbasa(ph)!=0) && (ftemppanas(temp)!=0))
        {
i=15;
            if (fbasa(ph)<ftemppanas(temp))
            {
                rule[i]=fbasa(ph);}
            else rule[i]=ftemppanas(temp);
            status="tidaklayakminum";
cout<<"Rule 15 =" <<rule[15]<< " (" <<status<< ")";
kondisiTakLayak[11]=rule[15];
cout<<endl;
        }

        else rule[i]=0;

cout<<endl;

inferensi_layak(max_l);

cout<<endl;

inferensi_tidak_layak(max_tl);

cout<<endl;
cout<<endl;
cout<<"Press Any Key to Continue";
getch();
system("cls");
cout<<"\n________________";
cout<<endl;
cout<<"\n==========DEFUZZIFIKASI==========";

cout<<"\nJumlah Sample Point = ";cin>>sampel;
cout<<endl;

defuzzifikasi(sampel, max_l, max_tl);

cout<<endl;
cout<<"Press Any Key to Continue";
getch();
system("cls");
cout<<"\n________________";
cout<<endl;
cout<<"\n==========DANKE==========";
cout<<endl;
cout<<"Tekan Y/y kalomaungulang = ";
cin>>answer;

    }

while(answer=='Y' || answer=='y');
}
