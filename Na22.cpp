#include <math.h>

void Na22(){
    double angle[10]={0,10,20,30,40,50,60,70,80,90};
    double coincidence[10] = {1267,560,121,58,39,55,45,46,59,56};

    TCanvas * Cvstheta = new TCanvas(" Voltage-Temperature plot","Voltage VS T",1); Cvstheta->SetGrid();Cvstheta->SetFillColor(0);Cvstheta->SetFillStyle(4000);
	TH1F *frame00 = Cvstheta->DrawFrame(00,0,100,1500);
	frame00->GetYaxis()->SetTitle("Counts ");
	frame00->GetXaxis()->SetTitle("Angle #theta ( #circ )");
    
	TGraphErrors * graph = new TGraphErrors(10,angle, coincidence,0,0);
    graph->SetMarkerStyle(21);

//    TF1 * gfit = new TF1("gfit","gaus",0,90);
     
    TF1 * gfit = new TF1("gfit"," [1] * exp( ( -0.5 ) * ( ( x - [2] ) / [3] )^2 )",0,90);

    graph->Draw("p");
    graph->Fit(gfit,"R");

    float Mean_ = gfit->GetParameter(1);
    float merr_ = gfit->GetParError(1); 
    float Sigma_ = gfit->GetParameter(2);
    float serr_ = gfit->GetParError(2);

    cout<<"test"<<endl;
    cout<<gfit->GetParameter(0)<<endl;

    TLegend *legNa = new TLegend(0.5, 0.6, 0.9, 0.8);/*legNa->SetFillColor(0);*/ legNa->SetTextSize(0.03);legNa->SetBorderSize(0);legNa->SetFillStyle(0);legNa->SetTextSize(0.04);
	stringstream label1; label1.precision(4); label1<<"Mean : "<<Mean_; label1.precision(2);label1<<" #pm "<<merr_;
	stringstream label2; label2.precision(4); label2<<"#sigma : "<<Sigma_; label2.precision(2); label2<<" #pm "<<serr_;
	legNa->AddEntry(gfit,"Gaussian Fit","l");
	legNa->AddEntry(gfit, label1.str() .c_str() ,"");
	legNa->AddEntry(gfit,label2.str() .c_str(),"");

    legNa->Draw();
}