# macbook

Microservices using the [XENOmat API](https://github.com/huebel/xenomat) on a MacBook.

## Introduction
This is a quick (i.e. one working day - see below for WorkBreakDownStructure) 
mash-up using the [awesome simple SMSLib](http://suitable.com/smslib.html) to 
get data from the MacBooks internal SMS device, and some browser side hacking 
on examples from [d3.js](https://github.com/d3/d3) and [THREE.js](https://github.com/mrdoob/three.js/).

## TODO
A lot of improvement is required by the Community, some of which I mention in
random order:

*  Return the data as a JSON array, or
*  reduce the precision of the floating point representation to fewer digits.
   I guess like 3 or so would do fine, or
*	cut the crap and switch to using binary buffers or even BLOB transfer, or
*  render the scenes on the MacBook (in C++). The machine should have enough
   power, at least consistent when supplied by an AC adapter, but
*	to save resource usage, consider [CBOR](https://cbor.io/). Your batteries will thank
   you (or at least they will start complaining much later).
   
Feel free to bring your own ideas, and consider making pull requests to this
repository.

## More fun
With the &lt;xeno:pipe/&gt; service, you can use all kinds of fancy scripts.
This [awesome curated list](https://github.com/herrbischoff/awesome-macos-command-line)
shows some of the near endless possiblilities.

## WorkBreakDownSturcture

Solid knowledge of the XENOmat API and DataVisualisation with d3.js was given,
so the tasks were largely:

* Learn about SMSLib and how to integrate Objective-C code - **2h**
* Fight with Cevelop (Eclipse CDT) about now wanting to integrate the above - **1h**
* Learn about THREE.js, experimenting in the browser - **2h**
* Polish the GUI, trimming parameters for this UseCase - **2h**
* Test the service with my adolescent son on his iPad, while throwing my MacBook
  around, and hearing his ideas for game development - ***priceless***
* Adding a view service and integrating into the XENOmat Demo Application - **1h**
  
In total it took about 8 hours and gave us (besides the App) hours of fun, new 
ideas, and some deeper insight into compilers, WebGL rendering, and Eclipse CDT.
