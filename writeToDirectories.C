//This macro illustrates how to write and read histograms to and from
//files that have multiple directories.

void writeToDirectories( const TString fileName = "writeToDirectories.root" )
{

    // --------------------- First make histograms and save them --------------- //

    // Create some histograms and fill them by sampling some functions
    TH1F h1("h1", "Gaussian distribution", 100, -3, 3);
    TH1F h2("h2", "Exponential distribution", 100, 0, 10);

    TF1 f1("f1","gaus(0)",-3,3);
    f1.SetParameters(1,0,1);
    TF1 f2("f2","expo(0)",0,-10);
    f2.SetParameters(0,-1);

    h1.FillRandom("f1",10000);
    h2.FillRandom("f2",10000);

    // Create two different output files and write data
    TFile* outFile = new TFile(fileName.Data(),"recreate");
    outFile->mkdir("Directory1");
    outFile->mkdir("Directory2");

    outFile->cd("Directory1");
    h1.Write();
    outFile->cd("Directory2");
    h2.Write();

    outFile->Close();
    delete outFile;

    // ----------- Now open the files, read the histos, and draw them --------------- //

    // Get the histos
    TFile* inFile = new TFile(fileName.Data(),"read");
    TH1F* h3 = (TH1F*) inFile->Get("Directory1/h1");
    TH1F* h4 = (TH1F*) inFile->Get("Directory2/h2");

    // Draw them
    TCanvas* can1 = new TCanvas("can1","Some Histograms",1);
    can1->Clear();
    can1->Divide(2,1);

    can1->cd(1);
    h3->Draw();

    can1->cd(2);
    h4->Draw();

}
