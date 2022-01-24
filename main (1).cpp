#include "class.h"

int main()
{
    std::chrono::steady_clock sc;		
    string EntryChoice;
    int Entry;
    int t, p;				
    vector <Studentas> Stud, Vargsiukai, Protingi;
    
  int a;
 cout << "Jeigu norite naudoti jau sugeneruotus failus spauskite 1, bet jei norite generuoti is naujo spauskite 0\n";
  label:
cin >> a;
    for (int i = 0; i < 1; i++)
     {
        if (a == 0)
                {

     cout << "\nKaip norite apskaiciuoti studentu galutini pazymi?\nSpauskite:"
        "\n1. Jei norite, jog butu naudojamas studento namu darbu rezultatu vidurkis"
       "\n2. Jei norite, jog butu naudojama mediana. " << endl;
                    int FMChoice;
                    string Entry2;

                    while (cin >> Entry2)
                    {
                        if (Entry2 == "1")
                        {
                            FMChoice = 0;
                            break;
                        }
                        else if (Entry2 == "2")
                        {
                            FMChoice = 1;
                            break;
                        }
                        else
                        {
                            cin.clear();
                            cin.ignore(256, '\n');
                            cout << "Klaida,toks pasirinkimas negalimas - veskite dar karta" << endl;
                            cin >> EntryChoice;
                            i--;
                        }

                    }

                    string filename;
                    for (size_t i = 100; i != 10000; i *= 10)
                    {
                        Stud.clear();
                        auto Start = sc.now();
                        Generavimas(i);
                        auto End = sc.now();
                        cout << i << " failo generavimas uztruko " << std::chrono::duration_cast<std::chrono::milliseconds>(End - Start).count() << " ms." << std::endl;
                    }


                    for (int i = 100; i < 10000; i *= 10)
                    {

                        filename = "Studentai_" + std::to_string(i) + ".txt";
                        auto StartSorting = sc.now();
                        Nuskaitymas(Stud, filename);

                        Skaiciavimai(Stud);
                        sort(Stud.begin(), Stud.end());

                        GeneravimasOutputFiles(Stud, Vargsiukai, Protingi, t);
                        Spausdinimas(Vargsiukai, t, "vargsiukai_" + std::to_string(i) + ".txt");
                        Spausdinimas(Protingi, t, "Protingi_" + std::to_string(i) + ".txt");

                        Vargsiukai.clear();
                        Stud.clear();

                        auto EndSorting = sc.now();


                        cout << i << " skirstymas ir spausdinimas uztruko" << std::chrono::duration_cast<std::chrono::milliseconds>(EndSorting - StartSorting).count() << " ms." << std::endl;

                    }

                }

                else
                    goto label;
            }
        

 return 0;
}