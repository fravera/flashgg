
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
// #include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
// #include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
// #include "DataFormats/VertexReco/interface/Vertex.h"
// #include "DataFormats/PatCandidates/interface/Photon.h"
#include "flashgg/DataFormats/interface/Proton.h"
// #include "flashgg/DataFormats/interface/GenPhotonExtra.h"
// #include "flashgg/DataFormats/interface/VertexCandidateMap.h"
// #include "flashgg/MicroAOD/interface/PhotonIdUtils.h"
// #include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
// #include "HiggsAnalysis/GBRLikelihoodEGTools/interface/EGEnergyCorrectorSemiParm.h"
// #include "DataFormats/PatCandidates/interface/Electron.h"
// #include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "flashgg/MicroAOD/interface/IsolationAlgoBase.h"
//PPS
#include "FastSimulation/PPSFastObjects/interface/PPSSpectrometer.h"
#include "FastSimulation/PPSFastObjects/interface/PPSGenData.h"
#include "FastSimulation/PPSFastObjects/interface/PPSSimData.h"
#include "FastSimulation/PPSFastObjects/interface/PPSRecoData.h"
#include "FastSimulation/PPSFastObjects/interface/PPSGenVertex.h"
#include "FastSimulation/PPSFastObjects/interface/PPSRecoVertex.h"

using namespace std;
using namespace edm;
using reco::PFCandidate;

namespace flashgg {

    class ProtonProducer : public EDProducer
    {

    public:
        ProtonProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        //edm::EDGetTokenT<PPSSpectrometer<PPSGenData> > tokGenPPS;
        edm::EDGetTokenT<PPSSpectrometer<PPSRecoData> > tokRecoPPS;


    };


    ProtonProducer::ProtonProducer( const ParameterSet &iConfig )
    {
        //tokGenPPS = consumes<PPSSpectrometer<PPSGenData> >(edm::InputTag("ppssim","PPSGen"));
        tokRecoPPS = consumes<PPSSpectrometer<PPSRecoData> >(edm::InputTag("ppssim","PPSReco"));
        produces<vector<flashgg::Proton> >();

    }

    void ProtonProducer::produce( Event &evt, const EventSetup &iSetup )
    {

        auto_ptr<vector<flashgg::Proton> > protonColl( new vector<flashgg::Proton> );


        Handle<PPSSpectrometer<PPSRecoData> > recoPPS;
        evt.getByToken(tokRecoPPS,recoPPS);
        short direction = 1;
        for(size_t iArmF=0; iArmF<recoPPS->ArmF.Tracks.size(); ++iArmF){
            flashgg::Proton protonArmF = Proton(recoPPS->ArmF.Tracks.at(iArmF));
            cout<<recoPPS->ArmF.Tracks.at(iArmF).xi<<endl;
            protonArmF.SetDirection(direction);
            protonColl->push_back(protonArmF);
        }

        direction = -1;
        for(size_t iArmB=0; iArmB<recoPPS->ArmB.Tracks.size(); ++iArmB){
            flashgg::Proton protonArmB = Proton(recoPPS->ArmB.Tracks.at(iArmB));
            protonArmB.SetDirection(direction);
            protonColl->push_back(protonArmB);
        }

        evt.put(protonColl);

    }
}



typedef flashgg::ProtonProducer FlashggProtonProducer;
DEFINE_FWK_MODULE( FlashggProtonProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

