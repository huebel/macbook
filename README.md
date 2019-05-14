# macbook

A set of microservices for the XENOmat on a MacBook.

## Introduction
This is a quick (i.e. one working day - see below for WorkBreakDownStructure) 
MashUp using the awesome simple SMSLib to get data from the MacBooks internal 
SMS device, and hacking on examples from d3.js, THREE.js on the browser side.

## TODO
A lot of improvement is required by the Community, some of which I mention in
random order:

*  Return the data as a JSON array,
*  reduce the precision of the floating point representation to fewer digits,
   like 3 or so, 
*	 cut the crap and go straight to binary numbers or blob's,
*  render the scene in C++ on the MacBook. Any modern MacBook should have the
   power, and consistent too when supplied with AC,
*	 but to save resource usage, go straight to CBOR. Your batteries will thank
   you (or at least start complaining much later).
   
Feel free to bring your own ideas.


## WorkBreakDownSturcture

Given was, that solid knowledge about the XENOmat API and d3.js was present,
the tasks were:

* Learning about SMSLib and how to integrate Objective-C code - 2h
* Fighting with Cevelop (Eclipse CDT) about now wanting to integrate the above - 1h
* Learning about THREE.js, experimenting in the browser - 2h
* Polishing the GUI, trimming parameters for this UseCase - 2h
* Testing with my adolescent son on his iPad, while throwing my MacBook
  around, and hearing his ideas for game development - priceless
* Adding a view service and integrating into the XENOmat Demo Application - 1h
  
All in all close to 8 hours.
