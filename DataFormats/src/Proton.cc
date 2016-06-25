#include "flashgg/DataFormats/interface/Proton.h"
//#include "FWCore/Utilities/interface/Exception.h"
#include <limits>

using namespace flashgg;

Proton::Proton() :
                direction_(0), X0_(0.),Y0_(0.),thetaX_(0.),thetaY_(0.),phi_(0.),
                xTrackChiSquare_(0.),yTrackChiSquare_(0.),timeOfFlight_(0.),
                Tracker1_(kFALSE),Tracker2_(kFALSE),Tof_(kFALSE)
{

}

Proton::Proton(const PPSRecoTrack &reco) :
                direction_(0.),X0_(0.),Y0_(0.),thetaX_(0.),thetaY_(0.),phi_(0.),
                xTrackChiSquare_(0.),yTrackChiSquare_(0.),timeOfFlight_(0.),
                Tracker1_(kFALSE),Tracker2_(kFALSE),Tof_(kFALSE)
{
  Variables(reco);
  Hits(reco);
}

void Proton::Variables(const PPSRecoTrack &reco)
{
  X0_ = reco.X0;
  Y0_ = reco.Y0;
  thetaX_ = reco.thetaX;
  thetaY_ = reco.thetaY;
  phi_ = reco.phi;
  xTrackChiSquare_ = reco.xTrackChiSquare;
  yTrackChiSquare_ = reco.yTrackChiSquare;
  timeOfFlight_ = reco.timeOfFlight;
}

void Proton::Hits(const PPSRecoTrack &reco)
{
  float Tr1X = reco.Det1.X;
  float Tr1Y = reco.Det1.Y;
  float Tr2X = reco.Det2.X;
  float Tr2Y = reco.Det2.Y;
  float ToFX = reco.ToF.X;
  float ToFt = reco.ToF.ToF;
  (Tr1X == 0 && Tr1Y == 0)? Tracker1_ = false : Tracker1_ = true;
  (Tr2X == 0 && Tr2Y == 0)? Tracker2_ = false : Tracker2_ = true;
  (ToFX == 0 && ToFt == 0)? Tof_ = false : Tof_ = true;
}

Proton::~Proton() {}

bool Proton::overlap( const Candidate & c ) const {
  // const RecoCandidate * o = dynamic_cast<const RecoCandidate *>( & c );
  // return ( o != 0 && (checkOverlap( superCluster(), o->superCluster() ) ));
  return false;
}
