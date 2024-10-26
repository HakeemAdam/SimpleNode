#include "SimpleAttribute.h"

#include <OP/OP_OPeratorTable.h>
#include <OP/OP_Operator.h>

#include <GU/GU_Detail.h>
#include <OP/OP_AutoLockInputs.h>
#include <PRM/PRM_Include.h>
#include <GA/GA_Handle.h>

void newSopOperator(OP_OperatorTable *table)
{
    table->addOperator(new OP_Operator(
        "simple_attribute",
        "Simple Attribute",
        SimpleAttribute::myConstructor,
        SimpleAttribute::myTemplateList,
        1,
        1,
        0
    ));
}

static PRM_Name names[]=
{
    PRM_Name("attrname", "Attribute Name"),
	PRM_Name("attrvalue", "Attribute Value")
};

static PRM_Default defaults[]=
{
	PRM_Default(0, "custom_attr"),
	PRM_Default(1.0f)
};

PRM_Template SimpleAttribute::myTemplateList[] =
{
	PRM_Template(PRM_STRING, 1, &names[0], &defaults[0]),
    PRM_Template(PRM_FLT, 1, &names[1], &defaults[1]),
    PRM_Template()
};


OP_Node* SimpleAttribute::myConstructor(OP_Network* net,const char* name, OP_Operator* op)
{
	return new SimpleAttribute(net,name,op);
}

SimpleAttribute::SimpleAttribute(OP_Network* net, const char* name, OP_Operator* op)
	: SOP_Node(net, name, op)
{

}
SimpleAttribute::~SimpleAttribute()
{

}

OP_ERROR SimpleAttribute::cookMySop(OP_Context &context)
{

	OP_AutoLockInputs inputs(this);
    if (inputs.lock(context) >= UT_ERROR_ABORT)
		return error();

	const GU_Detail* inputGdp = inputGeo(0);

	gdp->clear();
	gdp->copy(*inputGdp);

	UT_String attrName;
	evalString(attrName, "attrname", 0, context.getTime());

	float attrValue = evalFloat("attrvalue", 0, context.getTime());

	GA_RWHandleF handle = gdp->addFloatTuple(GA_ATTRIB_POINT, attrName, 1);
	if(handle.isValid())
	{
		GA_Offset ptoff;
		GA_FOR_ALL_PTOFF(gdp, ptoff)
		{
			handle.set(ptoff, attrValue);
		}
	}


	return error();
}