#include "getxyz.c" //unclean include. go fuck yourself, idc
#include <iostream>
#include <vector>
#include "TROOT.h"
#include "TTree.h"
#include "TFile.h"
#include "TGraph.h"
#include "TMath.h"
#include "Math/Point3D.h"
#include "Math/Vector3D.h"
#include "TAxis.h"
#include "TCanvas.h"
#include <TApplication.h> //to show the gui and not exit immediately
#include "TH1F.h"
#include <algorithm>
#include "THStack.h"
#include "TEllipse.h"
#include "TStyle.h"

double R_TILES = 60.6638;
double R_PIX_IN = 72.8849;
double R_PIX_OUT = 85.7547;

class Hit
{
    public:
        bool IsPixel();
        bool IsTile();
        UInt_t ID();
        ROOT::Math::XYZPoint Position();
        double Time();
    private:
        bool _ispixel;
        bool _istile;
        UInt_t _id;
};  
bool Hit::IsPixel()
{
    return(_ispixel);
};
bool Hit::IsTile()
{
    return(_istile);
};
UInt_t Hit::ID()
{
    return(_id);
};
ROOT::Math::XYZPoint Hit::Position()
{
    std::vector<Double_t> pos;
    if (_ispixel) pos = GetPixXYZ(_id);
    if (_istile) pos = GetTileXYZ(_id);
    ROOT::Math::XYZPoint temp(pos[0], pos[1], pos[3]);
    return(temp);
};



ROOT::Math::XYZPoint ToRootPoint(std::vector<Double_t> vector)
{
    if (vector.size()!=3) return (ROOT::Math::XYZPoint(0,0,0));
    ROOT::Math::XYZPoint temp(vector[0], vector[1], vector[2]);
    return(temp);
};


int main()
{
    int argc = 1;
    char* argv[] = { (char*)"app", nullptr };
    TApplication app("app", &argc, argv);
    TFile *file = TFile::Open("./test.sim.root");
    TTree *mu3e_tree = file->Get<TTree>("mu3e");
    std::vector<UInt_t> *tile_hit_ids = new std::vector<UInt_t>;
    std::vector<UInt_t> *pix_hit_ids = new std::vector<UInt_t>;
    std::vector<Double_t> *tile_times = new std::vector<Double_t>;
    std::vector<Double_t> *pix_times = new std::vector<Double_t>;

    mu3e_tree->SetBranchAddress("tilehit_tile", &tile_hit_ids);
    mu3e_tree->SetBranchAddress("hit_pixelid", &pix_hit_ids);
    mu3e_tree->SetBranchAddress("tilehit_time", &tile_times);
    mu3e_tree->SetBranchAddress("hit_timestamp", &pix_times);

    auto tile_hits = new TGraph();
    auto inner_pix_hits = new TGraph();
    auto outer_pix_hits = new TGraph();
    tile_hits->SetMarkerStyle(4);  
    tile_hits->SetMarkerColor(kBlue);
    inner_pix_hits->SetMarkerStyle(4);  
    inner_pix_hits->SetMarkerColor(kGreen);
    outer_pix_hits->SetMarkerStyle(4);  
    outer_pix_hits->SetMarkerColor(kRed);



    std::vector<TGraph*> tracks;

    //for (int i = 0; i < mu3e_tree->GetEntries(); ++i)
    for (int i = 800; i < 801; ++i)
    {   
        double framestart = 6400+64*i;
        auto canvas1 = new TCanvas();
        std::vector<TH1F*> time_bins;
        mu3e_tree->GetEntry(i);
        std::vector<bool> *used_tile_hits = new std::vector<bool>(tile_hit_ids->size());
        std::vector<bool> *used_pix_hits = new std::vector<bool>(pix_hit_ids->size());
        std::vector<bool> *is_inner_pix = new std::vector<bool>(pix_hit_ids->size());
        std::vector<bool> *is_outer_pix = new std::vector<bool>(pix_hit_ids->size());

        for (int j = 0; j < pix_hit_ids->size(); ++j)
        {
            if (GetPixXYZ((pix_hit_ids->at(j)>>16))[0]*GetPixXYZ((pix_hit_ids->at(j)>>16))[0] + GetPixXYZ((pix_hit_ids->at(j)>>16))[1]*GetPixXYZ((pix_hit_ids->at(j)>>16))[1] < 75*75 and  GetPixXYZ((pix_hit_ids->at(j)>>16))[0]*GetPixXYZ((pix_hit_ids->at(j)>>16))[0] + GetPixXYZ((pix_hit_ids->at(j)>>16))[1]*GetPixXYZ((pix_hit_ids->at(j)>>16))[1] > 70*70)
            is_inner_pix->at(j) = true;
            if (GetPixXYZ((pix_hit_ids->at(j)>>16))[0]*GetPixXYZ((pix_hit_ids->at(j)>>16))[0] + GetPixXYZ((pix_hit_ids->at(j)>>16))[1]*GetPixXYZ((pix_hit_ids->at(j)>>16))[1] < 90*90 and  GetPixXYZ((pix_hit_ids->at(j)>>16))[0]*GetPixXYZ((pix_hit_ids->at(j)>>16))[0] + GetPixXYZ((pix_hit_ids->at(j)>>16))[1]*GetPixXYZ((pix_hit_ids->at(j)>>16))[1] > 80*80)
            is_outer_pix->at(j) = true;
        };

        for (int j = 0; j < pix_hit_ids->size(); ++j)
        {
            if (is_outer_pix->at(j)) outer_pix_hits->AddPoint(GetPixXYZ((pix_hit_ids->at(j)>>16))[2], atan2(GetPixXYZ((pix_hit_ids->at(j)>>16))[1], GetPixXYZ((pix_hit_ids->at(j)>>16))[0]));
            if (is_inner_pix->at(j)) inner_pix_hits->AddPoint(GetPixXYZ((pix_hit_ids->at(j)>>16))[2], atan2(GetPixXYZ((pix_hit_ids->at(j)>>16))[1], GetPixXYZ((pix_hit_ids->at(j)>>16))[0]));
        };
        for (int j = 0; j < tile_hit_ids->size(); ++j)
        {
            tile_hits->AddPoint(GetTileXYZ(tile_hit_ids->at(j))[2], atan2(GetTileXYZ(tile_hit_ids->at(j))[1], GetTileXYZ(tile_hit_ids->at(j))[0]));
        };


        for (int j = 0; j < pix_hit_ids->size(); ++j)
        {
            if (!is_inner_pix->at(j)) continue;
            //if (used_pix_hits->at(j)) continue;
            ROOT::Math::XYZPoint inner_pix_hit;
            inner_pix_hit.SetX(GetPixXYZ((pix_hit_ids->at(j)>>16))[0]);
            inner_pix_hit.SetY(GetPixXYZ((pix_hit_ids->at(j)>>16))[1]);
            inner_pix_hit.SetZ(GetPixXYZ((pix_hit_ids->at(j)>>16))[2]);

            for (int k = 0; k < pix_hit_ids->size(); ++k)
            {
                if (!is_outer_pix->at(k)) continue;
                //if (used_pix_hits->at(k)) continue;
                ROOT::Math::XYZPoint outer_pix_hit;
                outer_pix_hit.SetX(GetPixXYZ((pix_hit_ids->at(k)>>16))[0]);
                outer_pix_hit.SetY(GetPixXYZ((pix_hit_ids->at(k)>>16))[1]);
                outer_pix_hit.SetZ(GetPixXYZ((pix_hit_ids->at(k)>>16))[2]);
                for (int l = 0; l < tile_hit_ids->size(); ++l)
                {
                    //if (used_pix_hits->at(k)) continue;
                    //if (used_pix_hits->at(j)) continue;
                    //if (used_tile_hits->at(l)) continue;
                    ROOT::Math::XYZPoint tile_hit;
                    tile_hit.SetX(GetTileXYZ(tile_hit_ids->at(l))[0]);
                    tile_hit.SetY(GetTileXYZ(tile_hit_ids->at(l))[1]);
                    tile_hit.SetZ(GetTileXYZ(tile_hit_ids->at(l))[2]);
                    if ((inner_pix_hit - outer_pix_hit).Mag2() > 100*100) continue;
                    if ((inner_pix_hit - tile_hit).Mag2() > 100*100) continue;
                    ROOT::Math::XYZVector outer_to_inner = inner_pix_hit - outer_pix_hit;
                    ROOT::Math::XYZVector inner_to_tile = tile_hit - inner_pix_hit;
                    bool colinear = false;
                    bool equidistant = false;
                    double max_length_factor = 3;
                    colinear = (outer_to_inner.Unit().Dot(inner_to_tile.Unit()) > 1 - 0.25);
                    equidistant = (sqrt(outer_to_inner.Mag2()/inner_to_tile.Mag2()) < max_length_factor and sqrt(outer_to_inner.Mag2()/inner_to_tile.Mag2()  > 1/max_length_factor));
                    if (colinear and equidistant)
                    {
                        used_pix_hits->at(j) = true;
                        used_pix_hits->at(k) = true;
                        used_tile_hits->at(l) = true;
                        auto track = new TGraph();
                        track->SetMarkerStyle(4);  
                        track->SetMarkerColor(kBlack);
                        track->AddPoint(outer_pix_hit.Z(), atan2(outer_pix_hit.Y(), outer_pix_hit.X()));
                        track->AddPoint(inner_pix_hit.Z(), atan2(inner_pix_hit.Y(), inner_pix_hit.X()));
                        track->AddPoint(tile_hit.Z(), atan2(tile_hit.Y(), tile_hit.X()));
                        tracks.push_back(track);
                        break;
                    };


                };
            };
        };


        delete used_tile_hits;
        delete used_pix_hits;
        delete is_inner_pix;
        delete is_outer_pix;

        outer_pix_hits->SetMinimum(-3.15);
        outer_pix_hits->SetMaximum(+3.15);
        outer_pix_hits->GetXaxis()->SetLimits(-650, 650);
        outer_pix_hits->Draw("AP");
        inner_pix_hits->Draw("P");
        tile_hits->Draw("P");

        for (int i = 0; i < tracks.size(); ++i)
        {
            (tracks[i])->Draw("L");
        };
        auto canvas2 = new TCanvas();
        auto times = new TH1F("Tile hit times", "Tile hit times", 100, *std::min_element(tile_times->begin(), tile_times->end()), *std::max_element(tile_times->begin(), tile_times->end()));
        for (int j = 0; j < tile_times->size(); ++j)
        {
            times->Fill(tile_times->at(j));
            std::cout << tile_times->at(j) << std::endl;
        };
        times->Draw();


        for (int j = 0; j < pix_times->size(); ++j)
        {
            pix_times->at(j) = pix_times->at(j)*4;
        };
        auto canvas3 = new TCanvas();
        auto times2 = new TH1F("Pix hit times", "Pix hit times", 100, *std::min_element(pix_times->begin(), pix_times->end()), *std::max_element(pix_times->begin(), pix_times->end()));
        //std::cout << *std::min_element(pix_times->begin(), pix_times->end()) << std::endl;
        for (int j = 0; j < pix_times->size(); ++j)
        {
            times2->Fill(pix_times->at(j));
            std::cout << pix_times->at(j) << std::endl;
        };
        times2->Draw();


        gStyle->SetCanvasPreferGL(true);  // enables OpenGL rendering for transparency

        gStyle->SetPalette(kBird);
        int color = 0;
        double radius = 100;
        std::vector<TGraph*> space_clusters;
        std::vector<TH1F*> cluster_times;
        std::cout << "color" << std::endl;
        std::vector<bool> *clustering_used_tiles = new std::vector<bool>(tile_hit_ids->size());
        std::vector<bool> *clustering_used_pix = new std::vector<bool>(pix_hit_ids->size());
        std::vector<TEllipse*> circles;
        for (int j = 0; j < pix_hit_ids->size(); ++j)
        {
            if (clustering_used_pix->at(j)) continue;
            if (is_outer_pix->at(j)) continue;
            clustering_used_pix->at(j) = true;
            color += 1;
            space_clusters.push_back(new TGraph);
            cluster_times.push_back(new TH1F(Form("time%d", color), "", 100, *std::min_element(pix_times->begin(), pix_times->end())-10, *std::max_element(pix_times->begin(), pix_times->end())+10));
            space_clusters.back()->SetMarkerStyle(4);
            space_clusters.back()->SetMarkerColor(color);
            cluster_times.back()->SetLineColor(color);
            cluster_times.back()->SetFillColor(color);
            ROOT::Math::XYZPoint center = ToRootPoint(GetPixXYZ((pix_hit_ids->at(j)>>16)));   
            space_clusters.back()->AddPoint(center.Z(), atan2(center.Y(), center.X()));
            cluster_times.back()->Fill(pix_times->at(j));
            circles.push_back(new TEllipse(center.Z(), atan2(center.Y(), center.X()),radius ,radius/R_PIX_IN));
            circles.back()->SetLineColor(color);
            for (int k = 0; k < pix_hit_ids->size(); ++k)
            {
                if (clustering_used_pix->at(k)) continue;
                ROOT::Math::XYZPoint current = ToRootPoint(GetPixXYZ((pix_hit_ids->at(k)>>16)));
                std::cout << current.X() << std::endl;
                if (sqrt(pow(center.Z()-current.Z(), 2) + pow(R_PIX_IN*(atan2(current.Y(), current.X())-atan2(center.Y(), center.X())),2)) < radius)
                {
                    clustering_used_pix->at(k) = true;
                    space_clusters.back()->AddPoint(current.Z(), atan2(current.Y(), current.X()));
                    cluster_times.back()->Fill(pix_times->at(k));
                };
            };
            std::cout << "doink" << std::endl;
            for (int k = 0; k < tile_hit_ids->size(); ++k)
            {
                if (clustering_used_tiles->at(k)) continue;
                ROOT::Math::XYZPoint current = ToRootPoint(GetTileXYZ(tile_hit_ids->at(k)));
                std::cout << current.X() << std::endl;
                if (sqrt(pow(center.Z()-current.Z(), 2) + pow(R_PIX_IN*(atan2(current.Y(), current.X())-atan2(center.Y(), center.X())),2)) < radius)
                {
                    clustering_used_tiles->at(k) = true;
                    space_clusters.back()->AddPoint(current.Z(), atan2(current.Y(), current.X()));
                    std::cout << current.X() << current.Y() << current.Z() << std::endl;
                    cluster_times.back()->Fill(tile_times->at(k));
                };
            };
        };
        auto spatial_canvas = new TCanvas();

        for (int j = 0; j < size(space_clusters); ++j) 
        {
            space_clusters.at(j)->SetMinimum(-3.15);
            space_clusters.at(j)->SetMaximum(+3.15);
            space_clusters.at(j)->GetXaxis()->SetLimits(-650, 650);
            space_clusters.at(j)->Draw(j == 0 ? "AP" : "P SAME");
        }
        //for (int j = 0; j < size(circles); ++j) circles.at(j)->Draw();
        auto time_canvas = new TCanvas();
        auto hstack = new THStack("hstack", "Cluster Times;Time;Counts");

        for (auto& hist : cluster_times) {
            hstack->Add(hist);
        }
        
        hstack->Draw("HIST");
        time_canvas->BuildLegend();



    };

    app.Run();
    return(0);

};

void time_clusters() //for running as a root macro with cling
{
    main();
};
