///////////////////////////////////////////////////////////////////////////////////////
// Run like this:                                                                    //
//    root -b -q "$ROOTCOREDIR/scripts/load_packages.C" 'RunTheEventLoop_All.cxx()'  //
///////////////////////////////////////////////////////////////////////////////////////

void RunTheEventLoop_All ()
{
    /*   Settings        */
    bool isPDSFJob = false;
    bool isGridJob = false;
    bool isFakesJob = false;
    bool isLowPtJob = false;
    bool isPhotonJob = false;
    bool isEWHighPtJob = false;
    bool isEWLowPtJob = false;

    // set up the job for xAOD access:
    xAOD::Init().ignore();
    
    // uncomment to exit on destruction of an unchecked StatusCode object, for debugging
    xAOD::TReturnCode::enableFailure();
    
    // compose a string with the current time for the output dir(s)
    TString dateAndTime(TDatime().AsSQLString());
    
    // create a new sample handler to describe the data files we use
    SH::SampleHandler sh;
    
    //================================//
    // define the samples to run over //
    //================================//
    
    if (isGridJob) {
        SH::addGrid(sh, "mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_SUSY2.e3698_s2608_s2183_r7725_r7676_p2613");
        string tag = "MAY4_v0_NoSyst"; // grid job tag
        string version = "00-22"; // version of ntuples

        // set the name of the output  dataset
        sh.setMetaString("data15_13TeV.*", "nc_outputSampleName", "user.%nickname%.%in:name[2]%.%in:name[3]%.%in:name[6]%.zmetjets-"+version+"_" + tag);
        sh.setMetaString("data15_13TeV.*", "nc_grid_filter", "*AOD*"); // default is "*.root*" - doesn't work for Tier-0 datasets          

        sh.setMetaString("data16_13TeV.*", "nc_outputSampleName", "user.%nickname%.%in:name[2]%.%in:name[3]%.%in:name[6]%.zmetjets-"+version+"_" + tag);
        sh.setMetaString("data16_13TeV.*", "nc_grid_filter", "*AOD*"); // default is "*.root*" - doesn't work for Tier-0 datasets                                                                          

        sh.setMetaString("mc15_13TeV.*", "nc_outputSampleName", "user.%nickname%.%in:name[2]%.%in:name[6]%.zmetjets-"+version+"_" + tag);

        sh.setMetaString("mc15_13TeV.*", "nc_grid_filter", "*AOD*"); // default is "*.root*" - doesn't work f

    }
    else { // Local Job

        // get all samples in a given dir (each subdir is treated as a separate sample)
        //SH::DiskListEOS list ("/eos/atlas/user/e/ekuwertz/mc15_13TeV/","root://eosatlas//eos/atlas/user/e/ekuwertz/mc15_13TeV/");
        SH::DiskListLocal list ("/afs/cern.ch/user/z/zmarshal/work/public/");

        SH::ScanDir()
            //.filePattern ("*_jer.root*")     // only include files with this pattern
            //.samplePattern ("*SM_GG_*DAOD*")       // only include samples with this pattern
            //.samplePattern ("*physics_Main*DAOD*") // Data test sample
            .samplePattern ("*410000*DAOD_SUSY2*") // MC test sample
            //.samplePostfix ("_gridDataset*") // merging directories, e.g. merge sampleA_gridDataset0 sampleA_gridDataset1
            .scan(sh, list);
        
        //SH::scanDir (sh, list, "*AOD*","mc15_13TeV.187150.PowhegPythia8_AU2CT10_WpWm_ee.merge.AOD.e3059_s2608_s2183_r6630_r6264_tid05593313_00");
        
        //SH::scanDir (sh, list, "*AOD*");                              // process all files
        
        // run over a single file
        //SH::DiskListLocal list ("/afs/cern.ch/work/t/tholmes/mc14_13TeV.147407.PowhegPythia8_AZNLO_Zmumu.merge.AOD.e3059_s1982_s2008_r5787_r5853_tid01598003_00");
        //SH::scanSingleDir (sh, "sample", list);

        //SH::DiskListLocal list ("/afs/cern.ch/work/l/longjon/SUSY/temp/");
        //SH::scanDir (sh, list, "*AOD*","mc15_13TeV.410000.PowhegPythiaEvtGen_P2012_ttbar_hdamp172p5_nonallhad.merge.DAOD_SUSY2.e3698_s2608_s2183_r6630_r6264_p2375_tid05892244_00");
        

      //---------------------------
      // ttbar
      //---------------------------

      // SH::DiskListEOS list ("/eos/atlas/user/b/benhoob/MC15/ttbar","root://eosatlas//eos/atlas/user/b/benhoob/MC15/ttbar");
      // string filename = "AOD.05567253._000011.pool.root.1"; // single ttbar file
      // SH::scanDir (sh, list,filename);   // process one MC15 ttbar file
    }

    // set xsec from SUSYTools in metadata
    SH::readSusyMeta(sh,"$ROOTCOREBIN/data/SUSYTools/susy_crosssections_13TeV.txt");
    SH::readSusyMeta(sh,"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/xsdb/mc15_13TeV/Backgrounds.txt");
    SH::readSusyMeta(sh,"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/xsdb/mc15_13TeV//MGPy8EG_A14N_SM_GG_N2_XX_YY_1.txt");
    SH::readSusyMeta(sh,"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/xsdb/mc15_13TeV//MGPy8EG_A14N_SM_SS_N2_XX_YY_1_2L.txt");
    SH::readSusyMeta(sh,"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/xsdb/mc15_13TeV//MGPy8EG_A14N_SM_GG_bbN2_XX_YY_1_2L.txt");
    SH::readSusyMeta(sh,"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/xsdb/mc15_13TeV//MGPy8EG_A14N_SM_GG_N2_ZN1_XX_YY_2L.txt");
    SH::readSusyMeta(sh,"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/xsdb/mc15_13TeV//MGPy8EG_A14N_SM_GG_N2_XX_YY_ZZ_2L.txt");
    SH::readSusyMeta(sh,"/cvmfs/atlas.cern.ch/repo/sw/database/GroupData/dev/SUSYTools/xsdb/mc15_13TeV//MGPy8EG_A14N_SM_GG_N2_SLN1_XX_YY_2L.txt");
    // set the name of the tree in our files (for xAOD: "CollectionTree")
    sh.setMetaString("nc_tree", "CollectionTree");
    
    // set the isData flag using dataset string matching
    sh.setMetaDouble(".*mc15_13TeV.*", "isData", 0.0);
    sh.setMetaDouble(".*data15_13TeV.*", "isData", 1.0);
    sh.setMetaDouble(".*data16_13TeV.*", "isData", 1.0);
    // and the same for ATLFAST
    sh.setMetaDouble(".*mc15_13TeV.*e.*_a.*_r.*", "isATLFAST", 1.0);
    
    //std::string sampleName = sh.getMetaString("sample_name");
    //bool isDAOD=(sampleName.find("DAOD")!=std::string::npos);
    
    // print out the samples we found
    std::cout << "Will now print the found samples:" << std::endl;
    sh.print();
    
    //==============================================//
    // set up the job, add our alg and configure it //
    //==============================================//
    
    EL::Job job;
    job.sampleHandler(sh);
    
    
    // Enable veto of duplicate events
    EL::DuplicateChecker * duplicates = new EL::DuplicateChecker;
    duplicates->setOutputTreeName("duplicate_info");
    duplicates->addKnownDuplicatesFile(gSystem->ExpandPathName("$ROOTCOREBIN/../TheEventLoop/data/duplicates_data"));
    job.algsAdd(duplicates);
    
    // define an output ntuple
    EL::OutputStream output("outputTree");
    job.outputAdd(output);
    EL::NTupleSvc *ntuple = new EL::NTupleSvc("outputTree");
    job.algsAdd(ntuple);
    
    TheEventLoop *alg = new TheEventLoop;

    // the below object definitions are passed on to QuickAna
    alg->muonDef      = (!isFakesJob ? "SUSYIso":
                                       "SUSYIso SUSYloose");
    alg->jetDef       = "AntiKt4EMTopo_SUSY";
    alg->electronDef  = (!isFakesJob ? "SUSYMediumIso":
                                       "SUSYMediumIso SUSYloose"); // MediumLH applied at analysis level
    alg->photonDef    = "tight_FixedCutTight";
    alg->tauDef       = "none";
    alg->metDef       = "susy2L";
    alg->met2Def      = "trackmet";
    alg->eventinfoDef = "default";
    alg->orDef        = "boostedHF_JVT";

    // Triggers from 2015 and 2016
    std::string TriggerDef = "HLT_mu50 HLT_e60_lhmedium HLT_e60_lhmedium_nod0 HLT_2e12_lhloose_L12EM10VH HLT_2e17_lhvloose_nod0 HLT_mu18_mu8noL1 HLT_mu20_mu8noL1 HLT_mu22_mu8noL1 HLT_2mu14_nomucomb HLT_e17_lhloose_mu14 HLT_e7_lhmedium_mu24 HLT_e17_lhloose_nod0_mu14 HLT_e7_lhmedium_nod0_mu24";
    // Adding triggers for matching dilepton trigger items
    TriggerDef += " HLT_mu18 HLT_mu22 HLT_e17_lhloose HLT_mu14 HLT_e7_lhmedium HLT_mu24 HLT_e17_lhloose_nod0 HLT_e12_lhloose_L1EM10VH HLT_2e15_lhvloose_nod0_L12EM13VH";
    //  Note: I think HLT_mu8noL1 might want to be here, but that's kinda an impossible item
    // Additional isolated triggers
    TriggerDef += " HLT_e24_lhmedium_nod0_L1EM20VH HLT_e24_lhtight_nod0_ivarloose HLT_e26_lhtight_nod0_ivarloose HLT_mu24_ivarmedium HLT_mu26_ivarmedium HLT_e24_lhmedium_L1EM20VH HLT_mu20_iloose_L1MU15 HLT_e24_lhmedium_nod0_L1EM20VHI_mu8noL1";


    if (isLowPtJob) TriggerDef += " HLT_xe70 HLT_xe80 HLT_xe80_wEFMu HLT_xe100 HLT_xe110_mht_L1XE50 HLT_xe110_mht_L1XE60 HLT_xe110_mht_L1XE50_AND_xe70_L1XE50 L1_XE50"; // HLT_xe100_mht HLT_xe100_mht_L1XE50 HLT_xe110_mht_L1XE50
    alg->triggerDef = TriggerDef; // quickana
    alg->triggerString = TriggerDef;   // trig manager

    alg->jetKine      = "pt > 20e3 && eta < 2.8 && eta > -2.8";
    alg->muonKine     = "pt > 10e3 && eta < 2.5 && eta > -2.5";
    if (isLowPtJob)     alg->muonKine     = "pt > 7e3 && eta < 2.5 && eta > -2.5";
    if (isEWLowPtJob)     alg->muonKine     = "pt > 4e3 && eta < 2.5 && eta > -2.5";
    alg->electronKine = "pt > 10e3 && eta < 2.47 && eta > -2.47";
    if (isLowPtJob)     alg->electronKine     = "pt > 7e3 && eta < 2.4 && eta > -2.4";
    if (isEWLowPtJob)     alg->electronKine     = "pt > 4e3 && eta < 2.4 && eta > -2.4";
    alg->photonKine   = "pt > 25e3 && eta < 2.37 && eta > -2.37";

    alg->muDataFiles = {"GoodRunsLists/data15_13TeV/20160720/physics_25ns_20.7.lumicalc.OflLumi-13TeV-005.root",
                        "GoodRunsLists/data16_13TeV/20170215/physics_25ns_20.7.lumicalc.OflLumi-13TeV-008.root"};
    alg->muMcFiles = {"dev/SUSYTools/merged_prw_mc15c_latest.root"}; //,"dev/SUSYTools/merged_prw_mc15c_signal_latest.root"};

    // Selection settings - post QuickAna cuts
    alg->m_muonSelectionPaths =     {"$ROOTCOREBIN/../TheEventLoop/config/muon.sel"};
    if (isFakesJob)   alg->m_muonSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/muon_SUSYIso.sel","$ROOTCOREBIN/../TheEventLoop/config/muon_SUSYloose.sel"};
    if (isLowPtJob)   alg->m_muonSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/muon.sel","$ROOTCOREBIN/../TheEventLoop/config/muon_lowpt.sel"};
    if (isEWLowPtJob)   alg->m_muonSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/muon.sel"};
    if (isLowPtJob && isFakesJob) alg->m_muonSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/muon_SUSYIso_lowpt.sel","$ROOTCOREBIN/../TheEventLoop/config/muon_SUSYloose_lowpt.sel"}; 

    alg->m_electronSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/electron.sel"};
    if (isFakesJob) alg->m_electronSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/electron_SUSYMediumIso.sel","$ROOTCOREBIN/../TheEventLoop/config/electron_SUSYloose.sel" };
    if (isLowPtJob) alg->m_electronSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/electron.sel","$ROOTCOREBIN/../TheEventLoop/config/electron_lowpt.sel" };
    if (isEWLowPtJob) alg->m_electronSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/electron.sel" };
    if (isFakesJob && isLowPtJob) alg->m_electronSelectionPaths = {"$ROOTCOREBIN/../TheEventLoop/config/electron_SUSYMediumIso_lowpt.sel","$ROOTCOREBIN/../TheEventLoop/config/electron_SUSYloose_lowpt.sel" };

    alg->m_photonSelectionPaths =   {"$ROOTCOREBIN/../TheEventLoop/config/photon.sel"};
    alg->m_jetSelectionPaths =      {"$ROOTCOREBIN/../TheEventLoop/config/jet.sel"};

    alg->m_eventSelectionPaths =    { "$ROOTCOREBIN/../TheEventLoop/config/SR1.sel", "$ROOTCOREBIN/../TheEventLoop/config/twolep.sel"};
    if (isFakesJob)  alg->m_eventSelectionPaths  =    { "$ROOTCOREBIN/../TheEventLoop/config/twolep_SUSYIso.sel","$ROOTCOREBIN/../TheEventLoop/config/twolep_loose.sel"};
    if (isLowPtJob)  alg->m_eventSelectionPaths  =    { "$ROOTCOREBIN/../TheEventLoop/config/twolep_lowpt.sel"};
    if (isEWLowPtJob)  alg->m_eventSelectionPaths  =    { "$ROOTCOREBIN/../TheEventLoop/config/twolep.sel"};
    if (isFakesJob && isLowPtJob)  alg->m_eventSelectionPaths  =    { "$ROOTCOREBIN/../TheEventLoop/config/twolep_SUSYIso_lowpt.sel","$ROOTCOREBIN/../TheEventLoop/config/twolep_loose_lowpt.sel"};
    if (isPhotonJob){
        alg->m_photonSelectionPaths =   {"$ROOTCOREBIN/../TheEventLoop/config/photon.sel"};
        alg->m_eventSelectionPaths =    {"$ROOTCOREBIN/../TheEventLoop/config/onephoton.sel"};
        alg->m_requireTwoGoodLeadingLeptons=false;
    }



    // Added for checking if something passes SUSY2 trigger requirements
    std::ifstream susy2trigfile (gSystem->ExpandPathName("$ROOTCOREBIN/../TheEventLoop/data/SUSY2_Triggers.txt"));
    std::vector<std::string> susy2Triggers;
    std::string trigger;
    while (susy2trigfile>>trigger) {
        susy2Triggers.push_back(trigger);
        std::cout << trigger << std::endl;
    }

    // The ususal trigger requirements
    TString trigFilePath;
    if (isLowPtJob || isEWLowPtJob) trigFilePath = "$ROOTCOREBIN/../TheEventLoop/config/triggers_SUSY5.txt";
    else trigFilePath = "$ROOTCOREBIN/../TheEventLoop/config/triggers.txt";
    std::ifstream trigfile (gSystem->ExpandPathName( "$ROOTCOREBIN/../TheEventLoop/config/triggers.txt" ));
    std::vector<std::string> myTriggers;
    while (trigfile>>trigger) {
        myTriggers.push_back(trigger);
    }
    
    alg->m_susy2Triggers=susy2Triggers;
    alg->triggerList=myTriggers;
    alg->m_writeTriggers=true;
    alg->m_doFakes=isFakesJob;    // needed for saving extra iso info
    alg->m_doPhotons=isPhotonJob;
    alg->m_doMultipleWP=false || isFakesJob;    // needed for multiple object working points
    alg->m_doLowPt=isLowPtJob;    // this is a low pt job, veto high pt events
    //alg->m_doSystematics=true;
    //alg->m_doPDFUncertainties=true;

    // Look up the PDFs from http://lhapdf.hepforge.org/pdfsets.html
    sh.setMetaString(".*PowhegPythiaEvtGen_P2012.*", "PDFSet", "CT10nlo");
    sh.setMetaString(".*NNPDF23LO13TeV.*", "PDFSet", "NNPDF23LO");

    // See QuickAna/Root/TriggerTool.cxx for definitions
    //alg->triggerDef = "SingleE SingleMu HLT_mu20_iloose_L1MU15 HLT_e24_lhmedium_iloose_L1EM20VH HLT_e24_tight_iloose";
    
    alg->m_fillTruthLevelHistos = true;
    alg->m_fillRecoLevelHistos = false;
    alg->m_fillOnlyCounterHistos = false;
    alg->m_writeTruthLeptons = true;

    alg->outputName = "outputTree";

    // For more output from QuickAna and the event loop
    //alg->msgLevel = MSG::VERBOSE;
    job.algsAdd(alg);
    
    //=======================================================//
    // set up the driver that will run the job and submit it //
    //=======================================================//
    alg->schedulerDef = "optimized";

    // set up the driver we want to use (options: local, grid, batch system, etc - see )    

    // Max number of events
    //job.options()->setDouble (EL::Job::optMaxEvents, 2000);

    // skip events
    //job.options()->setDouble (EL::Job::optSkipEvents, 15000);

    if (isGridJob){
        EL::PrunDriver driver;

        driver.options()->setDouble("nc_express", 1); // runs test jobs faster!
        //driver.options()->setString("nc_excludedSite", "CERN-PROD_DERIVED,CERN-PROD_TZDISK"); // can"t run there anyway
    
        // Important to turn off merging for data!
        driver.options()->setDouble(EL::Job::optGridMergeOutput, 0); 
        //driver.options()->setDouble(EL::Job::optGridNFilesPerJob,1);

        // Restrict the amount of data you run on
        //driver.options()->setDouble(EL::Job::optGridNGBPerJob,5);

        // submit!
        TString submitDir = TString("SusyZMETjetsOutput_")+dateAndTime;
        submitDir.ReplaceAll(" ","_").ReplaceAll("-","").ReplaceAll(":","");
        driver.submitOnly(job, submitDir.Data());
    }
    else if (isPDSFJob){
        // For running on PDSF batch system, use this instead
        EL::SoGEDriver driver;
        driver.options()->setString (EL::Job::optSubmitFlags, "-S /bin/bash"); // or whatever shell you are using
        driver.shellInit = "shopt -s expand_aliases\n";
        driver.options()->setString( "nc_EventLoop_SubmitFlags" , "-l eliza18io=1,h_vmem=8G" );
        
        // submit!
        TString submitDir = TString("SusyZMETjetsOutput_")+dateAndTime;
        //TString submitDir = TString("/afs/cern.ch/work/t/tholmes/ZMETSamples/SusyZMETjetsOutput_")+dateAndTime;
        submitDir.ReplaceAll(" ","_").ReplaceAll("-","").ReplaceAll(":","");
        driver.submit (job, submitDir.Data());
    }
    else{ // local job
        // For running locally, do this
        EL::DirectDriver driver;
        
        // with timestamp in output dir name
        TString submitDir = TString("SusyZMETjetsOutput_")+dateAndTime;
        //TString submitDir = TString("/afs/cern.ch/work/t/tholmes/ZMETSamples/SusyZMETjetsOutput_")+dateAndTime;
        submitDir.ReplaceAll(" ","_").ReplaceAll("-","").ReplaceAll(":","");
        driver.submit (job, submitDir.Data());
    }    

    std::cout << "Done" << std::endl;
}
