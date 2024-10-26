#ifndef __SIMPLE_ATTRIBUTE_H__
#define __SIMPLE_ATTRIBUTE_H__

#include "SOP/SOP_Node.h"

class SimpleAttribute : public SOP_Node 
{
public:
    static OP_Node* myConstructor(OP_Network*, const char*, OP_Operator*);
    static PRM_Template myTemplateList[];

protected:
    SimpleAttribute(OP_Network* net, const char* name, OP_Operator* op);
    virtual ~SimpleAttribute();
    
    virtual OP_ERROR cookMySop(OP_Context& context);
};

#endif