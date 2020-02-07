/*
 * sms_service.cpp
 *
 *  Created on: 12.05.2019
 *      Author: Peter Hübel
 */

//#define NDEBUG // always suppress traces
#include <xeno/trace.h>
#include <xeno/document.h>
#include <xeno/xeno_io.h>

#include "sms_service.hpp"

#include <cmath>
#include <boost/bind.hpp>

// Structure for specifying a calibration.
struct sms_calibration {
	float zeros[3];	// Zero points for three axes (X, Y, Z)
	float onegs[3];	// One gravity values for three axes
	sms_calibration() {}
	IO_CLASS(sms_calibration);
};

IO_CLASS_IMPL(sms_calibration)
{
	IO_ARRAY(zeros);
	IO_ARRAY(onegs);
}

extern "C" {

// Returns time in microseconds, clipped to a long
long getUTime() {
	struct timeval t;
	gettimeofday(&t, 0);
	return (t.tv_sec * 1000000 + t.tv_usec);
}

// Returns time in milliseconds, clipped to a long
long getMTime() {
	struct timeval t;
	gettimeofday(&t, 0);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

// Starts the accelerometer.
int smsStartup(void*, void*);

// Loads the calibration
int smsLoadCalibration(void);

// Shuts down the accelerometer.
void smsShutdown(void);

// Fills in the accel record with calibrated acceleration data. Takes
// 1-2ms to return a value. Returns 0 if success, error number if failure.
int smsGetData(macbook::sms_acceleration *accel);

int smsGetUncalibratedData(macbook::sms_acceleration *accel);

} // extern "C"


namespace macbook {

XENO_REGISTER(macbook, sms, sms_service);

sms_service::sms_service(Context& origin)
:	Origin(origin)
,	type("@type", origin, type::XML)
,	timer(get_io_service(), boost::posix_time::seconds(0))
,	buffer(50)
{
	if (smsStartup(nullptr, nullptr)) {
		throw "Can not initialise accelerometer";
	}
	else {
		TRACE("sms_service(%p)::CTOR\n", this);

		smsLoadCalibration();

		get_io_service().post(boost::bind(&sms_service::sample, this, error_code()));
	}
}

sms_service::~sms_service()
{
	smsShutdown();
}

void sms_service::invoke(contact& visitor, sequens& route)
{
	TRACELN("sms_service::invoke");
	if (route.empty()) {
		element& samples = visitor.content().element().child("data");
		samples.attr("count", std::to_string(buffer.size()));
		samples.attr("period", std::to_string(10000)+"µs");

		const auto arr1 = buffer.array_one();
		size_t to_go = buffer.capacity();
		for (size_t c=0; c<arr1.second && to_go > 0; ++c) {
			context_writer(samples.child("sms")).apply(arr1.first[c]);
			to_go--;
		}
		const auto arr2 = buffer.array_two();
		for (size_t c=0; c<arr2.second && to_go > 0; ++c) {
			context_writer(samples.child("sms")).apply(arr2.first[c]);
			to_go--;
		}
		visitor.content_type((type.str()+";charset=utf-8").c_str()).status("200 OK");
	}
	else if (route.heading("sync")) {
		float period = 0.01; // Time between samples in seconds (all 10ms)
		int count = 100;	 // Number of samples; 0 means "go forever"
		const long uPeriod = round(period * 1000000);
		long startMTime, lastUTime, thisUTime, waitUTime;
		lastUTime = getUTime();
		startMTime = getMTime();
		sms_acceleration accel;
		element& samples = visitor.content().element().child("data");
		samples.attr("count", std::to_string(count));
		samples.attr("period", std::to_string(uPeriod)+"µs");
		// Sample loop
		while (true) {
			if (0 == smsGetUncalibratedData(&accel)) {
				// TRACE("Sample [%04d]\t", count);
				context_writer(samples.child("sms")).apply(accel);
			}
			else {
				throw "Could not get SMS sample";
			}

			if (count > 0 && --count == 0) {
				// Time to stop sampling
				break;
			}

			// Yes, there's overflow all over the place here, but it doesn't
			// matter.
			thisUTime = getUTime();
			waitUTime = lastUTime + uPeriod - thisUTime;
			if (waitUTime > 0) {
				usleep(lastUTime + uPeriod - thisUTime);
			}
			lastUTime += uPeriod;
			// Make sure we don't get too far behind
			if (lastUTime < thisUTime) {
				lastUTime = thisUTime;
			}
		}	// End sample loop
		visitor.content_type((type.str()+";charset=utf-8").c_str()).status("200 OK");
	}
}


void sms_service::sample(const error_code ec)
{
	if (!ec) {
		sms_acceleration accel;
		//if (int err = smsGetUncalibratedData(&accel)) {
		if (int err = smsGetData(&accel)) {
			TRACE_FORCE("macbook:sms could not get SMS sample, error=%d\n", err);
			return;
		}
		buffer.push_back(accel);
		// TODO 10000 us = 10ms = 100Hz
		timer.expires_at(timer.expires_at() + boost::posix_time::microseconds(10000));
		timer.async_wait(boost::bind(&sms_service::sample, this, boost::asio::placeholders::error));
	}
}

void sms_service::write_raw_asio()
{
	// Construct a buffer sequence with either 1 or 2 data chunks
	std::vector<boost::asio::const_buffer> buffer_sequence;

	auto arr1 = buffer.array_one();
	buffer_sequence.push_back(boost::asio::buffer(arr1.first, arr1.second));

	auto arr2 = buffer.array_two();
	if (arr2.second != 0) {
		buffer_sequence.push_back(boost::asio::buffer(arr2.first, arr2.second));
	}

//	boost::asio::tcp::socket socket_;
//	boost::asio::write(socket_, buffer_sequence);
}

// Making the magic happen with a few macros from <xeno/xeno_io.h>
IO_CLASS_IMPL(sms_acceleration)
:	IO_ATTR(x)
,	IO_ATTR(y)
,	IO_ATTR(z)
{}

} // namespace macbook
