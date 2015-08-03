/*!
 * \file
 * \brief
 * \author Michal Laszkowski
 */

#include <memory>
#include <string>

#include "HomogMatrixMultiplication.hpp"
#include "Common/Logger.hpp"

#include <boost/bind.hpp>

namespace Processors {
namespace HomogMatrixMultiplication {

HomogMatrixMultiplication::HomogMatrixMultiplication(const std::string & name) :
        Base::Component(name),
        prop_inverse_hm1("inverse_hm1", false),
        prop_inverse_hm2("inverse_hm2", false){
            registerProperty(prop_inverse_hm1);
            registerProperty(prop_inverse_hm2);
}

HomogMatrixMultiplication::~HomogMatrixMultiplication() {
}

void HomogMatrixMultiplication::prepareInterface() {
	// Register data streams, events and event handlers HERE!
	registerStream("in_hm1", &in_hm1);
	registerStream("in_hm2", &in_hm2);
    registerStream("in_hms1", &in_hms1);
    registerStream("in_hms2", &in_hms2);
	registerStream("out_hm", &out_hm);
    registerStream("out_hms", &out_hms);
	// Register handlers
	registerHandler("multiplication", boost::bind(&HomogMatrixMultiplication::multiplication, this));
    addDependency("multiplication", &in_hm1);
	addDependency("multiplication", &in_hm2);

    registerHandler("vectors_multiplication", boost::bind(&HomogMatrixMultiplication::vectors_multiplication, this));
    addDependency("vectors_multiplication", &in_hms1);
    addDependency("vectors_multiplication", &in_hms2);

}

bool HomogMatrixMultiplication::onInit() {

	return true;
}

bool HomogMatrixMultiplication::onFinish() {
	return true;
}

bool HomogMatrixMultiplication::onStop() {
	return true;
}

bool HomogMatrixMultiplication::onStart() {
	return true;
}

void HomogMatrixMultiplication::multiplication() {
    CLOG(LTRACE) << "multiplication";
    Types::HomogMatrix hm1 = in_hm1.read();
    Types::HomogMatrix hm2 = in_hm2.read();
    Types::HomogMatrix hm;

    if(prop_inverse_hm1){
        CLOG(LTRACE) << "inverse hm1";
        Types::HomogMatrix hmi(hm1.inverse());
        hm1 = hmi;
    }
    if(prop_inverse_hm2){
        CLOG(LTRACE) << "inverse hm2";
        Types::HomogMatrix hmi(hm2.inverse());
        hm2 = hmi;
    }

    hm.matrix() = hm1.matrix() * hm2.matrix();
    CLOG(LDEBUG) << "Output matrix:\n" << hm;
    out_hm.write(hm);
}

void HomogMatrixMultiplication::vectors_multiplication() {
    CLOG(LTRACE) << "vectors_multiplication";
    vector<Types::HomogMatrix> hms1 = in_hms1.read();
    vector<Types::HomogMatrix> hms2 = in_hms2.read();
    vector<Types::HomogMatrix> hms;

    if(hms1.size() != hms2.size()){
        CLOG(LERROR) << "Wrong vector size";
    }

    for(int i = 0; i < hms1.size(); ++i){
        Types::HomogMatrix hm;
        hm.matrix() = hms1[i].matrix() * hms2[i].matrix();
        hms.push_back(hm);
    }
    out_hms.write(hms);
}

} //: namespace HomogMatrixMultiplication
} //: namespace Processors
