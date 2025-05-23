//
// Generated file, do not edit! Created by opp_msgtool 6.1 from ModelUpdate.msg.
//

#ifndef __MODELUPDATE_M_H
#define __MODELUPDATE_M_H

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wreserved-id-macro"
#endif
#include <omnetpp.h>

// opp_msgtool version check
#define MSGC_VERSION 0x0601
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgtool: 'make clean' should help.
#endif

class ModelUpdate;
/**
 * Class generated from <tt>ModelUpdate.msg:1</tt> by opp_msgtool.
 * <pre>
 * message ModelUpdate
 * {
 *     int senderId;
 *     double weights[]; // Array of weights
 *     double sendTime;
 * }
 * </pre>
 */
class ModelUpdate : public ::omnetpp::cMessage
{
  protected:
    int senderId = 0;
    double *weights = nullptr;
    size_t weights_arraysize = 0;
    double sendTime = 0;

  private:
    void copy(const ModelUpdate& other);

  protected:
    bool operator==(const ModelUpdate&) = delete;

  public:
    ModelUpdate(const char *name=nullptr, short kind=0);
    ModelUpdate(const ModelUpdate& other);
    virtual ~ModelUpdate();
    ModelUpdate& operator=(const ModelUpdate& other);
    virtual ModelUpdate *dup() const override {return new ModelUpdate(*this);}
    virtual void parsimPack(omnetpp::cCommBuffer *b) const override;
    virtual void parsimUnpack(omnetpp::cCommBuffer *b) override;

    virtual int getSenderId() const;
    virtual void setSenderId(int senderId);

    virtual void setWeightsArraySize(size_t size);
    virtual size_t getWeightsArraySize() const;
    virtual double getWeights(size_t k) const;
    virtual void setWeights(size_t k, double weights);
    virtual void insertWeights(size_t k, double weights);
    [[deprecated]] void insertWeights(double weights) {appendWeights(weights);}
    virtual void appendWeights(double weights);
    virtual void eraseWeights(size_t k);

    virtual double getSendTime() const;
    virtual void setSendTime(double sendTime);
};

inline void doParsimPacking(omnetpp::cCommBuffer *b, const ModelUpdate& obj) {obj.parsimPack(b);}
inline void doParsimUnpacking(omnetpp::cCommBuffer *b, ModelUpdate& obj) {obj.parsimUnpack(b);}


namespace omnetpp {

template<> inline ModelUpdate *fromAnyPtr(any_ptr ptr) { return check_and_cast<ModelUpdate*>(ptr.get<cObject>()); }

}  // namespace omnetpp

#endif // ifndef __MODELUPDATE_M_H

