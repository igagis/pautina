/*
MIT License

Copyright (c) 2023 Ivan Gagis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

/* ================ LICENSE END ================ */

#pragma once

#include <setka/tcp_socket.hpp>
#include <utki/span.hpp>

namespace pautina {

class connection
{
	friend class connection_thread;

	setka::tcp_socket socket;

public:
	connection(setka::tcp_socket&& socket);

	enum class state {
		receiving,
		sending
	};

private:
	state current_state = state::receiving;

	// stuff used in 'sending' state
	std::vector<uint8_t> data_to_send;
	size_t num_bytes_sent;

public:
	state state() const noexcept
	{
		return this->current_state;
	}

	void handle_received_data(utki::span<const uint8_t> data);

	void handle_all_data_sent();
};

} // namespace pautina
