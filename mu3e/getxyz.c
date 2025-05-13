#include <iostream>
#include <map>
#include <bitset>
#include <math.h>

std::vector<Double_t> GetTileXYZ(UInt_t id)
{
    static std::map<UInt_t, std::vector<Double_t>> coordinates;
    if (coordinates.size()==0)
    {
        TFile *file = TFile::Open("./test.sim.root");
        TTree *tiles_tree = file->Get<TTree>("alignment/tiles");
        Double_t x;
        Double_t y;
        Double_t z;
        UInt_t id;
        tiles_tree->SetBranchAddress("posx", &x);
        tiles_tree->SetBranchAddress("posy", &y);
        tiles_tree->SetBranchAddress("posz", &z);
        tiles_tree->SetBranchAddress("id", &id);
        for (int i = 0; i < tiles_tree->GetEntries(); ++i)
        {
            tiles_tree->GetEntry(i);
            std::vector<Double_t> temp;
            temp.push_back(x);
            temp.push_back(y);
            temp.push_back(z);
            coordinates[id] = temp;
        };
    };
    return(coordinates[id]);
};

std::vector<Double_t> GetPixXYZ(UInt_t id)
{
    static std::map<UInt_t, std::vector<Double_t>> coordinates;
    if (coordinates.size()==0)
    {
        TFile *file = TFile::Open("./test.sim.root");
        TTree *pix_tree = file->Get<TTree>("alignment/sensors");
        Double_t x;
        Double_t y;
        Double_t z;
        UInt_t id;
        pix_tree->SetBranchAddress("vx", &x);
        pix_tree->SetBranchAddress("vy", &y);
        pix_tree->SetBranchAddress("vz", &z);
        pix_tree->SetBranchAddress("id", &id);
        for (int i = 0; i < pix_tree->GetEntries(); ++i)
        {
            pix_tree->GetEntry(i);
            std::vector<Double_t> temp;
            temp.push_back(x);
            temp.push_back(y);
            temp.push_back(z);
            coordinates[id] = temp;
        };
    };
    return(coordinates[id]);
};