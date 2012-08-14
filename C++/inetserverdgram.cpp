# include "../headers/libinetsocket.h"
# include "../headers/socket.hpp"
# include "../headers/inetbase.hpp"
# include "../headers/inetdgram.hpp"
# include "../headers/exception.hpp"

# include <string.h>
# include <string>

# define TCP 1
# define UDP 2

# define IPv4 3
# define IPv6 4

# define BOTH 5 // what fits best (TCP/UDP or IPv4/6)
/*
The committers of the libsocket project, all rights reserved
(c) 2012, dermesser <lbo@spheniscida.de>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the
following conditions are met:

	1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following
	disclaimer.
	2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following
	disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT
NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/

/*
 * DESCRIPTION FOR INETSERVERDGRAM.CPP
 * 	inet_dgram_server provides nothing more than a constructor
 * 	which binds the UDP socket to the specified host. Everything
 * 	other, e.g. the I/O functions like rcvfrom and sndto are
 * 	inherited from inet_dgram.
 */

namespace libsocket
{
	using std::string;

/****************** DGRAM *******************/
	class inet_dgram_server : public inet_dgram
	{
		private:

		bool bound;

		public:

		inet_dgram_server(const char* host, const char* port, int proto_osi3, int flags=0);
		inet_dgram_server(const string& host, const string& port, int proto_osi3, int flags=0);
	};

	inet_dgram_server::inet_dgram_server(const char* bhost, const char* bport, int proto_osi3, int flags)
	{
		bound = false;

		if ( -1 == (sfd = create_inet_server_socket(bhost,bport,UDP,proto_osi3,flags)) )
			throw socket_exception(__FILE__,__LINE__,"inet_dgram_server::inet_dgram_server() - could not create server socket!\n");

		proto = proto_osi3;
		bound = true;

		host = string(bhost);
		port = string(bport);

	}

	inet_dgram_server::inet_dgram_server(const string& bhost, const string& bport, int proto_osi3, int flags)
	{
		bound = false;

		if ( -1 == (sfd = create_inet_server_socket(bhost.c_str(),bport.c_str(),UDP,proto_osi3,flags)) )
			throw socket_exception(__FILE__,__LINE__,"inet_dgram_server::inet_dgram_server() - could not create server socket!\n");

		proto = proto_osi3;
		bound = true;

		host = string(bhost);
		port = string(bport);
	}
}
