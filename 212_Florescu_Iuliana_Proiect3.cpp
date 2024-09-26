#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <exception>

using namespace std;

class IOinterface
{
public:
    virtual istream& citire(istream& in) = 0;
    virtual ostream& afisare(ostream& out) const = 0;
};
/*
template <class type>
class MaxPret
{
protected:
    type a, b;

public:
    void SetData(type x, type y)
    {
        a = x;
        b = y;
    }
    void Maxim()
    {
        if(a > b)
            cout<<"a este mai mare"<<endl;
        else
            cout<<"b este mai mare"<<endl;
    }
};
*/
class Flori : public IOinterface
{
protected:
    string nume;
    float pret;

public:

    void setNume(string nume)
    {
        this->nume = nume;
    }

    string getNume()
    {
        return this-> nume;
    }

    void setPret(float pret)
    {
        this->pret = pret;
    }

    float getPret()
    {
        return this-> pret;
    }

    Flori()
    {
        this->nume = "";
        this->pret = 0;
    }

    Flori(string nume, float pret)
    {
        this->nume = nume;
        this->pret = pret;
    }

    Flori(const Flori& f)
    {
        this->nume = f.nume;
        this->pret = f.pret;
    }

    Flori& operator= (const Flori& f)
    {
        if(this != &f)
        {
            this->nume = f.nume;
            this->pret = f.pret;
        }
        return *this;
    }

    istream& citire(istream& in)
    {
        cout<<"Care este numele?"<<endl;
        in>>this-> nume;
        cout<<"Care este pretul?"<<endl;
        try
        {
            in>>this-> pret;
            if(this-> pret < 0)
            throw invalid_argument("Pretul trebuie sa fie un numar pozitiv");
        }
        catch (const invalid_argument& e)
        {
            cout << "Eroare: " << e.what() << endl;
        }

        return in;
    }

    friend istream& operator>> (istream& in, Flori& f)
    {
        return f.citire(in);
    }

    ostream& afisare(ostream& out)const
    {
        out<<"Numele este: "<<this-> nume<<endl;
        out<<"Pretul  este: "<<this-> pret<<endl;
        return out;
    }

    friend ostream& operator << (ostream& out, const Flori& f)
    {
        return f.afisare(out);
    }

    void OrdoneazaFlori() // se ordoneaza crescator(dupa pret) cele mai vandute flori dintr-o saptamana, scrise in fisier
    {
        string linie;
        ifstream fisier;
        try
        {
            fisier.open("fisier.in");
            if(!fisier.is_open())
                throw ifstream::failure("Nu se poate deschide fisierul.");
        }
        catch (ifstream::failure& fail)
        {
            cout << "Eroare: " << fail.what() << endl;
        }
        map<float, set<string>> PretFlori;

        while (getline (fisier, linie))
        {
            float pret = stof(linie.substr(0, linie.find(":")));

            set<string> SetFlori;
            int start = linie.find(":") + 1;
            int end = linie.find(",");
            while (end != -1) {
                SetFlori.insert(linie.substr(start, end - start));
                start = end + 1;
                end = linie.find(",", start);
            }
            SetFlori.insert(linie.substr(start, end - start));

            PretFlori.insert(pair<float, set<string>>(pret, SetFlori));
        }

        fisier.close();

        ofstream fisier_out;

        try
        {
            fisier_out.open("fisier.out");

            for (map<float, set<string>>::iterator it = PretFlori.begin(); it != PretFlori.end(); ++it)
            {
                for (set<string>::iterator it2 = (*it).second.begin(); it2 != (*it).second.end(); ++it2)
                {
                    fisier_out << (*it).first << ": " << (*it2) << endl;
                }
            }

            fisier_out.close();
        }
        catch (ifstream::failure& fail)
        {
            cout << "Eroare: " << fail.what() << endl;
        }
    }

     template <typename T> void StergeFloare(list<Flori*>& ListaFlori, T numeFloare)
    {
            bool gasitFloare = false;
            list<Flori*>::iterator it;
            try
            {
                for (it = ListaFlori.begin(); it != ListaFlori.end(); ++it)
                {
                    if ((**it).getNume().compare(numeFloare) == 0)
                    {
                        ListaFlori.erase(it);
                        gasitFloare = true;
                        break;
                    }
                }
            }
            catch (const runtime_error& e)
            {
                cout << "Error: " << e.what() << endl;
            }

            if (gasitFloare == false)
            {
                cout << "Nu exista " << numeFloare << " in lista" << endl;
            }
    }

    ~Flori(){}
};

class FloriDeInterior : public Flori
{
protected:
    bool artificial;
    vector<string> TaraProvenienta;

public:
    void setArtificial(bool artificial)
    {
        this->artificial = artificial;
    }

    bool getArtificial()
    {
        return this-> artificial;
    }

    void setTaraProvenienta(vector<string>& TaraProvenienta)
    {
        this->TaraProvenienta = TaraProvenienta;
    }

    vector<string> getTaraProvenienta()
    {
        return this-> TaraProvenienta;
    }

    FloriDeInterior():Flori()
    {
        this->TaraProvenienta = {};
        this->artificial = true;
    }
    FloriDeInterior(vector<string> TaraProvenienta, bool artificial) : Flori(nume, pret)
    {
        this->TaraProvenienta = TaraProvenienta;
        this->artificial = artificial;
    }

    FloriDeInterior(const FloriDeInterior& f) : Flori(f)
    {
        this->TaraProvenienta = f.TaraProvenienta;
        this->artificial = f.artificial;
    }

    FloriDeInterior& operator= (const FloriDeInterior& f)
    {
        if(this != &f)
        {
            Flori :: operator = (f);
            this-> TaraProvenienta = f.TaraProvenienta;
            this-> artificial = f.artificial;
        }
        return *this;
    }
    istream& citire(istream& in)
    {
        Flori :: citire(in);
        cout<<"Care este numarul tarilor de provenienta?"<<endl;
        int nrTariProvenienta;
        in>> nrTariProvenienta;
        cout<<"Care sunt tarile de provenienta?"<<endl;
        for (int i=0; i < nrTariProvenienta; i++)
        {
            string tara;
            in>> tara;
            TaraProvenienta.push_back(tara);
        }
        cout<<"Este artificiala?"<<endl;
        in>>this-> artificial;
        return in;
    }
    ostream& afisare(ostream& out) const
    {
        Flori::afisare(out);
        try
        {
            out<<"Tarile de provenienta sunt: "<<endl;
            for(int i = 0; i<this-> TaraProvenienta.size(); i++)
                out<<this-> TaraProvenienta[i]<< endl;
        }
         catch (const out_of_range& e)
        {
            cout << "Eroare: " << e.what() << "\n";
        }

        out<<"Este artificiala:1-da,0-nu: "<<this-> artificial<<endl;
        return out;
    }

    ~FloriDeInterior(){}
};

class FloriNaturale : public FloriDeInterior
{
protected:
    string TipSol;
    int TempMaxima;

public:
    void setTipSol(string TipSol)
    {
        this->TipSol = TipSol;
    }

    void setTempMaxima(int TempMaxima)
    {
        this->TempMaxima = TempMaxima;
    }
    string getTipSol()
    {
        return this->TipSol;
    }

    int getTempMaxima()
    {
        return this->TempMaxima;
    }

    FloriNaturale() : FloriDeInterior()
    {
        this->TipSol = "";
        this->TempMaxima = 0;
    }

    FloriNaturale(string TipSol, int TempMaxima) : FloriDeInterior(TaraProvenienta, artificial)
    {
        this->TipSol = TipSol;
        this->TempMaxima = TempMaxima;
    }

    FloriNaturale(const FloriNaturale& f) : FloriDeInterior(f)
    {
        this->TipSol = f.TipSol;
        this->TempMaxima = f.TempMaxima;
    }

    FloriNaturale& operator = (const FloriNaturale& f)
    {
        if(this != &f)
        {
            FloriDeInterior :: operator = (f);
            this-> TipSol = f.TipSol;
            this-> TempMaxima = f.TempMaxima;
        }
        return *this;
    }

    istream& citire(istream& in)
    {
        FloriDeInterior :: citire(in);
        cout<<"Care este tipul de sol?"<<endl;
        in>>this-> TipSol;
        cout<<"Care este temperatura maxima suportata?"<<endl;
        try
        {
            in>>this-> TempMaxima;
            if(this-> TempMaxima < 0)
                throw invalid_argument("Temperatura trebuie sa fie un numar pozitiv");
        }
        catch (const invalid_argument& e)
        {
            cout << "Eroare: " << e.what() << endl;
        }


        return in;
    }

    ostream& afisare(ostream& out) const
    {
        FloriDeInterior :: afisare(out);
        out<<"Tipul de sol este: "<<this-> TipSol<<endl;
        out<<"Temperatura este: "<<this-> TempMaxima<<endl;
        return out;
    }

    template <typename T> void CautaFloare(list<Flori*> ListaFlori, T Temperatura)
    {
        list<Flori*>::iterator it;
        for (it = ListaFlori.begin(); it != ListaFlori.end(); ++it)
        {
            if ((static_cast<FloriNaturale&>(**it)).getTempMaxima() > Temperatura)
            {
                cout<< (**it).getNume() << " " << (static_cast<FloriNaturale&>(**it)).getTempMaxima()<<endl;
            }
        }
    }

      ~FloriNaturale(){}
};

class FloriDeExterior : public Flori
{
private:
    string TipMediu;

public:
    void setTipMediu(string TipMediu)
    {
        this->TipMediu = TipMediu;
    }
    string getTipMediu()
    {
        return this->TipMediu;
    }
    FloriDeExterior() : Flori()
    {
        this->TipMediu = "";
    }
    FloriDeExterior(string nume, float pret, string TipMediu) : Flori(nume, pret)
    {
        this->TipMediu = TipMediu;
    }
    FloriDeExterior(const FloriDeExterior& f) : Flori(f)
    {
        this->TipMediu = f.TipMediu;
    }
    FloriDeExterior& operator= (const FloriDeExterior& f)
    {
        if(this != &f)
        {
            Flori :: operator = (f);
            this->TipMediu = f.TipMediu;
        }
        return *this;
    }
    istream& citire(istream& in)
    {
        Flori :: citire(in);
        cout<<"Care este tipul de mediu?"<<endl;
        in>>this-> TipMediu;
        return in;
    }
    ostream& afisare(ostream& out) const
    {
        Flori :: afisare(out);
        out<<"Tipul de mediu este: "<<this-> TipMediu<<endl;
        return out;
    }

    void CautaFloareDupaMediu(list<Flori*> ListaFlori, string TipMediu)
    {
        list<Flori*>::iterator it;
        try
        {
            for (it = ListaFlori.begin(); it != ListaFlori.end(); ++it)
            {
                if ((dynamic_cast<FloriDeExterior&>(**it)).getTipMediu().compare(TipMediu) == 0)
                {
                    cout<<(**it).getNume()<<endl;
                }
            }
        }
        catch (bad_cast fail) {
        cout<<"Eroare: "<<fail.what() <<endl;
        }

    }

    ~FloriDeExterior(){}
};

class Singletone
{
private:
    static Singletone *obiect;

public:
    static Singletone* getInstance(){
        if(!obiect)
            obiect = new Singletone();

        return obiect;
    }


    void Meniu()
    {
        cout<< "1- Adauga o floare de interior naturala\n"
            << "2- Adauga o floare de exterior\n"
            << "3- Afiseaza\n"
            << "4- Sorteaza crescator dupa pret cele mai vandute flori\n"
            << "5- Template1\n"
            << "6- Template2\n"
            << "7- Cauta floarea dupa tipul de mediu\n"
          //  << "8- Clasa template\n"
            << "8- Stop"<<endl;
        list<Flori*> ListaFlori;
        while(true)
        {
            int s;
            cin>>s;

            switch (s)
            {
                case 1:
                    {
                        cout <<"** Adauga o floare de interior naturala :**" << endl;
                        FloriNaturale f;
                        cin>>f;
                        ListaFlori.push_back(new FloriNaturale(f));
                        break;
                    }
                case 2:
                    {
                        cout <<"** Adauga o floare de exterior :**" << endl;
                        FloriDeExterior f;
                        cin>>f;
                        ListaFlori.push_back(new FloriDeExterior(f));
                        break;
                    }
                case 3:
                    {
                         cout<<"** Afiseaza: **"<<endl;
                         list<Flori*>::iterator it;
                         for (it = ListaFlori.begin(); it != ListaFlori.end(); ++it)
                            cout << **it << endl;
                         break;
                    }
                case 4:
                    {
                        cout << "** Sorteaza crescator dupa pret cele mai vandute flori **\n";
                        Flori f;
                        f.OrdoneazaFlori();
                        cout<<"** A afisat in fisier **\n";
                        break;
                    }
                case 5:
                    {
                        int temperaturaInt;
                        cout<<"** Introdu temperatura (int) **\n";
                        cin>>temperaturaInt;
                        cout<<"** Cauta florile care rezista la temperaturi mai mari de **"<<temperaturaInt<<endl;
                        FloriNaturale f;
                        f.CautaFloare(ListaFlori, temperaturaInt);

                        float temperaturaFloat;
                        cout<<"** Introdu temperatura (float)** \n";
                        cin>>temperaturaFloat;
                        cout<<"** Cauta florile care rezista la temperaturi mai mari de **"<<temperaturaFloat<<endl;
                        FloriNaturale fl;
                        fl.CautaFloare(ListaFlori, temperaturaFloat);

                        break;
                    }

                case 6:
                    {
                        string NumeFloareString;
                        cout<<"** Introdu numele (string) **\n";
                        cin>>NumeFloareString;
                        cout<<"** S-a sters floarea  **"<<NumeFloareString<<endl;
                        Flori f;
                        f.StergeFloare(ListaFlori, NumeFloareString);

                        char* NumeFloareChar = new char[100];
                        cout<<"** Introdu numele (char*) **\n";
                        cin>>NumeFloareChar;
                        cout<<"** S-a sters floarea **"<<NumeFloareChar<<endl;
                        Flori fl;
                        fl.StergeFloare(ListaFlori, NumeFloareChar);
                        delete[] NumeFloareChar;
                        break;
                    }

             case 7:
                    {
                        string Mediu;
                        cout<<"**Introdu tipul de mediu**\n";
                        cin>>Mediu;
                        cout<<"**Cauta florile care rezista la acest tip de mediu\n"<<Mediu<<endl;
                        FloriDeExterior f;
                        f.CautaFloareDupaMediu(ListaFlori, Mediu);
                        break;
                    }
             /*
             case 8:
                {
                    MaxPret<int> obj1;
                    obj1.SetData(60, 20);

                    MaxPret<float> obj2;
                    obj2.SetData(34.6, 78.9);

                    obj1.Maxim();
                    obj2.Maxim();

                    break;
                }
            */
            case 8:
                {
                    cout<<"** Stop. **";
                    return;
                }
            }
        }
    }
};

Singletone* Singletone :: obiect = 0;

int main()
{
    Singletone *s = s-> getInstance();
    s-> Meniu();


    return 0;
}
