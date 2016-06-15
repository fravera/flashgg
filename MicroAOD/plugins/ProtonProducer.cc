
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "flashgg/DataFormats/interface/Photon.h"
#include "flashgg/DataFormats/interface/GenPhotonExtra.h"
#include "flashgg/DataFormats/interface/VertexCandidateMap.h"
#include "flashgg/MicroAOD/interface/PhotonIdUtils.h"
#include "DataFormats/PatCandidates/interface/PackedGenParticle.h"
// #include "HiggsAnalysis/GBRLikelihoodEGTools/interface/EGEnergyCorrectorSemiParm.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"
#include "flashgg/MicroAOD/interface/IsolationAlgoBase.h"

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
        tokGenPPS = consumes<PPSSpectrometer<PPSGenData> >(edm::InputTag("ppssim","PPSGen"));
        tokRecoPPS = consumes<PPSSpectrometer<PPSRecoData> >(edm::InputTag("ppssim","PPSReco"));


    };


    ProtonProducer::ProtonProducer( const ParameterSet &iConfig )
    {

    }

    void ProtonProducer::produce( Event &evt, const EventSetup &iSetup )
    {

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

