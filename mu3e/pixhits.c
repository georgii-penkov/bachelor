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


void pixhits()
{
    TFile *file = TFile::Open("./test.sim.root");
    TTree *mu3e_tree = file->Get<TTree>("mu3e");
    std::vector<UInt_t> *tile_hit_ids = new std::vector<UInt_t>;
    std::vector<UInt_t> *pix_hit_ids = new std::vector<UInt_t>;

    std::vector<Int_t > *pid = new std::vector<Int_t>;
    std::vector<Double_t> *vx = new std::vector<Double_t>;
    std::vector<Double_t> *vy = new std::vector<Double_t>;
    std::vector<Double_t> *vz = new std::vector<Double_t>;
    std::vector<Double_t> *px = new std::vector<Double_t>;
    std::vector<Double_t> *py = new std::vector<Double_t>;
    std::vector<Double_t> *pz = new std::vector<Double_t>;
    mu3e_tree->SetBranchAddress("traj_PID", &pid);
    mu3e_tree->SetBranchAddress("traj_vx", &vx);
    mu3e_tree->SetBranchAddress("traj_vy", &vy);
    mu3e_tree->SetBranchAddress("traj_vz", &vz);
    mu3e_tree->SetBranchAddress("traj_px", &px);
    mu3e_tree->SetBranchAddress("traj_py", &py);
    mu3e_tree->SetBranchAddress("traj_pz", &pz);


    auto pix_z_distribution = new TH1F("H1", "H1", 200, -1000, 1000);
    auto pix_r_distribution = new TH1F("H2", "H2", 200, -100, 100);


    auto tile_hits = new TGraph();
    auto inner_pix_hits = new TGraph();
    auto outer_pix_hits = new TGraph();
    tile_hits->SetMarkerStyle(4);  
    tile_hits->SetMarkerColor(kBlue);
    inner_pix_hits->SetMarkerStyle(4);  
    inner_pix_hits->SetMarkerColor(kGreen);
    outer_pix_hits->SetMarkerStyle(4);  
    outer_pix_hits->SetMarkerColor(kRed);

    mu3e_tree->SetBranchAddress("tilehit_tile", &tile_hit_ids);
    mu3e_tree->SetBranchAddress("hit_pixelid", &pix_hit_ids);

    //for (int i = 0; i < mu3e_tree->GetEntries(); ++i)
    for (int i = 1; i < 2; ++i)
    {
        mu3e_tree->GetEntry(i);
        for (int j = 0; j < pix_hit_ids->size(); ++j)
        {
            //drop 16 bits from mu3e/hit_pixelid to get actual id (lower 16 bits are column and row ids. whoever the f thought this was a good idea???)
            Double_t pix_x = GetPixXYZ((pix_hit_ids->at(j)>>16))[0];
            Double_t pix_y = GetPixXYZ((pix_hit_ids->at(j)>>16))[1];
            Double_t pix_z = GetPixXYZ((pix_hit_ids->at(j)>>16))[2];
            Double_t pix_r = sqrt(pix_x*pix_x+pix_y*pix_y);
            pix_z_distribution->Fill(pix_z);
            pix_r_distribution->Fill(pix_r);
            //select only hits in 2 recurl stations.
            if (pix_z < -200)
            {
                if (pix_r>70 and pix_r < 75)
                {
                    inner_pix_hits->AddPoint(pix_z, atan2(pix_y, pix_x));
                };
                if (pix_r>80 and pix_r< 90)
                {
                    outer_pix_hits->AddPoint(pix_z, atan2(pix_y, pix_x));
                };
            }
        };
        for (int j = 0; j < tile_hit_ids->size(); ++j)
        {
            Double_t tile_x = GetTileXYZ((*tile_hit_ids)[j])[0];
            Double_t tile_y = GetTileXYZ((*tile_hit_ids)[j])[1];
            Double_t tile_z = GetTileXYZ((*tile_hit_ids)[j])[2];
            if (tile_z < 0)
            {
                tile_hits->AddPoint(tile_z, atan2(tile_y, tile_x));
            };
        };

        //projected hits based on mc origin data (vertex position and start impulse)

        for (int j = 0; j < pid->size(); ++j)
        {
            std::cout << pid->at(j) << std::endl << vx->at(j) << std::endl << vy->at(j) << std::endl << vz->at(j) << std::endl;
        };
    };




    auto canvas1 = new TCanvas();
    pix_z_distribution->Draw();
    canvas1->SaveAs("./Images/Tracking/Pixel Z Distribution.png");
    auto canvas2 = new TCanvas();
    pix_r_distribution->Draw();
    canvas1->SaveAs("./Images/Tracking/Pixel R Distribution.png");


    auto canvas3 = new TCanvas();
    outer_pix_hits->SetMinimum(-3.15);
    outer_pix_hits->SetMaximum(+3.15);
    outer_pix_hits->GetXaxis()->SetLimits(-650, -200);
    outer_pix_hits->Draw("AP");
    inner_pix_hits->Draw("P");
    tile_hits->Draw("P");
    canvas3->SaveAs("./Images/Tracking/BasicTracking.png");

}