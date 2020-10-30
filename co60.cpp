
void co60(){
    //gStyle->SetOptFit(1111);
     TCanvas * Rvstheta = new TCanvas(" Ratio - Angle","Ratio VS Angle",1); Rvstheta->SetGrid();Rvstheta->SetFillColor(0);Rvstheta->SetFillStyle(4000);

    double angle[9] = {60,90,105,120,135,150,165,180,210};
    double ratio[9] = {1.080,1.000,1.049,1.059,1.088,1.151,1.148,1.165,1.087};
    //double exp_ang[13] =  {60,70,80,90,100,110,120,130,140,150,160,170,180};
    //double exp_count[13] ={104,123,130,107,101,121,131,111,128,112,108,116,160};
    //double exp_ratio[13];
    //double exp_ang[7] = {90,105,120,135,150,165,180}; // 1013 tue
    //double exp_count[7] = {532,647,588,600,632,615,686}; // 1013 tue
    //double exp_ang[7] = {70,90,105, 120, 135, 150, 165}; // 1015 thur wide window
    //double exp_count[7] = {1083,1091,1078,1054,1109,1091,1081}; // 1015 thur
    double exp_ang[8] = {60,90,105, 120, 135, 150, 165,180}; // 1015 thur bipolar setting
    double exp_ang_int[10] = {55,60,90,105, 120, 135, 150, 165,180,185}; // 1015 thur bipolar setting
    //double exp_count[8] = {923,882,920,904,912,924,1003,1007}; // 1015 thur + BG
    //double exp_count[8] = {888,848,878,864,948,920,984,990}; // 1015 thur No BG
    
    double exp_count1[8] = {929,880,902,905,912,949,1010,1011}; // 1015 thur + BG MCA 150 degree is too far from theory
    double exp_count2[8] = {868,848,868,864,886,911,963,980}; // 1015 thur No BG MCA
    double null_count[10] = {0,0,0,0,0,0,0,0,0,0};
    double null_ang[10] =  {55.3,60,90,105, 120, 135, 150, 165,180,185};
    double exp_s_err[8];
    double exp_ang_err[8];
    double exp_ratio1[8];
    double exp_ratio2[8];
    double exp_ratio_err[8];
    double exp_ratios_err[8];

    //calculate error of count
    for (int i=0;i<8;i++){
        exp_count1[i] = exp_count1[i];
        exp_count2[i] = exp_count2[i];
        exp_ang_err[i]= sqrt(exp_count1[i]); 
        exp_s_err[i] = sqrt( (exp_count1[i] + exp_count1[i] - exp_count2[i]));

        cout<<"error for each bin for S+B : "<<exp_ang_err[i]<<", and signal only : "<<exp_s_err[i]<<" at angle "<<exp_ang[i]<<endl;
    }

    for (int i=0;i<8;i++){
        exp_ratio1[i] = exp_count1[i]/exp_count1[1];
        exp_ratio2[i] = exp_count2[i]/exp_count2[1];
        exp_ratio_err[i] = exp_count1[i]/exp_count1[1]* sqrt(pow(exp_ang_err[i],2.0)/pow(exp_count1[i],2.0) + pow(exp_ang_err[1],2.0)/pow(exp_count1[1],2.0));
        exp_ratios_err[i] = exp_count2[i]/exp_count2[1]*sqrt(pow(exp_s_err[i],2.0)/pow(exp_count2[i],2.0) + pow(exp_s_err[1],2.0)/pow(exp_count2[1],2.0)) ;
        cout<<"experimental ratio is : "<<exp_ratio1[i]<<" +/- "<<exp_ratio_err[i]<<" at angle "<<exp_ang[i]<<endl;
        cout<<"Let's check my function works properly!"<<endl;
        cout<<"For the error of the ratio of counts between  two angles : "<< sqrt( exp_ang_err[i]*exp_ang_err[i]/exp_count1[i]/exp_count1[i] + exp_ang_err[1]*exp_ang_err[1]/exp_count1[1]/exp_count1[1]  )<<endl;
    }
    /*
    double T_value[9] ;
    for (int i=0;i<9;i++){
        T_value[i] = 1+0.125*cos(angle[i])*cos(angle[i]) + 0.042*TMath::Power(cos(angle[i]),4);
    }*/
	TH1F *frame00 = Rvstheta->DrawFrame(55,0.94,185,1.22);
	frame00->GetYaxis()->SetTitle("Y( #theta ) /  Y(90 #circ ) ");
	frame00->GetXaxis()->SetTitle(" #theta ( #circ )");

     //TF1 *Theory = new TF1("theory","cos(x)",90,185) ;
     //TF1 *Theory = new TF1("theory","1+0.102*(cos(x))^2+0.0091*cos(x)",90,185) ;
     TF1 *Theory1 = new TF1("theory1","1+0.125*cos(x*3.14/180)*cos(x*3.14/180)+0.042*cos(x*3.14/180)*cos(x*3.14/180)*cos(x*3.14/180)*cos(x*3.14/180)",55,185) ; //book  cosine
     TF1 *Theory2 = new TF1("theory2","1.05 + 0.102*  (3 * cos(x*3.14/180)*cos(x*3.14/180) - 1 )/2 + 0.0091/ 8 *( 35 * cos(x*3.14/180)*cos(x*3.14/180)*cos(x*3.14/180)*cos(x*3.14/180) - 30 *cos(x*3.14/180)*cos(x*3.14/180) + 3)",55,185) ; //manual
     Theory1->SetTitle("");
     Theory1->SetLineColor(8);
     Theory2->SetTitle("");
     Theory2->SetLineColor(9);

    //Theory1->Draw("SAME");
    Theory2->Draw("SAME");
	TGraphErrors * graph = new TGraphErrors(9,angle, ratio,0,0);
	TGraphErrors * graph1 = new TGraphErrors(8,exp_ang, exp_ratio2,0,exp_ratios_err);
    graph->SetMarkerStyle(21);
    graph1->SetMarkerStyle(22);
    graph1->SetFillColor(6);
    graph1->SetFillStyle(3003);

    

    //TF1 * lgfit = new TF1("lgfit","pol3",60,180);
    TF1 * lgfit = new TF1("lgfit","[0] + [1] * cos(x*3.14/180) + [2] *  (3 * (cos(x*3.14/180))^2 - 1 )/2 + [3] / 8 *( 35 * (cos(x*3.14/180))^4 - 30 *(cos(x*3.14/180))^2 + 3)",55,185);
    //TF1 * lgfit = new TF1("lgfit","[0] + [1] *cos(x*3.14/180)*cos(x*3.14/180)  + [2]*cos(x*3.14/180)*cos(x*3.14/180)*cos(x*3.14/180)*cos(x*3.14/180) ",55,185);
    //lgfit->FixParameter(0,1);
    lgfit->SetLineStyle(7);
    lgfit->SetLineColor(1);
    graph1->Fit(lgfit,"R");
    
    //Let's make confidence interval
    TGraphErrors *graph_interval = new TGraphErrors(10,null_ang,null_count,0,0);
    //TGraphErrors *graph_interval = new TGraphErrors(10,exp_ang_int,0);
    //TGraphErrors *graph_interval1 = new TGraphErrors(8,exp_ang,exp_ratio,0);

    /*Compute the confidence intervals at the x points of the created graph*/
    (TVirtualFitter::GetFitter())->GetConfidenceIntervals(graph_interval,0.68);
    //(TVirtualFitter::GetFitter())->GetConfidenceIntervals(graph_interval1,0.95);
    //Now the "graph_interval" graph contains function values as its y-coordinates
    //and confidence intervals as the errors on these coordinates
    //Draw the graph, the function and the confidence intervals

    graph_interval->SetFillColor(30);
    graph_interval->SetFillStyle(3001);
    //graph_interval1->SetFillColor(2);
    //graph_interval1->SetFillStyle(3005);
    graph_interval->Draw("e3");
    //graph_interval1->Draw("e3");
    //graph->Draw("p");
    graph1->Draw("p");

    //cout<<"comparing error of graph :"<<graph1->GetErrorY(3)<<endl;
    
    TLegend *legCo = new TLegend(0.2, 0.6, 0.5, 0.8);/*legCo->SetFillColor(0);*/ legCo->SetTextSize(0.3);legCo->SetBorderSize(0);legCo->SetFillStyle(0);legCo->SetTextSize(0.05);
	//stringstream label1; label1.precision(4); label1<<"Mean : "<<Mean_; label1.precision(2);label1<<" #pm "<<merr_;
	//stringstream label2; label2.precision(4); label2<<"#sigma : "<<Sigma_; label2.precision(2); label2<<" #pm "<<serr_;
	legCo->AddEntry(Theory2,"Theory","l");
//	legCo->AddEntry(gfit, label1.str() .c_str() ,"");
	legCo->AddEntry(lgfit,"Fit","l");
	legCo->AddEntry(graph_interval," Fit #pm #sigma","f");

    legCo->Draw();
}