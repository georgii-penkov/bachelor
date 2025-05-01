void thetaphi()
{
    TFile *file = TFile::Open("./test.rec.root");
    TTree *tiles_tree = file->Get<TTree>("alignment/tiles");
}