import FWCore.ParameterSet.Config as cms
import FWCore.Utilities.FileUtils as FileUtils

process = cms.Process("FLASHggMicroAOD")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff") # gives deprecated message in 80X but still runs
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")

from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_data')
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run2_prompt_WillDisappearInJul16')
#process.GlobalTag.globaltag = cms.string('81X_dataRun2_v1')
#process.GlobalTag = GlobalTag(process.GlobalTag,'80X_mcRun2_asymptotic_2016_miniAODv2')
process.GlobalTag = GlobalTag(process.GlobalTag,'80X_dataRun2_Prompt_v9')

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32( 100) )
process.MessageLogger.cerr.FwkReport.reportEvery = cms.untracked.int32( 1000 )

process.RandomNumberGeneratorService = cms.Service("RandomNumberGeneratorService")
process.RandomNumberGeneratorService.flashggRandomizedPhotons = cms.PSet(
          initialSeed = cms.untracked.uint32(16253245)
        )

#81x_pps
process.source = cms.Source("PoolSource",
	fileNames = cms.untracked.vstring(
#'/store/data/Run2016C/DoubleMuon/AOD/PromptReco-v2/000/275/846/00000/146AD6E8-733E-E611-8CA5-02163E011D08.root',
#'file:patTuple.root',
'file:/afs/cern.ch/work/l/lforthom/private/yyanalysis/CMSSW_8_1_0_pre8/src/miniAOD/miniAOD_PAT.root',
	)
)

process.MessageLogger.cerr.threshold = 'ERROR' # can't get suppressWarning to work: disable all warnings for now
# process.MessageLogger.suppressWarning.extend(['SimpleMemoryCheck','MemoryCheck']) # this would have been better...

# Uncomment the following if you notice you have a memory leak
# This is a lightweight tool to digg further
#process.SimpleMemoryCheck = cms.Service("SimpleMemoryCheck",
#                                        ignoreTotal = cms.untracked.int32(1),
#                                        monitorPssAndPrivate = cms.untracked.bool(True)
#                                       )

process.load("flashgg/MicroAOD/flashggMicroAODSequence_cff")

# NEEDED FOR ANYTHING PRIOR TO reMiniAOD
#process.weightsCount.pileupInfo = "addPileupInfo"

from flashgg.MicroAOD.flashggMicroAODOutputCommands_cff import microAODDefaultOutputCommand
process.out = cms.OutputModule("PoolOutputModule", fileName = cms.untracked.string('myMicroAODOutputFile.root'),
                               outputCommands = microAODDefaultOutputCommand
                               )

# All jets are now handled in MicroAODCustomize.py
# Switch from PFCHS to PUPPI with puppi=1 argument (both if puppi=2)

process.p = cms.Path(process.flashggMicroAODwithPPSSequence)
process.e = cms.EndPath(process.out)

# Uncomment these lines to run the example commissioning module and send its output to root
#process.commissioning = cms.EDAnalyzer('flashggCommissioning',
#                                       PhotonTag=cms.untracked.InputTag('flashggPhotons'),
#                                       DiPhotonTag = cms.untracked.InputTag('flashggDiPhotons'),
#                                       VertexTag=cms.untracked.InputTag('offlineSlimmedPrimaryVertices')
#)
#process.TFileService = cms.Service("TFileService",
#                                   fileName = cms.string("commissioningTree.root")
#)
#process.p *= process.commissioning


from flashgg.MicroAOD.MicroAODCustomize import customize
customize(process)
#customize.customizeHLT(process)
