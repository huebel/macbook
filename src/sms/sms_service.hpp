/*
 * sms_service.hpp
 *
 *  Created on: 12.05.2019
 *      Author: Peter Hübel
 */

#ifndef SMS_SERVICE_HPP_
#define SMS_SERVICE_HPP_

#include <xeno/service.h>
#include <boost/circular_buffer.hpp>

namespace macbook {

using namespace xeno;
using boost::asio::deadline_timer;
using boost::system::error_code;
using boost::circular_buffer;

struct sms_acceleration {

	float x;		// Right-left acceleration (positive is rightwards)
	float y;		// Front-rear acceleration (positive is towards back)
	float z;		// Up-down acceleration (positive is upwards)

	sms_acceleration()
	:	x(0)
	,	y(0)
	,	z(0)
	{}

	IO_CLASS(sms_acceleration);
};

class sms_service : public xeno::service<sms_service, const xeno::element> {
public:

	// The service has a complete context for initialisation,
	// the origin is 'const' so this service can *not* do any
	// selfattribution.
	sms_service(Context& origin);

	// The destructor releases the accelerometer again.
	~sms_service();

	// The service is invoked via this call. See the implementation
	// for an understanding of the "visitor" and its "route".
	void invoke(xeno::contact& visitor, xeno::sequens& route);

	// The generator function 'create' has a default implementation,
	// which invokes a constructor taking a context as argument.
	// Overwrite this function, if you need to access the context
	// before instantiation.

//	static xeno::action* create(xeno::context& origin)
//	{
//		return new sms_service(origin);
//	}

	void sample(const error_code ec);

	void write_raw_asio();

private:
	attribute type;
	deadline_timer timer;
	circular_buffer<sms_acceleration> buffer;
};

} // namespace macbook

#endif /* SMS_SERVICE_HPP_ */
