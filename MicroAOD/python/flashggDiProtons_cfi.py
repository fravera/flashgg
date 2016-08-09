import FWCore.ParameterSet.Config as cms

flashggDiProtons = cms.EDProducer('FlashggDiProtonProducer',
                                  ProtonTag              = cms.InputTag('flashggProtons'),
                                  ComEnergy              = cms.double(13000.)
                                  )
