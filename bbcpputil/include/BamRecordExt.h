//
// Created by Ruolin Liu on 5/10/21.
//

#ifndef CPPUTIL_INCLUDE_BAMRECORDEXT_CPP_H_
#define CPPUTIL_INCLUDE_BAMRECORDEXT_CPP_H_
#include<set>
#include <SeqLib/BamRecord.h>
#include "SeqLib/RefGenome.h"
namespace cpputil {

class BamPileup {
 public:
  SeqLib::BamRecord bam;
  int32_t qpos;
  int indel, level;
  uint32_t is_del:1, is_head:1, is_tail:1, is_refskip:1, aux:28;
  BamPileup(const bam_pileup1_t *pi): bam(pi->b) {
    qpos = pi->qpos;
    indel = pi->indel;
    level = pi->level;
    is_del = pi->is_del;
    is_head = pi->is_head;
    is_refskip = pi->is_refskip;
    aux = pi->aux;
  }
};

bool ProperPair(const SeqLib::BamRecord& bam);

std::pair<int32_t, int32_t> MatePositionAndPositionEndWithSoftClip(const SeqLib::BamRecord & bam);

int32_t GetUnclippedFramgentLength(const SeqLib::BamRecord &b);

std::pair<int32_t, int32_t> MatePositionAndPositionEnd(const SeqLib::BamRecord & bam);

//overlap len of paired end reads in the reference coordinate, excluding soft clipping
int32_t InsertSize(const SeqLib::BamRecord & read1, const SeqLib::BamRecord& read2);

std::pair<uint64_t, uint64_t> ProperPairFramgentEndsWithSclip(const SeqLib::BamRecord &b);

void PrintQual(const SeqLib::BamRecord &b);

int32_t CountNOrLowQInMatchedBases(const SeqLib::BamRecord &b, const int qcutoff);

void AddMatchedBasesToCycleCount( const SeqLib::BamRecord& b,
                                  std::vector<int64_t>& q0_cycle_count,
                                  std::vector<int64_t>& q30_cycle_count,
                                  int start = -1,
                                  int end = std::numeric_limits<int>::max());

int32_t CountNBasesInAlignment(const SeqLib::BamRecord &b);

int32_t NumSoftClip5End(const SeqLib::BamRecord &b);

uint32_t GetNumNonIndelAlignedBases(const SeqLib::BamRecord &bam);
int32_t GetNM(const SeqLib::BamRecord &bam);
int32_t GetNMismatch(const SeqLib::BamRecord &bam, bool NisMM = false);
bool HasClusteredMuts(const SeqLib::BamRecord &bam, const SeqLib::BamHeader& header,
                      const SeqLib::RefGenome& refgenome, const int cutoff);

bool GetBTag(const SeqLib::BamRecord&, const std::string&, std::vector<int64_t>&);

int32_t GetNMismatchX(const SeqLib::BamRecord &bam);
int GetFamilySize(const SeqLib::BamRecord &bam);
int32_t IndelLen(const SeqLib::BamRecord &bam);

int32_t GetTotalIndelLen(const SeqLib::BamRecord &bam);

int SoftClip3end(SeqLib::BamRecord &bam);

bool SoftClipBamRecord(SeqLib::BamRecord &bam);

void MaskBaseBelowMinBq(SeqLib::BamRecord &bam, int32_t mbp);

void TrimBamFromFragEnd(SeqLib::BamRecord &bam, int32_t mp, int32_t mate_position_end_with_sclip, int32_t end5, int32_t end3);

void TrimPairFromFragEnd(SeqLib::BamRecord &left, SeqLib::BamRecord&right, int32_t n_trim);

void TrimSingleFromFragEnd(SeqLib::BamRecord &bam, int32_t n_trim);

int RefPosToQueryPos(const SeqLib::BamRecord &bam, const int refpos);

bool IsPairOverlap(const SeqLib::BamRecord& one, const SeqLib::BamRecord& two);

std::pair<int, int> GetPairOverlapRStartAndRStop(const SeqLib::BamRecord& fwd, const SeqLib::BamRecord& rev);
int EffFragLen(const std::vector<SeqLib::BamRecord>&, int count_overhang);

std::pair<std::pair<int,int>,std::pair<int,int>>
GetPairOverlapQStartAndQStop(const SeqLib::BamRecord& fwd, const SeqLib::BamRecord& rev);


std::pair<int,int>
GetBamOverlapQStartAndQStop(const SeqLib::BamRecord& record, const SeqLib::GenomicRegion& gr);


} //end namespace


#endif //CPPUTIL_INCLUDE_BAMRECORDEXT_H_
