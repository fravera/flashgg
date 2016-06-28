#include "flashgg/DataFormats/interface/DiProtonCandidate.h"
#include "flashgg/DataFormats/interface/Proton.h"
#include "TMath.h"

using namespace flashgg;

DiProtonCandidate::~DiProtonCandidate() {}

DiProtonCandidate::DiProtonCandidate()
{
	doubleTrackingHitArmForward_  = kFALSE;
    doubleTrackingHitArmBackward_ = kFALSE;
    vertexFound_ = kFALSE;
    missingMass_ = -1.  ;
    rapidity_    = -100.;
}

DiProtonCandidate::DiProtonCandidate( edm::Ptr<flashgg::Proton> protonForward, edm::Ptr<flashgg::Proton> protonBackward, double energy, edm::Ptr<reco::Vertex> vertex )
{
    //    std::cout << " DiProtonCandidate::DiProtonCandidate " << std::endl;
    protonForward_  = protonForward ;
    doubleTrackingHitArmForward_  = kFALSE;
    if(protonForward_->Tracker1_  && protonForward_->Tracker2_ ) doubleTrackingHitArmForward_  = kTRUE;
    protonBackward_ = protonBackward;
    doubleTrackingHitArmBackward_ = kFALSE;
    if(protonBackward_->Tracker1_ && protonBackward_->Tracker2_) doubleTrackingHitArmBackward_ = kTRUE;
    CTPPSVertex_ = vertex;
    vertexFound_ = kTRUE;
    missingMass_ = -1.;
    comEnergy_ = energy;
    ComputeDiProtonObject();
    
}

void DiProtonCandidate::SetProtonForward(edm::Ptr<flashgg::Proton> protonForward)
{
	
	protonForward_  = protonForward ;
    if(protonForward_->Tracker1_  && protonForward_->Tracker2_ ) doubleTrackingHitArmForward_  = kTRUE;
    
}

void DiProtonCandidate::SetProtonBackward(edm::Ptr<flashgg::Proton> protonBackward)
{
	
	protonBackward_  = protonBackward ;
    if(protonBackward_->Tracker1_  && protonBackward_->Tracker2_ ) doubleTrackingHitArmBackward_  = kTRUE;
    
}

void DiProtonCandidate::SetVertex(edm::Ptr<reco::Vertex> vertex)
{
	CTPPSVertex_ = vertex;
    vertexFound_ = kTRUE;
}

bool DiProtonCandidate::ComputeDiProtonObject()
{
    // cout<<"computing"<<endl;
	// if( &protonBackward_ == NULL || &protonForward_ == NULL ) return kFALSE;
    cout<<protonForward_->eta()<<endl;
	if( (protonBackward_->GetDirection() * protonForward_->GetDirection()) >= 0 ) return kFALSE;
    // cout<<"direction F "<<protonForward_ ->GetDirection()<<endl;
    // cout<<"direction B "<<protonBackward_->GetDirection()<<endl;
	// missingMass_ = comEnergy_*TMath::Sqrt(protonForward_.xi)
    // this->setP4( protonForward_->p4() + protonBackward_->p4() );
    double xiForward  = (1.-protonForward_ ->energy()/(comEnergy_/2.));
    double xiBackward = (1.-protonBackward_->energy()/(comEnergy_/2.));
    // this->setMass(comEnergy_*TMath::Sqrt(xiForward*xiBackward));
    double px = -protonForward_->px() - protonBackward_->px();
    double py = -protonForward_->py() - protonBackward_->py();
    double pz = -protonForward_->pz() - protonBackward_->pz();
    double energy = comEnergy_ - protonForward_ ->energy() - protonBackward_->energy();
    LorentzVector lv(px,py,pz,energy);
    this->setP4(lv);
    cout<<"mass " << this->mass()<<" = "<<comEnergy_*TMath::Sqrt(xiForward*xiBackward)<<endl;
	return kTRUE;
}


bool DiProtonCandidate::overlap( const Candidate & c ) const {
  // const RecoCandidate * o = dynamic_cast<const RecoCandidate *>( & c );
  // return ( o != 0 && (checkOverlap( superCluster(), o->superCluster() ) ));
  return false;
}


