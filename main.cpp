#include <iostream>
#include <string.h>

using namespace std;

class Angajat;
class part_time;

class Data
{
    int zi;
    char* luna;
    int an;
public:
    Data();
    Data(int);
    Data(int, char*);
    Data(int, char*,int);
    Data(Data &);                       //constructor de copiere
    ~Data(){cout<<" ";}                 //destructor
    Data& operator =( const Data&);     //supraincarcarea operatorului = doar ca functie membra!!!
    friend istream& operator >>(istream& in, Data& d);
    friend ostream& operator <<(ostream& out, Data& d);
    friend istream& operator >>(istream& in,Angajat& a);//supraincarcare op citire Angajat
    friend ostream& operator <<(ostream &out, Angajat& a);
    friend class Angajat;
    friend class part_time;
    friend class permanent;
};

class Angajat{
protected:
    static int nr;
    char* nume;
    char* prenume;
    float salariu;
    float suma_standard;
    Data data_angajarii;

public:
    Angajat();
    Angajat(char *a, char *b, float s, float ss, Data d):data_angajarii(d.zi,d.luna,d.an)
    {
        nr++;
        nume=new char[20]; prenume=new char[20];
        strcpy(nume,a); strcpy(prenume,b); salariu=s; suma_standard=ss;
    };
    Angajat(char *a, char *b, float s, float ss, int d, char *e, int f );
    Angajat(Angajat &);
    ~Angajat();
    Angajat& operator=( const Angajat&);
    friend istream& operator>>(istream& in, Angajat &a);
    friend ostream& operator<<(ostream &out, Angajat &a);
    virtual void citire(){};
    virtual void afisare(){};
    virtual float prima(){ return 0;};
    static int get_nr(){return nr;}

};

int Angajat::nr;

class part_time:public Angajat
{
    int nr_ore_zi;
    Data final_contract;
public:
    part_time():Angajat(){nr_ore_zi=0; Data d; final_contract=d;};
    part_time(int n):Angajat(){ nr_ore_zi=n; };
    part_time(int n,int a,char *b,int c):Angajat(){ nr_ore_zi=n; final_contract.zi=a; final_contract.luna=new char[10];
                                  strcpy(final_contract.luna,b); final_contract.an=c; };
    part_time(part_time &);
    ~part_time(){ cout<<" "; }
    friend istream& operator>>(istream &in, part_time &p);
    friend ostream& operator<<(ostream &o, part_time &p);
    part_time& operator= (const part_time&);
    void citire();
    void afisare();
    float prima();
};

class permanent:public Angajat
{
    int nr_minori_intretinere;
public:
    permanent():Angajat(){nr_minori_intretinere=0;}
    permanent(int n):Angajat(){ nr_minori_intretinere=n; };
    permanent(permanent &);
    ~permanent(){ cout<<" ";}
    permanent& operator=(const permanent &);
    friend istream& operator>>(istream &in, permanent &p);
    friend ostream& operator<<(ostream &out, permanent &p);
    void citire();
    void afisare();
    float prima();
};

Data::Data()
{
    zi=0;
    luna=new char[10]; strcpy(luna,"no month");
    an=0;
}

Data::Data(int a)
{
    zi=a;
    luna=new char[10]; strcpy(luna,"no month");
    an=0;
}

Data::Data(int a,char *b)
{
    zi=a;
    luna=new char[10]; strcpy(luna,b);
    an=0;
}

Data::Data(int a, char* b, int c)
{
    zi=a;
    luna=b;
    an=c;
}

Data::Data( Data &a)
{
    zi=a.zi;  luna=a.luna;   an=a.an;
}

Data& Data::operator=(const Data& a)
{
    if(this != &a)
    {
        this->zi=a.zi;
        luna=new char[20];
        strcpy(luna,a.luna);
        an=a.an;
    }
    return (*this);
}

istream& operator>>(istream &in,Data &a)
{
    cout<<"ziua/ luna/ anul: ";
    a.luna=new char[10];
    in>>a.zi>>a.luna>>a.an;
    return in;
}

ostream& operator << (ostream &out,Data &d)
{
    out<<d.zi<<" "<<d.luna<<" "<<d.an<<endl;
    return out;
}

Angajat::Angajat()
{
    nr++;
    nume=new char[20]; prenume=new char[20]; data_angajarii.luna=new char[10];
    strcpy(nume,"No name");
    strcpy(prenume,"No name");
    salariu=0;
    suma_standard=0;
    data_angajarii.zi=0;
    strcpy(data_angajarii.luna,"no month");
    data_angajarii.an=0;
}

Angajat::Angajat(char *a, char *b, float s,float ss, int d, char *e, int f)
{
    nr++;
    nume=new char[20]; prenume=new char[20]; data_angajarii.luna=new char[10];
    strcpy(nume,a);
    strcpy(prenume,b);
    salariu=s;
    suma_standard=ss;
    data_angajarii.zi=d;
    data_angajarii.an=f;
    strcpy(data_angajarii.luna,e);
}

Angajat::Angajat(Angajat &a)
{
    nr++;
    nume=new char[20]; prenume=new char[20];
    strcpy(nume,a.nume);
    strcpy(prenume,a.prenume);
    salariu=a.salariu;
    suma_standard=a.suma_standard;
    data_angajarii=a.data_angajarii;
}

Angajat::~Angajat()
{ cout<<"D-Ang ";   }

istream& operator>>(istream &in, Angajat &a)
{
    cout<<"Introduceti numele prenumele salariul si suma_standard_stabilita_firma: "<<endl;
    in>>a.nume>>a.prenume>>a.salariu>>a.suma_standard;
    cout<<"Angajat in ";
    in>>a.data_angajarii;
    return in;
}

ostream& operator<<(ostream &out, Angajat &a)
{
    out<<a.nume<<" "<<a.prenume<<" "<<a.salariu<<" lei "<<a.suma_standard<<" lei Angajat in "<<a.data_angajarii;
    return out;
}

Angajat& Angajat::operator= (const Angajat &a)
{
    if(this != &a)
    {
        nume=new char[20]; prenume=new char[20];
        strcpy(nume,a.nume);
        strcpy(prenume,a.prenume);
        salariu=a.salariu;
        suma_standard=a.suma_standard;
        data_angajarii=a.data_angajarii;
    }
    return *this;
}

part_time::part_time(part_time &a):Angajat(a)
{
    nr_ore_zi=a.nr_ore_zi;
    final_contract=a.final_contract;
}

part_time& part_time:: operator= (const part_time& x)
{
    if(this!=&x)
    {
        this->Angajat::operator=(x);
        nr_ore_zi=x.nr_ore_zi;
        final_contract=x.final_contract;
    }
}

istream& operator >> (istream &in, part_time &p)
{
    in>>(Angajat &)p;
    cout<<"Introduceti nr_ore_zi:";
    in>>p.nr_ore_zi;
    cout<<"Final contract in ";
    in>>p.final_contract;
    return in;
}

ostream& operator<<(ostream& out, part_time &p)
{
    out<<(Angajat &)p;
    out<<p.nr_ore_zi<<"ore zi";
    cout<<"Final contract in ";
    out<<p.final_contract;
    return out;
}

void part_time::citire()
{
    cout<<"Introduceti numele prenumele salariul si suma_standard_stabilita_firma: ";
    cin>>nume>>prenume>>salariu>>suma_standard;
    cout<<"Angajat in ";
    cin>>data_angajarii;
    cout<<"Introduceti nr_ore_zi: ";
    cin>>nr_ore_zi; cout<<"Final contract in "; cin>>final_contract;
}

void part_time::afisare()
{
  cout<<nume<<" "<<prenume<<" "<<salariu<<" lei "<<suma_standard<<" lei Angajat in "<<data_angajarii;
  cout<<"Nr ore/zi: "<<nr_ore_zi<<". Final contract in "<<final_contract;
}

float part_time::prima()
{
    float p;
    if(strcmp(final_contract.luna,"aprilie")==0)
        p=0.75*suma_standard;
    else
        p=suma_standard;
    return p;
}

permanent::permanent(permanent &a):Angajat(a)
{
    nr_minori_intretinere=a.nr_minori_intretinere;
}

permanent& permanent::operator=(const permanent &p)
{
    if(this!= &p)
    {
        this->Angajat::operator=(p);
        nr_minori_intretinere=p.nr_minori_intretinere;
    }
}

istream& operator>>(istream &in, permanent &p)
{
    cout<<"Introduceti nr_minori_intretinere:";
    in>>p.nr_minori_intretinere;
    in>>(Angajat &)p;
    return in;
}

ostream& operator<<(ostream& out, permanent &p)
{
    out<<(Angajat &)p;
    out<<"Numar minori:"<<p.nr_minori_intretinere;
    return out;
}

void permanent::citire()
{
    cout<<"Introduceti numele prenumele salariul si suma_standard_stabilita_firma: ";
    cin>>nume>>prenume>>salariu>>suma_standard;
    cout<<"Angajat in ";
    cin>>data_angajarii;
    cout<<"Introduceti nr_minori_intretinere: ";
    cin>>nr_minori_intretinere;
}

void permanent::afisare()
{
    cout<<nume<<" "<<prenume<<" "<<salariu<<" lei "<<suma_standard<<" lei Angajat in "<<data_angajarii;
    cout<<"Nr minori: "<<nr_minori_intretinere<<endl;
}

float permanent::prima()
{
    float p;
    if(nr_minori_intretinere!=0)
        p=nr_minori_intretinere*suma_standard*(2018-data_angajarii.an)/100;
    else
        p=(2018-data_angajarii.an)*suma_standard/100;
    return p;
}

int main()
{
    int option,n;

    cout<<"Introduceti n:";
    cin>>n;
    Angajat *a[n];
    for(int i = 0; i < n; i++)
    {
        cout<<endl;
        cout<<"Introduceti 1 pentru a adauga angajat permanent"<<endl;
        cout<<"Introduceti 2 pentru a adauga angajat part-time"<<endl;
        cout<<"Introduceti 3 pentru EXIT"<<endl<<endl;
        cin>>option;

        switch(option)
        {

            case 1:{
                        a[i]=new permanent();
                        cin>>*(permanent*)a[i];
                        break;
                    }
            case 2:{
                        a[i]=new part_time();
                        cin>>*(part_time*)a[i];
                        break;
                    }

            case 3:{
                        return 0;
                    }

        }

    }
    for(int i=0; i < n; i++)
    {
        cout<<endl;
        cout<<Angajat::get_nr;
        a[i]->afisare();
        cout<<"Prima: "<<a[i]->prima();
        cout<<endl;
    }



    return 0;
}
