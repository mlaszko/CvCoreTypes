/*!
 * \file
 * \brief 
 * \author Michal Laszkowski
 */

#ifndef HOMOGMATRIXMULTIPLICATION_HPP_
#define HOMOGMATRIXMULTIPLICATION_HPP_

#include "Component_Aux.hpp"
#include "Component.hpp"
#include "DataStream.hpp"
#include "Property.hpp"
#include "EventHandler2.hpp"

#include "Types/HomogMatrix.hpp"


namespace Processors {
namespace HomogMatrixMultiplication {

/*!
 * \class HomogMatrixMultiplication
 * \brief HomogMatrixMultiplication processor class.
 *
 * 
 */
class HomogMatrixMultiplication: public Base::Component {
public:
	/*!
	 * Constructor.
	 */
	HomogMatrixMultiplication(const std::string & name = "HomogMatrixMultiplication");

	/*!
	 * Destructor
	 */
	virtual ~HomogMatrixMultiplication();

	/*!
	 * Prepare components interface (register streams and handlers).
	 * At this point, all properties are already initialized and loaded to 
	 * values set in config file.
	 */
	void prepareInterface();

protected:

	/*!
	 * Connects source to given device.
	 */
	bool onInit();

	/*!
	 * Disconnect source from device, closes streams, etc.
	 */
	bool onFinish();

	/*!
	 * Start component
	 */
	bool onStart();

	/*!
	 * Stop component
	 */
	bool onStop();


	// Input data streams
	Base::DataStreamIn<Types::HomogMatrix> in_hm1;
	Base::DataStreamIn<Types::HomogMatrix> in_hm2;
    Base::DataStreamIn<vector<Types::HomogMatrix> > in_hms1;
    Base::DataStreamIn<vector<Types::HomogMatrix> > in_hms2;

	// Output data streams
	Base::DataStreamOut<Types::HomogMatrix> out_hm;
    Base::DataStreamOut<vector<Types::HomogMatrix> > out_hms;

	// Handlers

	// Properties
    /// Property: inverse matrix 1.
    Base::Property<bool> prop_inverse_hm1;
	
    /// Property: inverse matrix 2.
    Base::Property<bool> prop_inverse_hm2;

	// Handlers
	void multiplication();
    void vectors_multiplication();

};

} //: namespace HomogMatrixMultiplication
} //: namespace Processors

/*
 * Register processor component.
 */
REGISTER_COMPONENT("HomogMatrixMultiplication", Processors::HomogMatrixMultiplication::HomogMatrixMultiplication)

#endif /* HOMOGMATRIXMULTIPLICATION_HPP_ */
