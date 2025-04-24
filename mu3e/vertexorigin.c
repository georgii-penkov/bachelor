void vertexorigin()
{
    TFile *file = TFile::Open("./test.rec.root");
    TTree *mc_tracks_tree= file->Get<TTree>("mc_tracks");
    std::vector<double>* x = new std::vector<double>;
    std::vector<double>* y = new std::vector<double>;
    std::vector<double>* z = new std::vector<double>;
    mc_tracks_tree->SetBranchAddress("vx", &x);
    mc_tracks_tree->SetBranchAddress("vy", &y);
    mc_tracks_tree->SetBranchAddress("vz", &z);
    auto xy_histogram = new TH2F("XY Vertex", "XY Vertex", 100, -100, 100, 100, -100, 100);
    auto canvas = new TCanvas();
    for (int i = 0; i < mc_tracks_tree->GetEntries(); ++i)
    {
        mc_tracks_tree->GetEntry(i);
        xy_histogram->Fill(x->at(0),y->at(0));
    };
    xy_histogram->Draw();
    canvas->SaveAs("./Images/XY Vertex.png");

    canvas->Clear();
    auto z_histogram = new TH1F("Z Vertex", "Z Vertex", 100, -100, 100);
    for (int i = 0; i < mc_tracks_tree->GetEntries(); ++i)
    {
        mc_tracks_tree->GetEntry(i);
        z_histogram->Fill(z->at(0));
    };
    z_histogram->Draw();
    canvas->SaveAs("./Images/Z Vertex.png");
}