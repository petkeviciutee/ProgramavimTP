#include "bibltka.h"

int main()
{
    std::vector<Studentas> studentas;
    Studentas Stud;
    std::string Entry;
    std::string::size_type IlgiausiasVardas = 0,
        IlgiausiaPavarde = 0;
    
        for (std::size_t i = 100; i != 10000; i *= 10)
        {

            std::string vardas_,
                pavarde_,
                Egzaminas,
                EntryLine;

            std::ifstream ReadFile("Studentai_" + std::to_string(i) + ".txt");

            try
            {
                if (!ReadFile.good() || ReadFile.peek() == std::ifstream::traits_type::eof())
                    throw "Toks failas neegzistuoja arba yra tuscias.";
            }
            catch (const char* Message)
            {
                std::cout << Message << std::endl;
            }

            while (std::getline(ReadFile, EntryLine))
            {
                std::istringstream ReadLine(EntryLine);
                ReadLine >> vardas_ >> pavarde_ >> Egzaminas;

                DidRaid(vardas_);
                DidRaid(pavarde_);
                IlgiausiasVardas = std::max(IlgiausiasVardas, vardas_.length());
                IlgiausiaPavarde = std::max(IlgiausiaPavarde, pavarde_.length());
                Stud.setStudentas(vardas_, pavarde_, Egzaminas);

                if (ReadLine)
                {
                    Stud.EmptyND();
                    while (ReadLine >> Entry)
                    {
                        if (Skaiciai(Entry))
                        {
                            int Mark = stoi(Entry);

                            if (Mark > 0 && Mark < 11)
                                Stud.SetND(Mark);
                        }
                    }
                    studentas.push_back(Stud);
                    ReadLine.clear();
                }
                //ReadLine.end;
                ReadFile.clear();
            }
           // ReadFile.end;*/

            auto StartSorting = std::chrono::high_resolution_clock::now();

            std::vector<Studentas> vargsiukai, protingi;
            std::vector<Studentas>::iterator IT = studentas.begin();

            while (IT != studentas.end())
            {
                if ((*IT).Galutinis(Vidurkis) < 5 && (*IT).Galutinis(Mediana) < 5)
                    vargsiukai.push_back(*IT);
                else
                    protingi.push_back(*IT);
                IT++;
            }

            std::ofstream Irasymasvargsiukai;
            Irasymasvargsiukai.open("vargsiukai.txt", std::ios::app);
            Spausdinti(Irasymasvargsiukai, vargsiukai, IlgiausiasVardas, IlgiausiaPavarde);
            Irasymasvargsiukai.close();

            std::ofstream Irasymasprotingi;
            Irasymasprotingi.open("protingi.txt", std::ios::app);
            Spausdinti(Irasymasprotingi, protingi, IlgiausiasVardas, IlgiausiaPavarde);
            Irasymasprotingi.close();

            auto EndSorting = std::chrono::high_resolution_clock::now();
            std::cout << "Studentu skirstymas ir isvedimas uztruko " << std::chrono::duration_cast<std::chrono::milliseconds>(EndSorting - StartSorting).count() << " ms." << std::endl;
        
        }
    return 0;
}
