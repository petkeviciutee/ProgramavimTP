#include "class.h"
#include <random>

Person::Person() {}

Person::Person(string Vardas, string Pavarde)
{

    Vardas_ = Vardas;
    Pavarde_ = Pavarde;
}

Person::~Person() {}


Studentas::Studentas(const Studentas& OldClass) {
    Vardas_ = OldClass.Vardas_;
    Pavarde_ = OldClass.Pavarde_;
    ND = OldClass.ND;
    Egzaminas = OldClass.Egzaminas;
    Vidurkis = OldClass.Vidurkis;
    Mediana = OldClass.Mediana;
    FinalMediana = OldClass.FinalMediana;
    FinalVidurkis = OldClass.FinalVidurkis;

}


Studentas::Studentas()
{
    int Egzaminas = 0;
    double Vidurkis = 0.0;
    double Mediana = 0.0;
    double FMediana = 0.0;
    double FVidurkis = 0.0;
}

Studentas::~Studentas() {}

void Studentas::setVardas(string Vardas)
{
    Vardas_ = Vardas;
}

void Studentas::setPavarde(string Pavarde)
{
    Pavarde_ = Pavarde;
}

void Studentas::setND(vector <double> ND_)
{
    ND = ND_;
}

void Studentas::setEgzaminas(int Egzaminas_)
{
    Egzaminas = Egzaminas_;
}

int Studentas::getEgzaminas() const
{
    return Egzaminas;
}

string Studentas::getVardas() const
{
    return Vardas_;
}

string Studentas::getPavarde() const
{
    return Pavarde_;
}

double Studentas::getFinalVidurkis() const
{
    return FinalVidurkis;
}

double Studentas::getFinalMediana() const
{
    return FinalMediana;
}


Studentas& Studentas::operator=(const Studentas& s)
{
    if (&s == this)
        return *this;
    Vardas_ = s.getVardas();										
    Pavarde_ = s.getPavarde();
    FinalMediana = s.getFinalMediana();
    FinalVidurkis = s.getFinalVidurkis();
    return *this;
}

bool Studentas::operator<(const Studentas& s2)
{
    if (Vardas_ != s2.getVardas())
        return Vardas_ < s2.getVardas();
    else
        return Pavarde_ < s2.getPavarde();
}

bool Studentas::operator>(const Studentas& s2)
{
    if (Vardas_ != s2.getVardas())
        return Vardas_ > s2.getVardas();
    else
        return Pavarde_ > s2.getPavarde();
}

bool Studentas::operator==(const Studentas& s2)
{
    if (Vardas_ == s2.getVardas() &&
        Pavarde_ == s2.getPavarde() &&
        FinalMediana == s2.getFinalMediana() &&
        FinalVidurkis == s2.getFinalVidurkis())
    {
        return true;
    }
}

bool Studentas::operator!=(const Studentas& s2)
{
    if (Vardas_ != s2.getVardas() ||
        Pavarde_ != s2.getPavarde() ||
        FinalMediana != s2.getFinalMediana() ||
        FinalVidurkis != s2.getFinalVidurkis())
    {
        return false;
    }


}

void Studentas::skaiciavimas()
{

    sort(ND.begin(), ND.end());
    int position = ND.size();

    if (position % 2 == 0)
    {
        Mediana = ((ND.at(position / 2)) + (ND.at(position / 2 - 1))) / 2;
    }
    else
    {
        Mediana = ND.at(position / 2);
    }
    FinalMediana = (0.4 * Mediana) + (0.6 * Egzaminas);

    for (int j = 0; j < ND.size(); j++)
    {
        Vidurkis += ND.at(j);
    }
    Vidurkis = Vidurkis / ND.size();
    FinalVidurkis = (0.4 * Vidurkis) + (0.6 * Egzaminas);
}

void Generavimas(std::size_t i)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    std::default_random_engine eng(seed);
    std::uniform_int_distribution <int> Interval(1, 10), Amount(10, 20);

    int NumberOfStudents = i,
        AmountOfResults = Amount(eng);

    std::ofstream Write;
    Write.open("Studentai_" + std::to_string(i) + ".txt");

    for (size_t j = 1; j <= NumberOfStudents; j++)
    {
        Write << "Vardas" << j << " Pavarde" << j << " " << Interval(eng);
        std::vector <int> Results;
        std::vector <int>::iterator IT;

        for (size_t k = 0; k < AmountOfResults; k++)
            Results.push_back(Interval(eng));

        for (IT = Results.begin(); IT < Results.end(); IT++)
            Write << " " << *IT;

        Write << std::endl;
    }
    Write.close();
}

void Nuskaitymas(vector<Studentas>& Stud, string filename)
{

    std::ifstream in(filename);

    string a;
    int ndsuma = 0;
    int l;
    Studentas Data;

    string Vardas, Pavarde;
    int egzaminas;

    vector<double> ND1;


    if (!in)
    {
        cout << "Duomenu failas neegzistuoja" << endl;
        exit(0);
    }

    in >> a >> a >> a;
    while (a[0] == 'N')
    {
        ndsuma++;
        in >> a;
    }

    while (!in.eof())
    {
        in >> Vardas >> Pavarde;

        Data.setVardas(Vardas);
        Data.setPavarde(Pavarde);

        for (int i = 0; i < ndsuma; i++)
            in >> i;
        if ((l < 0 ) || (l > 10))
        {
            l = 0;
            cout << "Pazymiuose rasta klaida" << endl;
        }
        ND1.push_back(l);
    }
    in >> egzaminas;
    Data.setEgzaminas(egzaminas);

    Data.setND(ND1);
    Stud.push_back(Data);
    ND1.clear();


    in.close();

}
void Skaiciavimai(vector <Studentas>& Stud)
{


    for (int i = 0; i < Stud.size(); i++)
    {

        Stud.at(i).skaiciavimas();

    }
}

bool vargsiukai1(Studentas& Stud)
{
    return (Stud.getFinalVidurkis() > 5);
}

bool vargsiukai2(Studentas& Stud)
{
    return (Stud.getFinalMediana() > 5);
}

void GeneravimasOutputFiles(vector <Studentas>& Stud, vector <Studentas>& Vargsiukai, vector <Studentas>& Protingi, int t)
{


    if (t == 0)
    {

        std::remove_copy_if(Stud.begin(), Stud.end(), std::back_inserter(Vargsiukai), vargsiukai1);
        std::copy_if(Stud.begin(), Stud.end(), std::back_inserter(Protingi), vargsiukai1);

        Stud.erase(Stud.begin(), Stud.end());

    }

    else
    {

        std::remove_copy_if(Stud.begin(), Stud.end(), std::back_inserter(Vargsiukai), vargsiukai2);
        std::copy_if(Stud.begin(), Stud.end(), std::back_inserter(Protingi), vargsiukai2);

        Stud.erase(Stud.begin(), Stud.end());
    }

}
void Spausdinimas(vector <Studentas>& Stud, int t, string text)
{


    std::ofstream in(text);

    in << left << setw(25) << "Vardas:" << left << setw(30) << "Pavarde:";
    if (t == 1)
    {
        in << "Mediana" << endl;
    }
    else if (t == 2)
    {
        in << "Vidurkis" << " Mediana" << endl;
    }
    else
    {
        in << "Vidurkis" << endl;
    }

    for (int i = 0; i < Stud.size(); i++)
    {

        in << left << setw(25) << Stud.at(i).getVardas() << left << setw(30) << Stud.at(i).getPavarde();
        if (t != 1)
        {
            in << left << setw(9) << setprecision(3) << Stud.at(i).getFinalVidurkis();
        }

        if (t != 0)
        {
            in << left << setw(9) << setprecision(2) << Stud.at(i).getFinalMediana();
        }

        in << endl;
    }
    in.close();

}
