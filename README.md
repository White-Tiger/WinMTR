WinMTR (Redux)
==============
**WinMTR (Redux)** in an extended fork of [Appnor's WinMTR](http://winmtr.net/) ([sourceforge](http://sourceforge.net/projects/winmtr/)) <br>
with IPv6 support and other different enhancements and bug fixes

### Download (binaries)
* [**view all available**](https://github.com/White-Tiger/WinMTR/releases)

#### Differences to [WinMTR](http://winmtr.net/) 0.98
- `[x]` - removed Windows 2000 support <br>
- `[x]` + added IPv6 support <br>
- `[x]` + clickable entries when stopped.. *(why the heck wasn't it possible before?)* <br>
- `[x]` * added start delay of about 30ms for each hop *(870ms before the 30th hop gets queried) <br>
this should improve performance and reduces network load* <br>
- `[x]` ! fixed trace list freeze *(list didn't update while tracing, happens when tracing just one hop)* <br>
- `[x]` * theme support *(more fancy look :P)* <br>
- ~~`[ ]` + remembers window size~~ <br>
- `[ ]` ! CTRL+A works for host input <br>
- `[ ]` + host history: pressing del key or right mouse will remove selected entry <br>
- `[ ]` * new icon <br>

### Requirements
* Windows XP+ *(Windows 2000 support can be added on request, but IPv6 will not work)*
* Microsoft Visual C++ 2010 Redistributables
([32bit](http://microsoft.com/en-us/download/details.aspx?id=5555) |
[64bit](http://microsoft.com/en-us/download/details.aspx?id=14632)) or use static build

### About me / why I decided to create this fork
There isn't that much to say actually, I've been using IPv6 for a few years now thanks to [**SixXS**](http://sixxs.net/)
and it always annoyed me that WinMTR couldn't handle IPv6... finally my ISP got some sort of IPv6 beta test.
And that's what I wanted to compare: native vs SixXS with long-term trace routes such as those WinMTR provides. <br>
Since there wasn't any WinMTR build with IPv6, I decided to do it myself ;) The result can be seen here :P <br>
*(after 1 day for IPv6, and 2 additional days to fix other stuff and polishing)*

**If you're looking for an alternative** *(not meant for long-term traces)* there's [**vTrace**](http://vtrace.pl).
It's some really interesting piece of Software ;) *(with more then just trace routes)*
~~~~

##About new fork by @smilepleeeaz
I have created this fork to support the WinMTR in console mode. 
I have changed the Linker Subsystem to console and added support for commandline argument --report or -r.
When run with commandline argument --report or -r, the WInMTR will be pure console and would show no GUI.
When run without --report or -r , the normal GUI of WinMTR will be shown with a blink of console window.
All my changes are contained in the compile time directive WIN_MTR_NO_GUI, and the original WinMTR can be restored by compiling it after undefining this macro. 
The reports are printed on standard output and errors, if any are printed on standard error.
I have added support for below two command line arguments - 
1. --duration (-d)
It specifies the duration in seconds for which duration the tracing is to be done. On duration expiry, the tracing is stopped and report is printed.
2. --report (-r)
It specifies whether the error logs should be printed on standard error or not. It works with duration param.
All these changes are under the same GPLv2 license as the original.

