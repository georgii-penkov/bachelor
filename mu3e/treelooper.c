#include <iostream>
#include <map>

std::vector<Double_t> GetXYZ(UInt_t id)
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
        tiles_tree->SetBranchAddress("posz", &z);s
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


void treelooper()
{
    TFile *file = TFile::Open("./test.sim.root");
    TTree *tiles_tree = file->Get<TTree>("alignment/tiles");
    Double_t z;
    UInt_t id;
    tiles_tree->SetBranchAddress("id", &id);
    tiles_tree->SetBranchAddress("posz", &z);

    auto canvas = new TCanvas();
    auto zposgraph = new TGraph();

    for (int i = 0; i < tiles_tree->GetEntries(); ++i)
    {
        tiles_tree->GetEntry(i);
        zposgraph->AddPoint(id, z);
    };
    zposgraph->GetXaxis()->SetTitle("ID of Tile");
    zposgraph->GetYaxis()->SetTitle("Z Position of Tile");
    zposgraph->SetTitle("Z Position vs ID of tiles in tile detector");
    zposgraph->Draw("ap");
    canvas->SaveAs("./Z Position vs id.png");
    canvas->Clear();

    auto z_distribution = new TH1F("H1", "H1", 200, -1000, 1000);
    TTree *mu3e_tree = file->Get<TTree>("mu3e");

    std::vector<UInt_t> *tile_hit_id = new std::vector<UInt_t>;
    mu3e_tree->SetBranchAddress("tilehit_tile", &tile_hit_id);
    for (int i = 0; i < mu3e_tree->GetEntries(); ++i)
    {
        mu3e_tree->GetEntry(i);
        for (int j = 0; j < tile_hit_id->size(); ++j)
        {
            z_distribution->Fill(GetXYZ((*tile_hit_id)[j])[2]);
        };
    };
    z_distribution->Draw();
    z_distribution->GetXaxis()->SetTitle("Z-Coordinate of Tile");
    z_distribution->GetYaxis()->SetTitle("# of hits");
    z_distribution->SetTitle("Z Distribution of hits");
    canvas->SaveAs("./Z Distribution hits.png");
};