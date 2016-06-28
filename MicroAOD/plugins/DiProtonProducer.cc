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

    class DiProtonProducer : public EDProducer
    {

    public:
        DiProtonProducer( const ParameterSet & );
    private:
        void produce( Event &, const EventSetup & ) override;
        EDGetTokenT<View<flashgg::Proton> > protonToken_;
        double ComEnergy_;
        
    };

    DiProtonProducer::DiProtonProducer( const ParameterSet &iConfig ) :
        protonToken_( consumes<View<flashgg::Proton> >( iConfig.getParameter<InputTag> ( "ProtonTag" ) ) ),
        ComEnergy_(iConfig.getParameter<double> ( "ComEnergy" ) )
    {
        produces<vector<flashgg::DiProtonCandidate> >();
    }

    void DiProtonProducer::produce( Event &evt, const EventSetup & )
    {
 
        Handle<View<flashgg::Proton> > protons;
        evt.getByToken( protonToken_, protons );
 
        auto_ptr<vector<DiProtonCandidate> > diProtonColl( new vector<DiProtonCandidate> );
        
        for( unsigned int i = 0 ; i < protons->size() ; i++ ) {

            DiProtonCandidate dipro;
            Ptr<flashgg::Proton> pp1 = protons->ptrAt( i );
            int directionProton1 = pp1->direction_;
            if(directionProton1==+1) dipro.SetProtonForward (pp1);
            if(directionProton1==-1) dipro.SetProtonBackward(pp1);
            // cout<<"i = "<<i<<" direction = "<<pp1->direction_<<endl;

            for( unsigned int j = i + 1 ; j < protons->size() ; j++ ) {
                
                Ptr<flashgg::Proton> pp2 = protons->ptrAt( j );
                int directionProton2 = pp2->direction_;
                if(directionProton2==+1) dipro.SetProtonForward (pp2);
                if(directionProton2==-1) dipro.SetProtonBackward(pp2);
                // cout<<"j = "<<j<<" direction = "<<pp2->direction_<<endl;

                if(directionProton1*directionProton2 >=0 ) continue;
                dipro.SetComEnergy(ComEnergy_);
                if(dipro.ComputeDiProtonObject()) diProtonColl->push_back( dipro );
            }
        }

        // std::sort( diProtonColl->begin(), diProtonColl->end(), greater<DiProtonCandidate>() );


        evt.put( diProtonColl );
    }
}
typedef flashgg::DiProtonProducer FlashggDiProtonProducer;
DEFINE_FWK_MODULE( FlashggDiProtonProducer );
// Local Variables:
// mode:c++
// indent-tabs-mode:nil
// tab-width:4
// c-basic-offset:4
// End:
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

