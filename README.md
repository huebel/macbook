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
*	cut the crap and go straight to binary buffers or even BLOB transfer,
*  render the scenes on the MacBook (in C++). The machines should have enough
   power, at least consistent when supplied by an AC adapter,
*	but to save resource usage, go straight to CBOR. Your batteries will thank
   you (or at least start complaining much later).
   
Feel free to bring your own ideas.

## More fun
With the <xeno:pipe/> service, you can use all kinds of fancy scripts.
The list on https://github.com/herrbischoff/awesome-macos-command-line
shows the near endless possiblilities.

## WorkBreakDownSturcture

Solid knowledge of the XENOmat API and DataVisualisation with d3.js was given,
so the tasks were largely:

* Learn about SMSLib and how to integrate Objective-C code - 2h
* Fight with Cevelop (Eclipse CDT) about now wanting to integrate the above - 1h
* Learn about THREE.js, experimenting in the browser - 2h
* Polish the GUI, trimming parameters for this UseCase - 2h
* Test the service with my adolescent son on his iPad, while throwing my MacBook
  around, and hearing his ideas for game development - priceless
* Adding a view service and integrating into the XENOmat Demo Application - 1h
  
All in all it took about 8 hours and made (besides the plugin) a lot of fun.
