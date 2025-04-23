#include <iostream>
void treelooper()
{
    TFile *file = TFile::Open("./test.sim.root");
    TTree *tiles_tree = file->Get<TTree>("alignment/tiles");
    std::cout << tiles_tree << std::endl;
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
            for (int k = 0; k < tiles_tree->GetEntries(); ++k)
            {
                tiles_tree->GetEntry(k);
                //std::cout << (*tile_hit_id)[0] << std::endl;
                if ((*tile_hit_id)[j] == id) 
                {
                    z_distribution->Fill(z);
                    std::cout << z << std::endl;
                }; 
            };
        };

    };
    z_distribution->Draw();
};