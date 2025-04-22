void analysis()
{
    TMultiGraph *mg = new TMultiGraph();
    TFile file("./data.root");
    TGraphErrors *graph = file.Get<TGraphErrors>("Graph");
    auto myCanvas = new TCanvas();
    graph->DrawClone();
    
    TF1 *fullfit = new TF1("fullfit", fitfunction, -10, 10, 6);
    fullfit->SetParameters(5.0,2.0,0.5,0.05,-0.5,6.0);
    //fullfit->SetParameters(1.0,1.0,1.0,0.05,0.0,5.0);
    graph->Fit(fullfit, "S", "W");
    fullfit->DrawClone("Same");
    
};
