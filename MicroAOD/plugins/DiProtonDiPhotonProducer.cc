
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "DataFormats/Common/interface/Handle.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/EDMException.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "flashgg/DataFormats/interface/Proton.h"
#include "flashgg/DataFormats/interface/DiProtonCandidate.h"
#include "flashgg/DataFormats/interface/Photon.h"
#include "flashgg/DataFormats/interface/DiPhotonCandidate.h"
#include "flashgg/DataFormats/interface/DiProtonDiPhoton.h"
// // #include "flashgg/MicroAOD/interface/ProtonIdUtils.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
// // #include "flashgg/MicroAOD/interface/VertexSelectorBase.h"
// // #include "DataFormats/PatCandidates/interface/PackedCandidate.h"
// // #include "flashgg/DataFormats/interface/VertexCandidateMap.h"
// // #include "DataFormats/EgammaCandidates/interface/Conversion.h"
// // #include "DataFormats/BeamSpot/interface/BeamSpot.h"

using namespace edm;
using namespace std;

namespace flashgg {

    class DiProtonDiPhotonProducer : public EDProducer
    {

    public:
        DiProtonDiPhotonProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        EDGetTokenT<View<flashgg::DiProtonCandidate> > diProtonToken_;
        EDGetTokenT<View<flashgg::DiPhotonCandidate> > diPhotonToken_;
        double DeltaMass_;
        double DeltaEta_;

    };

    DiProtonDiPhotonProducer::DiProtonDiPhotonProducer( const ParameterSet &iConfig ) :
        diProtonToken_( consumes<View<flashgg::DiProtonCandidate> >( iConfig.getParameter<InputTag> ( "DiProtonTag" ) ) ),
        diPhotonToken_( consumes<View<flashgg::DiPhotonCandidate> >( iConfig.getParameter<InputTag> ( "DiPhotonTag" ) ) )
        // DeltaMass_(iConfig.getParameter<double> ( "DeltaMass" ) ),
        // DeltaEta_(iConfig.getParameter<double> ( "DeltaEta" ) )
    {
        produces<vector<flashgg::DiProtonDiPhoton> >();
    }

    void DiProtonDiPhotonProducer::produce( Event &evt, const EventSetup & )
    {

        Handle<View<flashgg::DiProtonCandidate> > diProtons;
        evt.getByToken( diProtonToken_, diProtons );

        Handle<View<flashgg::DiPhotonCandidate> > diPhotons;
        evt.getByToken( diPhotonToken_, diPhotons );

        auto_ptr<vector<DiProtonDiPhoton> > diProtonDiPhotonColl( new vector<DiProtonDiPhoton> );

        for( unsigned int i = 0 ; i < diProtons->size() ; i++ ) {

            Ptr<flashgg::DiProtonCandidate> diPro = diProtons->ptrAt( i );

            for( unsigned int j = 0 ; j < diPhotons->size() ; j++ ) {

                Ptr<flashgg::DiPhotonCandidate> diPho = diPhotons->ptrAt( j );

                DiProtonDiPhoton diProDiPho(diPho,diPro);

                diProtonDiPhotonColl->push_back( diProDiPho );
                cout<<diProDiPho.GetDeltaMass() <<endl;
            }
        }



        evt.put( diProtonDiPhotonColl );
    }
}
typedef flashgg::DiProtonDiPhotonProducer FlashggDiProtonDiPhotonProducer;
DEFINE_FWK_MODULE( FlashggDiProtonDiPhotonProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
