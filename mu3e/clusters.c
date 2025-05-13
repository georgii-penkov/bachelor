#include "getxyz.c"

double R_TILES = 60.6638;
double R_PIX_IN = 72.8849;
double R_PIX_OUT = 85.7547;

void clusters()
{
    TFile *file = TFile::Open("./test.sim.root");
    TTree *mu3e_tree = file->Get<TTree>("mu3e");
    std::vector<UInt_t> *tile_hit_ids = new std::vector<UInt_t>;
    std::vector<UInt_t> *pix_hit_ids = new std::vector<UInt_t>;

    mu3e_tree->SetBranchAddress("tilehit_tile", &tile_hit_ids);
    mu3e_tree->SetBranchAddress("hit_pixelid", &pix_hit_ids);

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
    for (int i = 2; i < 3; ++i)
    {
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
            if (used_pix_hits->at(j)) continue;
            ROOT::Math::XYZPoint inner_pix_hit;
            inner_pix_hit.SetX(GetPixXYZ((pix_hit_ids->at(j)>>16))[0]);
            inner_pix_hit.SetY(GetPixXYZ((pix_hit_ids->at(j)>>16))[1]);
            inner_pix_hit.SetZ(GetPixXYZ((pix_hit_ids->at(j)>>16))[2]);

            for (int k = 0; k < pix_hit_ids->size(); ++k)
            {
                if (!is_outer_pix->at(k)) continue;
                if (used_pix_hits->at(k)) continue;
                ROOT::Math::XYZPoint outer_pix_hit;
                outer_pix_hit.SetX(GetPixXYZ((pix_hit_ids->at(k)>>16))[0]);
                outer_pix_hit.SetY(GetPixXYZ((pix_hit_ids->at(k)>>16))[1]);
                outer_pix_hit.SetZ(GetPixXYZ((pix_hit_ids->at(k)>>16))[2]);
                for (int l = 0; l < tile_hit_ids->size(); ++l)
                {
                    if (used_pix_hits->at(k)) continue;
                    if (used_pix_hits->at(j)) continue;
                    if (used_tile_hits->at(l)) continue;
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
                    colinear = (outer_to_inner.Unit().Dot(inner_to_tile.Unit()) > 1 - 0.25);
                    //equidistant = (outer_to_inner.Mag2()/inner_to_tile.Mag2() < 2 and (outer_to_inner.Mag2()/inner_to_tile.Mag2()  > 0.5));
                    equidistant = true;
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
    };


}