#include <random>

void histogrammacro()
{
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0, 3);
    TH2F *H2 = new TH2F("H2", "2d Histogram", 50, -10, 10, 50, -10, 10);
    for (int i = 0; i < 10000; ++i) 
    {
        H2->Fill(distribution(generator), distribution(generator));
    };
    H2->Draw("Lego2");
    

};