//*****************************************************************************
// FILE:            WinMTRLicense.cpp
//
//
//*****************************************************************************

#include "WinMTRGlobal.h"
#include "WinMTRLicense.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const char LICENCE_TEXT_1[]={
"		    GNU GENERAL PUBLIC LICENSE\r\n\
		       Version 2, June 1991\r\n\
			   \r\n\
 Copyright (C) 1989, 1991 Free Software Foundation, Inc.\r\n\
                       59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\r\n\
 Everyone is permitted to copy and distribute verbatim copies\r\n\
 of this license document, but changing it is not allowed.\r\n\
\r\n\
			    Preamble\r\n\
\r\n\
  The licenses for most software are designed to take away your\r\n\
freedom to share and change it.  By contrast, the GNU General Public\r\n\
License is intended to guarantee your freedom to share and change free\r\n\
software--to make sure the software is free for all its users.  This\r\n\
General Public License applies to most of the Free Software\r\n\
Foundation's software and to any other program whose authors commit to\r\n\
using it.  (Some other Free Software Foundation software is covered by\r\n\
the GNU Library General Public License instead.)  You can apply it to\r\n\
your programs, too.\r\n\
\r\n\
  When we speak of free software, we are referring to freedom, not\r\n\
price.  Our General Public Licenses are designed to make sure that you\r\n\
have the freedom to distribute copies of free software (and charge for\r\n\
this service if you wish), that you receive source code or can get it\r\n\
if you want it, that you can change the software or use pieces of it\r\n\
in new free programs; and that you know you can do these things.\r\n\
\r\n\
  To protect your rights, we need to make restrictions that forbid\r\n\
anyone to deny you these rights or to ask you to surrender the rights.\r\n\
These restrictions translate to certain responsibilities for you if you\r\n\
distribute copies of the software, or if you modify it.\r\n\
\r\n\
  For example, if you distribute copies of such a program, whether\r\n\
gratis or for a fee, you must give the recipients all the rights that\r\n\
you have.  You must make sure that they, too, receive or can get the\r\n\
source code.  And you must show them these terms so they know their\r\n\
rights.\r\n\
\r\n\
  We protect your rights with two steps: (1) copyright the software, and\r\n\
(2) offer you this license which gives you legal permission to copy,\r\n\
distribute and/or modify the software.\r\n\
\r\n\
  Also, for each author's protection and ours, we want to make certain\r\n\
that everyone understands that there is no warranty for this free\r\n\
software.  If the software is modified by someone else and passed on, we\r\n\
want its recipients to know that what they have is not the original, so\r\n\
that any problems introduced by others will not reflect on the original\r\n\
authors' reputations.\r\n\
\r\n\
  Finally, any free program is threatened constantly by software\r\n\
patents.  We wish to avoid the danger that redistributors of a free\r\n\
program will individually obtain patent licenses, in effect making the\r\n\
program proprietary.  To prevent this, we have made it clear that any\r\n\
patent must be licensed for everyone's free use or not licensed at all.\r\n\
\r\n\
  The precise terms and conditions for copying, distribution and\r\n\
modification follow.\r\n\
\r\n\
		    GNU GENERAL PUBLIC LICENSE\r\n\
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION\r\n\
\r\n\
  0. This License applies to any program or other work which contains\r\n\
a notice placed by the copyright holder saying it may be distributed\r\n\
under the terms of this General Public License.  The \"Program\", below,\r\n\
refers to any such program or work, and a \"work based on the Program\"\r\n\
means either the Program or any derivative work under copyright law:\r\n\
that is to say, a work containing the Program or a portion of it,\r\n\
either verbatim or with modifications and/or translated into another\r\n\
language.  (Hereinafter, translation is included without limitation in\r\n\
the term \"modification\".)  Each licensee is addressed as \"you\".\r\n\
\r\n\
Activities other than copying, distribution and modification are not\r\n\
covered by this License; they are outside its scope.  The act of\r\n\
running the Program is not restricted, and the output from the Program\r\n\
is covered only if its contents constitute a work based on the\r\n\
Program (independent of having been made by running the Program).\r\n\
Whether that is true depends on what the Program does.\r\n\
\r\n\
  1. You may copy and distribute verbatim copies of the Program's\r\n\
source code as you receive it, in any medium, provided that you\r\n\
conspicuously and appropriately publish on each copy an appropriate\r\n\
copyright notice and disclaimer of warranty; keep intact all the\r\n\
notices that refer to this License and to the absence of any warranty;\r\n\
and give any other recipients of the Program a copy of this License\r\n\
along with the Program.\r\n\
\r\n\
You may charge a fee for the physical act of transferring a copy, and\r\n\
you may at your option offer warranty protection in exchange for a fee.\r\n\
\r\n\
  2. You may modify your copy or copies of the Program or any portion\r\n\
of it, thus forming a work based on the Program, and copy and\r\n\
distribute such modifications or work under the terms of Section 1\r\n\
above, provided that you also meet all of these conditions:\r\n\
\r\n\
    a) You must cause the modified files to carry prominent notices\r\n\
    stating that you changed the files and the date of any change.\r\n\
\r\n\
    b) You must cause any work that you distribute or publish, that in\r\n\
    whole or in part contains or is derived from the Program or any\r\n\
    part thereof, to be licensed as a whole at no charge to all third\r\n\
    parties under the terms of this License.\r\n\
\r\n\
    c) If the modified program normally reads commands interactively\r\n\
    when run, you must cause it, when started running for such\r\n\
    interactive use in the most ordinary way, to print or display an\r\n\
    announcement including an appropriate copyright notice and a\r\n\
    notice that there is no warranty (or else, saying that you provide\r\n\
    a warranty) and that users may redistribute the program under\r\n\
    these conditions, and telling the user how to view a copy of this\r\n\
    License.  (Exception: if the Program itself is interactive but\r\n\
    does not normally print such an announcement, your work based on\r\n\
    the Program is not required to print an announcement.)\r\n\
\r\n\
These requirements apply to the modified work as a whole.  If\r\n\
identifiable sections of that work are not derived from the Program,\r\n\
and can be reasonably considered independent and separate works in\r\n\
themselves, then this License, and its terms, do not apply to those\r\n\
sections when you distribute them as separate works.  But when you\r\n\
distribute the same sections as part of a whole which is a work based\r\n\
on the Program, the distribution of the whole must be on the terms of\r\n\
this License, whose permissions for other licensees extend to the\r\n\
entire whole, and thus to each and every part regardless of who wrote it.\r\n\
\r\n\
Thus, it is not the intent of this section to claim rights or contest\r\n\
your rights to work written entirely by you; rather, the intent is to\r\n\
exercise the right to control the distribution of derivative or\r\n\
collective works based on the Program.\r\n\
\r\n\
In addition, mere aggregation of another work not based on the Program\r\n\
with the Program (or with a work based on the Program) on a volume of\r\n\
a storage or distribution medium does not bring the other work under\r\n\
the scope of this License.\r\n\
\r\n\
  3. You may copy and distribute the Program (or a work based on it,\r\n\
under Section 2) in object code or executable form under the terms of\r\n\
Sections 1 and 2 above provided that you also do one of the following:\r\n\
\r\n\
    a) Accompany it with the complete corresponding machine-readable\r\n\
    source code, which must be distributed under the terms of Sections\r\n\
    1 and 2 above on a medium customarily used for software interchange; or,\r\n\
\r\n\
    b) Accompany it with a written offer, valid for at least three\r\n\
    years, to give any third party, for a charge no more than your\r\n\
    cost of physically performing source distribution, a complete\r\n\
    machine-readable copy of the corresponding source code, to be\r\n\
    distributed under the terms of Sections 1 and 2 above on a medium\r\n\
    customarily used for software interchange; or,\r\n\
\r\n\
    c) Accompany it with the information you received as to the offer\r\n\
    to distribute corresponding source code.  (This alternative is\r\n\
    allowed only for noncommercial distribution and only if you\r\n\
    received the program in object code or executable form with such\r\n\
    an offer, in accord with Subsection b above.)\r\n\
\r\n\
The source code for a work means the preferred form of the work for\r\n\
making modifications to it.  For an executable work, complete source\r\n\
code means all the source code for all modules it contains, plus any\r\n\
associated interface definition files, plus the scripts used to\r\n\
control compilation and installation of the executable.  However, as a\r\n\
special exception, the source code distributed need not include\r\n\
anything that is normally distributed (in either source or binary\r\n\
form) with the major components (compiler, kernel, and so on) of the\r\n\
operating system on which the executable runs, unless that component\r\n\
itself accompanies the executable.\r\n\
\r\n\
If distribution of executable or object code is made by offering\r\n\
access to copy from a designated place, then offering equivalent\r\n\
access to copy the source code from the same place counts as\r\n\
distribution of the source code, even though third parties are not\r\n\
compelled to copy the source along with the object code.\r\n\
\r\n\
  4. You may not copy, modify, sublicense, or distribute the Program\r\n\
except as expressly provided under this License.  Any attempt\r\n\
otherwise to copy, modify, sublicense or distribute the Program is\r\n\
void, and will automatically terminate your rights under this License.\r\n\
However, parties who have received copies, or rights, from you under\r\n\
this License will not have their licenses terminated so long as such\r\n\
parties remain in full compliance.\r\n\
\r\n\
  5. You are not required to accept this License, since you have not\r\n\
signed it.  However, nothing else grants you permission to modify or\r\n\
distribute the Program or its derivative works.  These actions are\r\n\
prohibited by law if you do not accept this License.  Therefore, by\r\n\
modifying or distributing the Program (or any work based on the\r\n\
Program), you indicate your acceptance of this License to do so, and\r\n\
all its terms and conditions for copying, distributing or modifying\r\n\
the Program or works based on it.\r\n\
\r\n\
  6. Each time you redistribute the Program (or any work based on the\r\n\
Program), the recipient automatically receives a license from the\r\n\
original licensor to copy, distribute or modify the Program subject to\r\n\
these terms and conditions.  You may not impose any further\r\n\
restrictions on the recipients' exercise of the rights granted herein.\r\n\
You are not responsible for enforcing compliance by third parties to\r\n\
this License.\r\n\
\r\n\
  7. If, as a consequence of a court judgment or allegation of patent\r\n\
infringement or for any other reason (not limited to patent issues),\r\n\
conditions are imposed on you (whether by court order, agreement or\r\n\
otherwise) that contradict the conditions of this License, they do not\r\n\
excuse you from the conditions of this License.  If you cannot\r\n\
distribute so as to satisfy simultaneously your obligations under this\r\n\
License and any other pertinent obligations, then as a consequence you\r\n\
may not distribute the Program at all.  For example, if a patent\r\n\
license would not permit royalty-free redistribution of the Program by\r\n\
all those who receive copies directly or indirectly through you, then\r\n\
the only way you could satisfy both it and this License would be to\r\n\
refrain entirely from distribution of the Program.\r\n\
\r\n\
If any portion of this section is held invalid or unenforceable under\r\n\
any particular circumstance, the balance of the section is intended to\r\n\
apply and the section as a whole is intended to apply in other\r\n\
circumstances.\r\n\
\r\n\
It is not the purpose of this section to induce you to infringe any\r\n\
patents or other property right claims or to contest validity of any\r\n\
such claims; this section has the sole purpose of protecting the\r\n\
integrity of the free software distribution system, which is\r\n\
implemented by public license practices.  Many people have made\r\n\
generous contributions to the wide range of software distributed\r\n\
through that system in reliance on consistent application of that\r\n\
system; it is up to the author/donor to decide if he or she is willing\r\n\
to distribute software through any other system and a licensee cannot\r\n\
impose that choice.\r\n\
\r\n\
This section is intended to make thoroughly clear what is believed to\r\n\
be a consequence of the rest of this License.\r\n\
\r\n\
  8. If the distribution and/or use of the Program is restricted in\r\n\
certain countries either by patents or by copyrighted interfaces, the\r\n\
original copyright holder who places the Program under this License\r\n\
may add an explicit geographical distribution limitation excluding\r\n\
those countries, so that distribution is permitted only in or among\r\n\
countries not thus excluded.  In such case, this License incorporates\r\n\
the limitation as if written in the body of this License.\r\n\
\r\n\
  9. The Free Software Foundation may publish revised and/or new versions\r\n\
of the General Public License from time to time.  Such new versions will\r\n\
be similar in spirit to the present version, but may differ in detail to\r\n\
address new problems or concerns.\r\n\
\r\n\
Each version is given a distinguishing version number.  If the Program\r\n\
specifies a version number of this License which applies to it and \"any\r\n\
later version\", you have the option of following the terms and conditions\r\n\
either of that version or of any later version published by the Free\r\n\
Software Foundation.  If the Program does not specify a version number of\r\n\
this License, you may choose any version ever published by the Free Software\r\n\
Foundation.\r\n\
\r\n\
  10. If you wish to incorporate parts of the Program into other free\r\n\
programs whose distribution conditions are different, write to the author\r\n\
to ask for permission.  For software which is copyrighted by the Free\r\n\
Software Foundation, write to the Free Software Foundation; we sometimes\r\n\
make exceptions for this.  Our decision will be guided by the two goals\r\n\
of preserving the free status of all derivatives of our free software and\r\n\
of promoting the sharing and reuse of software generally.\r\n\
\r\n\
			    NO WARRANTY\r\n\
\r\n\
  11. BECAUSE THE PROGRAM IS LICENSED FREE OF CHARGE, THERE IS NO WARRANTY\r\n\
FOR THE PROGRAM, TO THE EXTENT PERMITTED BY APPLICABLE LAW.  EXCEPT WHEN\r\n\
OTHERWISE STATED IN WRITING THE COPYRIGHT HOLDERS AND/OR OTHER PARTIES\r\n\
PROVIDE THE PROGRAM \"AS IS\" WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESSED\r\n\
OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF\r\n\
MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE ENTIRE RISK AS\r\n\
TO THE QUALITY AND PERFORMANCE OF THE PROGRAM IS WITH YOU.  SHOULD THE\r\n\
PROGRAM PROVE DEFECTIVE, YOU ASSUME THE COST OF ALL NECESSARY SERVICING,\r\n\
REPAIR OR CORRECTION.\r\n\
\r\n\
  12. IN NO EVENT UNLESS REQUIRED BY APPLICABLE LAW OR AGREED TO IN WRITING\r\n\
WILL ANY COPYRIGHT HOLDER, OR ANY OTHER PARTY WHO MAY MODIFY AND/OR\r\n\
REDISTRIBUTE THE PROGRAM AS PERMITTED ABOVE, BE LIABLE TO YOU FOR DAMAGES,\r\n\
INCLUDING ANY GENERAL, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES ARISING\r\n\
OUT OF THE USE OR INABILITY TO USE THE PROGRAM (INCLUDING BUT NOT LIMITED\r\n\
TO LOSS OF DATA OR DATA BEING RENDERED INACCURATE OR LOSSES SUSTAINED BY\r\n\
YOU OR THIRD PARTIES OR A FAILURE OF THE PROGRAM TO OPERATE WITH ANY OTHER\r\n\
PROGRAMS), EVEN IF SUCH HOLDER OR OTHER PARTY HAS BEEN ADVISED OF THE\r\n\
POSSIBILITY OF SUCH DAMAGES.\r\n\
\r\n\
		     END OF TERMS AND CONDITIONS\r\n"};
static const char LICENCE_TEXT_2[]={
"\r\n\
	    How to Apply These Terms to Your New Programs\r\n\
\r\n\
  If you develop a new program, and you want it to be of the greatest\r\n\
possible use to the public, the best way to achieve this is to make it\r\n\
free software which everyone can redistribute and change under these terms.\r\n\
\r\n\
  To do so, attach the following notices to the program.  It is safest\r\n\
to attach them to the start of each source file to most effectively\r\n\
convey the exclusion of warranty; and each file should have at least\r\n\
the \"copyright\" line and a pointer to where the full notice is found.\r\n\
\r\n\
    <one line to give the program's name and a brief idea of what it does.>\r\n\
    Copyright (C) 19yy  <name of author>\r\n\
\r\n\
    This program is free software; you can redistribute it and/or modify\r\n\
    it under the terms of the GNU General Public License as published by\r\n\
    the Free Software Foundation; either version 2 of the License, or\r\n\
    (at your option) any later version.\r\n\
\r\n\
    This program is distributed in the hope that it will be useful,\r\n\
    but WITHOUT ANY WARRANTY; without even the implied warranty of\r\n\
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\r\n\
    GNU General Public License for more details.\r\n\
\r\n\
    You should have received a copy of the GNU General Public License\r\n\
    along with this program; if not, write to the Free Software\r\n\
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA\r\n\
\r\n\
\r\n\
Also add information on how to contact you by electronic and paper mail.\r\n\
\r\n\
If the program is interactive, make it output a short notice like this\r\n\
when it starts in an interactive mode:\r\n\
\r\n\
    Gnomovision version 69, Copyright (C) 19yy name of author\r\n\
    Gnomovision comes with ABSOLUTELY NO WARRANTY; for details type `show w'.\r\n\
    This is free software, and you are welcome to redistribute it\r\n\
    under certain conditions; type `show c' for details.\r\n\
\r\n\
The hypothetical commands `show w' and `show c' should show the appropriate\r\n\
parts of the General Public License.  Of course, the commands you use may\r\n\
be called something other than `show w' and `show c'; they could even be\r\n\
mouse-clicks or menu items--whatever suits your program.\r\n\
\r\n\
You should also get your employer (if you work as a programmer) or your\r\n\
school, if any, to sign a \"copyright disclaimer\" for the program, if\r\n\
necessary.  Here is a sample; alter the names:\r\n\
\r\n\
  Yoyodyne, Inc., hereby disclaims all copyright interest in the program\r\n\
  `Gnomovision' (which makes passes at compilers) written by James Hacker.\r\n\
\r\n\
  <signature of Ty Coon>, 1 April 1989\r\n\
  Ty Coon, President of Vice\r\n\
\r\n\
This General Public License does not permit incorporating your program into\r\n\
proprietary programs.  If your program is a subroutine library, you may\r\n\
consider it more useful to permit linking proprietary applications with the\r\n\
library.  If this is what you want to do, use the GNU Library General\r\n\
Public License instead of this License."};

//*****************************************************************************
// BEGIN_MESSAGE_MAP
//
// 
//*****************************************************************************
BEGIN_MESSAGE_MAP(WinMTRLicense, CDialog)
END_MESSAGE_MAP()


//*****************************************************************************
// WinMTRLicense::WinMTRLicense
//
// 
//*****************************************************************************
WinMTRLicense::WinMTRLicense(CWnd* pParent) : CDialog(WinMTRLicense::IDD, pParent)
{
}


//*****************************************************************************
// WinMTRLicense::DoDataExchange
//
// 
//*****************************************************************************
void WinMTRLicense::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


//*****************************************************************************
// WinMTRLicense::OnInitDialog
//
// 
//*****************************************************************************
BOOL WinMTRLicense::OnInitDialog() 
{
	CDialog::OnInitDialog();
	/*
	m_editLicense.SetSel(-1, -1);
	m_editLicense.ReplaceSel(LICENCE_TEXT_1);
	m_editLicense.SetSel(-1, -1);
	m_editLicense.ReplaceSel(LICENCE_TEXT_2);
	*/
	return FALSE;
}

