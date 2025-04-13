//
// Generated file, do not edit! Created by opp_msgtool 6.1 from ModelUpdate.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "ModelUpdate_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(ModelUpdate)

ModelUpdate::ModelUpdate(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

ModelUpdate::ModelUpdate(const ModelUpdate& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

ModelUpdate::~ModelUpdate()
{
    delete [] this->weights;
}

ModelUpdate& ModelUpdate::operator=(const ModelUpdate& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ModelUpdate::copy(const ModelUpdate& other)
{
    this->senderId = other.senderId;
    delete [] this->weights;
    this->weights = (other.weights_arraysize==0) ? nullptr : new double[other.weights_arraysize];
    weights_arraysize = other.weights_arraysize;
    for (size_t i = 0; i < weights_arraysize; i++) {
        this->weights[i] = other.weights[i];
    }
    this->sendTime = other.sendTime;
}

void ModelUpdate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->senderId);
    b->pack(weights_arraysize);
    doParsimArrayPacking(b,this->weights,weights_arraysize);
    doParsimPacking(b,this->sendTime);
}

void ModelUpdate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->senderId);
    delete [] this->weights;
    b->unpack(weights_arraysize);
    if (weights_arraysize == 0) {
        this->weights = nullptr;
    } else {
        this->weights = new double[weights_arraysize];
        doParsimArrayUnpacking(b,this->weights,weights_arraysize);
    }
    doParsimUnpacking(b,this->sendTime);
}

int ModelUpdate::getSenderId() const
{
    return this->senderId;
}

void ModelUpdate::setSenderId(int senderId)
{
    this->senderId = senderId;
}

size_t ModelUpdate::getWeightsArraySize() const
{
    return weights_arraysize;
}

double ModelUpdate::getWeights(size_t k) const
{
    if (k >= weights_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)weights_arraysize, (unsigned long)k);
    return this->weights[k];
}

void ModelUpdate::setWeightsArraySize(size_t newSize)
{
    double *weights2 = (newSize==0) ? nullptr : new double[newSize];
    size_t minSize = weights_arraysize < newSize ? weights_arraysize : newSize;
    for (size_t i = 0; i < minSize; i++)
        weights2[i] = this->weights[i];
    for (size_t i = minSize; i < newSize; i++)
        weights2[i] = 0;
    delete [] this->weights;
    this->weights = weights2;
    weights_arraysize = newSize;
}

void ModelUpdate::setWeights(size_t k, double weights)
{
    if (k >= weights_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)weights_arraysize, (unsigned long)k);
    this->weights[k] = weights;
}

void ModelUpdate::insertWeights(size_t k, double weights)
{
    if (k > weights_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)weights_arraysize, (unsigned long)k);
    size_t newSize = weights_arraysize + 1;
    double *weights2 = new double[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        weights2[i] = this->weights[i];
    weights2[k] = weights;
    for (i = k + 1; i < newSize; i++)
        weights2[i] = this->weights[i-1];
    delete [] this->weights;
    this->weights = weights2;
    weights_arraysize = newSize;
}

void ModelUpdate::appendWeights(double weights)
{
    insertWeights(weights_arraysize, weights);
}

void ModelUpdate::eraseWeights(size_t k)
{
    if (k >= weights_arraysize) throw omnetpp::cRuntimeError("Array of size %lu indexed by %lu", (unsigned long)weights_arraysize, (unsigned long)k);
    size_t newSize = weights_arraysize - 1;
    double *weights2 = (newSize == 0) ? nullptr : new double[newSize];
    size_t i;
    for (i = 0; i < k; i++)
        weights2[i] = this->weights[i];
    for (i = k; i < newSize; i++)
        weights2[i] = this->weights[i+1];
    delete [] this->weights;
    this->weights = weights2;
    weights_arraysize = newSize;
}

double ModelUpdate::getSendTime() const
{
    return this->sendTime;
}

void ModelUpdate::setSendTime(double sendTime)
{
    this->sendTime = sendTime;
}

class ModelUpdateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_senderId,
        FIELD_weights,
        FIELD_sendTime,
    };
  public:
    ModelUpdateDescriptor();
    virtual ~ModelUpdateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(ModelUpdateDescriptor)

ModelUpdateDescriptor::ModelUpdateDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(ModelUpdate)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

ModelUpdateDescriptor::~ModelUpdateDescriptor()
{
    delete[] propertyNames;
}

bool ModelUpdateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<ModelUpdate *>(obj)!=nullptr;
}

const char **ModelUpdateDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *ModelUpdateDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int ModelUpdateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 3+base->getFieldCount() : 3;
}

unsigned int ModelUpdateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_senderId
        FD_ISARRAY | FD_ISEDITABLE | FD_ISRESIZABLE,    // FIELD_weights
        FD_ISEDITABLE,    // FIELD_sendTime
    };
    return (field >= 0 && field < 3) ? fieldTypeFlags[field] : 0;
}

const char *ModelUpdateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "senderId",
        "weights",
        "sendTime",
    };
    return (field >= 0 && field < 3) ? fieldNames[field] : nullptr;
}

int ModelUpdateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "senderId") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "weights") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "sendTime") == 0) return baseIndex + 2;
    return base ? base->findField(fieldName) : -1;
}

const char *ModelUpdateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_senderId
        "double",    // FIELD_weights
        "double",    // FIELD_sendTime
    };
    return (field >= 0 && field < 3) ? fieldTypeStrings[field] : nullptr;
}

const char **ModelUpdateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *ModelUpdateDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int ModelUpdateDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_weights: return pp->getWeightsArraySize();
        default: return 0;
    }
}

void ModelUpdateDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_weights: pp->setWeightsArraySize(size); break;
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'ModelUpdate'", field);
    }
}

const char *ModelUpdateDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string ModelUpdateDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return long2string(pp->getSenderId());
        case FIELD_weights: return double2string(pp->getWeights(i));
        case FIELD_sendTime: return double2string(pp->getSendTime());
        default: return "";
    }
}

void ModelUpdateDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: pp->setSenderId(string2long(value)); break;
        case FIELD_weights: pp->setWeights(i,string2double(value)); break;
        case FIELD_sendTime: pp->setSendTime(string2double(value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ModelUpdate'", field);
    }
}

omnetpp::cValue ModelUpdateDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: return pp->getSenderId();
        case FIELD_weights: return pp->getWeights(i);
        case FIELD_sendTime: return pp->getSendTime();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'ModelUpdate' as cValue -- field index out of range?", field);
    }
}

void ModelUpdateDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_senderId: pp->setSenderId(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_weights: pp->setWeights(i,value.doubleValue()); break;
        case FIELD_sendTime: pp->setSendTime(value.doubleValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ModelUpdate'", field);
    }
}

const char *ModelUpdateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr ModelUpdateDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void ModelUpdateDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    ModelUpdate *pp = omnetpp::fromAnyPtr<ModelUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'ModelUpdate'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

